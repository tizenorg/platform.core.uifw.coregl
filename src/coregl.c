#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include "coregl_internal.h"

Mutex                   ctx_list_access_mutex = MUTEX_INITIALIZER;

void                   *egl_lib_handle;
void                   *gl_lib_handle;

GLContext_List         *glctx_list = NULL;

// Symbol definition for local
#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     RET_TYPE (*_COREGL_NAME_MANGLE(FUNC_NAME)) PARAM_LIST = NULL;
#include "headers/sym.h"
#undef _COREGL_SYMBOL

// Symbol definition for static
#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     RET_TYPE (*_sym_##FUNC_NAME) PARAM_LIST;
#include "headers/sym.h"
#undef _COREGL_SYMBOL

const char *
get_env_setting(const char *name)
{
	char *fp_env = NULL;
	static char *fp_default = "\0";
	fp_env = getenv(name);
	if (fp_env == NULL) fp_env = fp_default;
	return fp_env;
}

int
add_context_state_to_list(const void *option, const int option_len, GLContextState *cstate, Mutex *mtx)
{
	int ret = 0;
	int tid = 0;
	GLContext_List *current = NULL;
	GLContext_List *newitm = NULL;

	if (mtx != NULL) AST(mutex_lock(mtx) == 1);

	AST(cstate != NULL);

	tid = get_current_thread();

	current = glctx_list;
	while (current != NULL)
	{
		if (current->option_len == option_len &&
		    memcmp(current->option, option, option_len) == 0 &&
		    current->thread_id == tid)
		{
			AST(current->cstate == cstate);
			goto finish;
		}
		current = current->next;
	}

	newitm = (GLContext_List *)calloc(1, sizeof(GLContext_List));
	if (newitm == NULL)
	{
		ERR("Failed to create context list.\n");
		goto finish;
	}

	newitm->cstate = cstate;
	newitm->thread_id = tid;
	newitm->option_len = option_len;
	newitm->option = (void *)malloc(option_len);
	memcpy(newitm->option, option, option_len);

	if (glctx_list != NULL)
		newitm->next = glctx_list;

	glctx_list = newitm;

	ret = 1;
	goto finish;

finish:
	if (ret != 1)
	{
		if (newitm != NULL)
		{
			free(newitm);
			newitm = NULL;
		}
		if (cstate != NULL)
		{
			free(cstate);
			cstate = NULL;
		}
	}
	if (mtx != NULL) AST(mutex_unlock(mtx) == 1);

	return ret;
}

GLContextState *
get_context_state_from_list(const void *option, const int option_len, Mutex *mtx)
{
	GLContextState *ret = NULL;
	GLContext_List *current = NULL;
	int tid = 0;

	if (mtx != NULL) AST(mutex_lock(mtx) == 1);

	tid = get_current_thread();

	current = glctx_list;
	while (current != NULL)
	{
		if (current->option_len == option_len &&
		    memcmp(current->option, option, option_len) == 0 &&
		    current->thread_id == tid)
		{
			ret = current->cstate;
			goto finish;
		}
		current = current->next;
	}
	goto finish;

finish:
	if (mtx != NULL) AST(mutex_unlock(mtx) == 1);
	return ret;
}

int
remove_context_states_from_list(GLContextState *cstate, Mutex *mtx)
{
	int ret = 0;
	int tid = 0;
	GLContext_List *olditm = NULL;
	GLContext_List *current = NULL;

	if (mtx != NULL) AST(mutex_lock(mtx) == 1);

	AST(cstate != NULL);

	tid = get_current_thread();
	current = glctx_list;

	while (current != NULL)
	{
		if (current->cstate == cstate)
		{
			GLContext_List *nextitm = NULL;
			if (olditm != NULL)
			{
				olditm->next = current->next;
				nextitm = olditm->next;
			}
			else
			{
				glctx_list = current->next;
				nextitm = glctx_list;
			}
			free(current);
			ret = 1;
			current = nextitm;
			continue;
		}
		olditm = current;
		current = current->next;
	}
	goto finish;

finish:
	if (mtx != NULL) AST(mutex_unlock(mtx) == 1);
	return ret;
}

