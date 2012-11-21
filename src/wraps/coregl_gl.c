#include <stdio.h>
#include <dlfcn.h>

# include <GLES/glplatform.h>
# include "../headers/gl.h"

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

__attribute__((constructor))
int
coregl_glwrap_init()
{
	void *lib_handle = NULL;

	lib_handle = dlopen("libCOREGL.so", RTLD_NOW);
	if (!lib_handle)
	{
		fprintf(stderr, "\E[0;31;1mERROR : %s\E[0m\n\n", dlerror());
		fprintf(stderr, "\E[0;31;1mERROR : Invalid library link! (Check linkage of libEGL -> libCOREGL)\E[0m\n");
		return 0;
	}

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST) \
   ovr_##FUNC_NAME = (__typeof__(ovr_##FUNC_NAME))dlsym(lib_handle, #FUNC_NAME);
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
glVertexAttrib1f(GLuint indx, GLfloat x)
{
	ovr_glVertexAttrib1f(indx, x);
}

void
glVertexAttrib1fv(GLuint indx, const GLfloat* values)
{
	ovr_glVertexAttrib1fv(indx, values);
}

void
glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y)
{
	ovr_glVertexAttrib2f(indx, x, y);
}

void
glVertexAttrib2fv(GLuint indx, const GLfloat* values)
{
	ovr_glVertexAttrib2fv(indx, values);
}

void
glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z)
{
	ovr_glVertexAttrib3f(indx, x, y, z);
}

void
glVertexAttrib3fv(GLuint indx, const GLfloat* values)
{
	ovr_glVertexAttrib3fv(indx, values);
}

void
glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	ovr_glVertexAttrib4f(indx, x, y, z, w);
}

void
glVertexAttrib4fv(GLuint indx, const GLfloat* values)
{
	ovr_glVertexAttrib4fv(indx, values);
}

void
glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr)
{
	ovr_glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
}

void
glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	ovr_glViewport(x, y, width, height);
}

