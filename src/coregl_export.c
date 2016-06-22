#include "coregl_export.h"

#define _COREGL_SYMBOL(RET_TYPE, FUNC_NAME, PARAM_LIST)     RET_TYPE (*ovr_##FUNC_NAME) PARAM_LIST = NULL;
#include "headers/sym.h"
#undef _COREGL_SYMBOL

#include "coregl_internal.h"
#include "coregl_export.h"

#include <stdlib.h>

int export_initialized = 0;

static void
_clean_overrides()
{
#define OVERRIDE(f) \
		COREGL_OVERRIDE_API(ovr_, f, _sym_)

#define _COREGL_SYMBOL(RET_TYPE, FUNC_NAME, PARAM_LIST)     OVERRIDE(FUNC_NAME);
# include "headers/sym_egl.h"
#undef _COREGL_SYMBOL

#define _COREGL_SYMBOL(RET_TYPE, FUNC_NAME, PARAM_LIST)     OVERRIDE(FUNC_NAME);
if(driver_gl_version == COREGL_GLAPI_1) {
	#include "headers/sym_gl1.h"
	#include "headers/sym_gl_common.h"
}
else if(driver_gl_version == COREGL_GLAPI_2) {
	#include "headers/sym_gl2.h"
	#include "headers/sym_gl_common.h"
}
#undef _COREGL_SYMBOL

#undef OVERRIDE
}

void
init_export()
{
	_clean_overrides();
}

