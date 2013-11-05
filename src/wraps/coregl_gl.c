#include <stdio.h>
#include <dlfcn.h>

# include <GLES/glplatform.h>
# include "../headers/gl.h"

#define LOG_TAG "CoreGL_GLES2"
#include <dlog.h>

#define COREGL_API           __attribute__((visibility("default")))

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     COREGL_API extern RET_TYPE FUNC_NAME PARAM_LIST;
#define _COREGL_EXT_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)
# include "../headers/sym_gl.h"
#undef _COREGL_EXT_SYMBOL
#undef _COREGL_SYMBOL

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     RET_TYPE (*ovr_##FUNC_NAME) PARAM_LIST = NULL;
# include "../headers/sym_gl.h"
#undef _COREGL_SYMBOL

#define INIT_EXPORT()

void *lib_handle = NULL;

__attribute__((constructor))
int
coregl_glwrap_init()
{
	lib_handle = dlopen("libCOREGL.so", RTLD_NOW);
	if (!lib_handle)
	{
		LOGE(" \E[40;31;1m%s\E[0m\n\n", dlerror());
		LOGE(" \E[40;31;1mInvalid library link! (Check linkage of libEGL -> libCOREGL)\E[0m\n");
		return 0;
	}

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST) \
   ovr_##FUNC_NAME = (__typeof__(ovr_##FUNC_NAME))dlsym(lib_handle, "coregl_api_"#FUNC_NAME); \
	if (ovr_##FUNC_NAME == NULL) \
	{ \
		LOGE("\E[40;31;1mCan't find a symbol '%s'!\E[0m\n\n", #FUNC_NAME); \
		LOGE("\E[40;31;1mInvalid library link! (Check linkage of libGLESv2 -> libCOREGL)\E[0m\n"); \
	}
#include "../headers/sym_gl.h"
#undef _COREGL_SYMBOL

	return 1;
}

void
glActiveTexture(GLenum texture)
{
	ovr_glActiveTexture(texture);
}

void
glAttachShader(GLuint program, GLuint shader)
{
	ovr_glAttachShader(program, shader);
}

void
glBindAttribLocation(GLuint program, GLuint index, const char* name)
{
	ovr_glBindAttribLocation(program, index, name);
}

void
glBindBuffer(GLenum target, GLuint buffer)
{
	ovr_glBindBuffer(target, buffer);
}

void
glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	ovr_glBindFramebuffer(target, framebuffer);
}

void
glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
	ovr_glBindRenderbuffer(target, renderbuffer);
}

void
glBindTexture(GLenum target, GLuint texture)
{
	ovr_glBindTexture(target, texture);
}

void
glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	ovr_glBlendColor(red, green, blue, alpha);
}

void
glBlendEquation(GLenum mode)
{
	ovr_glBlendEquation(mode);
}

void
glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	ovr_glBlendEquationSeparate(modeRGB, modeAlpha);
}

void
glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	ovr_glBlendFunc(sfactor, dfactor);
}

void
glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	ovr_glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void
glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	ovr_glBufferData(target, size, data, usage);
}

void
glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
{
	ovr_glBufferSubData(target, offset, size, data);
}

GLenum
glCheckFramebufferStatus(GLenum target)
{
	return ovr_glCheckFramebufferStatus(target);
}

void
glClear(GLbitfield mask)
{
	ovr_glClear(mask);
}

void
glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	ovr_glClearColor(red, green, blue, alpha);
}

void
glClearDepthf(GLclampf depth)
{
	ovr_glClearDepthf(depth);
}

void
glClearStencil(GLint s)
{
	ovr_glClearStencil(s);
}

void
glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	ovr_glColorMask(red, green, blue, alpha);
}

void
glCompileShader(GLuint shader)
{
	ovr_glCompileShader(shader);
}

void
glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data)
{
	ovr_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}

void
glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data)
{
	ovr_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void
glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	ovr_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

void
glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	ovr_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

GLuint
glCreateProgram(void)
{
	return ovr_glCreateProgram();
}

GLuint
glCreateShader(GLenum type)
{
	return ovr_glCreateShader(type);
}

void
glCullFace(GLenum mode)
{
	ovr_glCullFace(mode);
}

void
glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	ovr_glDeleteBuffers(n, buffers);
}

void
glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
	ovr_glDeleteFramebuffers(n, framebuffers);
}

void
glDeleteProgram(GLuint program)
{
	ovr_glDeleteProgram(program);
}

void
glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
{
	ovr_glDeleteRenderbuffers(n, renderbuffers);
}

