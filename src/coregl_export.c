#include "coregl_export.h"

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     RET_TYPE (*ovr_##FUNC_NAME) PARAM_LIST = NULL;
#include "headers/sym.h"
#undef _COREGL_SYMBOL

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     RET_TYPE (*wrp_##FUNC_NAME) PARAM_LIST = NULL;
#include "headers/sym.h"
#undef _COREGL_SYMBOL

