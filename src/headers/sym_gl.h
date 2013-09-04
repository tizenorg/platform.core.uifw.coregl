
/*
 * gl3.h last updated on $Date: 2013-02-12 14:37:24 -0800 (Tue, 12 Feb 2013) $
 */

// Defult use-case for exporting symbols
#ifndef _COREGL_SYMBOL
#define _COREGL_SYMBOL_NOT_DEFINED
#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST) COREGL_API extern RET_TYPE FUNC_NAME PARAM_LIST;
#endif
#ifndef _COREGL_EXT_SYMBOL
#define _COREGL_EXT_SYMBOL_NOT_DEFINED
#define _COREGL_EXT_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST) _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)
#endif
#ifndef _COREGL_EXT_SYMBOL_ALIAS
#define _COREGL_EXT_SYMBOL_ALIAS_NOT_DEFINED
#define _COREGL_EXT_SYMBOL_ALIAS(FUNC_NAME, ALIAS_NAME)
#endif
#ifndef _COREGL_EXT_SYMBOL_FASTPATH_PASS
#define _COREGL_EXT_SYMBOL_FASTPATH_PASS_NOT_DEFINED
#define _COREGL_EXT_SYMBOL_FASTPATH_PASS(FUNC_NAME)
#endif
#ifndef _COREGL_EXT_SYMBOL_FASTPATH_BLOCK
#define _COREGL_EXT_SYMBOL_FASTPATH_BLOCK_NOT_DEFINED
#define _COREGL_EXT_SYMBOL_FASTPATH_BLOCK(FUNC_NAME)
#endif