void
glDeleteShader(GLuint shader)
{
	ovr_glDeleteShader(shader);
}

void
glDeleteTextures(GLsizei n, const GLuint* textures)
{
	ovr_glDeleteTextures(n, textures);
}

void
glDepthFunc(GLenum func)
{
	ovr_glDepthFunc(func);
}

void
glDepthMask(GLboolean flag)
{
	ovr_glDepthMask(flag);
}

void
glDepthRangef(GLclampf zNear, GLclampf zFar)
{
	ovr_glDepthRangef(zNear, zFar);
}

void
glDetachShader(GLuint program, GLuint shader)
{
	ovr_glDetachShader(program, shader);
}

void
glDisable(GLenum cap)
{
	ovr_glDisable(cap);
}

void
glDisableVertexAttribArray(GLuint index)
{
	ovr_glDisableVertexAttribArray(index);
}

void
glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	ovr_glDrawArrays(mode, first, count);
}

void
glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices)
{
	ovr_glDrawElements(mode, count, type, indices);
}

void
glEnable(GLenum cap)
{
	ovr_glEnable(cap);
}

void
glEnableVertexAttribArray(GLuint index)
{
	ovr_glEnableVertexAttribArray(index);
}

void
glFinish(void)
{
	ovr_glFinish();
}

void
glFlush(void)
{
	ovr_glFlush();
}

void
glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	ovr_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

void
glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	ovr_glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

void
glFrontFace(GLenum mode)
{
	ovr_glFrontFace(mode);
}

void
glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
{
	ovr_glGetVertexAttribfv(index, pname, params);
}

void
glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
{
	ovr_glGetVertexAttribiv(index, pname, params);
}

void
glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer)
{
	ovr_glGetVertexAttribPointerv(index, pname, pointer);
}

void
glHint(GLenum target, GLenum mode)
{
	ovr_glHint(target, mode);
}

void
glGenBuffers(GLsizei n, GLuint* buffers)
{
	ovr_glGenBuffers(n, buffers);
}

void
glGenerateMipmap(GLenum target)
{
	ovr_glGenerateMipmap(target);
}

void
glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
	ovr_glGenFramebuffers(n, framebuffers);
}

void
glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
	ovr_glGenRenderbuffers(n, renderbuffers);
}

void
glGenTextures(GLsizei n, GLuint* textures)
{
	ovr_glGenTextures(n, textures);
}

void
glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
{
	ovr_glGetActiveAttrib(program, index, bufsize, length, size, type, name);
}

void
glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
{
	ovr_glGetActiveUniform(program, index, bufsize, length, size, type, name);
}

void
glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
{
	ovr_glGetAttachedShaders(program, maxcount, count, shaders);
}

int
glGetAttribLocation(GLuint program, const char* name)
{
	return ovr_glGetAttribLocation(program, name);
}

void
glGetBooleanv(GLenum pname, GLboolean* params)
{
	ovr_glGetBooleanv(pname, params);
}

void
glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	ovr_glGetBufferParameteriv(target, pname, params);
}

GLenum
glGetError(void)
{
	return ovr_glGetError();
}

void
glGetFloatv(GLenum pname, GLfloat* params)
{
	ovr_glGetFloatv(pname, params);
}

void
glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
	ovr_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}

void
glGetIntegerv(GLenum pname, GLint* params)
{
	ovr_glGetIntegerv(pname, params);
}

void
glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
	ovr_glGetProgramiv(program, pname, params);
}

void
glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog)
{
	ovr_glGetProgramInfoLog(program, bufsize, length, infolog);
}

void
glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	ovr_glGetRenderbufferParameteriv(target, pname, params);
}

void
glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
	ovr_glGetShaderiv(shader, pname, params);
}

void
glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog)
{
	ovr_glGetShaderInfoLog(shader, bufsize, length, infolog);
}

void
glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
{
	ovr_glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
}

void
glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, char* source)
{
	ovr_glGetShaderSource(shader, bufsize, length, source);
}

const GLubyte *
glGetString(GLenum name)
{
	return ovr_glGetString(name);
}

void
glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params)
{
	ovr_glGetTexParameterfv(target, pname, params);
}

void
glGetTexParameteriv(GLenum target, GLenum pname, GLint* params)
{
	ovr_glGetTexParameteriv(target, pname, params);
}

void
glGetUniformfv(GLuint program, GLint location, GLfloat* params)
{
	ovr_glGetUniformfv(program, location, params);
}

