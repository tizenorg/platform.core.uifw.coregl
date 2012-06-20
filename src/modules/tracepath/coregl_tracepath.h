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

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (*_orig_tracepath_##FUNC_NAME) PARAM_LIST;
# include "../../headers/sym.h"
#undef _COREGL_SYMBOL

// Symbol definition for tracepath
#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (tracepath_##FUNC_NAME) PARAM_LIST;
# include "../../headers/sym.h"
#undef _COREGL_SYMBOL

#define COREGL_TRACEPATH_TRACE_ALL

#ifdef COREGL_TRACEPATH_TRACE_ALL
#define COREGL_TRACEPATH_TRACE_CONTEXT_INFO   // Context state & thread state & Glue-context info
#define COREGL_TRACEPATH_TRACE_STATE_INFO     // Glue-context state info
#define COREGL_TRACEPATH_TRACE_APICALL_INFO   // API call frequency info
#endif

#ifdef COREGL_TRACEPATH_TRACE_APICALL_INFO
# define _COREGL_TRACE_API_BEGIN(api, hint, trace_total_time) \
   tracepath_api_trace_begin(api, hint, trace_total_time);
# define _COREGL_TRACE_API_END(api, hint, trace_total_time) \
   tracepath_api_trace_end(api, hint, trace_total_time);
# define _COREGL_TRACE_API_OUTPUT(force_output) \
   tracepath_api_trace_output(force_output);
#else
# define _COREGL_TRACE_API_BEGIN(api, hint, trace_total_time) NULL;
# define _COREGL_TRACE_API_END(api, hint, trace_total_time)
# define _COREGL_TRACE_API_OUTPUT(force_output)
#endif

#define _COREGL_TRACEPATH_FUNC_BEGIN() \
	if (unlikely(trace_api_flag == 1)) \
		_COREGL_TRACE_API_BEGIN(__func__, NULL, 1);

#define _COREGL_TRACEPATH_FUNC_END() \
	if (unlikely(trace_api_flag == 1)) \
		_COREGL_TRACE_API_END(__func__, NULL, 1);

typedef struct _Tracepath_ThreadState
{
	Trace_Data             **ftd_table;
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

#endif // COREGL_TRACEPATH_H

