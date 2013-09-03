// Defult use-case for exporting symbols
#ifndef _COREGL_SYMBOL
#define _COREGL_SYMBOL_NOT_DEFINED
#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     COREGL_API extern RET_TYPE FUNC_NAME PARAM_LIST;
#endif
#ifndef _COREGL_EXT_SYMBOL
#define _COREGL_EXT_SYMBOL_NOT_DEFINED
#define _COREGL_EXT_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)  _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)
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

/* version 1: */
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

/* Extensions */

// OES_EGL_image
_COREGL_EXT_SYMBOL(GL_TRUE, void, glEGLImageTargetTexture2DOES, (GLenum target, GLeglImageOES image))
_COREGL_EXT_SYMBOL_ALIAS(glEGLImageTargetTexture2DOES, glEGLImageTargetTexture2D)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glEGLImageTargetRenderbufferStorageOES, (GLenum target, GLeglImageOES image))
_COREGL_EXT_SYMBOL_ALIAS(glEGLImageTargetRenderbufferStorageOES, glEGLImageTargetRenderbufferStorage)

// OES_get_program_binary
_COREGL_EXT_SYMBOL(GL_TRUE, void, glGetProgramBinaryOES, (GLuint program, GLsizei bufsize, GLsizei *length, GLenum *binaryFormat, void *binary))
_COREGL_EXT_SYMBOL_ALIAS(glGetProgramBinaryOES, glGetProgramBinary)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramBinaryOES, (GLuint program, GLenum binaryFormat, const void *binary, GLint length))
_COREGL_EXT_SYMBOL_ALIAS(glProgramBinaryOES, glProgramBinary)

// EXT_separate_shader_objects
_COREGL_EXT_SYMBOL(GL_TRUE, void, glUseProgramStagesEXT, (GLuint pipeline, GLbitfield stages, GLuint program))
_COREGL_EXT_SYMBOL_ALIAS(glUseProgramStagesEXT, glUseProgramStages)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glActiveShaderProgramEXT, (GLuint pipeline, GLuint program))
_COREGL_EXT_SYMBOL_ALIAS(glActiveShaderProgramEXT, glActiveShaderProgram)
_COREGL_EXT_SYMBOL(GL_TRUE, GLuint, glCreateShaderProgramvEXT, (GLenum type, GLsizei count, const char **strings))
_COREGL_EXT_SYMBOL_ALIAS(glCreateShaderProgramvEXT, glCreateShaderProgramv)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glBindProgramPipelineEXT, (GLuint pipeline))
_COREGL_EXT_SYMBOL_ALIAS(glBindProgramPipelineEXT, glBindProgramPipeline)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glDeleteProgramPipelinesEXT, (GLsizei n, const GLuint *pipelines))
_COREGL_EXT_SYMBOL_ALIAS(glDeleteProgramPipelinesEXT, glDeleteProgramPipelines)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glGenProgramPipelinesEXT, (GLsizei n, GLuint *pipelines))
_COREGL_EXT_SYMBOL_ALIAS(glGenProgramPipelinesEXT, glGenProgramPipelines)
_COREGL_EXT_SYMBOL(GL_TRUE, GLboolean, glIsProgramPipelineEXT, (GLuint pipeline))
_COREGL_EXT_SYMBOL_ALIAS(glIsProgramPipelineEXT, glIsProgramPipeline)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramParameteriEXT, (GLuint program, GLenum pname, GLint value))
_COREGL_EXT_SYMBOL_ALIAS(glProgramParameteriEXT, glProgramParameteri)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glGetProgramPipelineivEXT, (GLuint pipeline, GLenum pname, GLint *params))
_COREGL_EXT_SYMBOL_ALIAS(glGetProgramPipelineivEXT, glGetProgramPipelineiv)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform1iEXT, (GLuint program, GLint location, GLint x))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform1iEXT, glProgramUniform1i)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform2iEXT, (GLuint program, GLint location, GLint x, GLint y))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform2iEXT, glProgramUniform2i)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform3iEXT, (GLuint program, GLint location, GLint x, GLint y, GLint z))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform3iEXT, glProgramUniform3i)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform4iEXT, (GLuint program, GLint location, GLint x, GLint y, GLint z, GLint w))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform4iEXT, glProgramUniform4i)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform1fEXT, (GLuint program, GLint location, GLfloat x))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform1fEXT, glProgramUniform1f)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform2fEXT, (GLuint program, GLint location, GLfloat x, GLfloat y))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform2fEXT, glProgramUniform2f)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform3fEXT, (GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform3fEXT, glProgramUniform3f)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform4fEXT, (GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform4fEXT, glProgramUniform4f)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform1ivEXT, (GLuint program, GLint location, GLsizei count, const GLint *value))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform1ivEXT, glProgramUniform1iv)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform2ivEXT, (GLuint program, GLint location, GLsizei count, const GLint *value))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform2ivEXT, glProgramUniform2iv)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform3ivEXT, (GLuint program, GLint location, GLsizei count, const GLint *value))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform3ivEXT, glProgramUniform3iv)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform4ivEXT, (GLuint program, GLint location, GLsizei count, const GLint *value))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform4ivEXT, glProgramUniform4iv)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform1fvEXT, (GLuint program, GLint location, GLsizei count, const GLfloat *value))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform1fvEXT, glProgramUniform1fv)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform2fvEXT, (GLuint program, GLint location, GLsizei count, const GLfloat *value))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform2fvEXT, glProgramUniform2fv)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform3fvEXT, (GLuint program, GLint location, GLsizei count, const GLfloat *value))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform3fvEXT, glProgramUniform3fv)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniform4fvEXT, (GLuint program, GLint location, GLsizei count, const GLfloat *value))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniform4fvEXT, glProgramUniform4fv)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniformMatrix2fvEXT, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniformMatrix2fvEXT, glProgramUniformMatrix2fv)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniformMatrix3fvEXT, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniformMatrix3fvEXT, glProgramUniformMatrix3fv)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glProgramUniformMatrix4fvEXT, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))
_COREGL_EXT_SYMBOL_ALIAS(glProgramUniformMatrix4fvEXT, glProgramUniformMatrix4fv)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glValidateProgramPipelineEXT, (GLuint pipeline))
_COREGL_EXT_SYMBOL_ALIAS(glValidateProgramPipelineEXT, glValidateProgramPipeline)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glGetProgramPipelineInfoLogEXT, (GLuint pipeline, GLsizei bufSize, GLsizei *length, char *infoLog))
_COREGL_EXT_SYMBOL_ALIAS(glGetProgramPipelineInfoLogEXT, glGetProgramPipelineInfoLog)

