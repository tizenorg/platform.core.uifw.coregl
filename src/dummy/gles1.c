/*
 * from opengl-es-virtual-drv package
 *
 * Copyright (c) 2000 - 2016 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Minsu Han <minsu81.han@samsung.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <GLES/gl.h>

#pragma GCC visibility push(default)
/* Available only in Common profile */
void glAlphaFunc (GLenum func, GLclampf ref) { return; }
void glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) { return; }
void glClearDepthf (GLclampf depth) { return; }
void glClipPlanef (GLenum plane, const GLfloat *equation) { return; }
void glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) { return; }
void glDepthRangef (GLclampf zNear, GLclampf zFar) { return; }
void glFogf (GLenum pname, GLfloat param) { return; }
void glFogfv (GLenum pname, const GLfloat *params) { return; }
void glFrustumf (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) { return; }
void glGetClipPlanef (GLenum pname, GLfloat eqn[4]) { return; }
void glGetFloatv (GLenum pname, GLfloat *params) { return; }
void glGetLightfv (GLenum light, GLenum pname, GLfloat *params) { return; }
void glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params) { return; }
void glGetTexEnvfv (GLenum env, GLenum pname, GLfloat *params) { return; }
void glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params) { return; }
void glLightModelf (GLenum pname, GLfloat param) { return; }
void glLightModelfv (GLenum pname, const GLfloat *params) { return; }
void glLightf (GLenum light, GLenum pname, GLfloat param) { return; }
void glLightfv (GLenum light, GLenum pname, const GLfloat *params) { return; }
void glLineWidth (GLfloat width) { return; }
void glLoadMatrixf (const GLfloat *m) { return; }
void glMaterialf (GLenum face, GLenum pname, GLfloat param) { return; }
void glMaterialfv (GLenum face, GLenum pname, const GLfloat *params) { return; }
void glMultMatrixf (const GLfloat *m) { return; }
void glMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) { return; }
void glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz) { return; }
void glOrthof (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) { return; }
void glPointParameterf (GLenum pname, GLfloat param) { return; }
void glPointParameterfv (GLenum pname, const GLfloat *params) { return; }
void glPointSize (GLfloat size) { return; }
void glPolygonOffset (GLfloat factor, GLfloat units) { return; }
void glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z) { return; }
void glScalef (GLfloat x, GLfloat y, GLfloat z) { return; }
void glTexEnvf (GLenum target, GLenum pname, GLfloat param) { return; }
void glTexEnvfv (GLenum target, GLenum pname, const GLfloat *params) { return; }
void glTexParameterf (GLenum target, GLenum pname, GLfloat param) { return; }
void glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params) { return; }
void glTranslatef (GLfloat x, GLfloat y, GLfloat z) { return; }