/* OpenGL ES 2.0 */
_COREGL_SYMBOL(GL_FALSE, void, glActiveTexture, (GLenum texture))
_COREGL_SYMBOL(GL_FALSE, void, glAttachShader, (GLuint program, GLuint shader))
_COREGL_SYMBOL(GL_FALSE, void, glBindAttribLocation, (GLuint program, GLuint index, const char* name))
_COREGL_SYMBOL(GL_FALSE, void, glBindBuffer, (GLenum target, GLuint buffer))
_COREGL_SYMBOL(GL_FALSE, void, glBindFramebuffer, (GLenum target, GLuint framebuffer))
_COREGL_SYMBOL(GL_FALSE, void, glBindRenderbuffer, (GLenum target, GLuint renderbuffer))
_COREGL_SYMBOL(GL_FALSE, void, glBindTexture, (GLenum target, GLuint texture))
_COREGL_SYMBOL(GL_FALSE, void, glBlendColor, (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha))
_COREGL_SYMBOL(GL_FALSE, void, glBlendEquation, ( GLenum mode ))
_COREGL_SYMBOL(GL_FALSE, void, glBlendEquationSeparate, (GLenum modeRGB, GLenum modeAlpha))
_COREGL_SYMBOL(GL_FALSE, void, glBlendFunc, (GLenum sfactor, GLenum dfactor))
_COREGL_SYMBOL(GL_FALSE, void, glBlendFuncSeparate, (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha))
_COREGL_SYMBOL(GL_FALSE, void, glBufferData, (GLenum target, GLsizeiptr size, const void* data, GLenum usage))
_COREGL_SYMBOL(GL_FALSE, void, glBufferSubData, (GLenum target, GLintptr offset, GLsizeiptr size, const void* data))
_COREGL_SYMBOL(GL_FALSE, GLenum, glCheckFramebufferStatus, (GLenum target))
_COREGL_SYMBOL(GL_FALSE, void, glClear, (GLbitfield mask))
_COREGL_SYMBOL(GL_FALSE, void, glClearColor, (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha))
_COREGL_SYMBOL(GL_FALSE, void, glClearDepthf, (GLclampf depth))
_COREGL_SYMBOL(GL_FALSE, void, glClearStencil, (GLint s))
_COREGL_SYMBOL(GL_FALSE, void, glColorMask, (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha))
_COREGL_SYMBOL(GL_FALSE, void, glCompileShader, (GLuint shader))
_COREGL_SYMBOL(GL_FALSE, void, glCompressedTexImage2D, (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data))
_COREGL_SYMBOL(GL_FALSE, void, glCompressedTexSubImage2D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data))
_COREGL_SYMBOL(GL_FALSE, void, glCopyTexImage2D, (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border))
_COREGL_SYMBOL(GL_FALSE, void, glCopyTexSubImage2D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height))
_COREGL_SYMBOL(GL_FALSE, GLuint, glCreateProgram, (void))
_COREGL_SYMBOL(GL_FALSE, GLuint, glCreateShader, (GLenum type))
_COREGL_SYMBOL(GL_FALSE, void, glCullFace, (GLenum mode))
_COREGL_SYMBOL(GL_FALSE, void, glDeleteBuffers, (GLsizei n, const GLuint* buffers))
_COREGL_SYMBOL(GL_FALSE, void, glDeleteFramebuffers, (GLsizei n, const GLuint* framebuffers))
_COREGL_SYMBOL(GL_FALSE, void, glDeleteProgram, (GLuint program))
_COREGL_SYMBOL(GL_FALSE, void, glDeleteRenderbuffers, (GLsizei n, const GLuint* renderbuffers))
_COREGL_SYMBOL(GL_FALSE, void, glDeleteShader, (GLuint shader))
_COREGL_SYMBOL(GL_FALSE, void, glDeleteTextures, (GLsizei n, const GLuint* textures))
_COREGL_SYMBOL(GL_FALSE, void, glDepthFunc, (GLenum func))
_COREGL_SYMBOL(GL_FALSE, void, glDepthMask, (GLboolean flag))
_COREGL_SYMBOL(GL_FALSE, void, glDepthRangef, (GLclampf zNear, GLclampf zFar))
_COREGL_SYMBOL(GL_FALSE, void, glDetachShader, (GLuint program, GLuint shader))
_COREGL_SYMBOL(GL_FALSE, void, glDisable, (GLenum cap))
_COREGL_SYMBOL(GL_FALSE, void, glDisableVertexAttribArray, (GLuint index))
_COREGL_SYMBOL(GL_FALSE, void, glDrawArrays, (GLenum mode, GLint first, GLsizei count))
_COREGL_SYMBOL(GL_FALSE, void, glDrawElements, (GLenum mode, GLsizei count, GLenum type, const void* indices))
_COREGL_SYMBOL(GL_FALSE, void, glEnable, (GLenum cap))
_COREGL_SYMBOL(GL_FALSE, void, glEnableVertexAttribArray, (GLuint index))
_COREGL_SYMBOL(GL_FALSE, void, glFinish, (void))
_COREGL_SYMBOL(GL_FALSE, void, glFlush, (void))
_COREGL_SYMBOL(GL_FALSE, void, glFramebufferRenderbuffer, (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer))
_COREGL_SYMBOL(GL_FALSE, void, glFramebufferTexture2D, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level))
_COREGL_SYMBOL(GL_FALSE, void, glFrontFace, (GLenum mode))
_COREGL_SYMBOL(GL_FALSE, void, glGenBuffers, (GLsizei n, GLuint* buffers))
_COREGL_SYMBOL(GL_FALSE, void, glGenerateMipmap, (GLenum target))
_COREGL_SYMBOL(GL_FALSE, void, glGenFramebuffers, (GLsizei n, GLuint* framebuffers))
_COREGL_SYMBOL(GL_FALSE, void, glGenRenderbuffers, (GLsizei n, GLuint* renderbuffers))
_COREGL_SYMBOL(GL_FALSE, void, glGenTextures, (GLsizei n, GLuint* textures))
_COREGL_SYMBOL(GL_FALSE, void, glGetActiveAttrib, (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name))
_COREGL_SYMBOL(GL_FALSE, void, glGetActiveUniform, (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name))
_COREGL_SYMBOL(GL_FALSE, void, glGetAttachedShaders, (GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders))
_COREGL_SYMBOL(GL_FALSE, int, glGetAttribLocation, (GLuint program, const char* name))
_COREGL_SYMBOL(GL_FALSE, void, glGetBooleanv, (GLenum pname, GLboolean* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetBufferParameteriv, (GLenum target, GLenum pname, GLint* params))
_COREGL_SYMBOL(GL_FALSE, GLenum, glGetError, (void))
_COREGL_SYMBOL(GL_FALSE, void, glGetFloatv, (GLenum pname, GLfloat* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetFramebufferAttachmentParameteriv, (GLenum target, GLenum attachment, GLenum pname, GLint* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetIntegerv, (GLenum pname, GLint* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetProgramiv, (GLuint program, GLenum pname, GLint* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetProgramInfoLog, (GLuint program, GLsizei bufsize, GLsizei* length, char* infolog))
_COREGL_SYMBOL(GL_FALSE, void, glGetRenderbufferParameteriv, (GLenum target, GLenum pname, GLint* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetShaderiv, (GLuint shader, GLenum pname, GLint* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetShaderInfoLog, (GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog))
_COREGL_SYMBOL(GL_FALSE, void, glGetShaderPrecisionFormat, (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision))
_COREGL_SYMBOL(GL_FALSE, void, glGetShaderSource, (GLuint shader, GLsizei bufsize, GLsizei* length, char* source))
_COREGL_SYMBOL(GL_FALSE, const GLubyte *, glGetString, (GLenum name))
_COREGL_SYMBOL(GL_FALSE, void, glGetTexParameterfv, (GLenum target, GLenum pname, GLfloat* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetTexParameteriv, (GLenum target, GLenum pname, GLint* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetUniformfv, (GLuint program, GLint location, GLfloat* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetUniformiv, (GLuint program, GLint location, GLint* params))
_COREGL_SYMBOL(GL_FALSE, int, glGetUniformLocation, (GLuint program, const char* name))
_COREGL_SYMBOL(GL_FALSE, void, glGetVertexAttribfv, (GLuint index, GLenum pname, GLfloat* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetVertexAttribiv, (GLuint index, GLenum pname, GLint* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetVertexAttribPointerv, (GLuint index, GLenum pname, void** pointer))
_COREGL_SYMBOL(GL_FALSE, void, glHint, (GLenum target, GLenum mode))
_COREGL_SYMBOL(GL_FALSE, GLboolean, glIsBuffer, (GLuint buffer))
_COREGL_SYMBOL(GL_FALSE, GLboolean, glIsEnabled, (GLenum cap))
_COREGL_SYMBOL(GL_FALSE, GLboolean, glIsFramebuffer, (GLuint framebuffer))
_COREGL_SYMBOL(GL_FALSE, GLboolean, glIsProgram, (GLuint program))
_COREGL_SYMBOL(GL_FALSE, GLboolean, glIsRenderbuffer, (GLuint renderbuffer))
_COREGL_SYMBOL(GL_FALSE, GLboolean, glIsShader, (GLuint shader))
_COREGL_SYMBOL(GL_FALSE, GLboolean, glIsTexture, (GLuint texture))
_COREGL_SYMBOL(GL_FALSE, void, glLineWidth, (GLfloat width))
_COREGL_SYMBOL(GL_FALSE, void, glLinkProgram, (GLuint program))
_COREGL_SYMBOL(GL_FALSE, void, glPixelStorei, (GLenum pname, GLint param))
_COREGL_SYMBOL(GL_FALSE, void, glPolygonOffset, (GLfloat factor, GLfloat units))
_COREGL_SYMBOL(GL_FALSE, void, glReadPixels, (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels))
_COREGL_SYMBOL(GL_FALSE, void, glReleaseShaderCompiler, (void))
_COREGL_SYMBOL(GL_FALSE, void, glRenderbufferStorage, (GLenum target, GLenum internalformat, GLsizei width, GLsizei height))
_COREGL_SYMBOL(GL_FALSE, void, glSampleCoverage, (GLclampf value, GLboolean invert))
_COREGL_SYMBOL(GL_FALSE, void, glScissor, (GLint x, GLint y, GLsizei width, GLsizei height))
_COREGL_SYMBOL(GL_FALSE, void, glShaderBinary, (GLsizei n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length))
_COREGL_SYMBOL(GL_FALSE, void, glShaderSource, (GLuint shader, GLsizei count, const char** string, const GLint* length))
_COREGL_SYMBOL(GL_FALSE, void, glStencilFunc, (GLenum func, GLint ref, GLuint mask))
_COREGL_SYMBOL(GL_FALSE, void, glStencilFuncSeparate, (GLenum face, GLenum func, GLint ref, GLuint mask))
_COREGL_SYMBOL(GL_FALSE, void, glStencilMask, (GLuint mask))
_COREGL_SYMBOL(GL_FALSE, void, glStencilMaskSeparate, (GLenum face, GLuint mask))
_COREGL_SYMBOL(GL_FALSE, void, glStencilOp, (GLenum fail, GLenum zfail, GLenum zpass))
_COREGL_SYMBOL(GL_FALSE, void, glStencilOpSeparate, (GLenum face, GLenum fail, GLenum zfail, GLenum zpass))
_COREGL_SYMBOL(GL_FALSE, void, glTexImage2D, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels))
_COREGL_SYMBOL(GL_FALSE, void, glTexParameterf, (GLenum target, GLenum pname, GLfloat param))
_COREGL_SYMBOL(GL_FALSE, void, glTexParameterfv, (GLenum target, GLenum pname, const GLfloat* params))
_COREGL_SYMBOL(GL_FALSE, void, glTexParameteri, (GLenum target, GLenum pname, GLint param))
_COREGL_SYMBOL(GL_FALSE, void, glTexParameteriv, (GLenum target, GLenum pname, const GLint* params))
_COREGL_SYMBOL(GL_FALSE, void, glTexSubImage2D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels))
_COREGL_SYMBOL(GL_FALSE, void, glUniform1f, (GLint location, GLfloat x))
_COREGL_SYMBOL(GL_FALSE, void, glUniform1fv, (GLint location, GLsizei count, const GLfloat* v))
_COREGL_SYMBOL(GL_FALSE, void, glUniform1i, (GLint location, GLint x))
_COREGL_SYMBOL(GL_FALSE, void, glUniform1iv, (GLint location, GLsizei count, const GLint* v))
_COREGL_SYMBOL(GL_FALSE, void, glUniform2f, (GLint location, GLfloat x, GLfloat y))
_COREGL_SYMBOL(GL_FALSE, void, glUniform2fv, (GLint location, GLsizei count, const GLfloat* v))
_COREGL_SYMBOL(GL_FALSE, void, glUniform2i, (GLint location, GLint x, GLint y))
_COREGL_SYMBOL(GL_FALSE, void, glUniform2iv, (GLint location, GLsizei count, const GLint* v))
_COREGL_SYMBOL(GL_FALSE, void, glUniform3f, (GLint location, GLfloat x, GLfloat y, GLfloat z))
_COREGL_SYMBOL(GL_FALSE, void, glUniform3fv, (GLint location, GLsizei count, const GLfloat* v))
_COREGL_SYMBOL(GL_FALSE, void, glUniform3i, (GLint location, GLint x, GLint y, GLint z))
_COREGL_SYMBOL(GL_FALSE, void, glUniform3iv, (GLint location, GLsizei count, const GLint* v))
_COREGL_SYMBOL(GL_FALSE, void, glUniform4f, (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w))
_COREGL_SYMBOL(GL_FALSE, void, glUniform4fv, (GLint location, GLsizei count, const GLfloat* v))
_COREGL_SYMBOL(GL_FALSE, void, glUniform4i, (GLint location, GLint x, GLint y, GLint z, GLint w))
_COREGL_SYMBOL(GL_FALSE, void, glUniform4iv, (GLint location, GLsizei count, const GLint* v))
_COREGL_SYMBOL(GL_FALSE, void, glUniformMatrix2fv, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value))
_COREGL_SYMBOL(GL_FALSE, void, glUniformMatrix3fv, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value))
_COREGL_SYMBOL(GL_FALSE, void, glUniformMatrix4fv, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value))
_COREGL_SYMBOL(GL_FALSE, void, glUseProgram, (GLuint program))
_COREGL_SYMBOL(GL_FALSE, void, glValidateProgram, (GLuint program))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttrib1f, (GLuint indx, GLfloat x))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttrib1fv, (GLuint indx, const GLfloat* values))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttrib2f, (GLuint indx, GLfloat x, GLfloat y))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttrib2fv, (GLuint indx, const GLfloat* values))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttrib3f, (GLuint indx, GLfloat x, GLfloat y, GLfloat z))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttrib3fv, (GLuint indx, const GLfloat* values))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttrib4f, (GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttrib4fv, (GLuint indx, const GLfloat* values))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttribPointer, (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr))
_COREGL_SYMBOL(GL_FALSE, void, glViewport, (GLint x, GLint y, GLsizei width, GLsizei height))

