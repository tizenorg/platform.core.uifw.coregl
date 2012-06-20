#include "coregl_tracepath.h"

void
tracepath_glActiveTexture(GLenum texture)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glActiveTexture(texture);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glAttachShader(GLuint program, GLuint shader)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glAttachShader(program, shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBindAttribLocation(GLuint program, GLuint index, const char* name)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBindAttribLocation(program, index, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBindBuffer(GLenum target, GLuint buffer)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBindBuffer(target, buffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBindFramebuffer(target, framebuffer);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBindRenderbuffer(target, renderbuffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBindTexture(GLenum target, GLuint texture)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBindTexture(target, texture);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBlendColor(red, green, blue, alpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBlendEquation(GLenum mode)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBlendEquation(mode);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBlendEquationSeparate(modeRGB, modeAlpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBlendFunc(sfactor, dfactor);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBufferData(target, size, data, usage);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBufferSubData(target, offset, size, data);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

GLenum
tracepath_glCheckFramebufferStatus(GLenum target)
{
	GLenum ret = GL_NONE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glCheckFramebufferStatus(target);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

void
tracepath_glClear(GLbitfield mask)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glClear(mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glClearColor(red, green, blue, alpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glClearDepthf(GLclampf depth)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glClearDepthf(depth);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glClearStencil(GLint s)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glClearStencil(s);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glColorMask(red, green, blue, alpha);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glCompileShader(GLuint shader)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glCompileShader(shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

GLuint
tracepath_glCreateProgram(void)
{
	GLuint ret = _COREGL_INT_INIT_VALUE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glCreateProgram();
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

GLuint
tracepath_glCreateShader(GLenum type)
{
	GLuint ret = _COREGL_INT_INIT_VALUE;
	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glCreateShader(type);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

void
tracepath_glCullFace(GLenum mode)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glCullFace(mode);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDeleteBuffers(n, buffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDeleteFramebuffers(n, framebuffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDeleteProgram(GLuint program)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDeleteProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDeleteRenderbuffers(n, renderbuffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDeleteShader(GLuint shader)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDeleteShader(shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDeleteTextures(GLsizei n, const GLuint* textures)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDeleteTextures(n, textures);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDepthFunc(GLenum func)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDepthFunc(func);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDepthMask(GLboolean flag)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDepthMask(flag);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDepthRangef(GLclampf zNear, GLclampf zFar)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDepthRangef(zNear, zFar);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDetachShader(GLuint program, GLuint shader)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDetachShader(program, shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDisable(GLenum cap)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDisable(cap);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDisableVertexAttribArray(GLuint index)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDisableVertexAttribArray(index);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDrawArrays(mode, first, count);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDrawElements(mode, count, type, indices);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glEnable(GLenum cap)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glEnable(cap);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glEnableVertexAttribArray(GLuint index)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glEnableVertexAttribArray(index);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glFinish(void)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glFinish();
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	_COREGL_TRACE_API_OUTPUT(0);
}

void
tracepath_glFlush(void)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glFlush();
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	_COREGL_TRACE_API_OUTPUT(0);
}

void
tracepath_glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glFramebufferTexture2D(target, attachment, textarget, texture, level);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glFrontFace(GLenum mode)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glFrontFace(mode);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetVertexAttribfv(index, pname, params);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetVertexAttribiv(index, pname, params);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetVertexAttribPointerv(index, pname, pointer);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glHint(GLenum target, GLenum mode)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glHint(target, mode);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGenBuffers(GLsizei n, GLuint* buffers)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGenBuffers(n, buffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGenerateMipmap(GLenum target)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGenerateMipmap(target);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGenFramebuffers(n, framebuffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGenRenderbuffers(n, renderbuffers);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGenTextures(GLsizei n, GLuint* textures)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGenTextures(n, textures);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetActiveAttrib(program, index, bufsize, length, size, type, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetActiveUniform(program, index, bufsize, length, size, type, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetAttachedShaders(program, maxcount, count, shaders);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

int
tracepath_glGetAttribLocation(GLuint program, const char* name)
{
	int ret = _COREGL_INT_INIT_VALUE;
	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glGetAttribLocation(program, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

void
tracepath_glGetBooleanv(GLenum pname, GLboolean* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetBooleanv(pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetBufferParameteriv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

GLenum
tracepath_glGetError(void)
{
	GLenum ret = GL_NONE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glGetError();
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

void
tracepath_glGetFloatv(GLenum pname, GLfloat* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetFloatv(pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetIntegerv(GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetIntegerv(pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetProgramiv(program, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetProgramInfoLog(program, bufsize, length, infolog);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetRenderbufferParameteriv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetShaderiv(shader, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetShaderInfoLog(shader, bufsize, length, infolog);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, char* source)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetShaderSource(shader, bufsize, length, source);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

const GLubyte *
tracepath_glGetString(GLenum name)
{
	const GLubyte *ret = NULL;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glGetString(name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

void
tracepath_glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetTexParameterfv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetTexParameteriv(GLenum target, GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetTexParameteriv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetUniformfv(GLuint program, GLint location, GLfloat* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetUniformfv(program, location, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetUniformiv(GLuint program, GLint location, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetUniformiv(program, location, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}
int
tracepath_glGetUniformLocation(GLuint program, const char* name)
{
	int ret = _COREGL_INT_INIT_VALUE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glGetUniformLocation(program, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

GLboolean
tracepath_glIsBuffer(GLuint buffer)
{
	GLboolean ret = GL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glIsBuffer(buffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

GLboolean
tracepath_glIsEnabled(GLenum cap)
{
	GLboolean ret = GL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glIsEnabled(cap);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

GLboolean
tracepath_glIsFramebuffer(GLuint framebuffer)
{
	GLboolean ret = GL_FALSE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glIsFramebuffer(framebuffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

GLboolean
tracepath_glIsProgram(GLuint program)
{
	GLboolean ret;
	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glIsProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

GLboolean
tracepath_glIsRenderbuffer(GLuint renderbuffer)
{
	GLboolean ret;
	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glIsRenderbuffer(renderbuffer);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

GLboolean
tracepath_glIsShader(GLuint shader)
{
	GLboolean ret;
	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glIsShader(shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

GLboolean
tracepath_glIsTexture(GLuint texture)
{
	GLboolean ret;
	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glIsTexture(texture);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	return ret;
}

void
tracepath_glLineWidth(GLfloat width)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glLineWidth(width);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glLinkProgram(GLuint program)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glLinkProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glPixelStorei(GLenum pname, GLint param)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glPixelStorei(pname, param);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glPolygonOffset(GLfloat factor, GLfloat units)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glPolygonOffset(factor, units);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glReadPixels(x, y, width, height, format, type, pixels);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glReleaseShaderCompiler(void)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glReleaseShaderCompiler();
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glRenderbufferStorage(target, internalformat, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glSampleCoverage(GLclampf value, GLboolean invert)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glSampleCoverage(value, invert);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glScissor(x, y, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glShaderBinary(n, shaders, binaryformat, binary, length);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glShaderSource(shader, count, string, length);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glStencilFunc(func, ref, mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glStencilFuncSeparate(face, func, ref, mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glStencilMask(GLuint mask)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glStencilMask(mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glStencilMaskSeparate(GLenum face, GLuint mask)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glStencilMaskSeparate(face, mask);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glStencilOp(fail, zfail, zpass);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glStencilOpSeparate(face, fail, zfail, zpass);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glTexParameterf(target, pname, param);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glTexParameterfv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glTexParameteri(GLenum target, GLenum pname, GLint param)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glTexParameteri(target, pname, param);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glTexParameteriv(GLenum target, GLenum pname, const GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glTexParameteriv(target, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform1f(GLint location, GLfloat x)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform1f(location, x);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform1fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform1fv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform1i(GLint location, GLint x)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform1i(location, x);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform1iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform1iv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform2f(GLint location, GLfloat x, GLfloat y)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform2f(location, x, y);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform2fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform2fv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform2i(GLint location, GLint x, GLint y)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform2i(location, x, y);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform2iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform2iv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform3f(location, x, y, z);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform3fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform3fv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform3i(GLint location, GLint x, GLint y, GLint z)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform3i(location, x, y, z);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform3iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform3iv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform4f(location, x, y, z, w);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform4fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform4fv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform4i(location, x, y, z, w);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform4iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform4iv(location, count, v);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniformMatrix2fv(location, count, transpose, value);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniformMatrix3fv(location, count, transpose, value);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniformMatrix4fv(location, count, transpose, value);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUseProgram(GLuint program)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUseProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glValidateProgram(GLuint program)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glValidateProgram(program);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib1f(GLuint indx, GLfloat x)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib1f(indx, x);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib1fv(GLuint indx, const GLfloat* values)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib1fv(indx, values);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib2f(indx, x, y);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib2fv(GLuint indx, const GLfloat* values)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib2fv(indx, values);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib3f(indx, x, y, z);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib3fv(GLuint indx, const GLfloat* values)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib3fv(indx, values);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib4f(indx, x, y, z, w);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib4fv(GLuint indx, const GLfloat* values)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib4fv(indx, values);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glViewport(x, y, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}


// GLES Extensions...
void
tracepath_glEGLImageTargetTexture2DOES(GLenum target, GLeglImageOES image)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glEGLImageTargetTexture2DOES(target, image);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glEGLImageTargetRenderbufferStorageOES(GLenum target, GLeglImageOES image)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glEGLImageTargetRenderbufferStorageOES(target, image);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetProgramBinary(GLuint program, GLsizei bufsize, GLsizei* length, GLenum* binaryFormat, void* binary)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetProgramBinary(program, bufsize, length, binaryFormat, binary);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramBinary(GLuint program, GLenum binaryFormat, const void* binary, GLint length)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramBinary(program, binaryFormat, binary, length);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}


void
tracepath_glProgramParameteri(GLuint program, GLuint pname, GLint value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramParameteri(program, pname, value);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glRenderbufferStorageMultisampleEXT(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glRenderbufferStorageMultisampleEXT(target, samples, internalformat, width, height);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glFramebufferTexture2DMultisampleEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glFramebufferTexture2DMultisampleEXT(target, attachment, textarget, texture, level, samples);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum *attachments)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDiscardFramebufferEXT(target, numAttachments, attachments);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

