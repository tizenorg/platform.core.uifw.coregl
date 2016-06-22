#include "coregl_internal.h"
#include "coregl_export.h"

#include <stdlib.h>

void
init_overrides()
{
#define C_ORD(f) COREGL_OVERRIDE_API(ovr_, f, _sym_)

#define _COREGL_SYMBOL(RET_TYPE, FUNC_NAME, PARAM_LIST)     C_ORD(FUNC_NAME);
# include "headers/sym_egl.h"
#undef _COREGL_SYMBOL

#define _COREGL_SYMBOL(RET_TYPE, FUNC_NAME, PARAM_LIST)     C_ORD(FUNC_NAME);
# include "headers/sym_gl1.h"
# include "headers/sym_gl2.h"

#undef _COREGL_SYMBOL

#undef C_ORD
}