/* OpenGL ES 3.0 */
_COREGL_SYMBOL(GL_FALSE, void, glReadBuffer, (GLenum mode))
_COREGL_SYMBOL(GL_FALSE, void, glDrawRangeElements, (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid* indices))
_COREGL_SYMBOL(GL_FALSE, void, glTexImage3D, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* pixels))
_COREGL_SYMBOL(GL_FALSE, void, glTexSubImage3D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* pixels))
_COREGL_SYMBOL(GL_FALSE, void, glCopyTexSubImage3D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height))
_COREGL_SYMBOL(GL_FALSE, void, glCompressedTexImage3D, (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data))
_COREGL_SYMBOL(GL_FALSE, void, glCompressedTexSubImage3D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid* data))
_COREGL_SYMBOL(GL_FALSE, void, glGenQueries, (GLsizei n, GLuint* ids))
_COREGL_SYMBOL(GL_FALSE, void, glDeleteQueries, (GLsizei n, const GLuint* ids))
_COREGL_SYMBOL(GL_FALSE, GLboolean, glIsQuery, (GLuint id))
_COREGL_SYMBOL(GL_FALSE, void, glBeginQuery, (GLenum target, GLuint id))
_COREGL_SYMBOL(GL_FALSE, void, glEndQuery, (GLenum target))
_COREGL_SYMBOL(GL_FALSE, void, glGetQueryiv, (GLenum target, GLenum pname, GLint* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetQueryObjectuiv, (GLuint id, GLenum pname, GLuint* params))
_COREGL_SYMBOL(GL_FALSE, GLboolean, glUnmapBuffer, (GLenum target))
_COREGL_SYMBOL(GL_FALSE, void, glGetBufferPointerv, (GLenum target, GLenum pname, GLvoid** params))
_COREGL_SYMBOL(GL_FALSE, void, glDrawBuffers, (GLsizei n, const GLenum* bufs))
_COREGL_SYMBOL(GL_FALSE, void, glUniformMatrix2x3fv, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value))
_COREGL_SYMBOL(GL_FALSE, void, glUniformMatrix3x2fv, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value))
_COREGL_SYMBOL(GL_FALSE, void, glUniformMatrix2x4fv, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value))
_COREGL_SYMBOL(GL_FALSE, void, glUniformMatrix4x2fv, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value))
_COREGL_SYMBOL(GL_FALSE, void, glUniformMatrix3x4fv, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value))
_COREGL_SYMBOL(GL_FALSE, void, glUniformMatrix4x3fv, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value))
_COREGL_SYMBOL(GL_FALSE, void, glBlitFramebuffer, (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter))
_COREGL_SYMBOL(GL_FALSE, void, glRenderbufferStorageMultisample, (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height))
_COREGL_SYMBOL(GL_FALSE, void, glFramebufferTextureLayer, (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer))
_COREGL_SYMBOL(GL_FALSE, GLvoid*, glMapBufferRange, (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access))
_COREGL_SYMBOL(GL_FALSE, void, glFlushMappedBufferRange, (GLenum target, GLintptr offset, GLsizeiptr length))
_COREGL_SYMBOL(GL_FALSE, void, glBindVertexArray, (GLuint array))
_COREGL_SYMBOL(GL_FALSE, void, glDeleteVertexArrays, (GLsizei n, const GLuint* arrays))
_COREGL_SYMBOL(GL_FALSE, void, glGenVertexArrays, (GLsizei n, GLuint* arrays))
_COREGL_SYMBOL(GL_FALSE, GLboolean, glIsVertexArray, (GLuint array))
_COREGL_SYMBOL(GL_FALSE, void, glGetIntegeri_v, (GLenum target, GLuint index, GLint* data))
_COREGL_SYMBOL(GL_FALSE, void, glBeginTransformFeedback, (GLenum primitiveMode))
_COREGL_SYMBOL(GL_FALSE, void, glEndTransformFeedback, (void))
_COREGL_SYMBOL(GL_FALSE, void, glBindBufferRange, (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size))
_COREGL_SYMBOL(GL_FALSE, void, glBindBufferBase, (GLenum target, GLuint index, GLuint buffer))
_COREGL_SYMBOL(GL_FALSE, void, glTransformFeedbackVaryings, (GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode))
_COREGL_SYMBOL(GL_FALSE, void, glGetTransformFeedbackVarying, (GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttribIPointer, (GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer))
_COREGL_SYMBOL(GL_FALSE, void, glGetVertexAttribIiv, (GLuint index, GLenum pname, GLint* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetVertexAttribIuiv, (GLuint index, GLenum pname, GLuint* params))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttribI4i, (GLuint index, GLint x, GLint y, GLint z, GLint w))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttribI4ui, (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttribI4iv, (GLuint index, const GLint* v))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttribI4uiv, (GLuint index, const GLuint* v))
_COREGL_SYMBOL(GL_FALSE, void, glGetUniformuiv, (GLuint program, GLint location, GLuint* params))
_COREGL_SYMBOL(GL_FALSE, GLint, glGetFragDataLocation, (GLuint program, const GLchar *name))
_COREGL_SYMBOL(GL_FALSE, void, glUniform1ui, (GLint location, GLuint v0))
_COREGL_SYMBOL(GL_FALSE, void, glUniform2ui, (GLint location, GLuint v0, GLuint v1))
_COREGL_SYMBOL(GL_FALSE, void, glUniform3ui, (GLint location, GLuint v0, GLuint v1, GLuint v2))
_COREGL_SYMBOL(GL_FALSE, void, glUniform4ui, (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3))
_COREGL_SYMBOL(GL_FALSE, void, glUniform1uiv, (GLint location, GLsizei count, const GLuint* value))
_COREGL_SYMBOL(GL_FALSE, void, glUniform2uiv, (GLint location, GLsizei count, const GLuint* value))
_COREGL_SYMBOL(GL_FALSE, void, glUniform3uiv, (GLint location, GLsizei count, const GLuint* value))
_COREGL_SYMBOL(GL_FALSE, void, glUniform4uiv, (GLint location, GLsizei count, const GLuint* value))
_COREGL_SYMBOL(GL_FALSE, void, glClearBufferiv, (GLenum buffer, GLint drawbuffer, const GLint* value))
_COREGL_SYMBOL(GL_FALSE, void, glClearBufferuiv, (GLenum buffer, GLint drawbuffer, const GLuint* value))
_COREGL_SYMBOL(GL_FALSE, void, glClearBufferfv, (GLenum buffer, GLint drawbuffer, const GLfloat* value))
_COREGL_SYMBOL(GL_FALSE, void, glClearBufferfi, (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil))
_COREGL_SYMBOL(GL_FALSE, const GLubyte*, glGetStringi, (GLenum name, GLuint index))
_COREGL_SYMBOL(GL_FALSE, void, glCopyBufferSubData, (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size))
_COREGL_SYMBOL(GL_FALSE, void, glGetUniformIndices, (GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames, GLuint* uniformIndices))
_COREGL_SYMBOL(GL_FALSE, void, glGetActiveUniformsiv, (GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params))
_COREGL_SYMBOL(GL_FALSE, GLuint, glGetUniformBlockIndex, (GLuint program, const GLchar* uniformBlockName))
_COREGL_SYMBOL(GL_FALSE, void, glGetActiveUniformBlockiv, (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetActiveUniformBlockName, (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName))
_COREGL_SYMBOL(GL_FALSE, void, glUniformBlockBinding, (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding))
_COREGL_SYMBOL(GL_FALSE, void, glDrawArraysInstanced, (GLenum mode, GLint first, GLsizei count, GLsizei instanceCount))
_COREGL_SYMBOL(GL_FALSE, void, glDrawElementsInstanced, (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLsizei instanceCount))
_COREGL_SYMBOL(GL_FALSE, GLsync, glFenceSync, (GLenum condition, GLbitfield flags))
_COREGL_SYMBOL(GL_FALSE, GLboolean, glIsSync, (GLsync sync))
_COREGL_SYMBOL(GL_FALSE, void, glDeleteSync, (GLsync sync))
_COREGL_SYMBOL(GL_FALSE, GLenum, glClientWaitSync, (GLsync sync, GLbitfield flags, GLuint64 timeout))
_COREGL_SYMBOL(GL_FALSE, void, glWaitSync, (GLsync sync, GLbitfield flags, GLuint64 timeout))
_COREGL_SYMBOL(GL_FALSE, void, glGetInteger64v, (GLenum pname, GLint64* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetSynciv, (GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values))
_COREGL_SYMBOL(GL_FALSE, void, glGetInteger64i_v, (GLenum target, GLuint index, GLint64* data))
_COREGL_SYMBOL(GL_FALSE, void, glGetBufferParameteri64v, (GLenum target, GLenum pname, GLint64* params))
_COREGL_SYMBOL(GL_FALSE, void, glGenSamplers, (GLsizei count, GLuint* samplers))
_COREGL_SYMBOL(GL_FALSE, void, glDeleteSamplers, (GLsizei count, const GLuint* samplers))
_COREGL_SYMBOL(GL_FALSE, GLboolean, glIsSampler, (GLuint sampler))
_COREGL_SYMBOL(GL_FALSE, void, glBindSampler, (GLuint unit, GLuint sampler))
_COREGL_SYMBOL(GL_FALSE, void, glSamplerParameteri, (GLuint sampler, GLenum pname, GLint param))
_COREGL_SYMBOL(GL_FALSE, void, glSamplerParameteriv, (GLuint sampler, GLenum pname, const GLint* param))
_COREGL_SYMBOL(GL_FALSE, void, glSamplerParameterf, (GLuint sampler, GLenum pname, GLfloat param))
_COREGL_SYMBOL(GL_FALSE, void, glSamplerParameterfv, (GLuint sampler, GLenum pname, const GLfloat* param))
_COREGL_SYMBOL(GL_FALSE, void, glGetSamplerParameteriv, (GLuint sampler, GLenum pname, GLint* params))
_COREGL_SYMBOL(GL_FALSE, void, glGetSamplerParameterfv, (GLuint sampler, GLenum pname, GLfloat* params))
_COREGL_SYMBOL(GL_FALSE, void, glVertexAttribDivisor, (GLuint index, GLuint divisor))
_COREGL_SYMBOL(GL_FALSE, void, glBindTransformFeedback, (GLenum target, GLuint id))
_COREGL_SYMBOL(GL_FALSE, void, glDeleteTransformFeedbacks, (GLsizei n, const GLuint* ids))
_COREGL_SYMBOL(GL_FALSE, void, glGenTransformFeedbacks, (GLsizei n, GLuint* ids))
_COREGL_SYMBOL(GL_FALSE, GLboolean, glIsTransformFeedback, (GLuint id))
_COREGL_SYMBOL(GL_FALSE, void, glPauseTransformFeedback, (void))
_COREGL_SYMBOL(GL_FALSE, void, glResumeTransformFeedback, (void))
_COREGL_SYMBOL(GL_FALSE, void, glGetProgramBinary, (GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, GLvoid* binary))
_COREGL_SYMBOL(GL_FALSE, void, glProgramBinary, (GLuint program, GLenum binaryFormat, const GLvoid* binary, GLsizei length))
_COREGL_SYMBOL(GL_FALSE, void, glProgramParameteri, (GLuint program, GLenum pname, GLint value))
_COREGL_SYMBOL(GL_FALSE, void, glInvalidateFramebuffer, (GLenum target, GLsizei numAttachments, const GLenum* attachments))
_COREGL_SYMBOL(GL_FALSE, void, glInvalidateSubFramebuffer, (GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height))
_COREGL_SYMBOL(GL_FALSE, void, glTexStorage2D, (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height))
_COREGL_SYMBOL(GL_FALSE, void, glTexStorage3D, (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth))
_COREGL_SYMBOL(GL_FALSE, void, glGetInternalformativ, (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params))


/* Extensions */

// OES_EGL_image
_COREGL_EXT_SYMBOL(GL_TRUE, void, glEGLImageTargetTexture2DOES, (GLenum target, GLeglImageOES image))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glEGLImageTargetRenderbufferStorageOES, (GLenum target, GLeglImageOES image))

// OES_get_program_binary
_COREGL_EXT_SYMBOL(GL_TRUE, void, glGetProgramBinaryOES, (GLuint program, GLsizei bufsize, GLsizei *length, GLenum *binaryFormat, void *binary))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramBinaryOES, (GLuint program, GLenum binaryFormat, const void *binary, GLint length))

