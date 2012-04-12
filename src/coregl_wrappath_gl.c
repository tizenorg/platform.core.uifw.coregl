#include "coregl_wrappath.h"

void
glActiveTexture(GLenum texture)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glActiveTexture(texture);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glAttachShader(GLuint program, GLuint shader)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glAttachShader(program, shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glBindAttribLocation(GLuint program, GLuint index, const char* name)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glBindAttribLocation(program, index, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glBindBuffer(GLenum target, GLuint buffer)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glBindBuffer(target, buffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glBindFramebuffer(target, framebuffer);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glBindRenderbuffer(target, renderbuffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glBindTexture(GLenum target, GLuint texture)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glBindTexture(target, texture);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glBlendColor(red, green, blue, alpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glBlendEquation(GLenum mode)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glBlendEquation(mode);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glBlendEquationSeparate(modeRGB, modeAlpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glBlendFunc(sfactor, dfactor);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glBufferData(target, size, data, usage);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glBufferSubData(target, offset, size, data);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

GLenum
glCheckFramebufferStatus(GLenum target)
{
	GLenum ret = GL_NONE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_glCheckFramebufferStatus(target);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
glClear(GLbitfield mask)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glClear(mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glClearColor(red, green, blue, alpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glClearDepthf(GLclampf depth)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glClearDepthf(depth);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glClearStencil(GLint s)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glClearStencil(s);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glColorMask(red, green, blue, alpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glCompileShader(GLuint shader)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glCompileShader(shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

GLuint
glCreateProgram(void)
{
	GLuint ret = _COREGL_INT_INIT_VALUE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_glCreateProgram();
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLuint
glCreateShader(GLenum type)
{
	GLuint ret = _COREGL_INT_INIT_VALUE;
	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_glCreateShader(type);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
glCullFace(GLenum mode)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glCullFace(mode);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDeleteBuffers(n, buffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDeleteFramebuffers(n, framebuffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDeleteProgram(GLuint program)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDeleteProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDeleteRenderbuffers(n, renderbuffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDeleteShader(GLuint shader)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDeleteShader(shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDeleteTextures(GLsizei n, const GLuint* textures)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDeleteTextures(n, textures);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDepthFunc(GLenum func)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDepthFunc(func);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDepthMask(GLboolean flag)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDepthMask(flag);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDepthRangef(GLclampf zNear, GLclampf zFar)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDepthRangef(zNear, zFar);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDetachShader(GLuint program, GLuint shader)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDetachShader(program, shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDisable(GLenum cap)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDisable(cap);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDisableVertexAttribArray(GLuint index)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDisableVertexAttribArray(index);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDrawArrays(mode, first, count);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDrawElements(mode, count, type, indices);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glEnable(GLenum cap)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glEnable(cap);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glEnableVertexAttribArray(GLuint index)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glEnableVertexAttribArray(index);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glFinish(void)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glFinish();
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	_COREGL_TRACE_API_OUTPUT(0);
}

void
glFlush(void)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glFlush();
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	_COREGL_TRACE_API_OUTPUT(0);
}

void
glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glFramebufferTexture2D(target, attachment, textarget, texture, level);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glFrontFace(GLenum mode)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glFrontFace(mode);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetVertexAttribfv(index, pname, params);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetVertexAttribiv(index, pname, params);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetVertexAttribPointerv(index, pname, pointer);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glHint(GLenum target, GLenum mode)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glHint(target, mode);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGenBuffers(GLsizei n, GLuint* buffers)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGenBuffers(n, buffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGenerateMipmap(GLenum target)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGenerateMipmap(target);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGenFramebuffers(n, framebuffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGenRenderbuffers(n, renderbuffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGenTextures(GLsizei n, GLuint* textures)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGenTextures(n, textures);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetActiveAttrib(program, index, bufsize, length, size, type, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetActiveUniform(program, index, bufsize, length, size, type, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetAttachedShaders(program, maxcount, count, shaders);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

int
glGetAttribLocation(GLuint program, const char* name)
{
	int ret = _COREGL_INT_INIT_VALUE;
	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_glGetAttribLocation(program, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
glGetBooleanv(GLenum pname, GLboolean* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetBooleanv(pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetBufferParameteriv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

GLenum
glGetError(void)
{
	GLenum ret = GL_NONE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_glGetError();
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
glGetFloatv(GLenum pname, GLfloat* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetFloatv(pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetIntegerv(GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetIntegerv(pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetProgramiv(program, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetProgramInfoLog(program, bufsize, length, infolog);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetRenderbufferParameteriv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetShaderiv(shader, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetShaderInfoLog(shader, bufsize, length, infolog);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
{
	_COREGL_WRAP_FUNC_BEGIN();
#ifndef _COREGL_DESKTOP_GL
	ovr_glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
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
glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, char* source)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetShaderSource(shader, bufsize, length, source);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

const GLubyte *
glGetString(GLenum name)
{
	const GLubyte *ret = NULL;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_glGetString(name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetTexParameterfv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetTexParameteriv(GLenum target, GLenum pname, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetTexParameteriv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetUniformfv(GLuint program, GLint location, GLfloat* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetUniformfv(program, location, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetUniformiv(GLuint program, GLint location, GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetUniformiv(program, location, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}
int
glGetUniformLocation(GLuint program, const char* name)
{
	int ret = _COREGL_INT_INIT_VALUE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_glGetUniformLocation(program, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLboolean
glIsBuffer(GLuint buffer)
{
	GLboolean ret = GL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_glIsBuffer(buffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLboolean
glIsEnabled(GLenum cap)
{
	GLboolean ret = GL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_glIsEnabled(cap);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLboolean
glIsFramebuffer(GLuint framebuffer)
{
	GLboolean ret = GL_FALSE;

	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_glIsFramebuffer(framebuffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLboolean
glIsProgram(GLuint program)
{
	GLboolean ret;
	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_glIsProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLboolean
glIsRenderbuffer(GLuint renderbuffer)
{
	GLboolean ret;
	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_glIsRenderbuffer(renderbuffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLboolean
glIsShader(GLuint shader)
{
	GLboolean ret;
	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_glIsShader(shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

GLboolean
glIsTexture(GLuint texture)
{
	GLboolean ret;
	_COREGL_WRAP_FUNC_BEGIN();
	ret = ovr_glIsTexture(texture);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
	return ret;
}

void
glLineWidth(GLfloat width)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glLineWidth(width);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glLinkProgram(GLuint program)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glLinkProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glPixelStorei(GLenum pname, GLint param)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glPixelStorei(pname, param);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glPolygonOffset(GLfloat factor, GLfloat units)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glPolygonOffset(factor, units);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glReadPixels(x, y, width, height, format, type, pixels);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glReleaseShaderCompiler(void)
{
	_COREGL_WRAP_FUNC_BEGIN();
#ifndef _COREGL_DESKTOP_GL
	ovr_glReleaseShaderCompiler();
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
#else
	//FIXME!!! need something here?

#endif
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glRenderbufferStorage(target, internalformat, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glSampleCoverage(GLclampf value, GLboolean invert)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glSampleCoverage(value, invert);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glScissor(x, y, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length)
{
	_COREGL_WRAP_FUNC_BEGIN();
#ifndef _COREGL_DESKTOP_GL
	ovr_glShaderBinary(n, shaders, binaryformat, binary, length);
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
glShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glShaderSource(shader, count, string, length);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glStencilFunc(func, ref, mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glStencilFuncSeparate(face, func, ref, mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glStencilMask(GLuint mask)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glStencilMask(mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glStencilMaskSeparate(GLenum face, GLuint mask)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glStencilMaskSeparate(face, mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glStencilOp(fail, zfail, zpass);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glStencilOpSeparate(face, fail, zfail, zpass);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glTexParameterf(target, pname, param);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glTexParameterfv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glTexParameteri(GLenum target, GLenum pname, GLint param)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glTexParameteri(target, pname, param);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glTexParameteriv(GLenum target, GLenum pname, const GLint* params)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glTexParameteriv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform1f(GLint location, GLfloat x)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform1f(location, x);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform1fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform1fv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform1i(GLint location, GLint x)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform1i(location, x);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform1iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform1iv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform2f(GLint location, GLfloat x, GLfloat y)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform2f(location, x, y);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform2fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform2fv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform2i(GLint location, GLint x, GLint y)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform2i(location, x, y);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform2iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform2iv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform3f(location, x, y, z);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform3fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform3fv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform3i(GLint location, GLint x, GLint y, GLint z)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform3i(location, x, y, z);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform3iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform3iv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform4f(location, x, y, z, w);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform4fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform4fv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform4i(location, x, y, z, w);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniform4iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniform4iv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniformMatrix2fv(location, count, transpose, value);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniformMatrix3fv(location, count, transpose, value);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUniformMatrix4fv(location, count, transpose, value);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glUseProgram(GLuint program)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glUseProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glValidateProgram(GLuint program)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glValidateProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glVertexAttrib1f(GLuint indx, GLfloat x)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glVertexAttrib1f(indx, x);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glVertexAttrib1fv(GLuint indx, const GLfloat* values)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glVertexAttrib1fv(indx, values);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glVertexAttrib2f(indx, x, y);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glVertexAttrib2fv(GLuint indx, const GLfloat* values)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glVertexAttrib2fv(indx, values);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glVertexAttrib3f(indx, x, y, z);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glVertexAttrib3fv(GLuint indx, const GLfloat* values)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glVertexAttrib3fv(indx, values);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glVertexAttrib4f(indx, x, y, z, w);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glVertexAttrib4fv(GLuint indx, const GLfloat* values)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glVertexAttrib4fv(indx, values);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glViewport(x, y, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}


// GLES Extensions...
void
glEGLImageTargetTexture2DOES(GLenum target, GLeglImageOES image)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glEGLImageTargetTexture2DOES(target, image);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glEGLImageTargetRenderbufferStorageOES(GLenum target, GLeglImageOES image)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glEGLImageTargetRenderbufferStorageOES(target, image);
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glGetProgramBinary(GLuint program, GLsizei bufsize, GLsizei* length, GLenum* binaryFormat, void* binary)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glGetProgramBinary(program, bufsize, length, binaryFormat, binary);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glProgramBinary(GLuint program, GLenum binaryFormat, const void* binary, GLint length)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glProgramBinary(program, binaryFormat, binary, length);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}


void
glProgramParameteri(GLuint program, GLuint pname, GLint value)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glProgramParameteri(program, pname, value);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glRenderbufferStorageMultisampleEXT(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glRenderbufferStorageMultisampleEXT(target, samples, internalformat, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glFramebufferTexture2DMultisampleEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glFramebufferTexture2DMultisampleEXT(target, attachment, textarget, texture, level, samples);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

void
glDiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum *attachments)
{
	_COREGL_WRAP_FUNC_BEGIN();
	ovr_glDiscardFramebufferEXT(target, numAttachments, attachments);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_WRAP_FUNC_END();
}