int
init_new_thread_state()
{
	int ret = 0;
	GLThreadState *tstate = NULL;

	tstate = get_current_thread_state();
	AST(tstate == NULL);

	tstate = (GLThreadState *)calloc(1, sizeof(GLThreadState));
	tstate->thread_id = get_current_thread();

	set_current_thread_state(&ctx_list_access_mutex, tstate);

#ifdef COREGL_TRACE_CONTEXT_INFO
	add_to_general_trace_list(&thread_trace_list, tstate);
#endif // COREGL_TRACE_CONTEXT_INFO
	ret = 1;
	goto finish;

finish:
	return ret;
}

static void
_sym_missing()
{
	ERR("GL symbol missing!\n");
}

static int
_glue_sym_init(void)
{

#define FINDSYM(libhandle, getproc, dst, sym) \
   if ((!dst) && (getproc)) dst = (__typeof__(dst))getproc(sym); \
   if (!dst) dst = (__typeof__(dst))dlsym(libhandle, sym);

#define FALLBAK(dst) \
   if (!dst) { dst = (__typeof__(dst))_sym_missing; ERR("WARNING : symbol '"#dst"' missing!\n"); }


#ifndef _COREGL_DESKTOP_GL
# define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST) \
     FINDSYM(egl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME); \
     if (IS_EXTENSION == GL_TRUE) { \
        FINDSYM(egl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"EXT"); \
        FINDSYM(egl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"ARB"); \
        FINDSYM(egl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"OES"); \
        FINDSYM(egl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"KHR"); \
     } else { FALLBAK(_sym_##FUNC_NAME); }
# include "headers/sym_egl.h"
# undef _COREGL_SYMBOL
#else
# define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST) \
     FINDSYM(glue_lib_handle, _sym_glXGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME); \
     if (IS_EXTENSION == GL_TRUE) { \
        FINDSYM(gl_lib_handle, _sym_glXGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"EXT"); \
        FINDSYM(gl_lib_handle, _sym_glXGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"ARB"); \
        FINDSYM(gl_lib_handle, _sym_glXGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"OES"); \
        FINDSYM(gl_lib_handle, _sym_glXGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"MESA"); \
        FINDSYM(gl_lib_handle, _sym_glXGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"SGI"); \
     } else { FALLBAK(_sym_##FUNC_NAME); }
# include "headers/sym_glx.h"
# undef _COREGL_SYMBOL
#endif

#undef FINDSYM
#undef FALLBAK

	return 1;
}

static int
_gl_sym_init(void)
{

#define FINDSYM(libhandle, getproc, dst, sym) \
   if ((!dst) && (getproc)) dst = (__typeof__(dst))getproc(sym); \
   if (!dst) dst = (__typeof__(dst))dlsym(gl_lib_handle, sym);
#define FALLBAK(dst) \
   if (!dst) { dst = (__typeof__(dst))_sym_missing; ERR("WARNING : symbol '"#dst"' missing!\n"); }

#ifndef _COREGL_DESKTOP_GL
# define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST) \
     FINDSYM(gl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME); \
     if (IS_EXTENSION == GL_TRUE) { \
        FINDSYM(gl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"EXT"); \
        FINDSYM(gl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"ARB"); \
        FINDSYM(gl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"OES"); \
        FINDSYM(gl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"KHR"); \
      } else { FALLBAK(_sym_##FUNC_NAME); }
# include "headers/sym_gl.h"
# undef _COREGL_SYMBOL
#else
# define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST) \
     if (IS_EXTENSION == GL_TRUE) { \
        FINDSYM(gl_lib_handle, _sym_glXGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME); \
        FINDSYM(gl_lib_handle, _sym_glXGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"EXT"); \
        FINDSYM(gl_lib_handle, _sym_glXGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"ARB"); \
        FINDSYM(gl_lib_handle, _sym_glXGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"OES"); \
     } else { FALLBAK(_sym_##FUNC_NAME); }
# include "headers/sym_gl.h"
# undef _COREGL_SYMBOL
#endif

#undef FINDSYM
#undef FALLBAK

	return 1;
}

static int
_gl_lib_init(void)
{

#ifndef _COREGL_DESKTOP_GL
	//------------------------------------------------//
	// Open EGL Library as EGL is separate
#ifndef _COREGL_EMBED_EVAS
	egl_lib_handle = dlopen("libEGL_drv.so", RTLD_NOW | RTLD_GLOBAL);
#else
	egl_lib_handle = dlopen("libEGL.so.1", RTLD_NOW | RTLD_GLOBAL);
	if (!egl_lib_handle)
		egl_lib_handle = dlopen("libEGL.so", RTLD_NOW | RTLD_GLOBAL);
#endif
	if (!egl_lib_handle)
	{
		ERR("%s\n", dlerror());
		return 0;
	}

	// use gl_lib handle for GL symbols
#ifndef _COREGL_EMBED_EVAS
	gl_lib_handle = dlopen("libGLESv2_drv.so", RTLD_NOW);
#else
	gl_lib_handle = dlopen("libGLESv2.so.1", RTLD_NOW);
	if (!gl_lib_handle)
		gl_lib_handle = dlopen("libGLESv2.so", RTLD_NOW);
#endif
	if (!gl_lib_handle)
	{
		ERR("%s\n", dlerror());
		return 0;
	}
	//------------------------------------------------//

#else // GLX


#ifndef _COREGL_EMBED_EVAS
	gl_lib_handle = dlopen("libGL_drv.so", RTLD_NOW);
#else
	gl_lib_handle = dlopen("libGL.so.1", RTLD_NOW);
	if (!gl_lib_handle)
		gl_lib_handle = dlopen("libGL.so", RTLD_NOW);
#endif
	if (!gl_lib_handle)
	{
		ERR("%s\n", dlerror());
		return 0;
	}

	//------------------------------------------------//

#endif // _COREGL_DESKTOP_GL

	if (!_glue_sym_init()) return 0;
	if (!_gl_sym_init()) return 0;

	return 1;
}

#ifndef _COREGL_EMBED_EVAS
__attribute__((constructor))
#endif
int
init_gl()
{
	int fastpath_opt = 0;
	CoreGL_Opt_Flag api_opt = COREGL_NORMAL_PATH;

	LOG("[CoreGL] ");

	if (!_gl_lib_init()) return 0;

	fastpath_opt = atoi(get_env_setting("COREGL_FASTPATH"));

	switch (fastpath_opt)
	{
		case 1:
			api_opt = COREGL_FAST_PATH;
			LOG(": (%d) Fastpath enabled...\n", fastpath_opt);
			break;
		default:
			LOG(": (%d) Default API path enabled...\n", fastpath_opt);
			api_opt = COREGL_NORMAL_PATH;
			break;
		}

	override_glue_apis(api_opt);
	override_gl_apis(api_opt);

	return 1;
}

#ifndef _COREGL_EMBED_EVAS
__attribute__((destructor))
#endif
void
free_gl()
{
	GLContext_List *current = NULL;

	AST(mutex_lock(&ctx_list_access_mutex) == 1);

	{
		// Destroy remained context & Detect leaks
		int retry_destroy = 0;

		while (1)
		{
			retry_destroy = 0;
			current = glctx_list;
			while (current)
			{
				if (current->cstate != NULL)
				{
					ERR("\E[0;31;1mWARNING : Context attached to [dpy=%p|rctx=%p] has not been completely destroyed.(leak)\E[0m\n", current->cstate->rdpy, current->cstate->rctx);

#ifndef _COREGL_DESKTOP_GL
					_sym_eglMakeCurrent(current->cstate->rdpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
					_sym_eglDestroyContext(current->cstate->rdpy, current->cstate->rctx);
#else
					_sym_glXDestroyContext(current->cstate->rdpy, current->cstate->rctx);
#endif

					remove_context_states_from_list(current->cstate, NULL);
					retry_destroy = 1;
					break;
				}

				glctx_list = current->next;
				free(current);
				current = glctx_list;
			}
			if (retry_destroy == 0) break;
		}
	}

#ifndef _COREGL_DESKTOP_GL
	if (egl_lib_handle) dlclose(egl_lib_handle);
#endif
	if (gl_lib_handle) dlclose(gl_lib_handle);
	goto finish;

finish:
	AST(mutex_unlock(&ctx_list_access_mutex) == 1);
}

