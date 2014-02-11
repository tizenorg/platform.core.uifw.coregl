#ifndef COREGL_EXPORT_H
#define COREGL_EXPORT_H

#include "coregl_internal.h"

#define _COREGL_SYMBOL(RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (*ovr_##FUNC_NAME) PARAM_LIST;
# include "headers/sym.h"
#undef _COREGL_SYMBOL

extern int export_initialized;
extern int driver_gl_version;

extern void     init_export();
extern void     clean_overrides();

#endif // COREGL_EXPORT_H