void
glGetUniformiv(GLuint program, GLint location, GLint* params)
{
	ovr_glGetUniformiv(program, location, params);
}

int
glGetUniformLocation(GLuint program, const char* name)
{
	return ovr_glGetUniformLocation(program, name);
}

GLboolean
glIsBuffer(GLuint buffer)
{
	return ovr_glIsBuffer(buffer);
}

GLboolean
glIsEnabled(GLenum cap)
{
	return ovr_glIsEnabled(cap);
}

GLboolean
glIsFramebuffer(GLuint framebuffer)
{
	return ovr_glIsFramebuffer(framebuffer);
}

GLboolean
glIsProgram(GLuint program)
{
	return ovr_glIsProgram(program);
}

GLboolean
glIsRenderbuffer(GLuint renderbuffer)
{
	return ovr_glIsRenderbuffer(renderbuffer);
}

GLboolean
glIsShader(GLuint shader)
{
	return ovr_glIsShader(shader);
}

GLboolean
glIsTexture(GLuint texture)
{
	return ovr_glIsTexture(texture);
}

void
glLineWidth(GLfloat width)
{
	ovr_glLineWidth(width);
}

void
glLinkProgram(GLuint program)
{
	ovr_glLinkProgram(program);
}

void
glPixelStorei(GLenum pname, GLint param)
{
	ovr_glPixelStorei(pname, param);
}

void
glPolygonOffset(GLfloat factor, GLfloat units)
{
	ovr_glPolygonOffset(factor, units);
}

void
glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
{
	ovr_glReadPixels(x, y, width, height, format, type, pixels);
}

void
glReleaseShaderCompiler(void)
{
	ovr_glReleaseShaderCompiler();
}

void
glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
	ovr_glRenderbufferStorage(target, internalformat, width, height);
}

void
glSampleCoverage(GLclampf value, GLboolean invert)
{
	ovr_glSampleCoverage(value, invert);
}

void
glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	ovr_glScissor(x, y, width, height);
}

void
glShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length)
{
	ovr_glShaderBinary(n, shaders, binaryformat, binary, length);
}

void
glShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length)
{
	ovr_glShaderSource(shader, count, string, length);
}

void
glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
	ovr_glStencilFunc(func, ref, mask);
}

void
glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	ovr_glStencilFuncSeparate(face, func, ref, mask);
}

void
glStencilMask(GLuint mask)
{
	ovr_glStencilMask(mask);
}

void
glStencilMaskSeparate(GLenum face, GLuint mask)
{
	ovr_glStencilMaskSeparate(face, mask);
}

void
glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	ovr_glStencilOp(fail, zfail, zpass);
}

void
glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
{
	ovr_glStencilOpSeparate(face, fail, zfail, zpass);
}

void
glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels)
{
	ovr_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void
glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
	ovr_glTexParameterf(target, pname, param);
}

void
glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params)
{
	ovr_glTexParameterfv(target, pname, params);
}

void
glTexParameteri(GLenum target, GLenum pname, GLint param)
{
	ovr_glTexParameteri(target, pname, param);
}

void
glTexParameteriv(GLenum target, GLenum pname, const GLint* params)
{
	ovr_glTexParameteriv(target, pname, params);
}

void
glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
	ovr_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void
glUniform1f(GLint location, GLfloat x)
{
	ovr_glUniform1f(location, x);
}

void
glUniform1fv(GLint location, GLsizei count, const GLfloat* v)
{
	ovr_glUniform1fv(location, count, v);
}

void
glUniform1i(GLint location, GLint x)
{
	ovr_glUniform1i(location, x);
}

void
glUniform1iv(GLint location, GLsizei count, const GLint* v)
{
	ovr_glUniform1iv(location, count, v);
}

void
glUniform2f(GLint location, GLfloat x, GLfloat y)
{
	ovr_glUniform2f(location, x, y);
}

void
glUniform2fv(GLint location, GLsizei count, const GLfloat* v)
{
	ovr_glUniform2fv(location, count, v);
}

void
glUniform2i(GLint location, GLint x, GLint y)
{
	ovr_glUniform2i(location, x, y);
}

void
glUniform2iv(GLint location, GLsizei count, const GLint* v)
{
	ovr_glUniform2iv(location, count, v);
}

void
glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
{
	ovr_glUniform3f(location, x, y, z);
}

void
glUniform3fv(GLint location, GLsizei count, const GLfloat* v)
{
	ovr_glUniform3fv(location, count, v);
}

