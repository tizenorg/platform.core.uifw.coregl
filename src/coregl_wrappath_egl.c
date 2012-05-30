#include "coregl_wrappath.h"

EGLint
wpgl_eglGetError(void)
{
	EGLint ret = _COREGL_INT_INIT_VALUE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglGetError();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLDisplay
wpgl_eglGetDisplay(EGLNativeDisplayType display_id)
{
	EGLDisplay ret = EGL_NO_DISPLAY;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglGetDisplay(display_id);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglInitialize(EGLDisplay dpy, EGLint* major, EGLint* minor)
{
	EGLBoolean ret = EGL_FALSE;
	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglInitialize(dpy, major, minor);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglTerminate(EGLDisplay dpy)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglTerminate(dpy);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglGetConfigs(dpy, configs, config_size, num_config);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglChooseConfig(EGLDisplay dpy, const EGLint* attrib_list, EGLConfig* configs, EGLint config_size, EGLint* num_config)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglChooseConfig(dpy, attrib_list, configs, config_size, num_config);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglGetConfigAttrib(dpy, config, attribute, value);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}


EGLSurface
wpgl_eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint* attrib_list)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglCreateWindowSurface(dpy, config, win, attrib_list);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLSurface
wpgl_eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglCreatePbufferSurface(dpy, config, attrib_list);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLSurface
wpgl_eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint* attrib_list)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglCreatePixmapSurface(dpy, config, pixmap, attrib_list);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglDestroySurface(dpy, surface);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglQuerySurface(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglQuerySurface(dpy, surface, attribute, value);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglBindAPI(EGLenum api)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglBindAPI(api);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLenum
wpgl_eglQueryAPI(void)
{
	EGLenum ret = 0;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglQueryAPI();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglWaitClient(void)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglWaitClient();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglReleaseThread(void)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglReleaseThread();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLSurface
wpgl_eglCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglCreatePbufferFromClientBuffer(dpy, buftype, buffer, config, attrib_list);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglSurfaceAttrib(dpy, surface, attribute, value);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglBindTexImage(dpy, surface, buffer);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglReleaseTexImage(dpy, surface, buffer);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglSwapInterval(EGLDisplay dpy, EGLint interval)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglSwapInterval(dpy, interval);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLContext
wpgl_eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint* attrib_list)
{
	EGLContext ret = EGL_NO_CONTEXT;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglCreateContext(dpy, config, share_context, attrib_list);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglDestroyContext(dpy, ctx);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglMakeCurrent(dpy, draw, read, ctx);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
#ifdef COREGL_TRACE_STATE_INFO
	if (unlikely(trace_state_flag == 1))
	{
		if (wrp_eglMakeCurrent == _sym_eglMakeCurrent)
			dump_wrap_context_states(0);
	}
#endif // COREGL_TRACE_STATE_INFO
	return ret;
}

EGLContext
wpgl_eglGetCurrentContext(void)
{
	EGLContext ret = EGL_NO_CONTEXT;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglGetCurrentContext();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLSurface
wpgl_eglGetCurrentSurface(EGLint readdraw)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglGetCurrentSurface(readdraw);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLDisplay
wpgl_eglGetCurrentDisplay(void)
{
	EGLDisplay ret = EGL_NO_DISPLAY;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglGetCurrentDisplay();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglQueryContext(dpy, ctx, attribute, value);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglWaitGL(void)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglWaitGL();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglWaitNative(EGLint engine)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglWaitNative(engine);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglSwapBuffers(dpy, surface);

	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	_COREGL_TRACE_API_OUTPUT(0);
	return ret;
}

EGLBoolean
wpgl_eglCopyBuffers(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglCopyBuffers(dpy, surface, target);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

_eng_fn
wpgl_eglGetProcAddress(const char* procname)
{
	_eng_fn ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglGetProcAddress(procname);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

const char *
wpgl_eglQueryString(EGLDisplay dpy, EGLint name)
{
	const char *ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglQueryString(dpy, name);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLImageKHR
wpgl_eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list)
{
	void *ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglCreateImageKHR(dpy, ctx, target, buffer, attrib_list);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglDestroyImageKHR(EGLDisplay dpy, EGLImageKHR image)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglDestroyImageKHR(dpy, image);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void *
wpgl_eglMapImageSEC(EGLDisplay dpy, EGLImageKHR image)
{
	void *ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglMapImageSEC(dpy, image);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglUnmapImageSEC(EGLDisplay dpy, EGLImageKHR image)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglUnmapImageSEC(dpy, image);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglGetImageAttribSEC(EGLDisplay dpy, EGLImageKHR image, EGLint attribute, EGLint *value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglGetImageAttribSEC(dpy, image, attribute, value);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglLockSurfaceKHR(EGLDisplay display, EGLSurface surface, const EGLint *attrib_list)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglLockSurfaceKHR(display, surface, attrib_list);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

EGLBoolean
wpgl_eglUnlockSurfaceKHR(EGLDisplay display, EGLSurface surface)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_eglUnlockSurfaceKHR(display, surface);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