// EXT_separate_shader_objects
_COREGL_EXT_SYMBOL(GL_TRUE, void, glUseProgramStagesEXT, (GLuint pipeline, GLbitfield stages, GLuint program))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glActiveShaderProgramEXT, (GLuint pipeline, GLuint program))
_COREGL_EXT_SYMBOL(GL_TRUE, GLuint, glCreateShaderProgramvEXT, (GLenum type, GLsizei count, const char **strings))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glBindProgramPipelineEXT, (GLuint pipeline))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glDeleteProgramPipelinesEXT, (GLsizei n, const GLuint *pipelines))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glGenProgramPipelinesEXT, (GLsizei n, GLuint *pipelines))
_COREGL_EXT_SYMBOL(GL_TRUE, GLboolean, glIsProgramPipelineEXT, (GLuint pipeline))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramParameteriEXT, (GLuint program, GLenum pname, GLint value))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glGetProgramPipelineivEXT, (GLuint pipeline, GLenum pname, GLint *params))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform1iEXT, (GLuint program, GLint location, GLint x))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform2iEXT, (GLuint program, GLint location, GLint x, GLint y))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform3iEXT, (GLuint program, GLint location, GLint x, GLint y, GLint z))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform4iEXT, (GLuint program, GLint location, GLint x, GLint y, GLint z, GLint w))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform1fEXT, (GLuint program, GLint location, GLfloat x))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform2fEXT, (GLuint program, GLint location, GLfloat x, GLfloat y))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform3fEXT, (GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform4fEXT, (GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform1ivEXT, (GLuint program, GLint location, GLsizei count, const GLint *value))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform2ivEXT, (GLuint program, GLint location, GLsizei count, const GLint *value))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform3ivEXT, (GLuint program, GLint location, GLsizei count, const GLint *value))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform4ivEXT, (GLuint program, GLint location, GLsizei count, const GLint *value))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform1fvEXT, (GLuint program, GLint location, GLsizei count, const GLfloat *value))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform2fvEXT, (GLuint program, GLint location, GLsizei count, const GLfloat *value))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform3fvEXT, (GLuint program, GLint location, GLsizei count, const GLfloat *value))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform4fvEXT, (GLuint program, GLint location, GLsizei count, const GLfloat *value))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniformMatrix2fvEXT, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniformMatrix3fvEXT, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniformMatrix4fvEXT, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glValidateProgramPipelineEXT, (GLuint pipeline))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glGetProgramPipelineInfoLogEXT, (GLuint pipeline, GLsizei bufSize, GLsizei *length, char *infoLog))

