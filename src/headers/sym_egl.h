// Defult use-case for exporting symbols
#ifndef _COREGL_SYMBOL
#define _COREGL_SYMBOL_NOT_DEFINED
#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     COREGL_API extern RET_TYPE FUNC_NAME PARAM_LIST;
#endif
#ifndef _COREGL_EXT_SYMBOL
#define _COREGL_EXT_SYMBOL_NOT_DEFINED
#define _COREGL_EXT_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)   _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)
#endif
#ifndef _COREGL_EXT_SYMBOL_ALIAS
#define _COREGL_EXT_SYMBOL_ALIAS_NOT_DEFINED
#define _COREGL_EXT_SYMBOL_ALIAS(FUNC_NAME, ALIAS_NAME)
#endif
#ifndef _COREGL_EXT_SYMBOL_FASTPATH_PASS
#define _COREGL_EXT_SYMBOL_FASTPATH_PASS_NOT_DEFINED
#define _COREGL_EXT_SYMBOL_FASTPATH_PASS(FUNC_NAME)
#endif
#ifndef _COREGL_EXT_SYMBOL_FASTPATH_BLOCK
#define _COREGL_EXT_SYMBOL_FASTPATH_BLOCK_NOT_DEFINED
#define _COREGL_EXT_SYMBOL_FASTPATH_BLOCK(FUNC_NAME)
#endif

// Standard EGL APIs

_COREGL_SYMBOL(GL_FALSE, EGLint, eglGetError, (void))
_COREGL_SYMBOL(GL_FALSE, EGLDisplay, eglGetDisplay, (EGLNativeDisplayType display_id))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglInitialize, (EGLDisplay dpy, EGLint* major, EGLint *minor))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglTerminate, (EGLDisplay dpy))
_COREGL_SYMBOL(GL_FALSE, const char*, eglQueryString, (EGLDisplay dpy, EGLint name))

_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglGetConfigs, (EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglChooseConfig, (EGLDisplay dpy, const EGLint* attrib_list, EGLConfig* configs, EGLint config_size, EGLint* num_config))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglGetConfigAttrib, (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value))

_COREGL_SYMBOL(GL_FALSE, EGLSurface, eglCreateWindowSurface, (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint* attrib_list))
_COREGL_SYMBOL(GL_FALSE, EGLSurface, eglCreatePbufferSurface, (EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list))
_COREGL_SYMBOL(GL_FALSE, EGLSurface, eglCreatePixmapSurface, (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint* attrib_list))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglDestroySurface, (EGLDisplay dpy, EGLSurface surface))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglQuerySurface, (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value))

_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglBindAPI, (EGLenum api))
_COREGL_SYMBOL(GL_FALSE, EGLenum, eglQueryAPI, (void))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglWaitClient, (void))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglReleaseThread, (void))
_COREGL_SYMBOL(GL_FALSE, EGLSurface, eglCreatePbufferFromClientBuffer, (EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list))

_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglSurfaceAttrib, (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglBindTexImage, (EGLDisplay dpy, EGLSurface surface, EGLint buffer))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglReleaseTexImage, (EGLDisplay dpy, EGLSurface surface, EGLint buffer))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglSwapInterval, (EGLDisplay dpy, EGLint interval))
_COREGL_SYMBOL(GL_FALSE, EGLContext, eglCreateContext, (EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint* attrib_list))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglDestroyContext, (EGLDisplay dpy, EGLContext ctx))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglMakeCurrent, (EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx))
_COREGL_SYMBOL(GL_FALSE, EGLContext, eglGetCurrentContext, (void))
_COREGL_SYMBOL(GL_FALSE, EGLSurface, eglGetCurrentSurface, (EGLint readdraw))
_COREGL_SYMBOL(GL_FALSE, EGLDisplay, eglGetCurrentDisplay, (void))

_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglQueryContext, (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglWaitGL, (void))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglWaitNative, (EGLint engine))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglSwapBuffers, (EGLDisplay dpy, EGLSurface surface))
_COREGL_SYMBOL(GL_FALSE, EGLBoolean, eglCopyBuffers, (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target))

_COREGL_SYMBOL(GL_FALSE, _eng_fn, eglGetProcAddress, (const char* procname))


// Extensions
_COREGL_EXT_SYMBOL(GL_TRUE, EGLImageKHR, eglCreateImageKHR, (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list))
_COREGL_EXT_SYMBOL(GL_TRUE, EGLBoolean, eglDestroyImageKHR, (EGLDisplay dpy, EGLImageKHR image))

_COREGL_EXT_SYMBOL(GL_TRUE, void*, eglMapImageSEC, (EGLDisplay dpy, EGLImageKHR image, EGLint device_type, EGLint access_option))
_COREGL_EXT_SYMBOL(GL_TRUE, EGLBoolean, eglUnmapImageSEC, (EGLDisplay dpy, EGLImageKHR image, EGLint device_type))
_COREGL_EXT_SYMBOL(GL_TRUE, EGLBoolean, eglGetImageAttribSEC, (EGLDisplay dpy, EGLImageKHR image, EGLint attribute, EGLint *value))

_COREGL_EXT_SYMBOL(GL_TRUE, EGLBoolean, eglLockSurfaceKHR, (EGLDisplay display, EGLSurface surface, const EGLint *attrib_list))
_COREGL_EXT_SYMBOL(GL_TRUE, EGLBoolean, eglUnlockSurfaceKHR, (EGLDisplay display, EGLSurface surface))

/* Fastpath Verified extensions */
_COREGL_EXT_SYMBOL_FASTPATH_PASS(eglSwapBuffersRegionEXT)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(eglSwapBuffersRegionSEC)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(eglSwapBuffersWithDamageEXT)

/* Fastpath Blocked extensions */
//_COREGL_EXT_SYMBOL_FASTPATH_BLOCK()

#ifdef _COREGL_EXT_SYMBOL_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL
#endif

#ifdef _COREGL_SYMBOL_NOT_DEFINED
#undef _COREGL_SYMBOL_NOT_DEFINED
#undef _COREGL_SYMBOL
#endif

#ifdef _COREGL_EXT_SYMBOL_ALIAS_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL_ALIAS_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL_ALIAS
#endif

#ifdef _COREGL_EXT_SYMBOL_FASTPATH_PASS_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL_FASTPATH_PASS_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL_FASTPATH_PASS
#endif

#ifdef _COREGL_EXT_SYMBOL_FASTPATH_BLOCK_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL_FASTPATH_BLOCK_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL_FASTPATH_BLOCK
#endif

