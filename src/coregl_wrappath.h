
#include "coregl_internal.h"

// Symbol definition for override
#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (*_COREGL_NAME_MANGLE(FUNC_NAME)) PARAM_LIST;
# include "headers/sym.h"
#undef _COREGL_SYMBOL

extern void init_wrap_gl();
extern void free_wrap_gl();

extern void dump_wrap_context_states(int force_output);

