#include "coregl_wrappath.h"

void
wpgl_glActiveTexture(GLenum texture)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glActiveTexture(texture);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glAttachShader(GLuint program, GLuint shader)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glAttachShader(program, shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glBindAttribLocation(GLuint program, GLuint index, const char* name)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glBindAttribLocation(program, index, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glBindBuffer(GLenum target, GLuint buffer)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glBindBuffer(target, buffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glBindFramebuffer(target, framebuffer);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glBindRenderbuffer(target, renderbuffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glBindTexture(GLenum target, GLuint texture)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glBindTexture(target, texture);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glBlendColor(red, green, blue, alpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glBlendEquation(GLenum mode)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glBlendEquation(mode);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glBlendEquationSeparate(modeRGB, modeAlpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glBlendFunc(sfactor, dfactor);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glBufferData(target, size, data, usage);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glBufferSubData(target, offset, size, data);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

GLenum
wpgl_glCheckFramebufferStatus(GLenum target)
{
	GLenum ret = GL_NONE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_glCheckFramebufferStatus(target);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
wpgl_glClear(GLbitfield mask)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glClear(mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glClearColor(red, green, blue, alpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glClearDepthf(GLclampf depth)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glClearDepthf(depth);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glClearStencil(GLint s)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glClearStencil(s);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glColorMask(red, green, blue, alpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glCompileShader(GLuint shader)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glCompileShader(shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

GLuint
wpgl_glCreateProgram(void)
{
	GLuint ret = _COREGL_INT_INIT_VALUE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_glCreateProgram();
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLuint
wpgl_glCreateShader(GLenum type)
{
	GLuint ret = _COREGL_INT_INIT_VALUE;
	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_glCreateShader(type);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
wpgl_glCullFace(GLenum mode)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glCullFace(mode);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDeleteBuffers(n, buffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDeleteFramebuffers(n, framebuffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDeleteProgram(GLuint program)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDeleteProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDeleteRenderbuffers(n, renderbuffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDeleteShader(GLuint shader)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDeleteShader(shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDeleteTextures(GLsizei n, const GLuint* textures)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDeleteTextures(n, textures);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDepthFunc(GLenum func)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDepthFunc(func);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDepthMask(GLboolean flag)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDepthMask(flag);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDepthRangef(GLclampf zNear, GLclampf zFar)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDepthRangef(zNear, zFar);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDetachShader(GLuint program, GLuint shader)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDetachShader(program, shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDisable(GLenum cap)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDisable(cap);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDisableVertexAttribArray(GLuint index)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDisableVertexAttribArray(index);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDrawArrays(mode, first, count);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDrawElements(mode, count, type, indices);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glEnable(GLenum cap)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glEnable(cap);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glEnableVertexAttribArray(GLuint index)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glEnableVertexAttribArray(index);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glFinish(void)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glFinish();
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	_COREGL_TRACE_API_OUTPUT(0);
}

void
wpgl_glFlush(void)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glFlush();
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	_COREGL_TRACE_API_OUTPUT(0);
}

void
wpgl_glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glFramebufferTexture2D(target, attachment, textarget, texture, level);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glFrontFace(GLenum mode)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glFrontFace(mode);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetVertexAttribfv(index, pname, params);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetVertexAttribiv(index, pname, params);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetVertexAttribPointerv(index, pname, pointer);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glHint(GLenum target, GLenum mode)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glHint(target, mode);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGenBuffers(GLsizei n, GLuint* buffers)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGenBuffers(n, buffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGenerateMipmap(GLenum target)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGenerateMipmap(target);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGenFramebuffers(n, framebuffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGenRenderbuffers(n, renderbuffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGenTextures(GLsizei n, GLuint* textures)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGenTextures(n, textures);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetActiveAttrib(program, index, bufsize, length, size, type, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetActiveUniform(program, index, bufsize, length, size, type, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetAttachedShaders(program, maxcount, count, shaders);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

int
wpgl_glGetAttribLocation(GLuint program, const char* name)
{
	int ret = _COREGL_INT_INIT_VALUE;
	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_glGetAttribLocation(program, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
wpgl_glGetBooleanv(GLenum pname, GLboolean* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetBooleanv(pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetBufferParameteriv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

GLenum
wpgl_glGetError(void)
{
	GLenum ret = GL_NONE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_glGetError();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
wpgl_glGetFloatv(GLenum pname, GLfloat* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetFloatv(pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetIntegerv(GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetIntegerv(pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetProgramiv(program, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetProgramInfoLog(program, bufsize, length, infolog);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetRenderbufferParameteriv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetShaderiv(shader, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetShaderInfoLog(shader, bufsize, length, infolog);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
{
	_COREGL_WRAP_FUNC_BEGIN();
#ifndef _COREGL_DESKTOP_GL
	wrp_glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
#else
	if (range)
	{
		range[0] = -126; // floor(log2(FLT_MIN))
		range[1] = 127; // floor(log2(FLT_MAX))
	}
	if (precision)
	{
		precision[0] = 24; // floor(-log2((1.0/16777218.0)));
	}
	return;
	shadertype = precisiontype = 0;
#endif

	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, char* source)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetShaderSource(shader, bufsize, length, source);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

const GLubyte *
wpgl_glGetString(GLenum name)
{
	const GLubyte *ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_glGetString(name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
wpgl_glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetTexParameterfv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetTexParameteriv(GLenum target, GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetTexParameteriv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetUniformfv(GLuint program, GLint location, GLfloat* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetUniformfv(program, location, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetUniformiv(GLuint program, GLint location, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetUniformiv(program, location, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}
int
wpgl_glGetUniformLocation(GLuint program, const char* name)
{
	int ret = _COREGL_INT_INIT_VALUE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_glGetUniformLocation(program, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLboolean
wpgl_glIsBuffer(GLuint buffer)
{
	GLboolean ret = GL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_glIsBuffer(buffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLboolean
wpgl_glIsEnabled(GLenum cap)
{
	GLboolean ret = GL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_glIsEnabled(cap);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLboolean
wpgl_glIsFramebuffer(GLuint framebuffer)
{
	GLboolean ret = GL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_glIsFramebuffer(framebuffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLboolean
wpgl_glIsProgram(GLuint program)
{
	GLboolean ret;
	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_glIsProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLboolean
wpgl_glIsRenderbuffer(GLuint renderbuffer)
{
	GLboolean ret;
	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_glIsRenderbuffer(renderbuffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLboolean
wpgl_glIsShader(GLuint shader)
{
	GLboolean ret;
	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_glIsShader(shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLboolean
wpgl_glIsTexture(GLuint texture)
{
	GLboolean ret;
	_COREGL_WRAP_FUNC_BEGIN();
	ret = wrp_glIsTexture(texture);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
wpgl_glLineWidth(GLfloat width)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glLineWidth(width);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glLinkProgram(GLuint program)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glLinkProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glPixelStorei(GLenum pname, GLint param)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glPixelStorei(pname, param);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glPolygonOffset(GLfloat factor, GLfloat units)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glPolygonOffset(factor, units);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glReadPixels(x, y, width, height, format, type, pixels);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glReleaseShaderCompiler(void)
{
	_COREGL_WRAP_FUNC_BEGIN();
#ifndef _COREGL_DESKTOP_GL
	wrp_glReleaseShaderCompiler();
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
#else
	//FIXME!!! need something here?

#endif
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glRenderbufferStorage(target, internalformat, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glSampleCoverage(GLclampf value, GLboolean invert)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glSampleCoverage(value, invert);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glScissor(x, y, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length)
{
	_COREGL_WRAP_FUNC_BEGIN();
#ifndef _COREGL_DESKTOP_GL
	wrp_glShaderBinary(n, shaders, binaryformat, binary, length);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
#else
// FIXME: need to dlsym/getprocaddress for this
	return;
	/*
	   n = binaryformat = length = 0;
	   shaders = binary = 0;
	*/
#endif
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glShaderSource(shader, count, string, length);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glStencilFunc(func, ref, mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glStencilFuncSeparate(face, func, ref, mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glStencilMask(GLuint mask)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glStencilMask(mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glStencilMaskSeparate(GLenum face, GLuint mask)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glStencilMaskSeparate(face, mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glStencilOp(fail, zfail, zpass);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glStencilOpSeparate(face, fail, zfail, zpass);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glTexParameterf(target, pname, param);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glTexParameterfv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glTexParameteri(GLenum target, GLenum pname, GLint param)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glTexParameteri(target, pname, param);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glTexParameteriv(GLenum target, GLenum pname, const GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glTexParameteriv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform1f(GLint location, GLfloat x)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform1f(location, x);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform1fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform1fv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform1i(GLint location, GLint x)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform1i(location, x);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform1iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform1iv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform2f(GLint location, GLfloat x, GLfloat y)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform2f(location, x, y);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform2fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform2fv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform2i(GLint location, GLint x, GLint y)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform2i(location, x, y);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform2iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform2iv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform3f(location, x, y, z);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform3fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform3fv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform3i(GLint location, GLint x, GLint y, GLint z)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform3i(location, x, y, z);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform3iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform3iv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform4f(location, x, y, z, w);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform4fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform4fv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform4i(location, x, y, z, w);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniform4iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniform4iv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniformMatrix2fv(location, count, transpose, value);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniformMatrix3fv(location, count, transpose, value);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUniformMatrix4fv(location, count, transpose, value);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glUseProgram(GLuint program)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glUseProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glValidateProgram(GLuint program)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glValidateProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glVertexAttrib1f(GLuint indx, GLfloat x)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glVertexAttrib1f(indx, x);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glVertexAttrib1fv(GLuint indx, const GLfloat* values)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glVertexAttrib1fv(indx, values);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glVertexAttrib2f(indx, x, y);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glVertexAttrib2fv(GLuint indx, const GLfloat* values)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glVertexAttrib2fv(indx, values);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glVertexAttrib3f(indx, x, y, z);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glVertexAttrib3fv(GLuint indx, const GLfloat* values)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glVertexAttrib3fv(indx, values);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glVertexAttrib4f(indx, x, y, z, w);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glVertexAttrib4fv(GLuint indx, const GLfloat* values)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glVertexAttrib4fv(indx, values);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glViewport(x, y, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}


// GLES Extensions...
void
wpgl_glEGLImageTargetTexture2DOES(GLenum target, GLeglImageOES image)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glEGLImageTargetTexture2DOES(target, image);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glEGLImageTargetRenderbufferStorageOES(GLenum target, GLeglImageOES image)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glEGLImageTargetRenderbufferStorageOES(target, image);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glGetProgramBinary(GLuint program, GLsizei bufsize, GLsizei* length, GLenum* binaryFormat, void* binary)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glGetProgramBinary(program, bufsize, length, binaryFormat, binary);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glProgramBinary(GLuint program, GLenum binaryFormat, const void* binary, GLint length)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glProgramBinary(program, binaryFormat, binary, length);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}


void
wpgl_glProgramParameteri(GLuint program, GLuint pname, GLint value)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glProgramParameteri(program, pname, value);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glRenderbufferStorageMultisampleEXT(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glRenderbufferStorageMultisampleEXT(target, samples, internalformat, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glFramebufferTexture2DMultisampleEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glFramebufferTexture2DMultisampleEXT(target, attachment, textarget, texture, level, samples);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
wpgl_glDiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum *attachments)
{
	_COREGL_WRAP_FUNC_BEGIN();
	wrp_glDiscardFramebufferEXT(target, numAttachments, attachments);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

