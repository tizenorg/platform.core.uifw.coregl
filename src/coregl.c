#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include "coregl_internal.h"
#include "coregl_export.h"

void               *egl_lib_handle;
void               *gl_lib_handle;

// Symbol definition for real
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

void
cleanup_current_thread_state()
{
	GLThreadState *tstate = NULL;

	tstate = get_current_thread_state();

	if (tstate != NULL)
	{
		LOG("[COREGL] de-init thread state \n");
		deinit_modules_tstate(tstate);
		free(tstate);
		tstate = NULL;
	}

	set_current_thread_state(NULL);
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

	init_modules_tstate(tstate);

	set_current_thread_state(tstate);

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

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST) \
    FINDSYM(egl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME); \
    if (IS_EXTENSION == GL_TRUE) { \
       FINDSYM(egl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"EXT"); \
       FINDSYM(egl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"ARB"); \
       FINDSYM(egl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"OES"); \
       FINDSYM(egl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"KHR"); \
    } else { FALLBAK(_sym_##FUNC_NAME); }
#include "headers/sym_egl.h"
#undef _COREGL_SYMBOL

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

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST) \
    FINDSYM(gl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME); \
    if (IS_EXTENSION == GL_TRUE) { \
       FINDSYM(gl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"EXT"); \
       FINDSYM(gl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"ARB"); \
       FINDSYM(gl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"OES"); \
       FINDSYM(gl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"KHR"); \
     } else { FALLBAK(_sym_##FUNC_NAME); }
#include "headers/sym_gl.h"
#undef _COREGL_SYMBOL

#undef FINDSYM
#undef FALLBAK

	return 1;
}

COREGL_API void coregl_symbol_exported()
{
	LOG("\E[0;31;1mERROR : Invalid library link! (Check linkage of libCOREGL)\E[0m\n");
}

static int
_gl_lib_init(void)
{

	//------------------------------------------------//
	// Open EGL Library as EGL is separate
	egl_lib_handle = dlopen("libEGL_drv.so", RTLD_NOW);
	if (!egl_lib_handle)
	{
		ERR("\E[0;31;1mERROR : %s\E[0m\n\n", dlerror());
		ERR("\E[0;31;1mERROR : Invalid library link! (Check linkage of libCOREGL -> libEGL_drv)\E[0m\n");
		return 0;
	}

	// test for invalid linking egl
	if (dlsym(egl_lib_handle, "coregl_symbol_exported"))
	{
		ERR("\E[0;31;1mERROR : Invalid library link! (Check linkage of libCOREGL -> libEGL_drv)\E[0m\n");
		return 0;
	}

	// use gl_lib handle for GL symbols
	gl_lib_handle = dlopen("libGLESv2_drv.so", RTLD_NOW);
	if (!gl_lib_handle)
	{
		ERR("\E[0;31;1mERROR : %s\E[0m\n\n", dlerror());
		ERR("\E[0;31;1mERROR : Invalid library link! (Check linkage of libCOREGL -> libGLESv2_drv)\E[0m\n");
		return 0;
	}

	// test for invalid linking gl
	if (dlsym(gl_lib_handle, "coregl_symbol_exported"))
	{
		ERR("\E[0;31;1mERROR : Invalid library link! (Check linkage of libCOREGL -> libGLESv2_drv)\E[0m\n");
		return 0;
	}
	//------------------------------------------------//

	if (!_glue_sym_init()) return 0;
	if (!_gl_sym_init()) return 0;

	return 1;
}

static int
_gl_lib_deinit(void)
{
	if (egl_lib_handle) dlclose(egl_lib_handle);
	if (gl_lib_handle) dlclose(gl_lib_handle);

	return 1;
}

int
coregl_initialize()
{
	LOG("[CoreGL] Library initializing...");

	if (!_gl_lib_init()) return 0;

	init_export();

	LOG(" -> Completed\n");

	init_modules();

	return 1;
}

__attribute__((destructor))
void
coregl_terminate()
{
	if (export_initialized != 0)
	{
		deinit_modules();

		_gl_lib_deinit();
	}
}