/* Available in both Common and Common-Lite profiles */
void glActiveTexture (GLenum texture) { return; }
void glAlphaFuncx (GLenum func, GLclampx ref) { return; }
void glBindBuffer (GLenum target, GLuint buffer) { return; }
void glBindTexture (GLenum target, GLuint texture) { return; }
void glBlendFunc (GLenum sfactor, GLenum dfactor) { return; }
void glBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage) { return; }
void glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data) { return; }
void glClear (GLbitfield mask) { return; }
void glClearColorx (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha) { return; }
void glClearDepthx (GLclampx depth) { return; }
void glClearStencil (GLint s) { return; }
void glClientActiveTexture (GLenum texture) { return; }
void glClipPlanex (GLenum plane, const GLfixed *equation) { return; }
void glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) { return; }
void glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha) { return; }
void glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) { return; }
void glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) { return; }
void glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data) { return; }
void glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data) { return; }
void glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) { return; }
void glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) { return; }
void glCullFace (GLenum mode) { return; }
void glDeleteBuffers (GLsizei n, const GLuint *buffers) { return; }
void glDeleteTextures (GLsizei n, const GLuint *textures) { return; }
void glDepthFunc (GLenum func) { return; }
void glDepthMask (GLboolean flag) { return; }
void glDepthRangex (GLclampx zNear, GLclampx zFar) { return; }
void glDisable (GLenum cap) { return; }
void glDisableClientState (GLenum array) { return; }
void glDrawArrays (GLenum mode, GLint first, GLsizei count) { return; }
void glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) { return; }
void glEnable (GLenum cap) { return; }
void glEnableClientState (GLenum array) { return; }
void glFinish (void) { return; }
void glFlush (void) { return; }
void glFogx (GLenum pname, GLfixed param) { return; }
void glFogxv (GLenum pname, const GLfixed *params) { return; }
void glFrontFace (GLenum mode) { return; }
void glFrustumx (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar) { return; }
void glGetBooleanv (GLenum pname, GLboolean *params) { return; }
void glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params) { return; }
void glGetClipPlanex (GLenum pname, GLfixed eqn[4]) { return; }
void glGenBuffers (GLsizei n, GLuint *buffers) { return; }
void glGenTextures (GLsizei n, GLuint *textures) { return; }
GLenum glGetError (void) { return 0; }
void glGetFixedv (GLenum pname, GLfixed *params) { return; }
void glGetIntegerv (GLenum pname, GLint *params) { return; }
void glGetLightxv (GLenum light, GLenum pname, GLfixed *params) { return; }
void glGetMaterialxv (GLenum face, GLenum pname, GLfixed *params) { return; }
void glGetPointerv (GLenum pname, GLvoid **params) { return; }
const GLubyte * GL_APIENTRY glGetString (GLenum name) { return 0; }
void glGetTexEnviv (GLenum env, GLenum pname, GLint *params) { return; }
void glGetTexEnvxv (GLenum env, GLenum pname, GLfixed *params) { return; }
void glGetTexParameteriv (GLenum target, GLenum pname, GLint *params) { return; }
void glGetTexParameterxv (GLenum target, GLenum pname, GLfixed *params) { return; }
void glHint (GLenum target, GLenum mode) { return; }
GLboolean glIsBuffer (GLuint buffer) { return 0; }
GLboolean glIsEnabled (GLenum cap) { return 0; }
GLboolean glIsTexture (GLuint texture) { return 0; }
void glLightModelx (GLenum pname, GLfixed param) { return; }
void glLightModelxv (GLenum pname, const GLfixed *params) { return; }
void glLightx (GLenum light, GLenum pname, GLfixed param) { return; }
void glLightxv (GLenum light, GLenum pname, const GLfixed *params) { return; }
void glLineWidthx (GLfixed width) { return; }
void glLoadIdentity (void) { return; }
void glLoadMatrixx (const GLfixed *m) { return; }
void glLogicOp (GLenum opcode) { return; }
void glMaterialx (GLenum face, GLenum pname, GLfixed param) { return; }
void glMaterialxv (GLenum face, GLenum pname, const GLfixed *params) { return; }
void glMatrixMode (GLenum mode) { return; }
void glMultMatrixx (const GLfixed *m) { return; }
void glMultiTexCoord4x (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q) { return; }
void glNormal3x (GLfixed nx, GLfixed ny, GLfixed nz) { return; }
void glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer) { return; }
void glOrthox (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar) { return; }
void glPixelStorei (GLenum pname, GLint param) { return; }
void glPointParameterx (GLenum pname, GLfixed param) { return; }
void glPointParameterxv (GLenum pname, const GLfixed *params) { return; }
void glPointSizex (GLfixed size) { return; }
void glPolygonOffsetx (GLfixed factor, GLfixed units) { return; }
void glPopMatrix (void) { return; }
void glPushMatrix (void) { return; }
void glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels) { return; }
void glRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z) { return; }
void glSampleCoverage (GLclampf value, GLboolean invert) { return; }
void glSampleCoveragex (GLclampx value, GLboolean invert) { return; }
void glScalex (GLfixed x, GLfixed y, GLfixed z) { return; }
void glScissor (GLint x, GLint y, GLsizei width, GLsizei height) { return; }
void glShadeModel (GLenum mode) { return; }
void glStencilFunc (GLenum func, GLint ref, GLuint mask) { return; }
void glStencilMask (GLuint mask) { return; }
void glStencilOp (GLenum fail, GLenum zfail, GLenum zpass) { return; }
void glTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) { return; }
void glTexEnvi (GLenum target, GLenum pname, GLint param) { return; }
void glTexEnvx (GLenum target, GLenum pname, GLfixed param) { return; }
void glTexEnviv (GLenum target, GLenum pname, const GLint *params) { return; }
void glTexEnvxv (GLenum target, GLenum pname, const GLfixed *params) { return; }
void glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels) { return; }
void glTexParameteri (GLenum target, GLenum pname, GLint param) { return; }
void glTexParameterx (GLenum target, GLenum pname, GLfixed param) { return; }
void glTexParameteriv (GLenum target, GLenum pname, const GLint *params) { return; }
void glTexParameterxv (GLenum target, GLenum pname, const GLfixed *params) { return; }
void glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) { return; }
void glTranslatex (GLfixed x, GLfixed y, GLfixed z) { return; }
void glVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) { return; }
void glViewport (GLint x, GLint y, GLsizei width, GLsizei height) { return; }
void glPointSizePointerOES (GLenum type, GLsizei stride, const GLvoid *pointer) { return; }