void
glUniform3i(GLint location, GLint x, GLint y, GLint z)
{
	ovr_glUniform3i(location, x, y, z);
}

void
glUniform3iv(GLint location, GLsizei count, const GLint* v)
{
	ovr_glUniform3iv(location, count, v);
}

void
glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	ovr_glUniform4f(location, x, y, z, w);
}

void
glUniform4fv(GLint location, GLsizei count, const GLfloat* v)
{
	ovr_glUniform4fv(location, count, v);
}

void
glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
{
	ovr_glUniform4i(location, x, y, z, w);
}

void
glUniform4iv(GLint location, GLsizei count, const GLint* v)
{
	ovr_glUniform4iv(location, count, v);
}

void
glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	ovr_glUniformMatrix2fv(location, count, transpose, value);
}

void
glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	ovr_glUniformMatrix3fv(location, count, transpose, value);
}

void
glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	ovr_glUniformMatrix4fv(location, count, transpose, value);
}

void
glUseProgram(GLuint program)
{
	ovr_glUseProgram(program);
}

void
glValidateProgram(GLuint program)
{
	ovr_glValidateProgram(program);
}

void
glVertexAttrib1f(GLuint index, GLfloat x)
{
	ovr_glVertexAttrib1f(index, x);
}

void
glVertexAttrib1fv(GLuint index, const GLfloat* values)
{
	ovr_glVertexAttrib1fv(index, values);
}

void
glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
{
	ovr_glVertexAttrib2f(index, x, y);
}

void
glVertexAttrib2fv(GLuint index, const GLfloat* values)
{
	ovr_glVertexAttrib2fv(index, values);
}

void
glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
	ovr_glVertexAttrib3f(index, x, y, z);
}

void
glVertexAttrib3fv(GLuint index, const GLfloat* values)
{
	ovr_glVertexAttrib3fv(index, values);
}

void
glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	ovr_glVertexAttrib4f(index, x, y, z, w);
}

void
glVertexAttrib4fv(GLuint index, const GLfloat* values)
{
	ovr_glVertexAttrib4fv(index, values);
}

void
glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	ovr_glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void
glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	ovr_glViewport(x, y, width, height);
}

/* OpenGL ES 3.0 */
void
glReadBuffer(GLenum mode)
{
	ovr_glReadBuffer(mode);
}

void
glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid* indices)
{
	ovr_glDrawRangeElements(mode, start, end, count, type, indices);
}

void
glTexImage3D(GLenum target, GLint level, GLint GLinternalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
	ovr_glTexImage3D(target, level, GLinternalFormat, width, height, depth, border, format, type, pixels);
}

void
glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels)
{
	ovr_glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

void
glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	ovr_glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

void
glCompressedTexImage3D(GLenum target, GLint level, GLenum GLinternalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data)
{
	ovr_glCompressedTexImage3D(target, level, GLinternalformat, width, height, depth, border, imageSize, data);
}

void
glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	ovr_glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

void
glGenQueries(GLsizei n, GLuint* ids)
{
	ovr_glGenQueries(n, ids);
}

void
glDeleteQueries(GLsizei n, const GLuint* ids)
{
	ovr_glDeleteQueries(n, ids);
}

GLboolean
glIsQuery(GLuint id)
{
	return ovr_glIsQuery(id);
}

void
glBeginQuery(GLenum target, GLuint id)
{
	ovr_glBeginQuery(target, id);
}

void
glEndQuery(GLenum target)
{
	ovr_glEndQuery(target);
}

void
glGetQueryiv(GLenum target, GLenum pname, GLint* params)
{
	ovr_glGetQueryiv(target, pname, params);
}

void
glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint* params)
{
	ovr_glGetQueryObjectuiv(id, pname, params);
}

GLboolean
glUnmapBuffer(GLenum target)
{
	return ovr_glUnmapBuffer(target);
}

void
glGetBufferPointerv(GLenum target, GLenum pname, GLvoid** params)
{
	ovr_glGetBufferPointerv(target, pname, params);
}

void
glDrawBuffers(GLsizei n, const GLenum* bufs)
{
	ovr_glDrawBuffers(n, bufs);
}

void
glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	ovr_glUniformMatrix2x3fv(location, count, transpose, value);
}

void
glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	ovr_glUniformMatrix3x2fv(location, count, transpose, value);
}

void
glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	ovr_glUniformMatrix2x4fv(location, count, transpose, value);
}

void
glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	ovr_glUniformMatrix4x2fv(location, count, transpose, value);
}

