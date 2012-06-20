#ifndef COREGL_H
#define COREGL_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define COREGL_API           __attribute__((visibility("default")))

// Include GL/EGL/GLX types
# include <GLES/glplatform.h>
# include <EGL/eglplatform.h>
# include "headers/egl.h"
# include "headers/gl.h"

typedef void (*_eng_fn) (void);

#include "headers/sym.h"

extern int  init_gl();
extern void free_gl();

#endif // COREGL_H