/*------------------------------------------------------------------------*
 * End of extension tokens, start of corresponding extension functions
 *------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*
 * OES extension functions
 *------------------------------------------------------------------------*/

/* GL_OES_blend_equation_separate */
#ifdef GL_OES_blend_equation_separate
GL_API void GL_APIENTRY glBlendEquationSeparateOES (GLenum modeRGB, GLenum modeAlpha){ return; }
#endif

/* GL_OES_blend_func_separate */
#ifdef GL_OES_blend_func_separate
GL_API void GL_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha){ return; }
#endif

/* GL_OES_blend_subtract */
#ifdef GL_OES_blend_subtract
GL_API void GL_APIENTRY glBlendEquationOES (GLenum mode){ return; }
#endif


/* GL_OES_draw_texture */
#ifdef GL_OES_draw_texture
GL_API void GL_APIENTRY glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort width, GLshort height){ return; }
GL_API void GL_APIENTRY glDrawTexiOES (GLint x, GLint y, GLint z, GLint width, GLint height){ return; }
GL_API void GL_APIENTRY glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height){ return; }
GL_API void GL_APIENTRY glDrawTexsvOES (const GLshort *coords){ return; }
GL_API void GL_APIENTRY glDrawTexivOES (const GLint *coords){ return; }
GL_API void GL_APIENTRY glDrawTexxvOES (const GLfixed *coords){ return; }
GL_API void GL_APIENTRY glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height){ return; }
GL_API void GL_APIENTRY glDrawTexfvOES (const GLfloat *coords){ return; }
#endif

/* GL_OES_EGL_image */
#ifdef GL_OES_EGL_image
GL_API void GL_APIENTRY glEGLImageTargetTexture2DOES (GLenum target, GLeglImageOES image){ return; }
GL_API void GL_APIENTRY glEGLImageTargetRenderbufferStorageOES (GLenum target, GLeglImageOES image){ return; }
#endif

