#include "coregl_appopt.h"

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     RET_TYPE (*_orig_appopt_##FUNC_NAME) PARAM_LIST = NULL;
#include "../../headers/sym.h"
#undef _COREGL_SYMBOL

void
init_modules_appopt()
{
	LOG("[CoreGL] <Appopt> : ");

	LOG("Not yet implemented\n");

	appopt_apply_overrides();
}

void
deinit_modules_appopt()
{
}

void
init_modules_tstate_appopt(GLThreadState *tstate)
{
	MY_MODULE_TSTATE *tstate_mt = NULL;

	tstate_mt = (MY_MODULE_TSTATE *)calloc(1, sizeof(MY_MODULE_TSTATE));


	tstate->module_data[MY_MODULE_ID] = tstate_mt;
}

void
deinit_modules_tstate_appopt(GLThreadState *tstate)
{
	if (tstate->module_data[MY_MODULE_ID] != NULL)
	{
		free(tstate->module_data[MY_MODULE_ID]);
		tstate->module_data[MY_MODULE_ID] = NULL;
	}
}

void
appopt_apply_overrides()
{
	//appopt_apply_overrides_egl(1);
	//appopt_apply_overrides_gl(1);
}

#define OVERRIDE(f) \
	if (enable == 1) \
	{ \
		COREGL_OVERRIDE_API(_orig_appopt_, f, ovr_); \
		COREGL_OVERRIDE_API(ovr_, f, appopt_); \
	} \
	else \
	{ \
		AST(ovr_##f != NULL); \
		COREGL_OVERRIDE_API(ovr_, f, _orig_appopt_); \
		_orig_appopt_##f = NULL; \
	}

void
appopt_apply_overrides_egl(int enable)
{
	// Fast-Path Core Functions
}

void
appopt_apply_overrides_gl(int enable)
{
	// Fast-Path Functions
}

#undef A_ORD

