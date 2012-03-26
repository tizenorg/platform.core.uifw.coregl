#include "coregl_wrappath.h"

_eng_fn
glXGetProcAddress(const char* procName)
{
	_eng_fn ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXGetProcAddress(procName);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

XVisualInfo*
glXChooseVisual(Display* dpy, int screen, int* attribList)
{
	XVisualInfo *ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXChooseVisual(dpy, screen, attribList);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLXContext
glXCreateContext(Display* dpy, XVisualInfo* vis, GLXContext shareList, Bool direct)
{
	GLXContext ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXCreateContext(dpy, vis, shareList, direct);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
glXDestroyContext(Display* dpy, GLXContext ctx)
{
	_COREGL_WRAP_FUNC_BEGIN();
	glsym_glXDestroyContext(dpy, ctx);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

GLXContext
glXGetCurrentContext(void)
{
	GLXContext ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXGetCurrentContext();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLXDrawable
glXGetCurrentDrawable(void)
{
	GLXDrawable ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXGetCurrentDrawable();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}


Bool
glXMakeCurrent(Display* dpy, GLXDrawable draw, GLXContext ctx)
{
	Bool ret = False;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXMakeCurrent(dpy, draw, ctx);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glXSwapBuffers(Display* dpy, GLXDrawable draw)
{
	_COREGL_WRAP_FUNC_BEGIN();
	glsym_glXSwapBuffers(dpy, draw);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glXWaitX(void)
{
	_COREGL_WRAP_FUNC_BEGIN();
	glsym_glXWaitX();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glXWaitGL(void)
{
	_COREGL_WRAP_FUNC_BEGIN();
	glsym_glXWaitGL();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

Bool
glXQueryExtension(Display* dpy, int* errorb, int* event)
{
	Bool ret = False;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXQueryExtension(dpy, errorb, event);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

const char *
glXQueryExtensionsString(Display *dpy, int screen)
{
	const char *ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXQueryExtensionsString(dpy, screen);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLXFBConfig*
glXChooseFBConfig(Display* dpy, int screen, const int* attribList, int* nitems)
{
	GLXFBConfig *ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXChooseFBConfig(dpy, screen, attribList, nitems);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLXFBConfig*
glXGetFBConfigs(Display* dpy, int screen, int* nelements)
{
	GLXFBConfig *ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXGetFBConfigs(dpy, screen, nelements);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

//!!!!! FIXME Called too many times
int
glXGetFBConfigAttrib(Display* dpy, GLXFBConfig config, int attribute, int* value)
{
	int ret = _COREGL_INT_INIT_VALUE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXGetFBConfigAttrib(dpy, config, attribute, value);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

//!!!!! FIXME Called too many times
XVisualInfo*
glXGetVisualFromFBConfig(Display* dpy, GLXFBConfig config)
{
	XVisualInfo *ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXGetVisualFromFBConfig(dpy, config);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
glXDestroyWindow(Display* dpy, GLXWindow window)
{
	_COREGL_WRAP_FUNC_BEGIN();
	glsym_glXDestroyWindow(dpy, window);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

Bool
glXMakeContextCurrent(Display* dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx)
{
	Bool ret = False;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXMakeContextCurrent(dpy, draw, read, ctx);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
glXBindTexImage(Display* dpy, GLXDrawable draw, int buffer, int* attribList)
{
	_COREGL_WRAP_FUNC_BEGIN();
	glsym_glXBindTexImage(dpy, draw, buffer, attribList);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glXReleaseTexImage(Display* dpy, GLXDrawable draw, int buffer)
{
	_COREGL_WRAP_FUNC_BEGIN();
	glsym_glXReleaseTexImage(dpy, draw, buffer);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

int
glXGetVideoSync(unsigned int* count)
{
	int ret = _COREGL_INT_INIT_VALUE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXGetVideoSync(count);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

int
glXWaitVideoSync(int divisor, int remainder, unsigned int* count)
{
	int ret = _COREGL_INT_INIT_VALUE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXWaitVideoSync(divisor, remainder, count);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

XID
glXCreatePixmap(Display* dpy, void* config, Pixmap pixmap, const int* attribList)
{
	XID ret = None;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXCreatePixmap(dpy, config, pixmap, attribList);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
glXDestroyPixmap(Display* dpy, XID pixmap)
{
	_COREGL_WRAP_FUNC_BEGIN();
	glsym_glXDestroyPixmap(dpy, pixmap);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glXQueryDrawable(Display* dpy, XID draw, int attribute, unsigned int* value)
{
	_COREGL_WRAP_FUNC_BEGIN();
	glsym_glXQueryDrawable(dpy, draw, attribute, value);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

int
glXSwapIntervalSGI(int interval)
{
	int ret = _COREGL_INT_INIT_VALUE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = glsym_glXSwapIntervalSGI(interval);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
glXSwapIntervalEXT(Display* dpy, GLXDrawable draw, int interval)
{
	_COREGL_WRAP_FUNC_BEGIN();
	glsym_glXSwapIntervalEXT(dpy, draw, interval);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

