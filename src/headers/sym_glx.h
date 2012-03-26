// Defult use-case for exporting symbols
#ifndef _COREGL_SYMBOL
#define _COREGL_SYMBOL_NOT_DEFINED
#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (*_COREGL_NAME_MANGLE(FUNC_NAME)) PARAM_LIST;
#endif

_COREGL_SYMBOL(GL_FALSE, _eng_fn, glXGetProcAddress, (const char* procName))

// Standard GL(glX) functions
_COREGL_SYMBOL(GL_FALSE, XVisualInfo*, glXChooseVisual, (Display* dpy, int screen, int* attribList))
_COREGL_SYMBOL(GL_FALSE, GLXContext, glXCreateContext, (Display* dpy, XVisualInfo* vis, GLXContext shareList, Bool direct))
_COREGL_SYMBOL(GL_FALSE, void, glXDestroyContext, (Display* dpy, GLXContext ctx))
_COREGL_SYMBOL(GL_FALSE, GLXContext, glXGetCurrentContext, (void))
_COREGL_SYMBOL(GL_FALSE, GLXDrawable, glXGetCurrentDrawable, (void))
_COREGL_SYMBOL(GL_FALSE, Bool, glXMakeCurrent, (Display* dpy, GLXDrawable draw, GLXContext ctx))
_COREGL_SYMBOL(GL_FALSE, void, glXSwapBuffers, (Display* dpy, GLXDrawable draw))
_COREGL_SYMBOL(GL_FALSE, void, glXWaitX, (void))
_COREGL_SYMBOL(GL_FALSE, void, glXWaitGL, (void))
_COREGL_SYMBOL(GL_FALSE, Bool, glXQueryExtension, (Display* dpy, int* errorb, int* event))
_COREGL_SYMBOL(GL_FALSE, const char*, glXQueryExtensionsString, (Display *dpy, int screen))

_COREGL_SYMBOL(GL_FALSE, GLXFBConfig*, glXChooseFBConfig, (Display* dpy, int screen, const int* attribList, int* nitems))
_COREGL_SYMBOL(GL_FALSE, GLXFBConfig*, glXGetFBConfigs, (Display* dpy, int screen, int* nelements))
_COREGL_SYMBOL(GL_FALSE, int, glXGetFBConfigAttrib, (Display* dpy, GLXFBConfig config, int attribute, int* value))
_COREGL_SYMBOL(GL_FALSE, XVisualInfo*, glXGetVisualFromFBConfig, (Display* dpy, GLXFBConfig config))
_COREGL_SYMBOL(GL_FALSE, void, glXDestroyWindow, (Display* dpy, GLXWindow window))
_COREGL_SYMBOL(GL_FALSE, Bool, glXMakeContextCurrent, (Display* dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx))

_COREGL_SYMBOL(GL_FALSE, void, glXBindTexImage, (Display* dpy, GLXDrawable draw, int buffer, int* attribList))
_COREGL_SYMBOL(GL_FALSE, void, glXReleaseTexImage, (Display* dpy, GLXDrawable draw, int buffer))
_COREGL_SYMBOL(GL_FALSE, int, glXGetVideoSync, (unsigned int* count))
_COREGL_SYMBOL(GL_FALSE, int, glXWaitVideoSync, (int divisor, int remainder, unsigned int* count))
_COREGL_SYMBOL(GL_FALSE, XID, glXCreatePixmap, (Display* dpy, void* config, Pixmap pixmap, const int* attribList))
_COREGL_SYMBOL(GL_FALSE, void, glXDestroyPixmap, (Display* dpy, XID pixmap))
_COREGL_SYMBOL(GL_FALSE, void, glXQueryDrawable, (Display* dpy, XID draw, int attribute, unsigned int* value))
_COREGL_SYMBOL(GL_FALSE, int, glXSwapIntervalSGI, (int interval))
_COREGL_SYMBOL(GL_FALSE, void, glXSwapIntervalEXT, (Display* dpy, GLXDrawable draw, int interval))

#ifdef _COREGL_SYMBOL_NOT_DEFINED
#undef _COREGL_SYMBOL_NOT_DEFINED
#undef _COREGL_SYMBOL
#endif

