#ifndef COREGL_WRAPPATH_H
#define COREGL_WRAPPATH_H

#include "coregl_internal.h"
#include "coregl_export.h"

// Symbol definition for wrappath
#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (wpgl_##FUNC_NAME) PARAM_LIST;
# include "headers/sym.h"
#undef _COREGL_SYMBOL

extern void init_wrap_gl();
extern void free_wrap_gl();

extern void dump_wrap_context_states(int force_output);

#endif // COREGL_WRAPPATH_H