/* GL_OES_fixed_point */
#ifdef GL_OES_fixed_point
GL_API void GL_APIENTRY glAlphaFuncxOES (GLenum func, GLclampx ref){ return; }
GL_API void GL_APIENTRY glClearColorxOES (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha){ return; }
GL_API void GL_APIENTRY glClearDepthxOES (GLclampx depth){ return; }
GL_API void GL_APIENTRY glClipPlanexOES (GLenum plane, const GLfixed *equation){ return; }
GL_API void GL_APIENTRY glColor4xOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha){ return; }
GL_API void GL_APIENTRY glDepthRangexOES (GLclampx zNear, GLclampx zFar){ return; }
GL_API void GL_APIENTRY glFogxOES (GLenum pname, GLfixed param){ return; }
GL_API void GL_APIENTRY glFogxvOES (GLenum pname, const GLfixed *params){ return; }
GL_API void GL_APIENTRY glFrustumxOES (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar){ return; }
GL_API void GL_APIENTRY glGetClipPlanexOES (GLenum pname, GLfixed eqn[4]){ return; }
GL_API void GL_APIENTRY glGetFixedvOES (GLenum pname, GLfixed *params){ return; }
GL_API void GL_APIENTRY glGetLightxvOES (GLenum light, GLenum pname, GLfixed *params){ return; }
GL_API void GL_APIENTRY glGetMaterialxvOES (GLenum face, GLenum pname, GLfixed *params){ return; }
GL_API void GL_APIENTRY glGetTexEnvxvOES (GLenum env, GLenum pname, GLfixed *params){ return; }
GL_API void GL_APIENTRY glGetTexParameterxvOES (GLenum target, GLenum pname, GLfixed *params){ return; }
GL_API void GL_APIENTRY glLightModelxOES (GLenum pname, GLfixed param){ return; }
GL_API void GL_APIENTRY glLightModelxvOES (GLenum pname, const GLfixed *params){ return; }
GL_API void GL_APIENTRY glLightxOES (GLenum light, GLenum pname, GLfixed param){ return; }
GL_API void GL_APIENTRY glLightxvOES (GLenum light, GLenum pname, const GLfixed *params){ return; }
GL_API void GL_APIENTRY glLineWidthxOES (GLfixed width){ return; }
GL_API void GL_APIENTRY glLoadMatrixxOES (const GLfixed *m){ return; }
GL_API void GL_APIENTRY glMaterialxOES (GLenum face, GLenum pname, GLfixed param){ return; }
GL_API void GL_APIENTRY glMaterialxvOES (GLenum face, GLenum pname, const GLfixed *params){ return; }
GL_API void GL_APIENTRY glMultMatrixxOES (const GLfixed *m){ return; }
GL_API void GL_APIENTRY glMultiTexCoord4xOES (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q){ return; }
GL_API void GL_APIENTRY glNormal3xOES (GLfixed nx, GLfixed ny, GLfixed nz){ return; }
GL_API void GL_APIENTRY glOrthoxOES (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar){ return; }
GL_API void GL_APIENTRY glPointParameterxOES (GLenum pname, GLfixed param){ return; }
GL_API void GL_APIENTRY glPointParameterxvOES (GLenum pname, const GLfixed *params){ return; }
GL_API void GL_APIENTRY glPointSizexOES (GLfixed size){ return; }
GL_API void GL_APIENTRY glPolygonOffsetxOES (GLfixed factor, GLfixed units){ return; }
GL_API void GL_APIENTRY glRotatexOES (GLfixed angle, GLfixed x, GLfixed y, GLfixed z){ return; }
GL_API void GL_APIENTRY glSampleCoveragexOES (GLclampx value, GLboolean invert){ return; }
GL_API void GL_APIENTRY glScalexOES (GLfixed x, GLfixed y, GLfixed z){ return; }
GL_API void GL_APIENTRY glTexEnvxOES (GLenum target, GLenum pname, GLfixed param){ return; }
GL_API void GL_APIENTRY glTexEnvxvOES (GLenum target, GLenum pname, const GLfixed *params){ return; }
GL_API void GL_APIENTRY glTexParameterxOES (GLenum target, GLenum pname, GLfixed param){ return; }
GL_API void GL_APIENTRY glTexParameterxvOES (GLenum target, GLenum pname, const GLfixed *params){ return; }
GL_API void GL_APIENTRY glTranslatexOES (GLfixed x, GLfixed y, GLfixed z){ return; }
#endif