void
glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	ovr_glUniformMatrix3x4fv(location, count, transpose, value);
}

void
glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	ovr_glUniformMatrix4x3fv(location, count, transpose, value);
}

void
glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
	ovr_glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

void
glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
	ovr_glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
}

void
glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
	ovr_glFramebufferTextureLayer(target, attachment, texture, level, layer);
}

GLvoid*
glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	return ovr_glMapBufferRange(target, offset, length, access);
}

void
glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
{
	ovr_glFlushMappedBufferRange(target, offset, length);
}

void
glBindVertexArray(GLuint array)
{
	ovr_glBindVertexArray(array);
}

void
glDeleteVertexArrays(GLsizei n, const GLuint* arrays)
{
	ovr_glDeleteVertexArrays(n, arrays);
}

void
glGenVertexArrays(GLsizei n, GLuint* arrays)
{
	ovr_glGenVertexArrays(n, arrays);
}

GLboolean
glIsVertexArray(GLuint array)
{
	return ovr_glIsVertexArray(array);
}

void
glGetIntegeri_v(GLenum target, GLuint index, GLint* data)
{
	ovr_glGetIntegeri_v(target, index, data);
}

void
glBeginTransformFeedback(GLenum primitiveMode)
{
	ovr_glBeginTransformFeedback(primitiveMode);
}

void
glEndTransformFeedback()
{
	ovr_glEndTransformFeedback();
}

void
glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	ovr_glBindBufferRange(target, index, buffer, offset, size);
}

void
glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
	ovr_glBindBufferBase(target, index, buffer);
}

void
glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode)
{
	ovr_glTransformFeedbackVaryings(program, count, varyings, bufferMode);
}

void
glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name)
{
	ovr_glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
}

void
glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
	ovr_glVertexAttribIPointer(index, size, type, stride, pointer);
}

void
glGetVertexAttribIiv(GLuint index, GLenum pname, GLint* params)
{
	ovr_glGetVertexAttribIiv(index, pname, params);
}

void
glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint* params)
{
	ovr_glGetVertexAttribIuiv(index, pname, params);
}

void
glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
{
	ovr_glVertexAttribI4i(index, x, y, z, w);
}

void
glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
	ovr_glVertexAttribI4ui(index, x, y, z, w);
}

void
glVertexAttribI4iv(GLuint index, const GLint* v)
{
	ovr_glVertexAttribI4iv(index, v);
}

void
glVertexAttribI4uiv(GLuint index, const GLuint* v)
{
	ovr_glVertexAttribI4uiv(index, v);
}

void
glGetUniformuiv(GLuint program, GLint location, GLuint* params)
{
	ovr_glGetUniformuiv(program, location, params);
}

GLint
glGetFragDataLocation(GLuint program, const GLchar *name)
{
	return ovr_glGetFragDataLocation(program, name);
}

void
glUniform1ui(GLint location, GLuint v0)
{
	ovr_glUniform1ui(location, v0);
}

void
glUniform2ui(GLint location, GLuint v0, GLuint v1)
{
	ovr_glUniform2ui(location, v0, v1);
}

void
glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
	ovr_glUniform3ui(location, v0, v1, v2);
}

void
glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	ovr_glUniform4ui(location, v0, v1, v2, v3);
}

void
glUniform1uiv(GLint location, GLsizei count, const GLuint* value)
{
	ovr_glUniform1uiv(location, count, value);
}

void
glUniform2uiv(GLint location, GLsizei count, const GLuint* value)
{
	ovr_glUniform2uiv(location, count, value);
}

void
glUniform3uiv(GLint location, GLsizei count, const GLuint* value)
{
	ovr_glUniform3uiv(location, count, value);
}

void
glUniform4uiv(GLint location, GLsizei count, const GLuint* value)
{
	ovr_glUniform4uiv(location, count, value);
}

void
glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint* value)
{
	ovr_glClearBufferiv(buffer, drawbuffer, value);
}

void
glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint* value)
{
	ovr_glClearBufferuiv(buffer, drawbuffer, value);
}

void
glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value)
{
	ovr_glClearBufferfv(buffer, drawbuffer, value);
}

void
glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
	ovr_glClearBufferfi(buffer, drawbuffer, depth, stencil);
}

const GLubyte*
glGetStringi(GLenum name, GLuint index)
{
	return ovr_glGetStringi(name, index);
}

void
glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
	ovr_glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
}

void
glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames, GLuint* uniformIndices)
{
	ovr_glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
}

