#include "coregl_internal.h"
#include "coregl_wrappath.h"
#include "coregl_fastpath.h"

#include <stdlib.h>

#define COREGL_OVERRIDE_API(func, prefix) \
   _COREGL_NAME_MANGLE(func) = prefix##func

void
override_glue_normal_path()
{
#define N_ORD(f) COREGL_OVERRIDE_API(f, _sym_) // GL Normal Path

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     N_ORD(FUNC_NAME);
# ifndef _COREGL_DESKTOP_GL
#  include "headers/sym_egl.h"
# else
#  include "headers/sym_glx.h"
# endif
#undef _COREGL_SYMBOL

#undef N_ORD
}

void
override_glue_fast_path()
{
	// Inherit from normal path
	override_glue_normal_path();

#define F_ORD(f) COREGL_OVERRIDE_API(f, fpgl_) // GL Fast Path


#ifndef _COREGL_DESKTOP_GL
	// Fast-Path Core Functions
	F_ORD(eglGetProcAddress);

	F_ORD(eglBindAPI);
	F_ORD(eglQueryAPI);

	F_ORD(eglCreateContext);
	F_ORD(eglCreateImageKHR);
	F_ORD(eglMakeCurrent);
	F_ORD(eglDestroyContext);
	F_ORD(eglQueryContext);
	F_ORD(eglGetCurrentContext);
	F_ORD(eglReleaseThread);
	F_ORD(eglGetCurrentSurface);

#else
	// Fastpath-ed Functions
	F_ORD(glXCreateContext);
	F_ORD(glXDestroyContext);
	F_ORD(glXMakeCurrent);
	F_ORD(glXGetCurrentContext);
	F_ORD(glXGetCurrentDrawable);

	F_ORD(glXMakeContextCurrent);
#endif

#undef F_ORD
}

void
override_gl_normal_path()
{
#define N_ORD(f) COREGL_OVERRIDE_API(f, _sym_) // GL Normal Path

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     N_ORD(FUNC_NAME);
# include "headers/sym_gl.h"
#undef _COREGL_SYMBOL

#undef N_ORD
}

void
override_gl_fast_path()
{
	// Inherit from normal path
	override_gl_normal_path();

#define F_ORD(f) COREGL_OVERRIDE_API(f, fpgl_) // GL Wrapped Path

	// Fast-Path Functions
	if (debug_nofp != 1)
	{
		F_ORD(glGetError);

		F_ORD(glActiveTexture);
		F_ORD(glGenTextures);
		F_ORD(glBindTexture);
		F_ORD(glIsTexture);
		F_ORD(glFramebufferTexture2D);
		F_ORD(glDeleteTextures);

		F_ORD(glGenBuffers);
		F_ORD(glBindBuffer);
		F_ORD(glIsBuffer);
		F_ORD(glDeleteBuffers);

		F_ORD(glGenFramebuffers);
		F_ORD(glBindFramebuffer);
		F_ORD(glIsFramebuffer);
		F_ORD(glDeleteFramebuffers);

		F_ORD(glGenRenderbuffers);
		F_ORD(glBindRenderbuffer);
		F_ORD(glFramebufferRenderbuffer);
		F_ORD(glIsRenderbuffer);
		F_ORD(glDeleteRenderbuffers);

		F_ORD(glCreateShader);
		F_ORD(glCreateProgram);
		F_ORD(glAttachShader);
		F_ORD(glCompileShader);
		F_ORD(glShaderBinary);
		F_ORD(glDeleteShader);
		F_ORD(glDetachShader);
		F_ORD(glGetShaderiv);
		F_ORD(glGetShaderInfoLog);
		F_ORD(glGetShaderSource);
		F_ORD(glIsShader);
		F_ORD(glShaderSource);
		F_ORD(glBindAttribLocation);
		F_ORD(glDeleteProgram);
		F_ORD(glDetachShader);
		F_ORD(glGetActiveAttrib);
		F_ORD(glGetActiveUniform);
		F_ORD(glGetAttachedShaders);
		F_ORD(glGetAttribLocation);
		F_ORD(glGetProgramiv);
		F_ORD(glGetProgramInfoLog);
		F_ORD(glGetUniformfv);
		F_ORD(glGetUniformiv);
		F_ORD(glGetUniformLocation);
		F_ORD(glIsProgram);
		F_ORD(glLinkProgram);
		F_ORD(glUseProgram);
		F_ORD(glValidateProgram);
		F_ORD(glGetProgramBinary);
		F_ORD(glProgramBinary);

		F_ORD(glBlendColor);
		F_ORD(glBlendEquation);
		F_ORD(glBlendEquationSeparate);
		F_ORD(glBlendFunc);
		F_ORD(glBlendFuncSeparate);
		F_ORD(glClearColor);
		F_ORD(glClearDepthf);
		F_ORD(glClearStencil);
		F_ORD(glColorMask);
		F_ORD(glCullFace);
		F_ORD(glDepthFunc);
		F_ORD(glDepthMask);
		F_ORD(glDepthRangef);
		F_ORD(glDisable);
		F_ORD(glDisableVertexAttribArray);
		F_ORD(glDrawArrays);
		F_ORD(glDrawElements);
		F_ORD(glEnable);
		F_ORD(glEnableVertexAttribArray);
		F_ORD(glFrontFace);
		F_ORD(glGetVertexAttribfv);
		F_ORD(glGetVertexAttribiv);
		F_ORD(glGetVertexAttribPointerv);
		F_ORD(glHint);
		F_ORD(glLineWidth);
		F_ORD(glPixelStorei);
		F_ORD(glPolygonOffset);
		F_ORD(glSampleCoverage);
		F_ORD(glScissor);
		F_ORD(glStencilFunc);
		F_ORD(glStencilFuncSeparate);
		F_ORD(glStencilMask);
		F_ORD(glStencilMaskSeparate);
		F_ORD(glStencilOp);
		F_ORD(glStencilOpSeparate);
		F_ORD(glVertexAttrib1f);
		F_ORD(glVertexAttrib1fv);
		F_ORD(glVertexAttrib2f);
		F_ORD(glVertexAttrib2fv);
		F_ORD(glVertexAttrib3f);
		F_ORD(glVertexAttrib3fv);
		F_ORD(glVertexAttrib4f);
		F_ORD(glVertexAttrib4fv);
		F_ORD(glVertexAttribPointer);
		F_ORD(glViewport);

		F_ORD(glGetIntegerv);
		F_ORD(glGetFloatv);
		F_ORD(glGetBooleanv);

		F_ORD(glEGLImageTargetTexture2DOES);
		F_ORD(glFramebufferTexture2DMultisampleEXT);

	}
	else
	{
		LOG("\E[0;35;1m[CoreGL] SKIP GL FASTPATH...\E[0m\n");
	}

#undef F_ORD
}


void
override_glue_apis(CoreGL_Opt_Flag opt)
{
	switch (opt)
	{
		case COREGL_NORMAL_PATH:
			override_glue_normal_path();
			break;
		case COREGL_FAST_PATH:
			override_glue_fast_path();
			break;
		default:
			ERR("Invalide GL Override Option!!!\n");
	}
}

void
override_gl_apis(CoreGL_Opt_Flag opt)
{
	switch (opt)
	{
		case COREGL_NORMAL_PATH:
			override_gl_normal_path();
			break;
		case COREGL_FAST_PATH:
			override_gl_fast_path();
			break;
		default:
			ERR("Invalide GL Override Option!!!\n");
	}
}

