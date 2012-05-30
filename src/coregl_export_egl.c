#include "coregl_export.h"

EGLint
eglGetError(void)
{
	return ovr_eglGetError();
}

EGLDisplay
eglGetDisplay(EGLNativeDisplayType display_id)
{
	return ovr_eglGetDisplay(display_id);
}

EGLBoolean
eglInitialize(EGLDisplay dpy, EGLint* major, EGLint* minor)
{
	return ovr_eglInitialize(dpy, major, minor);
}

EGLBoolean
eglTerminate(EGLDisplay dpy)
{
	return ovr_eglTerminate(dpy);
}

EGLBoolean
eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
	return ovr_eglGetConfigs(dpy, configs, config_size, num_config);
}

EGLBoolean
eglChooseConfig(EGLDisplay dpy, const EGLint* attrib_list, EGLConfig* configs, EGLint config_size, EGLint* num_config)
{
	return ovr_eglChooseConfig(dpy, attrib_list, configs, config_size, num_config);
}

EGLBoolean
eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
{
	return ovr_eglGetConfigAttrib(dpy, config, attribute, value);
}


EGLSurface
eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint* attrib_list)
{
	return ovr_eglCreateWindowSurface(dpy, config, win, attrib_list);
}

EGLSurface
eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
	return ovr_eglCreatePbufferSurface(dpy, config, attrib_list);
}

EGLSurface
eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint* attrib_list)
{
	return ovr_eglCreatePixmapSurface(dpy, config, pixmap, attrib_list);
}

EGLBoolean
eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
	return ovr_eglDestroySurface(dpy, surface);
}

EGLBoolean
eglQuerySurface(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value)
{
	return ovr_eglQuerySurface(dpy, surface, attribute, value);
}

EGLBoolean
eglBindAPI(EGLenum api)
{
	return ovr_eglBindAPI(api);
}

EGLenum
eglQueryAPI(void)
{
	return ovr_eglQueryAPI();
}

EGLBoolean
eglWaitClient(void)
{
	return ovr_eglWaitClient();
}

EGLBoolean
eglReleaseThread(void)
{
	return ovr_eglReleaseThread();
}

EGLSurface
eglCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list)
{
	return ovr_eglCreatePbufferFromClientBuffer(dpy, buftype, buffer, config, attrib_list);
}

EGLBoolean
eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value)
{
	return ovr_eglSurfaceAttrib(dpy, surface, attribute, value);
}

EGLBoolean
eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
	return ovr_eglBindTexImage(dpy, surface, buffer);
}

EGLBoolean
eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
	return ovr_eglReleaseTexImage(dpy, surface, buffer);
}

EGLBoolean
eglSwapInterval(EGLDisplay dpy, EGLint interval)
{
	return ovr_eglSwapInterval(dpy, interval);
}

EGLContext
eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint* attrib_list)
{
	return ovr_eglCreateContext(dpy, config, share_context, attrib_list);
}

EGLBoolean
eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
	return ovr_eglDestroyContext(dpy, ctx);
}

EGLBoolean
eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
	return ovr_eglMakeCurrent(dpy, draw, read, ctx);
}

EGLContext
eglGetCurrentContext(void)
{
	return ovr_eglGetCurrentContext();
}

EGLSurface
eglGetCurrentSurface(EGLint readdraw)
{
	return ovr_eglGetCurrentSurface(readdraw);
}

EGLDisplay
eglGetCurrentDisplay(void)
{
	return ovr_eglGetCurrentDisplay();
}

EGLBoolean
eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value)
{
	return ovr_eglQueryContext(dpy, ctx, attribute, value);
}

EGLBoolean
eglWaitGL(void)
{
	return ovr_eglWaitGL();
}

EGLBoolean
eglWaitNative(EGLint engine)
{
	return ovr_eglWaitNative(engine);
}

EGLBoolean
eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
	return ovr_eglSwapBuffers(dpy, surface);
}

EGLBoolean
eglCopyBuffers(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target)
{
	return ovr_eglCopyBuffers(dpy, surface, target);
}

_eng_fn
eglGetProcAddress(const char* procname)
{
	return ovr_eglGetProcAddress(procname);
}

const char *
eglQueryString(EGLDisplay dpy, EGLint name)
{
	return ovr_eglQueryString(dpy, name);
}

EGLImageKHR
eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list)
{
	return ovr_eglCreateImageKHR(dpy, ctx, target, buffer, attrib_list);
}

EGLBoolean
eglDestroyImageKHR(EGLDisplay dpy, EGLImageKHR image)
{
	return ovr_eglDestroyImageKHR(dpy, image);
}

void *
eglMapImageSEC(EGLDisplay dpy, EGLImageKHR image)
{
	return ovr_eglMapImageSEC(dpy, image);
}

EGLBoolean
eglUnmapImageSEC(EGLDisplay dpy, EGLImageKHR image)
{
	return ovr_eglUnmapImageSEC(dpy, image);
}

EGLBoolean
eglGetImageAttribSEC(EGLDisplay dpy, EGLImageKHR image, EGLint attribute, EGLint *value)
{
	return ovr_eglGetImageAttribSEC(dpy, image, attribute, value);
}

EGLBoolean
eglLockSurfaceKHR(EGLDisplay display, EGLSurface surface, const EGLint *attrib_list)
{
	return ovr_eglLockSurfaceKHR(display, surface, attrib_list);
}

EGLBoolean
eglUnlockSurfaceKHR(EGLDisplay display, EGLSurface surface)
{
	return ovr_eglUnlockSurfaceKHR(display, surface);
}