// EXT_multisampled_render_to_texture
_COREGL_EXT_SYMBOL(GL_TRUE, void, glRenderbufferStorageMultisampleEXT, (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height))
_COREGL_EXT_SYMBOL(GL_TRUE, void, glFramebufferTexture2DMultisampleEXT, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples))

// EXT_discard_framebuffer
_COREGL_EXT_SYMBOL(GL_TRUE, void, glDiscardFramebufferEXT, (GLenum target, GLsizei numAttachments, const GLenum *attachments))

// OES_texture_3d
_COREGL_EXT_SYMBOL_ALIAS(glTexImage3DOES, glTexImage3D) // Replaced to ES 3.0 API
_COREGL_EXT_SYMBOL_ALIAS(glTexSubImage3DOES, glTexSubImage3D) // Replaced to ES 3.0 API
_COREGL_EXT_SYMBOL_ALIAS(glCopyTexSubImage3DOES, glCopyTexSubImage3D) // Replaced to ES 3.0 API
_COREGL_EXT_SYMBOL_ALIAS(glCompressedTexImage3DOES, glCompressedTexImage3D) // Replaced to ES 3.0 API
_COREGL_EXT_SYMBOL_ALIAS(glCompressedTexSubImage3DOES, glCompressedTexSubImage3D) // Replaced to ES 3.0 API
_COREGL_EXT_SYMBOL(GL_TRUE, void, glFramebufferTexture3DOES, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset))


