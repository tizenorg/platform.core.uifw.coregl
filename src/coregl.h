#ifndef COREGL_H
#define COREGL_H

#define COREGL_API           __attribute__((visibility("default")))

// Include GL/EGL/GLX types
# include <GLES/glplatform.h>
# include <EGL/eglplatform.h>
# include "headers/egl.h"
# include "headers/gl.h"

typedef void (*_eng_fn) (void);

#define _COREGL_EXT_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)
#include "headers/sym.h"
#undef _COREGL_EXT_SYMBOL

extern int  coregl_initialize();
extern void coregl_terminate();

#endif // COREGL_H

