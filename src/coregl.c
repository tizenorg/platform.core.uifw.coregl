#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

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
		COREGL_LOG("[COREGL] de-init thread state \n");
		deinit_modules_tstate(tstate);
		remove_from_general_trace_list(&thread_trace_list, tstate);
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
	add_to_general_trace_list(&thread_trace_list, tstate);

	init_modules_tstate(tstate);
	set_current_thread_state(tstate);

	ret = 1;
	goto finish;

finish:
	return ret;
}

static void
_sym_missing()
{
	COREGL_ERR("GL symbol missing! Check client version!\n");
}

static int
_glue_sym_init(void)
{

#define FINDSYM(libhandle, getproc, dst, sym) \
   if ((!dst) && (getproc)) dst = (__typeof__(dst))getproc(sym); \
   if (!dst) dst = (__typeof__(dst))dlsym(libhandle, sym);

#define FALLBAK(dst) \
   if (!dst) { dst = (__typeof__(dst))_sym_missing; }

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST) \
    FINDSYM(egl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME); \
    if (IS_EXTENSION == GL_TRUE) { \
       FINDSYM(egl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"EXT"); \
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
   if (!dst) { dst = (__typeof__(dst))_sym_missing; }

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST) \
    FINDSYM(gl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME); \
    if (IS_EXTENSION == GL_TRUE) { \
       FINDSYM(gl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"EXT"); \
       FINDSYM(gl_lib_handle, _sym_eglGetProcAddress, _sym_##FUNC_NAME, #FUNC_NAME"OES"); \
     } else { FALLBAK(_sym_##FUNC_NAME); }
#include "headers/sym_gl.h"
#undef _COREGL_SYMBOL

#undef FINDSYM
#undef FALLBAK

	return 1;
}

COREGL_API void coregl_symbol_exported()
{
	COREGL_ERR("\E[40;31;1mInvalid library link! (Check linkage of libCOREGL)\E[0m\n");
}

static int
_gl_lib_init(void)
{

	//------------------------------------------------//
	// Open EGL Library as EGL is separate
	egl_lib_handle = dlopen("/usr/lib/driver/libEGL.so.1.4", RTLD_NOW);
	if (!egl_lib_handle)
	{
		COREGL_ERR("\E[40;31;1m%s\E[0m\n\n", dlerror());
		COREGL_ERR("\E[40;31;1mInvalid library link! (Check linkage of libCOREGL -> /usr/lib/driver/libEGL.so.1.4)\E[0m\n");
		return 0;
	}

	// test for invalid linking egl
	if (dlsym(egl_lib_handle, "coregl_symbol_exported"))
	{
		COREGL_ERR("\E[40;31;1mInvalid library link! (Check linkage of libCOREGL -> /usr/lib/driver/libEGL.so.1.4)\E[0m\n");
		return 0;
	}

	// use gl_lib handle for GL symbols
	gl_lib_handle = dlopen("/usr/lib/driver/libGLESv2.so.2.0", RTLD_NOW);
	if (!gl_lib_handle)
	{
		COREGL_ERR("\E[40;31;1m%s\E[0m\n\n", dlerror());
		COREGL_ERR("\E[40;31;1mInvalid library link! (Check linkage of libCOREGL -> /usr/lib/driver/libGLESv2.so.2.0)\E[0m\n");
		return 0;
	}

	// test for invalid linking gl
	if (dlsym(gl_lib_handle, "coregl_symbol_exported"))
	{
		COREGL_ERR("\E[40;31;1mInvalid library link! (Check linkage of libCOREGL -> /usr/lib/driver/libGLESv2.so.2.0)\E[0m\n");
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
	COREGL_LOG("[CoreGL] <%d> (%s) Library initializing...", getpid(), _COREGL_COMPILE_DATE);

	if (!_gl_lib_init()) return 0;

	init_export();

	COREGL_LOG(" -> Completed\n");

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

