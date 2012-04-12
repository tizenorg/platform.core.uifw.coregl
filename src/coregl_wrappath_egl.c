#include "coregl_wrappath.h"

EGLint
eglGetError(void)
{
	EGLint ret = _COREGL_INT_INIT_VALUE;

	_COREGL_WRAP_FUNC_BEGIN();
	if (api_opt == COREGL_UNKNOWN_PATH) goto finish;
	ret = ovr_eglGetError();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLDisplay
eglGetDisplay(EGLNativeDisplayType display_id)
{
	EGLDisplay ret = EGL_NO_DISPLAY;

	_COREGL_WRAP_FUNC_BEGIN();
	if (api_opt == COREGL_UNKNOWN_PATH) goto finish;
	ret = ovr_eglGetDisplay(display_id);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglInitialize(EGLDisplay dpy, EGLint* major, EGLint* minor)
{
	EGLBoolean ret = EGL_FALSE;
	_COREGL_WRAP_FUNC_BEGIN();
	if (api_opt == COREGL_UNKNOWN_PATH) goto finish;
	ret = ovr_eglInitialize(dpy, major, minor);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglTerminate(EGLDisplay dpy)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	if (api_opt == COREGL_UNKNOWN_PATH) goto finish;
	ret = ovr_eglTerminate(dpy);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglGetConfigs(dpy, configs, config_size, num_config);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglChooseConfig(EGLDisplay dpy, const EGLint* attrib_list, EGLConfig* configs, EGLint config_size, EGLint* num_config)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglChooseConfig(dpy, attrib_list, configs, config_size, num_config);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglGetConfigAttrib(dpy, config, attribute, value);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}


EGLSurface
eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint* attrib_list)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglCreateWindowSurface(dpy, config, win, attrib_list);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLSurface
eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglCreatePbufferSurface(dpy, config, attrib_list);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLSurface
eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint* attrib_list)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglCreatePixmapSurface(dpy, config, pixmap, attrib_list);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglDestroySurface(dpy, surface);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglQuerySurface(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglQuerySurface(dpy, surface, attribute, value);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglBindAPI(EGLenum api)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	if (api_opt == COREGL_UNKNOWN_PATH) goto finish;
	ret = ovr_eglBindAPI(api);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLenum
eglQueryAPI(void)
{
	EGLenum ret = 0;

	_COREGL_WRAP_FUNC_BEGIN();
	if (api_opt == COREGL_UNKNOWN_PATH) goto finish;
	ret = ovr_eglQueryAPI();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglWaitClient(void)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglWaitClient();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglReleaseThread(void)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglReleaseThread();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLSurface
eglCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglCreatePbufferFromClientBuffer(dpy, buftype, buffer, config, attrib_list);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglSurfaceAttrib(dpy, surface, attribute, value);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_eglBindTexImage(dpy, surface, buffer);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

EGLBoolean
eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglReleaseTexImage(dpy, surface, buffer);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglSwapInterval(EGLDisplay dpy, EGLint interval)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglSwapInterval(dpy, interval);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLContext
eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint* attrib_list)
{
	EGLContext ret = EGL_NO_CONTEXT;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglCreateContext(dpy, config, share_context, attrib_list);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglDestroyContext(dpy, ctx);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglMakeCurrent(dpy, draw, read, ctx);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
#ifdef COREGL_TRACE_STATE_INFO
	if (ovr_eglMakeCurrent == _sym_eglMakeCurrent)
		dump_wrap_context_states(0);
#endif // COREGL_TRACE_STATE_INFO
	return ret;
}

EGLContext
eglGetCurrentContext(void)
{
	EGLContext ret = EGL_NO_CONTEXT;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglGetCurrentContext();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLSurface
eglGetCurrentSurface(EGLint readdraw)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglGetCurrentSurface(readdraw);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLDisplay
eglGetCurrentDisplay(void)
{
	EGLDisplay ret = EGL_NO_DISPLAY;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglGetCurrentDisplay();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglQueryContext(dpy, ctx, attribute, value);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglWaitGL(void)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglWaitGL();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglWaitNative(EGLint engine)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglWaitNative(engine);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglSwapBuffers(dpy, surface);

	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	_COREGL_TRACE_API_OUTPUT(0);
	return ret;
}

EGLBoolean
eglCopyBuffers(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglCopyBuffers(dpy, surface, target);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

_eng_fn
eglGetProcAddress(const char* procname)
{
	_eng_fn ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	if (api_opt == COREGL_UNKNOWN_PATH) goto finish;
	ret = ovr_eglGetProcAddress(procname);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

const char *
eglQueryString(EGLDisplay dpy, EGLint name)
{
	const char *ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	if (api_opt == COREGL_UNKNOWN_PATH) goto finish;
	ret = ovr_eglQueryString(dpy, name);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLImageKHR
eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list)
{
	void *ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglCreateImageKHR(dpy, ctx, target, buffer, attrib_list);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglDestroyImageKHR(EGLDisplay dpy, EGLImageKHR image)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglDestroyImageKHR(dpy, image);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void *
eglMapImageSEC(EGLDisplay dpy, EGLImageKHR image)
{
	void *ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglMapImageSEC(dpy, image);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglUnmapImageSEC(EGLDisplay dpy, EGLImageKHR image)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglUnmapImageSEC(dpy, image);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglGetImageAttribSEC(EGLDisplay dpy, EGLImageKHR image, EGLint attribute, EGLint *value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglGetImageAttribSEC(dpy, image, attribute, value);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglLockSurfaceKHR(EGLDisplay display, EGLSurface surface, const EGLint *attrib_list)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglLockSurfaceKHR(display, surface, attrib_list);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
eglUnlockSurfaceKHR(EGLDisplay display, EGLSurface surface)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_eglUnlockSurfaceKHR(display, surface);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