/* GL_OES_framebuffer_object */
#ifdef GL_OES_framebuffer_object
GL_API GLboolean GL_APIENTRY glIsRenderbufferOES (GLuint renderbuffer){ return; }
GL_API void GL_APIENTRY glBindRenderbufferOES (GLenum target, GLuint renderbuffer){ return; }
GL_API void GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, const GLuint* renderbuffers){ return; }
GL_API void GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint* renderbuffers){ return; }
GL_API void GL_APIENTRY glRenderbufferStorageOES (GLenum target, GLenum internalformat, GLsizei width, GLsizei height){ return; }
GL_API void GL_APIENTRY glGetRenderbufferParameterivOES (GLenum target, GLenum pname, GLint* params){ return; }
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer){ return; }
GL_API void GL_APIENTRY glBindFramebufferOES (GLenum target, GLuint framebuffer){ return; }
GL_API void GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, const GLuint* framebuffers){ return; }
GL_API void GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint* framebuffers){ return; }
GL_API GLenum GL_APIENTRY glCheckFramebufferStatusOES (GLenum target){ return; }
GL_API void GL_APIENTRY glFramebufferRenderbufferOES (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer){ return; }
GL_API void GL_APIENTRY glFramebufferTexture2DOES (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){ return; }
GL_API void GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum target, GLenum attachment, GLenum pname, GLint* params){ return; }
GL_API void GL_APIENTRY glGenerateMipmapOES (GLenum target){ return; }
#endif

/* GL_OES_mapbuffer */
#ifdef GL_OES_mapbuffer
GL_API void* GL_APIENTRY glMapBufferOES (GLenum target, GLenum access){ return; }
GL_API GLboolean GL_APIENTRY glUnmapBufferOES (GLenum target){ return; }
GL_API void GL_APIENTRY glGetBufferPointervOES (GLenum target, GLenum pname, void** params){ return; }
#endif

/* GL_OES_matrix_palette */
#ifdef GL_OES_matrix_palette
GL_API void GL_APIENTRY glCurrentPaletteMatrixOES (GLuint matrixpaletteindex){ return; }
GL_API void GL_APIENTRY glLoadPaletteFromModelViewMatrixOES (void){ return; }
GL_API void GL_APIENTRY glMatrixIndexPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer){ return; }
GL_API void GL_APIENTRY glWeightPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer){ return; }
#endif

/* GL_OES_query_matrix */
#ifdef GL_OES_query_matrix
GL_API GLbitfield GL_APIENTRY glQueryMatrixxOES (GLfixed mantissa[16], GLint exponent[16]){ return; }
#endif

/* GL_OES_single_precision */
#ifdef GL_OES_single_precision
GL_API void GL_APIENTRY glDepthRangefOES (GLclampf zNear, GLclampf zFar){ return; }
GL_API void GL_APIENTRY glFrustumfOES (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar){ return; }
GL_API void GL_APIENTRY glOrthofOES (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar){ return; }
GL_API void GL_APIENTRY glClipPlanefOES (GLenum plane, const GLfloat *equation){ return; }
GL_API void GL_APIENTRY glGetClipPlanefOES (GLenum pname, GLfloat eqn[4]){ return; }
GL_API void GL_APIENTRY glClearDepthfOES (GLclampf depth){ return; }
#endif

/* GL_OES_texture_cube_map */
#ifdef GL_OES_texture_cube_map
GL_API void GL_APIENTRY glTexGenfOES (GLenum coord, GLenum pname, GLfloat param){ return; }
GL_API void GL_APIENTRY glTexGenfvOES (GLenum coord, GLenum pname, const GLfloat *params){ return; }
GL_API void GL_APIENTRY glTexGeniOES (GLenum coord, GLenum pname, GLint param){ return; }
GL_API void GL_APIENTRY glTexGenivOES (GLenum coord, GLenum pname, const GLint *params){ return; }
GL_API void GL_APIENTRY glTexGenxOES (GLenum coord, GLenum pname, GLfixed param){ return; }
GL_API void GL_APIENTRY glTexGenxvOES (GLenum coord, GLenum pname, const GLfixed *params){ return; }
GL_API void GL_APIENTRY glGetTexGenfvOES (GLenum coord, GLenum pname, GLfloat *params){ return; }
GL_API void GL_APIENTRY glGetTexGenivOES (GLenum coord, GLenum pname, GLint *params){ return; }
GL_API void GL_APIENTRY glGetTexGenxvOES (GLenum coord, GLenum pname, GLfixed *params){ return; }
#endif

