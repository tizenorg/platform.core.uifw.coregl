#ifndef COREGL_H
#define COREGL_H

#define COREGL_API           __attribute__((visibility("default")))

// Include GL/EGL/GLX types
# include <GLES/glplatform.h>
# include <EGL/eglplatform.h>
# include "headers/egl.h"
# include "headers/gl.h"

typedef void (*_eng_fn) (void);

#include "headers/sym.h"

extern int  coregl_initialize();
extern void coregl_terminate();

#endif // COREGL_H