// EXT_multisampled_render_to_texture
_COREGL_EXT_SYMBOL(GL_TRUE, void, glRenderbufferStorageMultisampleEXT, (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height))
_COREGL_EXT_SYMBOL_ALIAS(glRenderbufferStorageMultisampleEXT, glRenderbufferStorageMultisample)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glFramebufferTexture2DMultisampleEXT, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples))
_COREGL_EXT_SYMBOL_ALIAS(glFramebufferTexture2DMultisampleEXT, glFramebufferTexture2DMultisample)

// EXT_discard_framebuffer
_COREGL_EXT_SYMBOL(GL_TRUE, void, glDiscardFramebufferEXT, (GLenum target, GLsizei numAttachments, const GLenum *attachments))
_COREGL_EXT_SYMBOL_ALIAS(glDiscardFramebufferEXT, glDiscardFramebuffer)

// OES_texture_3d
_COREGL_EXT_SYMBOL(GL_TRUE, void, glTexImage3DOES, (GLenum target, GLint level, GLenum GLinternalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels))
_COREGL_EXT_SYMBOL_ALIAS(glTexImage3DOES, glTexImage3D)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glTexSubImage3DOES, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels))
_COREGL_EXT_SYMBOL_ALIAS(glTexSubImage3DOES, glTexSubImage3D)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glCopyTexSubImage3DOES, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height))
_COREGL_EXT_SYMBOL_ALIAS(glCopyTexSubImage3DOES, glCopyTexSubImage3D)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glCompressedTexImage3DOES, (GLenum target, GLint level, GLenum GLinternalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data))
_COREGL_EXT_SYMBOL_ALIAS(glCompressedTexImage3DOES, glCompressedTexImage3D)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glCompressedTexSubImage3DOES, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data))
_COREGL_EXT_SYMBOL_ALIAS(glCompressedTexSubImage3DOES, glCompressedTexSubImage3D)
_COREGL_EXT_SYMBOL(GL_TRUE, void, glFramebufferTexture3DOES, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset))
_COREGL_EXT_SYMBOL_ALIAS(glFramebufferTexture3DOES, glFramebufferTexture3D)

// ANGLE_framebuffer_blit
_COREGL_EXT_SYMBOL(GL_TRUE, void, glBlitFramebufferANGLE, (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter))

// ANGLE_framebuffer_multisample
_COREGL_EXT_SYMBOL(GL_TRUE, void, glRenderbufferStorageMultisampleANGLE, (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height))



/* Verified extensions */

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

/* Blocked extensions */
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

