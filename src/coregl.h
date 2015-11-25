#ifndef COREGL_H
#define COREGL_H

#define COREGL_API           __attribute__((visibility("default")))

// Include GL/EGL/GLX types
# include <GLES/glplatform.h>
# include <EGL/eglplatform.h>
# include "headers/egl.h"
# include "headers/gl.h"

typedef void (*_eng_fn) (void);

#define _COREGL_SYMBOL(RET_TYPE, FUNC_NAME, PARAM_LIST)     COREGL_API extern RET_TYPE coregl_api_##FUNC_NAME PARAM_LIST;
#define _COREGL_EXT_SYMBOL(RET_TYPE, FUNC_NAME, PARAM_LIST)
#include "headers/sym.h"
#undef _COREGL_EXT_SYMBOL
#undef _COREGL_SYMBOL

extern int  coregl_initialize();
extern void coregl_terminate();

#endif // COREGL_H

