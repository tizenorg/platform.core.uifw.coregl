#ifndef __egl_h_
#define __egl_h_

#define _COREGL_NAME_MANGLE(name) name

typedef void (*_eng_fn) (void);

#include <EGL/eglplatform.h>

#include "def_egl.h"
#include "sym_egl.h"

#undef GL

#endif /* __egl_h_ */

