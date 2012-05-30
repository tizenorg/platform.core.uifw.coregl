#ifndef COREGL_EXPORT_H
#define COREGL_EXPORT_H

#include "coregl_internal.h"

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (*ovr_##FUNC_NAME) PARAM_LIST;
# include "headers/sym.h"
#undef _COREGL_SYMBOL

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (*wrp_##FUNC_NAME) PARAM_LIST;
# include "headers/sym.h"
#undef _COREGL_SYMBOL

#endif // COREGL_EXPORT_H

