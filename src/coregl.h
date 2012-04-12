#ifndef COREGL_H
#define COREGL_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#if defined (GLES_VARIETY_S3C6410) || defined (GLES_VARIETY_SGX)
#else
# define _COREGL_DESKTOP_GL
#endif

#if defined(_COREGL_EMBEDDED_GL)
#undef _COREGL_DESKTOP_GL
#endif

#define COREGL_API           __attribute__((visibility("default")))

// Include GL/EGL/GLX types
#ifndef _COREGL_DESKTOP_GL
# include <GLES/glplatform.h>
# include <EGL/eglplatform.h>
# include "headers/egl.h"
#else
# include "headers/glx.h"
#endif
# include "headers/gl.h"

typedef void (*_eng_fn) (void);

#include "headers/sym.h"

extern int  init_gl();
extern void free_gl();

#endif // COREGL_H

