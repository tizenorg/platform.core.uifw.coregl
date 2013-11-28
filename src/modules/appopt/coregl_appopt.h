#ifndef COREGL_APPOPT_H
#define COREGL_APPOPT_H

#include "../coregl_module.h"

#ifndef COREGL_USE_MODULE_APPOPT
#error "COREGL_USE_MODULE_APPOPT must defined!!!"
#endif

#define MY_MODULE_ID              COREGL_MODULE_APPOPT
#define MY_MODULE_TSTATE         Appopt_ThreadState

#include "../../coregl_internal.h"
#include "../../coregl_export.h"

#define _COREGL_SYMBOL(RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (*_orig_appopt_##FUNC_NAME) PARAM_LIST;
# include "../../headers/sym.h"
#undef _COREGL_SYMBOL

// Symbol definition for appopt
#define _COREGL_SYMBOL(RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (appopt_##FUNC_NAME) PARAM_LIST;
# include "../../headers/sym.h"
#undef _COREGL_SYMBOL

typedef struct _Appopt_ThreadState
{
	void				*_notusedyet;
} Appopt_ThreadState;


#define _COREGL_APPOPT_FUNC_BEGIN()

#define _COREGL_APPOPT_FUNC_END()


extern void     init_modules_appopt();
extern void     deinit_modules_appopt();
extern void     init_modules_tstate_appopt(GLThreadState *tstate);
extern void     deinit_modules_tstate_appopt(GLThreadState *tstate);

extern void     appopt_apply_overrides();
extern void     appopt_apply_overrides_egl(int enable);
extern void     appopt_apply_overrides_gl(int enable);


#endif // COREGL_APPOPT_H