/* GL_OES_vertex_array_object  */
#ifdef GL_OES_vertex_array_object
GL_API void GL_APIENTRY glBindVertexArrayOES(GLuint vertexarray){ return; }
GL_API void GL_APIENTRY glDeleteVertexArraysOES(GLsizei n, const GLuint *vertexarrays){ return; }
GL_API void GL_APIENTRY glGenVertexArraysOES(GLsizei n, const GLuint *vertexarrays){ return; }
GL_API GLboolean GL_APIENTRY glIsVertexArrayOES (GLuint vertexarray){ return; }
#endif

/* GL_APPLE_framebuffer_multisample */
#ifdef GL_APPLE_framebuffer_multisample
GL_API void GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum, GLsizei, GLenum, GLsizei, GLsizei){ return; }
GL_API void GL_APIENTRY glResolveMultisampleFramebufferAPPLE (void){ return; }
#endif

/* GL_EXT_discard_framebuffer */
#ifdef GL_EXT_discard_framebuffer
GL_API void GL_APIENTRY glDiscardFramebufferEXT (GLenum target, GLsizei numAttachments, const GLenum *attachments){ return; }
#endif

/* GL_EXT_multi_draw_arrays */
#ifdef GL_EXT_multi_draw_arrays
GL_API void GL_APIENTRY glMultiDrawArraysEXT (GLenum, GLint *, GLsizei *, GLsizei){ return; }
GL_API void GL_APIENTRY glMultiDrawElementsEXT (GLenum, const GLsizei *, GLenum, const GLvoid* *, GLsizei){ return; }
#endif

/* GL_EXT_multisampled_render_to_texture */
#ifdef GL_EXT_multisampled_render_to_texture
GL_APICALL void GL_APIENTRY glRenderbufferStorageMultisampleEXT( GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height){ return; }
GL_APICALL void GL_APIENTRY glFramebufferTexture2DMultisampleEXT( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples){ return; }
#endif

/* GL_IMG_user_clip_plane */
#ifdef GL_IMG_user_clip_plane
GL_API void GL_APIENTRY glClipPlanefIMG (GLenum, const GLfloat *){ return; }
GL_API void GL_APIENTRY glClipPlanexIMG (GLenum, const GLfixed *){ return; }
#endif

/* GL_IMG_multisampled_render_to_texture */
#ifdef GL_IMG_multisampled_render_to_texture
GL_API void GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum, GLsizei, GLenum, GLsizei, GLsizei){ return; }
GL_API void GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum, GLenum, GLenum, GLuint, GLint, GLsizei){ return; }
#endif

/* GL_IMG_texture_stream */
#ifdef GL_IMG_texture_stream
GL_API void GL_APIENTRY glTexBindStreamIMG(GLint device, GLint deviceoffset){ return; }
GL_API void GL_APIENTRY glGetTexStreamDeviceAttributeivIMG(GLint device, GLenum pname, GLint *params){ return; }
GL_API const GLubyte * GL_APIENTRY glGetTexStreamDeviceNameIMG(GLint device){ return; }
#endif

