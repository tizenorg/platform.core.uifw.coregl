#ifndef COREGL_TRACEPATH_H
#define COREGL_TRACEPATH_H

#include "../coregl_module.h"

#ifndef COREGL_USE_MODULE_TRACEPATH
#error "COREGL_USE_MODULE_TRACEPATH must defined!!!"
#endif

#define MY_MODULE_ID              COREGL_MODULE_TRACEPATH
#define MY_MODULE_TSTATE         Tracepath_ThreadState

#include "../../coregl_internal.h"
#include "../../coregl_export.h"

#define _COREGL_SYMBOL(RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (*_orig_tracepath_##FUNC_NAME) PARAM_LIST;
# include "../../headers/sym.h"
#undef _COREGL_SYMBOL

// Symbol definition for tracepath
#define _COREGL_SYMBOL(RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (tracepath_##FUNC_NAME) PARAM_LIST;
# include "../../headers/sym.h"
#undef _COREGL_SYMBOL

#define MAX_TRACE_NAME_LENGTH  256
#define MAX_TRACE_TABLE_SIZE   65536

#define COREGL_TRACEPATH_TRACE_ALL

#ifdef COREGL_TRACEPATH_TRACE_ALL
#define COREGL_TRACEPATH_TRACE_CONTEXT_INFO   // Context state & thread state & Glue-context info
#define COREGL_TRACEPATH_TRACE_STATE_INFO     // Glue-context state info
#define COREGL_TRACEPATH_TRACE_APICALL_INFO   // API call frequency & each frame call info
#define COREGL_TRACEPATH_TRACE_MEMUSE_INFO   // Memory usage info
#define COREGL_TRACEPATH_TRACE_SURFACE_INFO  // Surface dump info
#endif

#ifdef COREGL_TRACEPATH_TRACE_APICALL_INFO
# define _COREGL_TRACE_API_BEGIN(api, hint, trace_total_time) \
   tracepath_api_trace_begin(api, hint, trace_total_time);
# define _COREGL_TRACE_API_END(api, hint, trace_total_time) \
   tracepath_api_trace_end(api, hint, trace_total_time);
# define _COREGL_TRACE_API_OUTPUT(force_output) \
   tracepath_api_trace_output(force_output);
# define _COREGL_TRACE_API_RESET_FRAME() \
   tracepath_api_trace_reset_frame();
#else
# define _COREGL_TRACE_API_BEGIN(api, hint, trace_total_time) NULL;
# define _COREGL_TRACE_API_END(api, hint, trace_total_time)
# define _COREGL_TRACE_API_OUTPUT(force_output)
# define _COREGL_TRACE_API_RESET_FRAME()
#endif

#ifdef COREGL_TRACEPATH_TRACE_MEMUSE_INFO
# define _COREGL_TRACE_MEM_ADD(desc, alloc_size) \
   tracepath_mem_trace_add(desc, alloc_size);
# define _COREGL_TRACE_MEM_REMOVE(desc, alloc_size) \
   tracepath_mem_trace_remove(desc, alloc_size);
# define _COREGL_TRACE_MEM_OUTPUT(force_output) \
   tracepath_mem_trace_output(force_output);
#else
# define _COREGL_TRACE_MEM_ADD(desc, alloc_size)
# define _COREGL_TRACE_MEM_REMOVE(desc, alloc_size)
# define _COREGL_TRACE_MEM_OUTPUT(force_output)
#endif

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
# define _COREGL_TRACE_SURFACE(force_output, type, position) \
   tracepath_surface_trace(force_output, type, position);
#else
# define _COREGL_TRACE_SURFACE(force_output, type, position)
#endif

#define _COREGL_TRACEPATH_FUNC_BEGIN() \
	if (unlikely(trace_api_flag == 1)) \
		_COREGL_TRACE_API_BEGIN(__func__, NULL, 1);

#define _COREGL_TRACEPATH_FUNC_END() \
	if (unlikely(trace_api_flag == 1)) \
		_COREGL_TRACE_API_END(__func__, NULL, 1);

typedef struct _Trace_Data Trace_Data;
typedef struct _Apicall_Data Apicall_Data;
typedef struct _Memuse_Data Memuse_Data;
typedef struct _Surface_Data Surface_Data;

#define MTD_GLBUF_HASH_ARRAY 10000

typedef struct _Glbuf_Data Glbuf_Data;
typedef struct _Sostate_Data
{
	int                         ref_count;

	Glbuf_Data                 *glbuf_tex[MTD_GLBUF_HASH_ARRAY];
	Glbuf_Data                 *glbuf_rb[MTD_GLBUF_HASH_ARRAY];
} Sostate_Data;

typedef struct _Ctx_Data
{
	GLDisplay                dpy;
	GLContext                handle;
	int                      ref_count;
	int                      mc_count;
	Sostate_Data            *sostate;

	struct _Ctx_Data       *next;
} Ctx_Data;

extern Mutex               ctx_access_mutex;

extern Mutex               access_mutex;
extern Memuse_Data       **table;

typedef struct _Tracepath_ThreadState
{
	Apicall_Data            **ftd_table;
	Ctx_Data                 *ctx;

	GLSurface                *surf_draw;
	GLSurface                *surf_read;
} Tracepath_ThreadState;

extern void                init_modules_tracepath();
extern void                deinit_modules_tracepath();
extern void                init_modules_tstate_tracepath(GLThreadState *tstate);
extern void                deinit_modules_tstate_tracepath(GLThreadState *tstate);


extern void                tracepath_apply_overrides();
extern void                tracepath_apply_overrides_egl();
extern void                tracepath_apply_overrides_gl();

extern void                tracepath_dump_context_states(int force_output);

extern void               *tracepath_api_trace_begin(const char *name, void *hint, int trace_total_time);
extern void               *tracepath_api_trace_end(const char *name, void *hint, int trace_total_time);
extern void                tracepath_api_trace_output(int force_output);
extern void                tracepath_api_trace_reset_frame();

extern void                tracepath_mem_trace_add(const char *desc, int alloc_size);
extern void                tracepath_mem_trace_remove(const char *desc, int alloc_size);
extern void                tracepath_mem_trace_output(int force_output);

extern void                tracepath_surface_trace_add(const char *desc, GLDisplay dpy, GLContext ctx, GLSurface surf, GLint fbo, GLint tex, GLint rb, GLint tex_w, GLint tex_h, GLint tex_format, const char *dump);
extern void                tracepath_surface_trace(int force_output, int type, const char *position);

extern void                tracepath_glbuf_clear(Glbuf_Data **glbuf);

#endif // COREGL_TRACEPATH_H

