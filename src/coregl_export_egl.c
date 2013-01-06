#include "coregl_export.h"

Mutex init_export_mutex = MUTEX_INITIALIZER;

#define INIT_EXPORT() \
	if (unlikely(export_initialized == 0)) \
	{ \
		mutex_lock(&init_export_mutex); \
		if (export_initialized == 0) \
		{ \
			coregl_initialize(); \
			export_initialized = 1; \
		} \
		mutex_unlock(&init_export_mutex); \
	}

EGLint
eglGetError(void)
{
	INIT_EXPORT();
	return ovr_eglGetError();
}

EGLDisplay
eglGetDisplay(EGLNativeDisplayType display_id)
{
	INIT_EXPORT();
	return ovr_eglGetDisplay(display_id);
}

EGLBoolean
eglInitialize(EGLDisplay dpy, EGLint* major, EGLint* minor)
{
	INIT_EXPORT();
	return ovr_eglInitialize(dpy, major, minor);
}

EGLBoolean
eglTerminate(EGLDisplay dpy)
{
	INIT_EXPORT();
	return ovr_eglTerminate(dpy);
}

EGLBoolean
eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
	INIT_EXPORT();
	return ovr_eglGetConfigs(dpy, configs, config_size, num_config);
}

EGLBoolean
eglChooseConfig(EGLDisplay dpy, const EGLint* attrib_list, EGLConfig* configs, EGLint config_size, EGLint* num_config)
{
	INIT_EXPORT();
	return ovr_eglChooseConfig(dpy, attrib_list, configs, config_size, num_config);
}

EGLBoolean
eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
{
	INIT_EXPORT();
	return ovr_eglGetConfigAttrib(dpy, config, attribute, value);
}


EGLSurface
eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint* attrib_list)
{
	INIT_EXPORT();
	return ovr_eglCreateWindowSurface(dpy, config, win, attrib_list);
}

EGLSurface
eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
	INIT_EXPORT();
	return ovr_eglCreatePbufferSurface(dpy, config, attrib_list);
}

EGLSurface
eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint* attrib_list)
{
	INIT_EXPORT();
	return ovr_eglCreatePixmapSurface(dpy, config, pixmap, attrib_list);
}

EGLBoolean
eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
	INIT_EXPORT();
	return ovr_eglDestroySurface(dpy, surface);
}

EGLBoolean
eglQuerySurface(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value)
{
	INIT_EXPORT();
	return ovr_eglQuerySurface(dpy, surface, attribute, value);
}

EGLBoolean
eglBindAPI(EGLenum api)
{
	INIT_EXPORT();
	return ovr_eglBindAPI(api);
}

EGLenum
eglQueryAPI(void)
{
	INIT_EXPORT();
	return ovr_eglQueryAPI();
}

EGLBoolean
eglWaitClient(void)
{
	INIT_EXPORT();
	return ovr_eglWaitClient();
}

EGLBoolean
eglReleaseThread(void)
{
	INIT_EXPORT();
	return ovr_eglReleaseThread();
}

EGLSurface
eglCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list)
{
	INIT_EXPORT();
	return ovr_eglCreatePbufferFromClientBuffer(dpy, buftype, buffer, config, attrib_list);
}

EGLBoolean
eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value)
{
	INIT_EXPORT();
	return ovr_eglSurfaceAttrib(dpy, surface, attribute, value);
}

EGLBoolean
eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
	INIT_EXPORT();
	return ovr_eglBindTexImage(dpy, surface, buffer);
}

EGLBoolean
eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
	INIT_EXPORT();
	return ovr_eglReleaseTexImage(dpy, surface, buffer);
}

EGLBoolean
eglSwapInterval(EGLDisplay dpy, EGLint interval)
{
	INIT_EXPORT();
	return ovr_eglSwapInterval(dpy, interval);
}

EGLContext
eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint* attrib_list)
{
	INIT_EXPORT();
	return ovr_eglCreateContext(dpy, config, share_context, attrib_list);
}

EGLBoolean
eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
	INIT_EXPORT();
	return ovr_eglDestroyContext(dpy, ctx);
}

EGLBoolean
eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
	INIT_EXPORT();
	return ovr_eglMakeCurrent(dpy, draw, read, ctx);
}

EGLContext
eglGetCurrentContext(void)
{
	INIT_EXPORT();
	return ovr_eglGetCurrentContext();
}

EGLSurface
eglGetCurrentSurface(EGLint readdraw)
{
	INIT_EXPORT();
	return ovr_eglGetCurrentSurface(readdraw);
}

EGLDisplay
eglGetCurrentDisplay(void)
{
	INIT_EXPORT();
	return ovr_eglGetCurrentDisplay();
}

EGLBoolean
eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value)
{
	INIT_EXPORT();
	return ovr_eglQueryContext(dpy, ctx, attribute, value);
}

EGLBoolean
eglWaitGL(void)
{
	INIT_EXPORT();
	return ovr_eglWaitGL();
}

EGLBoolean
eglWaitNative(EGLint engine)
{
	INIT_EXPORT();
	return ovr_eglWaitNative(engine);
}

EGLBoolean
eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
	INIT_EXPORT();
	return ovr_eglSwapBuffers(dpy, surface);
}

EGLBoolean
eglCopyBuffers(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target)
{
	INIT_EXPORT();
	return ovr_eglCopyBuffers(dpy, surface, target);
}

_eng_fn
eglGetProcAddress(const char* procname)
{
	INIT_EXPORT();
	return ovr_eglGetProcAddress(procname);
}

const char *
eglQueryString(EGLDisplay dpy, EGLint name)
{
	INIT_EXPORT();
	return ovr_eglQueryString(dpy, name);
}

EGLImageKHR
eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list)
{
	INIT_EXPORT();
	return ovr_eglCreateImageKHR(dpy, ctx, target, buffer, attrib_list);
}

EGLBoolean
eglDestroyImageKHR(EGLDisplay dpy, EGLImageKHR image)
{
	INIT_EXPORT();
	return ovr_eglDestroyImageKHR(dpy, image);
}

void *
eglMapImageSEC(EGLDisplay dpy, EGLImageKHR image, EGLint device_type, EGLint access_option)
{
	INIT_EXPORT();
	return ovr_eglMapImageSEC(dpy, image, device_type, access_option);
}

EGLBoolean
eglUnmapImageSEC(EGLDisplay dpy, EGLImageKHR image, EGLint device_type)
{
	INIT_EXPORT();
	return ovr_eglUnmapImageSEC(dpy, image, device_type);
}

EGLBoolean
eglGetImageAttribSEC(EGLDisplay dpy, EGLImageKHR image, EGLint attribute, EGLint *value)
{
	INIT_EXPORT();
	return ovr_eglGetImageAttribSEC(dpy, image, attribute, value);
}

EGLBoolean
eglLockSurfaceKHR(EGLDisplay display, EGLSurface surface, const EGLint *attrib_list)
{
	INIT_EXPORT();
	return ovr_eglLockSurfaceKHR(display, surface, attrib_list);
}

EGLBoolean
eglUnlockSurfaceKHR(EGLDisplay display, EGLSurface surface)
{
	INIT_EXPORT();
	return ovr_eglUnlockSurfaceKHR(display, surface);
}