/* GL_IMG_vertex_program */
#ifdef GL_IMG_vertex_program
GL_API void GL_APIENTRY glVertexAttrib4fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w){ return; }
GL_API void GL_APIENTRY glProgramEnvParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w){ return; }
GL_API void GL_APIENTRY glProgramEnvParameter4fvARB(GLenum target, GLuint index, const GLfloat *params){ return; }
GL_API void GL_APIENTRY glProgramLocalParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w){ return; }
GL_API void GL_APIENTRY glProgramLocalParameter4fvARB(GLenum target, GLuint index, const GLfloat *params){ return; }
GL_API void GL_APIENTRY glVertexAttrib4xIMG(GLuint index, GLfixed x, GLfixed y, GLfixed z, GLfixed w){ return; }
GL_API void GL_APIENTRY glProgramLocalParameter4xIMG(GLenum target, GLuint index, GLfixed x, GLfixed y, GLfixed z, GLfixed w){ return; }
GL_API void GL_APIENTRY glProgramLocalParameter4xvIMG(GLenum target, GLuint index, const GLfixed *params){ return; }
GL_API void GL_APIENTRY glProgramEnvParameter4xIMG(GLenum target, GLuint index, GLfixed x, GLfixed y, GLfixed z, GLfixed w){ return; }
GL_API void GL_APIENTRY glProgramEnvParameter4xvIMG(GLenum target, GLuint index, const GLfixed *params){ return; }
GL_API void GL_APIENTRY glVertexAttribPointerARB(GLuint index, GLsizei size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer){ return; }
GL_API void GL_APIENTRY glEnableVertexAttribArrayARB(GLuint index){ return; }
GL_API void GL_APIENTRY glDisableVertexAttribArrayARB(GLuint index){ return; }
GL_API void GL_APIENTRY glProgramStringARB(GLenum target, GLenum format, GLsizei len, const void *string){ return; }
GL_API void GL_APIENTRY glBindProgramARB(GLenum target, GLuint program){ return; }
GL_API void GL_APIENTRY glDeleteProgramsARB(GLsizei n, const GLuint *programs){ return; }
GL_API void GL_APIENTRY glGenProgramsARB(GLsizei n, GLuint *programs){ return; }
#endif


/*------------------------------------------------------------------------*
 * NV extension functions
 *------------------------------------------------------------------------*/

/* NV_fence */
#ifdef GL_NV_fence
GL_API void GL_APIENTRY glDeleteFencesNV (GLsizei, const GLuint *){ return; }
GL_API void GL_APIENTRY glGenFencesNV (GLsizei, GLuint *){ return; }
GL_API GLboolean GL_APIENTRY glIsFenceNV (GLuint){ return; }
GL_API GLboolean GL_APIENTRY glTestFenceNV (GLuint){ return; }
GL_API void GL_APIENTRY glGetFenceivNV (GLuint, GLenum, GLint *){ return; }
GL_API void GL_APIENTRY glFinishFenceNV (GLuint){ return; }
GL_API void GL_APIENTRY glSetFenceNV (GLuint, GLenum){ return; }
#endif


/*------------------------------------------------------------------------*
 * QCOM extension functions
 *------------------------------------------------------------------------*/

/* GL_QCOM_driver_control */
#ifdef GL_QCOM_driver_control
GL_API void GL_APIENTRY glGetDriverControlsQCOM (GLint *num, GLsizei size, GLuint *driverControls){ return; }
GL_API void GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei bufSize, GLsizei *length, char *driverControlString){ return; }
GL_API void GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl){ return; }
GL_API void GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl){ return; }
#endif

/* GL_QCOM_extended_get */
#ifdef GL_QCOM_extended_get
GL_API void GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *numTextures){ return; }
GL_API void GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *numBuffers){ return; }
GL_API void GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *numRenderbuffers){ return; }
GL_API void GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *numFramebuffers){ return; }
GL_API void GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params){ return; }
GL_API void GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum target, GLenum pname, GLint param){ return; }
GL_API void GL_APIENTRY glExtGetTexSubImageQCOM (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, void *texels){ return; }
GL_API void GL_APIENTRY glExtGetBufferPointervQCOM (GLenum target, void **params){ return; }
#endif

/* GL_QCOM_extended_get2 */
#ifdef GL_QCOM_extended_get2
GL_API void GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *numShaders){ return; }
GL_API void GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *numPrograms){ return; }
GL_API GLboolean GL_APIENTRY glExtIsProgramBinaryQCOM (GLuint program){ return; }
GL_API void GL_APIENTRY glExtGetProgramBinarySourceQCOM (GLuint program, GLenum shadertype, char *source, GLint *length){ return; }
#endif

/* GL_QCOM_tiled_rendering */
#ifdef GL_QCOM_tiled_rendering
GL_API void GL_APIENTRY glStartTilingQCOM (GLuint x, GLuint y, GLuint width, GLuint height, GLbitfield preserveMask){ return; }
GL_API void GL_APIENTRY glEndTilingQCOM (GLbitfield preserveMask){ return; }
#endif

#pragma GCC visibility pop