/* Fastpath Verified extensions */

// AMD_performance_monitor
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glGetPerfMonitorGroupsAMD)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glGetPerfMonitorCountersAMD)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glGetPerfMonitorGroupStringAMD)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glGetPerfMonitorCounterStringAMD)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glGetPerfMonitorCounterInfoAMD)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glGenPerfMonitorsAMD)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glDeletePerfMonitorsAMD)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glSelectPerfMonitorCountersAMD)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glBeginPerfMonitorAMD)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glEndPerfMonitorAMD)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glGetPerfMonitorCounterDataAMD)

// NV_fence
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glSetFenceNV)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glTestFenceNV)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glFinishFenceNV)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glGenFencesNV)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glDeleteFencesNV)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glIsFenceNV)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glGetFenceivNV)

// QCOM_driver_control
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glGetDriverControlsQCOM)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glGetDriverControlStringQCOM)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glEnableDriverControlQCOM)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glDisableDriverControlQCOM)

// QCOM_tiled_rendering
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glStartTilingQCOM)
_COREGL_EXT_SYMBOL_FASTPATH_PASS(glEndTilingQCOM)


/* Fastpath Blocked extensions */
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glMapBufferRange)
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glUnmapBuffer)
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glGetBufferPointerv)

// QCOM_extended_get
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glExtGetTexturesQCOM)
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glExtGetBuffersQCOM)
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glExtGetRenderbuffersQCOM)
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glExtGetFramebuffersQCOM)
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glExtGetTexLevelParameterivQCOM)
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glExtTexObjectStateOverrideiQCOM)
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glExtGetTexSubImageQCOM)
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glExtGetBufferPointervQCOM)

// QCOM_extended_get2
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glExtGetShadersQCOM)
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glExtGetProgramsQCOM)
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glExtIsProgramBinaryQCOM)
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glExtGetProgramBinarySourceQCOM)

// ANGLE_framebuffer_blit
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glBlitFramebufferANGLE)

// ANGLE_framebuffer_multisample
_COREGL_EXT_SYMBOL_FASTPATH_BLOCK(glRenderbufferStorageMultisampleANGLE)


#ifdef _COREGL_EXT_SYMBOL_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL
#endif

#ifdef _COREGL_SYMBOL_NOT_DEFINED
#undef _COREGL_SYMBOL_NOT_DEFINED
#undef _COREGL_SYMBOL
#endif

#ifdef _COREGL_EXT_SYMBOL_ALIAS_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL_ALIAS_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL_ALIAS
#endif

#ifdef _COREGL_EXT_SYMBOL_FASTPATH_PASS_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL_FASTPATH_PASS_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL_FASTPATH_PASS
#endif

#ifdef _COREGL_EXT_SYMBOL_FASTPATH_BLOCK_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL_FASTPATH_BLOCK_NOT_DEFINED
#undef _COREGL_EXT_SYMBOL_FASTPATH_BLOCK
#endif