void
glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params)
{
	ovr_glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
}

GLuint
glGetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName)
{
	return ovr_glGetUniformBlockIndex(program, uniformBlockName);
}

void
glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params)
{
	ovr_glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
}

void
glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName)
{
	ovr_glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
}

void
glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
{
	ovr_glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
}

void
glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount)
{
	ovr_glDrawArraysInstanced(mode, first, count, instanceCount);
}

void
glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLsizei instanceCount)
{
	ovr_glDrawElementsInstanced(mode, count, type, indices, instanceCount);
}

GLsync
glFenceSync(GLenum condition, GLbitfield flags)
{
	return ovr_glFenceSync(condition, flags);
}

GLboolean
glIsSync(GLsync sync)
{
	return ovr_glIsSync(sync);
}

void
glDeleteSync(GLsync sync)
{
	ovr_glDeleteSync(sync);
}

GLenum
glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
	return ovr_glClientWaitSync(sync, flags, timeout);
}

void
glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
	ovr_glWaitSync(sync, flags, timeout);
}

void
glGetInteger64v(GLenum pname, GLint64* params)
{
	ovr_glGetInteger64v(pname, params);
}

void
glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values)
{
	ovr_glGetSynciv(sync, pname, bufSize, length, values);
}

void
glGetInteger64i_v(GLenum target, GLuint index, GLint64* data)
{
	ovr_glGetInteger64i_v(target, index, data);
}

void
glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64* params)
{
	ovr_glGetBufferParameteri64v(target, pname, params);
}

void
glGenSamplers(GLsizei count, GLuint* samplers)
{
	ovr_glGenSamplers(count, samplers);
}

void
glDeleteSamplers(GLsizei count, const GLuint* samplers)
{
	ovr_glDeleteSamplers(count, samplers);
}

GLboolean
glIsSampler(GLuint sampler)
{
	return ovr_glIsSampler(sampler);
}

void
glBindSampler(GLuint unit, GLuint sampler)
{
	ovr_glBindSampler(unit, sampler);
}

void
glSamplerParameteri(GLuint sampler, GLenum pname, GLint param)
{
	ovr_glSamplerParameteri(sampler, pname, param);
}

void
glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint* param)
{
	ovr_glSamplerParameteriv(sampler, pname, param);
}

void
glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
{
	ovr_glSamplerParameterf(sampler, pname, param);
}

void
glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat* param)
{
	ovr_glSamplerParameterfv(sampler, pname, param);
}

void
glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint* params)
{
	ovr_glGetSamplerParameteriv(sampler, pname, params);
}

void
glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat* params)
{
	ovr_glGetSamplerParameterfv(sampler, pname, params);
}

void
glVertexAttribDivisor(GLuint index, GLuint divisor)
{
	ovr_glVertexAttribDivisor(index, divisor);
}

void
glBindTransformFeedback(GLenum target, GLuint id)
{
	ovr_glBindTransformFeedback(target, id);
}

void
glDeleteTransformFeedbacks(GLsizei n, const GLuint* ids)
{
	ovr_glDeleteTransformFeedbacks(n, ids);
}

void
glGenTransformFeedbacks(GLsizei n, GLuint* ids)
{
	ovr_glGenTransformFeedbacks(n, ids);
}

GLboolean
glIsTransformFeedback(GLuint id)
{
	return ovr_glIsTransformFeedback(id);
}

void
glPauseTransformFeedback()
{
	ovr_glPauseTransformFeedback();
}

void
glResumeTransformFeedback()
{
	ovr_glResumeTransformFeedback();
}

void
glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, GLvoid* binary)
{
	ovr_glGetProgramBinary(program, bufSize, length, binaryFormat, binary);
}

void
glProgramBinary(GLuint program, GLenum binaryFormat, const GLvoid* binary, GLsizei length)
{
	ovr_glProgramBinary(program, binaryFormat, binary, length);
}

void
glProgramParameteri(GLuint program, GLenum pname, GLint value)
{
	ovr_glProgramParameteri(program, pname, value);
}

void
glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments)
{
	ovr_glInvalidateFramebuffer(target, numAttachments, attachments);
}

void
glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height)
{
	ovr_glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
}

void
glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	ovr_glTexStorage2D(target, levels, internalformat, width, height);
}

void
glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
	ovr_glTexStorage3D(target, levels, internalformat, width, height, depth);
}

void
glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params)
{
	ovr_glGetInternalformativ(target, internalformat, pname, bufSize, params);
}

