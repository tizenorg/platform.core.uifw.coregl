#ifndef COREGL_INTERNAL_H
#define COREGL_INTERNAL_H

#include <stdio.h>

#include "coregl.h"

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

#ifdef COREGL_DEBUG
# define AST(expr) \
     if (!(expr)) { fprintf(stderr, "\E[0;31;1m%s(%d) error. '"#expr"'\E[0m\n", __func__, __LINE__); }
#else
# define AST(expr) \
     if (expr)
#endif

typedef GLvoid *     GLvoidptr;
typedef GLuint       GLuintmask;

//#define COREGL_TRACE_ALL
#define COREGL_TRACE_CONTEXT_INFO
#define COREGL_TRACE_STATE_INFO
//#define COREGL_TRACE_APICALL_INFO

#ifdef COREGL_TRACE_ALL
#define COREGL_TRACE_CONTEXT_INFO   // Context state & thread state & Glue-context info
#define COREGL_TRACE_STATE_INFO     // Glue-context state info
#define COREGL_TRACE_APICALL_INFO   // API call frequency info
#endif

#define _COREGL_TRACE_OUTPUT_INTERVAL_SEC 5

#define _COREGL_INT_INIT_VALUE -3

#ifdef COREGL_ERRORS
# define GLERR(fn, fl, ln, op)
#else
# define GLERR(fn, fl, ln, op)
#endif

#define _COREGL_NAME_MANGLE(name) ovr_##name

typedef struct _Trace_Data Trace_Data;

#ifdef COREGL_TRACE_APICALL_INFO
# define _COREGL_TRACE_API_BEGIN(api, hint, trace_total_time) \
   trace_begin(api, hint, trace_total_time);
# define _COREGL_TRACE_API_END(api, hint, trace_total_time) \
   trace_end(api, hint, trace_total_time);
# define _COREGL_TRACE_API_OUTPUT(force_output) \
   trace_output(force_output);
#else
# define _COREGL_TRACE_API_BEGIN(api, hint, trace_total_time) NULL;
# define _COREGL_TRACE_API_END(api, hint, trace_total_time)
# define _COREGL_TRACE_API_OUTPUT(force_output)
#endif


#define _COREGL_FAST_FUNC_BEGIN()

#define _COREGL_FAST_FUNC_END()

#define _COREGL_FAST_FUNC_SYMCALL_BEGIN()

#define _COREGL_FAST_FUNC_SYMCALL_END()

#define _COREGL_WRAP_FUNC_BEGIN() \
	static void *trace_hint = NULL; \
	if (trace_api_flag == 1) \
		trace_hint = _COREGL_TRACE_API_BEGIN(__func__, trace_hint, 1);

#define _COREGL_WRAP_FUNC_END() \
	if (trace_api_flag == 1) \
		_COREGL_TRACE_API_END(__func__, trace_hint, 1);

typedef enum _CoreGL_Opt_Flag
{
    COREGL_UNKNOWN_PATH,
    COREGL_NORMAL_PATH,
    COREGL_FAST_PATH
} CoreGL_Opt_Flag;

extern CoreGL_Opt_Flag api_opt;

#ifndef _COREGL_DESKTOP_GL
typedef EGLSurface     GLSurface;
typedef EGLDisplay     GLDisplay;
typedef EGLContext     GLContext;
#else
typedef GLXDrawable    GLSurface;
typedef Display        GLDisplay;
typedef GLXContext     GLContext;
#endif

typedef struct _GLContextState
{
	int                      ref_count;
	GLContext               *rctx;
	GLDisplay               *rdpy;
	void                    *data;
} GLContextState;

typedef struct _GLThreadState
{
	int                      thread_id;
	EGLenum                  binded_api;
	GLContextState          *cstate;
	GLSurface               *rsurf_draw;
	GLSurface               *rsurf_read;
	Trace_Data             **ftd_table;
} GLThreadState;

typedef struct _GLContext_List
{
	void                    *option;
	int                      option_len;
	int                      thread_id;
	GLContextState          *cstate;
	struct _GLContext_List *next;
} GLContext_List;

extern void                *glue_lib_handle;
extern void                *egl_lib_handle;

extern GLContext_List      *glctx_list;

#include "coregl_thread_pthread.h"
extern Mutex                ctx_list_access_mutex;

typedef struct _General_Trace_List
{
	void                          *value;
	struct _General_Trace_List    *next;
} General_Trace_List;

extern General_Trace_List  *thread_trace_list;
extern Mutex                general_trace_lists_access_mutex;

extern int                 trace_api_flag;
extern int                 trace_ctx_flag;
extern int                 trace_ctx_force_flag;
extern int                 trace_state_flag;
extern int                 debug_nofp;
extern FILE               *trace_fp;

// Environment functions
extern const char         *get_env_setting(const char *name);

// Main utility functions
extern int                 init_new_thread_state();

// Thread functions
extern int                 mutex_lock(Mutex *mt);
extern int                 mutex_unlock(Mutex *mt);
extern int                 get_current_thread();
extern int                 set_current_thread_state(Mutex *mt, GLThreadState *tstate);
extern GLThreadState      *get_current_thread_state();


// Context state functions
extern int                 add_context_state_to_list(const void *data, const int datalen, GLContextState *cstate, Mutex *mtx);
extern int                 remove_context_states_from_list(GLContextState *cstate, Mutex *mtx);
extern GLContextState     *get_context_state_from_list(const void *data, const int datalen, Mutex *mtx);


// Override functions
extern void                override_glue_normal_path();
extern void                override_glue_fast_path();
extern void                override_gl_normal_path();
extern void                override_gl_fast_path();
extern void                override_glue_apis(CoreGL_Opt_Flag opt);
extern void                override_gl_apis(CoreGL_Opt_Flag opt);


// Debug & Trace functions
extern int                 add_to_general_trace_list(General_Trace_List **gtl, void *value);
extern int                 remove_from_general_trace_list(General_Trace_List **gtl, void *value);
extern void               *trace_begin(const char *name, void *hint, int trace_total_time);
extern void               *trace_end(const char *name, void *hint, int trace_total_time);
extern void                trace_output(int force_output);

#endif // COREGL_INTERNAL_H

