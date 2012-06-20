#include "coregl_tracepath.h"

EGLint
tracepath_eglGetError(void)
{
	EGLint ret = _COREGL_INT_INIT_VALUE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglGetError();
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLDisplay
tracepath_eglGetDisplay(EGLNativeDisplayType display_id)
{
	EGLDisplay ret = EGL_NO_DISPLAY;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglGetDisplay(display_id);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglInitialize(EGLDisplay dpy, EGLint* major, EGLint* minor)
{
	EGLBoolean ret = EGL_FALSE;
	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglInitialize(dpy, major, minor);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglTerminate(EGLDisplay dpy)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglTerminate(dpy);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglGetConfigs(dpy, configs, config_size, num_config);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglChooseConfig(EGLDisplay dpy, const EGLint* attrib_list, EGLConfig* configs, EGLint config_size, EGLint* num_config)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglChooseConfig(dpy, attrib_list, configs, config_size, num_config);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglGetConfigAttrib(dpy, config, attribute, value);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}


EGLSurface
tracepath_eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint* attrib_list)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglCreateWindowSurface(dpy, config, win, attrib_list);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLSurface
tracepath_eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglCreatePbufferSurface(dpy, config, attrib_list);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLSurface
tracepath_eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint* attrib_list)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglCreatePixmapSurface(dpy, config, pixmap, attrib_list);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglDestroySurface(dpy, surface);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglQuerySurface(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglQuerySurface(dpy, surface, attribute, value);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglBindAPI(EGLenum api)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglBindAPI(api);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLenum
tracepath_eglQueryAPI(void)
{
	EGLenum ret = 0;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglQueryAPI();
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglWaitClient(void)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglWaitClient();
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglReleaseThread(void)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglReleaseThread();
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLSurface
tracepath_eglCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglCreatePbufferFromClientBuffer(dpy, buftype, buffer, config, attrib_list);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglSurfaceAttrib(dpy, surface, attribute, value);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglBindTexImage(dpy, surface, buffer);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglReleaseTexImage(dpy, surface, buffer);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglSwapInterval(EGLDisplay dpy, EGLint interval)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglSwapInterval(dpy, interval);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLContext
tracepath_eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint* attrib_list)
{
	EGLContext ret = EGL_NO_CONTEXT;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglCreateContext(dpy, config, share_context, attrib_list);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglDestroyContext(dpy, ctx);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglMakeCurrent(dpy, draw, read, ctx);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
#ifdef COREGL_TRACE_STATE_INFO
	if (unlikely(trace_state_flag == 1))
	{
		if (_orig_tracepath_eglMakeCurrent == _sym_eglMakeCurrent)
			tracepath_dump_context_states(0);
	}
#endif // COREGL_TRACE_STATE_INFO
	return ret;
}

EGLContext
tracepath_eglGetCurrentContext(void)
{
	EGLContext ret = EGL_NO_CONTEXT;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglGetCurrentContext();
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLSurface
tracepath_eglGetCurrentSurface(EGLint readdraw)
{
	EGLSurface ret = EGL_NO_SURFACE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglGetCurrentSurface(readdraw);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLDisplay
tracepath_eglGetCurrentDisplay(void)
{
	EGLDisplay ret = EGL_NO_DISPLAY;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglGetCurrentDisplay();
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglQueryContext(dpy, ctx, attribute, value);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglWaitGL(void)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglWaitGL();
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglWaitNative(EGLint engine)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglWaitNative(engine);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglSwapBuffers(dpy, surface);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	_COREGL_TRACE_API_OUTPUT(0);
	return ret;
}

EGLBoolean
tracepath_eglCopyBuffers(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglCopyBuffers(dpy, surface, target);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

_eng_fn
tracepath_eglGetProcAddress(const char* procname)
{
	_eng_fn ret = NULL;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglGetProcAddress(procname);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

const char *
tracepath_eglQueryString(EGLDisplay dpy, EGLint name)
{
	const char *ret = NULL;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglQueryString(dpy, name);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLImageKHR
tracepath_eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list)
{
	void *ret = NULL;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglCreateImageKHR(dpy, ctx, target, buffer, attrib_list);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglDestroyImageKHR(EGLDisplay dpy, EGLImageKHR image)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglDestroyImageKHR(dpy, image);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

void *
tracepath_eglMapImageSEC(EGLDisplay dpy, EGLImageKHR image)
{
	void *ret = NULL;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglMapImageSEC(dpy, image);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglUnmapImageSEC(EGLDisplay dpy, EGLImageKHR image)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglUnmapImageSEC(dpy, image);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglGetImageAttribSEC(EGLDisplay dpy, EGLImageKHR image, EGLint attribute, EGLint *value)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglGetImageAttribSEC(dpy, image, attribute, value);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglLockSurfaceKHR(EGLDisplay display, EGLSurface surface, const EGLint *attrib_list)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglLockSurfaceKHR(display, surface, attrib_list);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

EGLBoolean
tracepath_eglUnlockSurfaceKHR(EGLDisplay display, EGLSurface surface)
{
	EGLBoolean ret = EGL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_eglUnlockSurfaceKHR(display, surface);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

