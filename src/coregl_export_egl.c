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
coregl_api_eglGetError(void)
{
	INIT_EXPORT();
	return ovr_eglGetError();
}

EGLDisplay
coregl_api_eglGetDisplay(EGLNativeDisplayType display_id)
{
	INIT_EXPORT();
	return ovr_eglGetDisplay(display_id);
}

EGLBoolean
coregl_api_eglInitialize(EGLDisplay dpy, EGLint* major, EGLint* minor)
{
	INIT_EXPORT();
	return ovr_eglInitialize(dpy, major, minor);
}

EGLBoolean
coregl_api_eglTerminate(EGLDisplay dpy)
{
	INIT_EXPORT();
	return ovr_eglTerminate(dpy);
}

EGLBoolean
coregl_api_eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
	INIT_EXPORT();
	return ovr_eglGetConfigs(dpy, configs, config_size, num_config);
}

EGLBoolean
coregl_api_eglChooseConfig(EGLDisplay dpy, const EGLint* attrib_list, EGLConfig* configs, EGLint config_size, EGLint* num_config)
{
	INIT_EXPORT();
	return ovr_eglChooseConfig(dpy, attrib_list, configs, config_size, num_config);
}

EGLBoolean
coregl_api_eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
{
	INIT_EXPORT();
	return ovr_eglGetConfigAttrib(dpy, config, attribute, value);
}


EGLSurface
coregl_api_eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint* attrib_list)
{
	INIT_EXPORT();
	return ovr_eglCreateWindowSurface(dpy, config, win, attrib_list);
}

EGLSurface
coregl_api_eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
	INIT_EXPORT();
	return ovr_eglCreatePbufferSurface(dpy, config, attrib_list);
}

EGLSurface
coregl_api_eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint* attrib_list)
{
	INIT_EXPORT();
	return ovr_eglCreatePixmapSurface(dpy, config, pixmap, attrib_list);
}

EGLBoolean
coregl_api_eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
	INIT_EXPORT();
	return ovr_eglDestroySurface(dpy, surface);
}

EGLBoolean
coregl_api_eglQuerySurface(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value)
{
	INIT_EXPORT();
	return ovr_eglQuerySurface(dpy, surface, attribute, value);
}

EGLBoolean
coregl_api_eglBindAPI(EGLenum api)
{
	INIT_EXPORT();
	return ovr_eglBindAPI(api);
}

EGLenum
coregl_api_eglQueryAPI(void)
{
	INIT_EXPORT();
	return ovr_eglQueryAPI();
}

EGLBoolean
coregl_api_eglWaitClient(void)
{
	INIT_EXPORT();
	return ovr_eglWaitClient();
}

EGLBoolean
coregl_api_eglReleaseThread(void)
{
	INIT_EXPORT();
	return ovr_eglReleaseThread();
}

EGLSurface
coregl_api_eglCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list)
{
	INIT_EXPORT();
	return ovr_eglCreatePbufferFromClientBuffer(dpy, buftype, buffer, config, attrib_list);
}

EGLBoolean
coregl_api_eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value)
{
	INIT_EXPORT();
	return ovr_eglSurfaceAttrib(dpy, surface, attribute, value);
}

EGLBoolean
coregl_api_eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
	INIT_EXPORT();
	return ovr_eglBindTexImage(dpy, surface, buffer);
}

EGLBoolean
coregl_api_eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
	INIT_EXPORT();
	return ovr_eglReleaseTexImage(dpy, surface, buffer);
}

EGLBoolean
coregl_api_eglSwapInterval(EGLDisplay dpy, EGLint interval)
{
	INIT_EXPORT();
	return ovr_eglSwapInterval(dpy, interval);
}

EGLContext
coregl_api_eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint* attrib_list)
{
	INIT_EXPORT();
	return ovr_eglCreateContext(dpy, config, share_context, attrib_list);
}

EGLBoolean
coregl_api_eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
	INIT_EXPORT();
	return ovr_eglDestroyContext(dpy, ctx);
}

EGLBoolean
coregl_api_eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
	INIT_EXPORT();
	return ovr_eglMakeCurrent(dpy, draw, read, ctx);
}

EGLContext
coregl_api_eglGetCurrentContext(void)
{
	INIT_EXPORT();
	return ovr_eglGetCurrentContext();
}

EGLSurface
coregl_api_eglGetCurrentSurface(EGLint readdraw)
{
	INIT_EXPORT();
	return ovr_eglGetCurrentSurface(readdraw);
}

EGLDisplay
coregl_api_eglGetCurrentDisplay(void)
{
	INIT_EXPORT();
	return ovr_eglGetCurrentDisplay();
}

EGLBoolean
coregl_api_eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value)
{
	INIT_EXPORT();
	return ovr_eglQueryContext(dpy, ctx, attribute, value);
}

EGLBoolean
coregl_api_eglWaitGL(void)
{
	INIT_EXPORT();
	return ovr_eglWaitGL();
}

EGLBoolean
coregl_api_eglWaitNative(EGLint engine)
{
	INIT_EXPORT();
	return ovr_eglWaitNative(engine);
}

EGLBoolean
coregl_api_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
	INIT_EXPORT();
	return ovr_eglSwapBuffers(dpy, surface);
}

EGLBoolean
coregl_api_eglCopyBuffers(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target)
{
	INIT_EXPORT();
	return ovr_eglCopyBuffers(dpy, surface, target);
}

_eng_fn
coregl_api_eglGetProcAddress(const char* procname)
{
	INIT_EXPORT();
	return ovr_eglGetProcAddress(procname);
}

const char *
coregl_api_eglQueryString(EGLDisplay dpy, EGLint name)
{
	INIT_EXPORT();
	return ovr_eglQueryString(dpy, name);
}

