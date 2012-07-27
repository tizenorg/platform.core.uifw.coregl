#ifndef COREGL_INTERNAL_H
#define COREGL_INTERNAL_H

#include <stdio.h>

#include "coregl.h"

#include "modules/coregl_module.h"

#define unlikely(x) __builtin_expect(x, 0)

// Symbol definition for real
#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (*_sym_##FUNC_NAME) PARAM_LIST;
# include "headers/sym.h"
#undef _COREGL_SYMBOL

#define COREGL_DEBUG

# define ERR(...) \
     fprintf(stderr, __VA_ARGS__)
# ifdef COREGL_DEBUG
#  define DBG(...) \
     fprintf(stderr, __VA_ARGS__)
# else
#  define DBG(...)
# endif

# define LOG(...) \
     fprintf(stderr, __VA_ARGS__)


# define TRACE(...) \
     fprintf(trace_fp, __VA_ARGS__)
# define TRACE_END() \
     fflush(trace_fp)
#define _COREGL_TRACE_OUTPUT_INTERVAL_SEC 5


#ifdef COREGL_DEBUG
# define AST(expr) \
     if (!(expr)) { fprintf(stderr, "\E[0;31;1m%s(%d) error. '"#expr"'\E[0m\n", __func__, __LINE__); }
#else
# define AST(expr) \
     if (expr)
#endif

typedef GLvoid *     GLvoidptr;
typedef GLuint       GLuintmask;

#define _COREGL_INT_INIT_VALUE -3

#ifdef COREGL_ERRORS
# define GLERR(fn, fl, ln, op)
#else
# define GLERR(fn, fl, ln, op)
#endif

#define COREGL_OVERRIDE_API(mangle, func, prefix) \
   mangle##func = prefix##func

typedef EGLSurface     GLSurface;
typedef EGLDisplay     GLDisplay;
typedef EGLContext     GLContext;

#define COREGL_GL_NO_CONTEXT EGL_NO_CONTEXT

typedef struct _GLThreadState
{
	int                      thread_id;
	void                    *module_data[COREGL_MAX_MODULES];
} GLThreadState;

extern void                *glue_lib_handle;
extern void                *egl_lib_handle;

#include "coregl_thread_pthread.h"

typedef struct _General_Trace_List
{
	void                          *value;
	struct _General_Trace_List    *next;
} General_Trace_List;

extern General_Trace_List  *thread_trace_list;
extern Mutex                general_trace_lists_access_mutex;

extern FILE               *trace_fp;

extern int                 trace_api_flag;
extern int                 trace_api_all_flag;
extern int                 trace_mem_flag;
extern int                 trace_ctx_flag;
extern int                 trace_ctx_force_flag;
extern int                 trace_state_flag;

#define USE_TRACEPATH		(trace_api_flag == 1 || trace_ctx_flag == 1 || trace_state_flag == 1 || trace_mem_flag == 1)

// Environment functions
extern const char         *get_env_setting(const char *name);

// Main utility functions
extern int                 init_new_thread_state();

// Thread functions
extern int                 mutex_lock(Mutex *mt);
extern int                 mutex_unlock(Mutex *mt);
extern int                 get_current_thread();
extern int                 set_current_thread_state(GLThreadState *tstate);
extern GLThreadState      *get_current_thread_state();


// Override functions
extern void                init_export();
extern void                deinit_export();

// Module interfaces
extern void                init_modules();
extern void                deinit_modules();
extern void                init_modules_tstate(GLThreadState *tstate);
extern void                deinit_modules_tstate(GLThreadState *tstate);


// Debug & Trace functions
extern int                 add_to_general_trace_list(General_Trace_List **gtl, void *value);
extern int                 remove_from_general_trace_list(General_Trace_List **gtl, void *value);

#endif // COREGL_INTERNAL_H

