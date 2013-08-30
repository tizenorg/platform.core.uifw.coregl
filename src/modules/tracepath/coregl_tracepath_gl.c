#include "coregl_tracepath.h"

#include <stdlib.h>

struct _Glbuf_Data
{
	int obj_idx;
	int width;
	int height;
	int bpp;
	char format[80];

	struct _Glbuf_Data *next;
};

static void
__addhash_glbuf_object(Glbuf_Data **glbuf, Glbuf_Data *target)
{
	Glbuf_Data *data = glbuf[target->obj_idx % MTD_GLBUF_HASH_ARRAY];
	if (data == NULL)
	{
		glbuf[target->obj_idx % MTD_GLBUF_HASH_ARRAY] = target;
	}
	else
	{
		while (data->next != NULL)
		{
			AST(data->obj_idx != target->obj_idx);
			data = data->next;
		}
		AST(data->obj_idx != target->obj_idx);
		data->next = target;
	}
	goto finish;

finish:
	return;
}

static void
__removehash_glbuf_object(Glbuf_Data **glbuf, Glbuf_Data **target)
{
	Glbuf_Data *data = glbuf[(*target)->obj_idx % MTD_GLBUF_HASH_ARRAY];
	Glbuf_Data *prev = NULL;
	while (data != NULL)
	{
		if (data->obj_idx == (*target)->obj_idx)
		{
			if (prev != NULL)
				prev->next = data->next;
			else
				glbuf[(*target)->obj_idx % MTD_GLBUF_HASH_ARRAY] = data->next;

			free(*target);
			*target = NULL;
			break;
		}
		prev = data;
		data = data->next;
	}
	goto finish;

finish:
	return;
}

static Glbuf_Data *
__findhash_glbuf_object(Glbuf_Data **glbuf, int obj_idx)
{
	Glbuf_Data *data = glbuf[obj_idx % MTD_GLBUF_HASH_ARRAY];
	while (data != NULL)
	{
		if (data->obj_idx == obj_idx)
			break;
		data = data->next;
	}
	goto finish;

finish:
	return data;
}

void
tracepath_glbuf_clear(Glbuf_Data **glbuf)
{
	int i;

	for (i = 0; i < MTD_GLBUF_HASH_ARRAY; i++)
	{
		Glbuf_Data *data = glbuf[i];

		while (data)
		{
			Glbuf_Data *delitm = data;
			data = data->next;
			free(delitm);
			delitm = NULL;
		}
	}
}

static void
_add_glbuf_object(Glbuf_Data **glbuf, int obj_idx, const char *obj_type, int width, int height, int bpp, const char *format)
{
	Glbuf_Data *data = __findhash_glbuf_object(glbuf, obj_idx);
	if (data == NULL)
	{
		data = (Glbuf_Data *)calloc(1, sizeof(Glbuf_Data));
		data->obj_idx = obj_idx;
		__addhash_glbuf_object(glbuf, data);
	}
	else
	{
		// Update
		{
			char ment[MAX_TRACE_NAME_LENGTH];
			sprintf(ment, "%s(%4dx%4d %s)", obj_type, data->width, data->height, data->format);
			_COREGL_TRACE_MEM_REMOVE(ment, data->width * data->height * data->bpp);
		}
	}

	data->width = width;
	data->height = height;
	data->bpp = bpp;
	sprintf(data->format, "%s", format);

	{
		char ment[MAX_TRACE_NAME_LENGTH];
		sprintf(ment, "%s(%4dx%4d %s)", obj_type, data->width, data->height, data->format);
		_COREGL_TRACE_MEM_ADD(ment, data->width * data->height * data->bpp);
	}
	goto finish;

finish:
	return;
}

static void
_remove_glbuf_object(Glbuf_Data **glbuf, int obj_idx, const char *obj_type)
{
	Glbuf_Data *data = __findhash_glbuf_object(glbuf, obj_idx);
	if (data == NULL)
	{
		COREGL_WRN("\E[40;31;1mError deleting %s object %d. (is not created)\E[0m\n", obj_type, obj_idx);
		return;
	}

	{
		char ment[MAX_TRACE_NAME_LENGTH];
		sprintf(ment, "%s(%4dx%4d %s)", obj_type, data->width, data->height, data->format);
		_COREGL_TRACE_MEM_REMOVE(ment, data->width * data->height * data->bpp);
	}

	__removehash_glbuf_object(glbuf, &data);
	goto finish;

finish:
	return;
}


#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
void
_surface_trace_set(int set, GLint fbname, GLenum attachment, MY_MODULE_TSTATE *tstate)
{
	int atttype = _COREGL_INT_INIT_VALUE;
   _orig_tracepath_glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &atttype);
	AST(atttype != _COREGL_INT_INIT_VALUE);
	int attname = _COREGL_INT_INIT_VALUE;
   _orig_tracepath_glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &attname);
	AST(attname != _COREGL_INT_INIT_VALUE);
	if (set == 1)
	{
		switch (atttype)
		{
			case GL_TEXTURE:
				//COREGL_LOG("FBO DUMPING BEGIN = (TEX)0x%X\n", attname);
				{
					char name[256];
					sprintf(name, "FBOTEX_0x%X", attname);
					tracepath_surface_trace_add(name, tstate->ctx->dpy, tstate->ctx->handle, tstate->surf_draw, fbname, attname, 0, -1, -1, -1, NULL);
				}
				break;
			case GL_RENDERBUFFER:
				//COREGL_LOG("FBO DUMPING BEGIN = (RB)0x%X\n", attname);
				{
					char name[256];
					sprintf(name, "FBORB_0x%X", attname);
					tracepath_surface_trace_add(name, tstate->ctx->dpy, tstate->ctx->handle, tstate->surf_draw, fbname, 0, attname, -1, -1, -1, NULL);
				}
				break;
		}
	}
	else
	{
		switch (atttype)
		{
			case GL_TEXTURE:
				//COREGL_LOG("FBO DUMPING END = (TEX)0x%X\n", attname);
				{
					char name[256];
					sprintf(name, "FBOTEX_0x%X", attname);
					tracepath_surface_trace_add(name, tstate->ctx->dpy, tstate->ctx->handle, tstate->surf_draw, 0, attname, 0, -1, -1, -1, NULL);
				}
				break;
			case GL_RENDERBUFFER:
				//COREGL_LOG("FBO DUMPING END = (RB)0x%X\n", attname);
				{
					char name[256];
					sprintf(name, "FBORB_0x%X", attname);
					tracepath_surface_trace_add(name, tstate->ctx->dpy, tstate->ctx->handle, tstate->surf_draw, 0, 0, attname, -1, -1, -1, NULL);
				}
				break;
		}
	}
}

void
tracepath_fbdump_update(GLint set)
{
	if (trace_surface_flag == 1)
	{
		GLint fbname = _COREGL_INT_INIT_VALUE;
		_orig_tracepath_glGetIntegerv(GL_FRAMEBUFFER_BINDING, &fbname);
		AST(fbname != _COREGL_INT_INIT_VALUE);
		if (fbname != 0)
		{
			MY_MODULE_TSTATE *tstate = NULL;

			GET_MY_TSTATE(tstate, get_current_thread_state());
			AST(tstate != NULL);
			if (tstate->ctx != NULL)
			{
				_surface_trace_set(set, fbname, GL_COLOR_ATTACHMENT0, tstate);
//				_surface_trace_set(set, fbname, GL_DEPTH_ATTACHMENT, tstate);
//				_surface_trace_set(set, fbname, GL_STENCIL_ATTACHMENT, tstate);
			}
		}
	}
}
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO






/* OpenGL ES 2.0 */

void
tracepath_glActiveTexture(GLenum texture)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glActiveTexture(texture);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glAttachShader(GLuint program, GLuint shader)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glAttachShader(program, shader);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBindAttribLocation(GLuint program, GLuint index, const char* name)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBindAttribLocation(program, index, name);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBindBuffer(GLenum target, GLuint buffer)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBindBuffer(target, buffer);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	GLint oldfb;
	_orig_tracepath_glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldfb);
	if (oldfb != 0)
	{
		_COREGL_TRACE_SURFACE(0, 2, "GLBINDFBO");
	}

	tracepath_fbdump_update(0);
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO

	_orig_tracepath_glBindFramebuffer(target, framebuffer);

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	tracepath_fbdump_update(1);
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBindRenderbuffer(target, renderbuffer);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBindTexture(GLenum target, GLuint texture)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBindTexture(target, texture);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBlendColor(red, green, blue, alpha);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBlendEquation(GLenum mode)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBlendEquation(mode);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBlendEquationSeparate(modeRGB, modeAlpha);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBlendFunc(sfactor, dfactor);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBufferData(target, size, data, usage);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBufferSubData(target, offset, size, data);

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

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glClearColor(red, green, blue, alpha);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glClearDepthf(GLclampf depth)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glClearDepthf(depth);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glClearStencil(GLint s)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glClearStencil(s);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glColorMask(red, green, blue, alpha);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glCompileShader(GLuint shader)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glCompileShader(shader);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);

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

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDeleteBuffers(n, buffers);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	tracepath_fbdump_update(0);
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO

	_orig_tracepath_glDeleteFramebuffers(n, framebuffers);

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	tracepath_fbdump_update(1);
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDeleteProgram(GLuint program)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDeleteProgram(program);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	tracepath_fbdump_update(0);
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO

	_orig_tracepath_glDeleteRenderbuffers(n, renderbuffers);

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	tracepath_fbdump_update(1);
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
#ifdef COREGL_TRACEPATH_TRACE_MEMUSE_INFO
	if (trace_mem_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;

		GET_MY_TSTATE(tstate, get_current_thread_state());
		AST(tstate != NULL);
		if (tstate->ctx != NULL)
		{
			for (int i = 0; i < n; i++)
			{
				if (renderbuffers[i] == 0) continue;
				_remove_glbuf_object(tstate->ctx->sostate->glbuf_rb, renderbuffers[i], "Renderbuffer");
			}
		}
	}
#endif // COREGL_TRACEPATH_TRACE_MEMUSE_INFO
}

void
tracepath_glDeleteShader(GLuint shader)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDeleteShader(shader);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDeleteTextures(GLsizei n, const GLuint* textures)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	tracepath_fbdump_update(0);
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO

	_orig_tracepath_glDeleteTextures(n, textures);

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	tracepath_fbdump_update(1);
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
#ifdef COREGL_TRACEPATH_TRACE_MEMUSE_INFO
	if (trace_mem_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;

		GET_MY_TSTATE(tstate, get_current_thread_state());
		AST(tstate != NULL);
		if (tstate->ctx != NULL)
		{
			for (int i = 0; i < n; i++)
			{
				if (textures[i] == 0) continue;
				_remove_glbuf_object(tstate->ctx->sostate->glbuf_tex, textures[i], "Texture");
			}
		}
	}
#endif // COREGL_TRACEPATH_TRACE_MEMUSE_INFO
}

void
tracepath_glDepthFunc(GLenum func)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDepthFunc(func);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDepthMask(GLboolean flag)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDepthMask(flag);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDepthRangef(GLclampf zNear, GLclampf zFar)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDepthRangef(zNear, zFar);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDetachShader(GLuint program, GLuint shader)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDetachShader(program, shader);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDisable(GLenum cap)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDisable(cap);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDisableVertexAttribArray(GLuint index)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDisableVertexAttribArray(index);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDrawArrays(mode, first, count);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	if (trace_surface_flag == 1)
	{
		GLint fbname = _COREGL_INT_INIT_VALUE;
		_orig_tracepath_glGetIntegerv(GL_FRAMEBUFFER_BINDING, &fbname);
		AST(fbname != _COREGL_INT_INIT_VALUE);
		if (fbname == 0)
		{
			char name[256];
			EGLint btype;
			_orig_tracepath_eglQuerySurface(_orig_tracepath_eglGetCurrentDisplay(), _orig_tracepath_eglGetCurrentSurface(EGL_DRAW), EGL_RENDER_BUFFER, &btype);
			if (btype == EGL_SINGLE_BUFFER)
				sprintf(name, "EGLPIXMAP_%p", _orig_tracepath_eglGetCurrentSurface(EGL_DRAW));
			else
				sprintf(name, "EGLWINDOW_%p", _orig_tracepath_eglGetCurrentSurface(EGL_DRAW));
			tracepath_surface_trace_add(name, _orig_tracepath_eglGetCurrentDisplay(), _orig_tracepath_eglGetCurrentContext(), _orig_tracepath_eglGetCurrentSurface(EGL_DRAW), 0, 0, 0, 0, 0, 0, NULL);
		}
   }
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO
}

void
tracepath_glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDrawElements(mode, count, type, indices);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	if (trace_surface_flag == 1)
	{
		GLint fbname = _COREGL_INT_INIT_VALUE;
		_orig_tracepath_glGetIntegerv(GL_FRAMEBUFFER_BINDING, &fbname);
		AST(fbname != _COREGL_INT_INIT_VALUE);
		if (fbname == 0)
		{
			char name[256];
			EGLint btype;
			_orig_tracepath_eglQuerySurface(_orig_tracepath_eglGetCurrentDisplay(), _orig_tracepath_eglGetCurrentSurface(EGL_DRAW), EGL_RENDER_BUFFER, &btype);
			if (btype == EGL_SINGLE_BUFFER)
				sprintf(name, "EGLPIXMAP_%p", _orig_tracepath_eglGetCurrentSurface(EGL_DRAW));
			else
				sprintf(name, "EGLWINDOW_%p", _orig_tracepath_eglGetCurrentSurface(EGL_DRAW));
			tracepath_surface_trace_add(name, _orig_tracepath_eglGetCurrentDisplay(), _orig_tracepath_eglGetCurrentContext(), _orig_tracepath_eglGetCurrentSurface(EGL_DRAW), 0, 0, 0, 0, 0, 0, NULL);
		}
   }
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO
}

void
tracepath_glEnable(GLenum cap)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glEnable(cap);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glEnableVertexAttribArray(GLuint index)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glEnableVertexAttribArray(index);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glFinish(void)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glFinish();

	_COREGL_TRACE_SURFACE(0, 0, "GLFINISH");

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	_COREGL_TRACE_API_OUTPUT(0);
	_COREGL_TRACE_MEM_OUTPUT(0);
}

void
tracepath_glFlush(void)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glFlush();

	_COREGL_TRACE_SURFACE(0, 0, "GLFLUSH");

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
	_COREGL_TRACE_API_OUTPUT(0);
	_COREGL_TRACE_MEM_OUTPUT(0);
}

void
tracepath_glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	tracepath_fbdump_update(0);
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO

	_orig_tracepath_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	tracepath_fbdump_update(1);
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	tracepath_fbdump_update(0);
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO

	_orig_tracepath_glFramebufferTexture2D(target, attachment, textarget, texture, level);

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	tracepath_fbdump_update(1);
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glFrontFace(GLenum mode)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glFrontFace(mode);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetVertexAttribfv(index, pname, params);


	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetVertexAttribiv(index, pname, params);


	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetVertexAttribPointerv(index, pname, pointer);



	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glHint(GLenum target, GLenum mode)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glHint(target, mode);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGenBuffers(GLsizei n, GLuint* buffers)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGenBuffers(n, buffers);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGenerateMipmap(GLenum target)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGenerateMipmap(target);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGenFramebuffers(n, framebuffers);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGenRenderbuffers(n, renderbuffers);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
#ifdef COREGL_TRACEPATH_TRACE_MEMUSE_INFO
	if (trace_mem_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;

		GET_MY_TSTATE(tstate, get_current_thread_state());
		AST(tstate != NULL);
		if (tstate->ctx != NULL)
		{
			for (int i = 0; i < n; i++)
			{
				if (renderbuffers[i] == 0) continue;
				_add_glbuf_object(tstate->ctx->sostate->glbuf_rb, renderbuffers[i], "Renderbuffer", 0, 0, 0, "Unknown");
			}
		}
	}
#endif // COREGL_TRACEPATH_TRACE_MEMUSE_INFO
}

void
tracepath_glGenTextures(GLsizei n, GLuint* textures)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGenTextures(n, textures);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
#ifdef COREGL_TRACEPATH_TRACE_MEMUSE_INFO
	if (trace_mem_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;

		GET_MY_TSTATE(tstate, get_current_thread_state());
		AST(tstate != NULL);
		if (tstate->ctx != NULL)
		{
			for (int i = 0; i < n; i++)
			{
				if (textures[i] == 0) continue;
				_add_glbuf_object(tstate->ctx->sostate->glbuf_tex, textures[i], "Texture", 0, 0, 0, "Unknown");
			}
		}
	}
#endif // COREGL_TRACEPATH_TRACE_MEMUSE_INFO
}

void
tracepath_glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetActiveAttrib(program, index, bufsize, length, size, type, name);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetActiveUniform(program, index, bufsize, length, size, type, name);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetAttachedShaders(program, maxcount, count, shaders);

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

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetBufferParameteriv(target, pname, params);

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

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetIntegerv(GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetIntegerv(pname, params);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetProgramiv(program, pname, params);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetProgramInfoLog(program, bufsize, length, infolog);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetRenderbufferParameteriv(target, pname, params);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetShaderiv(shader, pname, params);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetShaderInfoLog(shader, bufsize, length, infolog);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, char* source)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetShaderSource(shader, bufsize, length, source);

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

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetTexParameteriv(GLenum target, GLenum pname, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetTexParameteriv(target, pname, params);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetUniformfv(GLuint program, GLint location, GLfloat* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetUniformfv(program, location, params);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetUniformiv(GLuint program, GLint location, GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetUniformiv(program, location, params);

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

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glLinkProgram(GLuint program)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glLinkProgram(program);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glPixelStorei(GLenum pname, GLint param)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glPixelStorei(pname, param);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glPolygonOffset(GLfloat factor, GLfloat units)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glPolygonOffset(factor, units);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glReadPixels(x, y, width, height, format, type, pixels);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glReleaseShaderCompiler(void)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glReleaseShaderCompiler();

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();

	_orig_tracepath_glRenderbufferStorage(target, internalformat, width, height);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
#ifdef COREGL_TRACEPATH_TRACE_MEMUSE_INFO
	if (trace_mem_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;

		GET_MY_TSTATE(tstate, get_current_thread_state());
		AST(tstate != NULL);
		if (tstate->ctx != NULL)
		{
			int objidx = _COREGL_INT_INIT_VALUE;
			_orig_tracepath_glGetIntegerv(GL_RENDERBUFFER_BINDING, &objidx);
			AST(objidx != _COREGL_INT_INIT_VALUE);

			// Detect byte per pixel
			int bpp = 0;
			char formatment[80];
			switch (internalformat)
			{
				case GL_ALPHA: sprintf(formatment, "ALPHA"); bpp = 1; break;
				case GL_LUMINANCE: sprintf(formatment, "LUMINANCE"); bpp = 1; break;
				case GL_LUMINANCE_ALPHA: sprintf(formatment, "LUMINANCE_ALPHA"); bpp = 1; break;
				case GL_RGB: sprintf(formatment, "RGB"); bpp = 2; break;
				case GL_RGBA: sprintf(formatment, "RGBA"); bpp = 4; break;
				case 0x80E1: sprintf(formatment, "BGRA_EXT"); bpp = 4; break;
				case 0x84F9: sprintf(formatment, "DEPTH_STENCIL_OES"); bpp = 4; break;
				case GL_DEPTH_COMPONENT : sprintf(formatment, "DEPTH_COMPONENT"); bpp = 1; break;
				case 0x81A5: sprintf(formatment, "DEPTH_COMPONENT16_ARB"); bpp = 2; break;
				case 0x81A6: sprintf(formatment, "DEPTH_COMPONENT24_ARB"); bpp = 3; break;
				case 0x81A7: sprintf(formatment, "DEPTH_COMPONENT32_ARB"); bpp = 4; break;
				case 0x8D46 : sprintf(formatment, "STENCIL_INDEX1_OES"); bpp = 1; break;
				case 0x8D47 : sprintf(formatment, "STENCIL_INDEX4_OES"); bpp = 1; break;
				case 0x8D48 : sprintf(formatment, "STENCIL_INDEX8_OES"); bpp = 1; break;
				default: sprintf(formatment, "0x%X", internalformat); bpp = 0; break;
			}

			_add_glbuf_object(tstate->ctx->sostate->glbuf_rb, objidx, "Renderbuffer", width, height, bpp, formatment);
		}
	}
#endif // COREGL_TRACEPATH_TRACE_MEMUSE_INFO
#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	if (trace_surface_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;

		GET_MY_TSTATE(tstate, get_current_thread_state());
		AST(tstate != NULL);
		if (tstate->ctx != NULL)
		{
			int objidx = _COREGL_INT_INIT_VALUE;
			_orig_tracepath_glGetIntegerv(GL_RENDERBUFFER_BINDING, &objidx);
			AST(objidx != _COREGL_INT_INIT_VALUE);

			{
				int channel = 0;
				switch (internalformat)
				{
					case GL_ALPHA:
					case GL_LUMINANCE:
					case GL_DEPTH_COMPONENT :
					case 0x81A5:
					case 0x81A6:
					case 0x81A7:
					case 0x8D46 :
					case 0x8D47 :
					case 0x8D48 : channel = 1; break;
					case GL_LUMINANCE_ALPHA:
					case 0x84F9: channel = 2; break;
					case GL_RGB: channel = 3; break;
					case GL_RGBA:
					case 0x80E1: channel = 4; break;
				}

				char name[256];
				sprintf(name, "FBORB_%d", objidx);
				tracepath_surface_trace_add(name, tstate->ctx->dpy, tstate->ctx->handle, tstate->surf_draw, -1, 0, objidx, width, height, channel, NULL);
			}
		}
	}
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO
}

void
tracepath_glSampleCoverage(GLclampf value, GLboolean invert)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glSampleCoverage(value, invert);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glScissor(x, y, width, height);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glShaderBinary(n, shaders, binaryformat, binary, length);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glShaderSource(shader, count, string, length);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glStencilFunc(func, ref, mask);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glStencilFuncSeparate(face, func, ref, mask);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glStencilMask(GLuint mask)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glStencilMask(mask);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glStencilMaskSeparate(GLenum face, GLuint mask)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glStencilMaskSeparate(face, mask);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glStencilOp(fail, zfail, zpass);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glStencilOpSeparate(face, fail, zfail, zpass);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
#ifdef COREGL_TRACEPATH_TRACE_MEMUSE_INFO
	if (trace_mem_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;

		GET_MY_TSTATE(tstate, get_current_thread_state());
		AST(tstate != NULL);
		if (tstate->ctx != NULL)
		{
			int objidx = _COREGL_INT_INIT_VALUE;
			_orig_tracepath_glGetIntegerv(GL_TEXTURE_BINDING_2D, &objidx);
			AST(objidx != _COREGL_INT_INIT_VALUE);

			// Detect byte per pixel
			int bpp = 0;
			char formatment[80];
			switch (internalformat)
			{
				case GL_ALPHA: sprintf(formatment, "ALPHA"); bpp = 1; break;
				case GL_LUMINANCE: sprintf(formatment, "LUMINANCE"); bpp = 1; break;
				case GL_LUMINANCE_ALPHA: sprintf(formatment, "LUMINANCE_ALPHA"); bpp = 1; break;
				case GL_RGB: sprintf(formatment, "RGB"); bpp = 2; break;
				case GL_RGBA: sprintf(formatment, "RGBA"); bpp = 4; break;
				case 0x80E1: sprintf(formatment, "BGRA_EXT"); bpp = 4; break;
				case 0x84F9: sprintf(formatment, "DEPTH_STENCIL_OES"); bpp = 4; break;
				case GL_DEPTH_COMPONENT : sprintf(formatment, "DEPTH_COMPONENT"); bpp = 1; break;
				case 0x81A5: sprintf(formatment, "DEPTH_COMPONENT16_ARB"); bpp = 2; break;
				case 0x81A6: sprintf(formatment, "DEPTH_COMPONENT24_ARB"); bpp = 3; break;
				case 0x81A7: sprintf(formatment, "DEPTH_COMPONENT32_ARB"); bpp = 4; break;
				case 0x8D46 : sprintf(formatment, "STENCIL_INDEX1_OES"); bpp = 1; break;
				case 0x8D47 : sprintf(formatment, "STENCIL_INDEX4_OES"); bpp = 1; break;
				case 0x8D48 : sprintf(formatment, "STENCIL_INDEX8_OES"); bpp = 1; break;
				default: sprintf(formatment, "0x%X", internalformat); bpp = 0; break;
			}

			_add_glbuf_object(tstate->ctx->sostate->glbuf_tex, objidx, "Texture", width, height, bpp, formatment);
		}
	}
#endif // COREGL_TRACEPATH_TRACE_MEMUSE_INFO
#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	if (trace_surface_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;

		GET_MY_TSTATE(tstate, get_current_thread_state());
		AST(tstate != NULL);
		if (tstate->ctx != NULL)
		{
			int objidx = _COREGL_INT_INIT_VALUE;
			_orig_tracepath_glGetIntegerv(GL_TEXTURE_BINDING_2D, &objidx);
			AST(objidx != _COREGL_INT_INIT_VALUE);

			{
				int channel = 0;
				switch (internalformat)
				{
					case GL_ALPHA:
					case GL_LUMINANCE:
					case GL_DEPTH_COMPONENT :
					case 0x81A5:
					case 0x81A6:
					case 0x81A7:
					case 0x8D46 :
					case 0x8D47 :
					case 0x8D48 : channel = 1; break;
					case GL_LUMINANCE_ALPHA:
					case 0x84F9: channel = 2; break;
					case GL_RGB: channel = 3; break;
					case GL_RGBA:
					case 0x80E1: channel = 4; break;
				}

				char name[256];
				sprintf(name, "FBOTEX_0x%X", objidx);
				tracepath_surface_trace_add(name, tstate->ctx->dpy, tstate->ctx->handle, tstate->surf_draw, -1, objidx, 0, width, height, channel, NULL);
			}
		}
	}
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO
}

void
tracepath_glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glTexParameterf(target, pname, param);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glTexParameterfv(target, pname, params);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glTexParameteri(GLenum target, GLenum pname, GLint param)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glTexParameteri(target, pname, param);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glTexParameteriv(GLenum target, GLenum pname, const GLint* params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glTexParameteriv(target, pname, params);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform1f(GLint location, GLfloat x)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform1f(location, x);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform1fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform1fv(location, count, v);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform1i(GLint location, GLint x)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform1i(location, x);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform1iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform1iv(location, count, v);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform2f(GLint location, GLfloat x, GLfloat y)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform2f(location, x, y);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform2fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform2fv(location, count, v);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform2i(GLint location, GLint x, GLint y)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform2i(location, x, y);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform2iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform2iv(location, count, v);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform3f(location, x, y, z);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform3fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform3fv(location, count, v);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform3i(GLint location, GLint x, GLint y, GLint z)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform3i(location, x, y, z);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform3iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform3iv(location, count, v);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform4f(location, x, y, z, w);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform4fv(GLint location, GLsizei count, const GLfloat* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform4fv(location, count, v);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform4i(location, x, y, z, w);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniform4iv(GLint location, GLsizei count, const GLint* v)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniform4iv(location, count, v);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniformMatrix2fv(location, count, transpose, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniformMatrix3fv(location, count, transpose, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUniformMatrix4fv(location, count, transpose, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUseProgram(GLuint program)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUseProgram(program);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glValidateProgram(GLuint program)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glValidateProgram(program);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib1f(GLuint indx, GLfloat x)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib1f(indx, x);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib1fv(GLuint indx, const GLfloat* values)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib1fv(indx, values);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib2f(indx, x, y);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib2fv(GLuint indx, const GLfloat* values)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib2fv(indx, values);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib3f(indx, x, y, z);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib3fv(GLuint indx, const GLfloat* values)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib3fv(indx, values);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib4f(indx, x, y, z, w);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttrib4fv(GLuint indx, const GLfloat* values)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttrib4fv(indx, values);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glVertexAttribPointer(indx, size, type, normalized, stride, ptr);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glViewport(x, y, width, height);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}


/* OpenGL ES 3.0 */
void
tracepath_glReadBuffer(GLenum mode)
{
}

void
tracepath_glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid* indices)
{
}

void
tracepath_glTexImage3D(GLenum target, GLint level, GLenum GLinternalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glTexImage3D(target, level, GLinternalFormat, width, height, depth, border, format, type, pixels);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glCompressedTexImage3D(GLenum target, GLint level, GLenum GLinternalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glCompressedTexImage3D(target, level, GLinternalformat, width, height, depth, border, imageSize, data);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGenQueries(GLsizei n, GLuint* ids)
{
}
void
tracepath_glDeleteQueries(GLsizei n, const GLuint* ids)
{
}
GLboolean
tracepath_glIsQuery(GLuint id)
{
}
void
tracepath_glBeginQuery(GLenum target, GLuint id)
{
}
void
tracepath_glEndQuery(GLenum target)
{
}
void
tracepath_glGetQueryiv(GLenum target, GLenum pname, GLint* params)
{
}
void
tracepath_glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint* params)
{
}
GLboolean
tracepath_glUnmapBuffer(GLenum target)
{
}
void
tracepath_glGetBufferPointerv(GLenum target, GLenum pname, GLvoid** params)
{
}
void
tracepath_glDrawBuffers(GLsizei n, const GLenum* bufs)
{
}
void
tracepath_glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
}
void
tracepath_glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
}
void
tracepath_glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
}
void
tracepath_glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
}
void
tracepath_glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
}
void
tracepath_glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
}
void
tracepath_glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
}
void
tracepath_glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
}
void
tracepath_glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
}
GLvoid*
tracepath_glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
}
void
tracepath_glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
{
}
void
tracepath_glBindVertexArray(GLuint array)
{
}
void
tracepath_glDeleteVertexArrays(GLsizei n, const GLuint* arrays)
{
}
void
tracepath_glGenVertexArrays(GLsizei n, GLuint* arrays)
{
}
GLboolean
tracepath_glIsVertexArray(GLuint array)
{
}
void
tracepath_glGetIntegeri_v(GLenum target, GLuint index, GLint* data)
{
}
void
tracepath_glBeginTransformFeedback(GLenum primitiveMode)
{
}
void
tracepath_glEndTransformFeedback(void)
{
}
void
tracepath_glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
}
void
tracepath_glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
}
void
tracepath_glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode)
{
}
void
tracepath_glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name)
{
}
void
tracepath_glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
}
void
tracepath_glGetVertexAttribIiv(GLuint index, GLenum pname, GLint* params)
{
}
void
tracepath_glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint* params)
{
}
void
tracepath_glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
{
}
void
tracepath_glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
}
void
tracepath_glVertexAttribI4iv(GLuint index, const GLint* v)
{
}
void
tracepath_glVertexAttribI4uiv(GLuint index, const GLuint* v)
{
}
void
tracepath_glGetUniformuiv(GLuint program, GLint location, GLuint* params)
{
}
GLint
tracepath_glGetFragDataLocation(GLuint program, const GLchar *name)
{
}
void
tracepath_glUniform1ui(GLint location, GLuint v0)
{
}
void
tracepath_glUniform2ui(GLint location, GLuint v0, GLuint v1)
{
}
void
tracepath_glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
}
void
tracepath_glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
}
void
tracepath_glUniform1uiv(GLint location, GLsizei count, const GLuint* value)
{
}
void
tracepath_glUniform2uiv(GLint location, GLsizei count, const GLuint* value)
{
}
void
tracepath_glUniform3uiv(GLint location, GLsizei count, const GLuint* value)
{
}
void
tracepath_glUniform4uiv(GLint location, GLsizei count, const GLuint* value)
{
}
void
tracepath_glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint* value)
{
}
void
tracepath_glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint* value)
{
}
void
tracepath_glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value)
{
}
void
tracepath_glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
}
const GLubyte*
tracepath_glGetStringi(GLenum name, GLuint index)
{
}
void
tracepath_glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
}
void
tracepath_glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames, GLuint* uniformIndices)
{
}
void
tracepath_glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params)
{
}
GLuint
tracepath_glGetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName)
{
}
void
tracepath_glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params)
{
}
void
tracepath_glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName)
{
}
void
tracepath_glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
{
}
void
tracepath_glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount)
{
}
void
tracepath_glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLsizei instanceCount)
{
}
GLsync
tracepath_glFenceSync(GLenum condition, GLbitfield flags)
{
}
GLboolean
tracepath_glIsSync(GLsync sync)
{
}
void
tracepath_glDeleteSync(GLsync sync)
{
}
GLenum
tracepath_glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
}
void
tracepath_glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
}
void
tracepath_glGetInteger64v(GLenum pname, GLint64* params)
{
}
void
tracepath_glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values)
{
}
void
tracepath_glGetInteger64i_v(GLenum target, GLuint index, GLint64* data)
{
}
void
tracepath_glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64* params)
{
}
void
tracepath_glGenSamplers(GLsizei count, GLuint* samplers)
{
}
void
tracepath_glDeleteSamplers(GLsizei count, const GLuint* samplers)
{
}
GLboolean
tracepath_glIsSampler(GLuint sampler)
{
}
void
tracepath_glBindSampler(GLuint unit, GLuint sampler)
{
}
void
tracepath_glSamplerParameteri(GLuint sampler, GLenum pname, GLint param)
{
}
void
tracepath_glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint* param)
{
}
void
tracepath_glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
{
}
void
tracepath_glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat* param)
{
}
void
tracepath_glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint* params)
{
}
void
tracepath_glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat* params)
{
}
void
tracepath_glVertexAttribDivisor(GLuint index, GLuint divisor)
{
}
void
tracepath_glBindTransformFeedback(GLenum target, GLuint id)
{
}
void
tracepath_glDeleteTransformFeedbacks(GLsizei n, const GLuint* ids)
{
}
void
tracepath_glGenTransformFeedbacks(GLsizei n, GLuint* ids)
{
}
GLboolean
tracepath_glIsTransformFeedback(GLuint id)
{
}
void
tracepath_glPauseTransformFeedback(void)
{
}
void
tracepath_glResumeTransformFeedback(void)
{
}
void
tracepath_glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, GLvoid* binary)
{
}
void
tracepath_glProgramBinary(GLuint program, GLenum binaryFormat, const GLvoid* binary, GLsizei length)
{
}
void
tracepath_glProgramParameteri(GLuint program, GLenum pname, GLint value)
{
}
void
tracepath_glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments)
{
}
void
tracepath_glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height)
{
}
void
tracepath_glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
}
void
tracepath_glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
}
void
tracepath_glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params)
{
}

/* GLES Extensions */
void
tracepath_glEGLImageTargetTexture2DOES(GLenum target, GLeglImageOES image)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glEGLImageTargetTexture2DOES(target, image);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
#ifdef COREGL_TRACEPATH_TRACE_MEMUSE_INFO
	if (trace_mem_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;

		GET_MY_TSTATE(tstate, get_current_thread_state());
		AST(tstate != NULL);
		if (tstate->ctx != NULL)
		{
			int objidx = _COREGL_INT_INIT_VALUE;
			_orig_tracepath_glGetIntegerv(GL_TEXTURE_BINDING_2D, &objidx);
			AST(objidx != _COREGL_INT_INIT_VALUE);

			_add_glbuf_object(tstate->ctx->sostate->glbuf_tex, objidx, "Texture", 0, 0, 0, "Unknown");
		}
	}
#endif // COREGL_TRACEPATH_TRACE_MEMUSE_INFO
}

void
tracepath_glEGLImageTargetRenderbufferStorageOES(GLenum target, GLeglImageOES image)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glEGLImageTargetRenderbufferStorageOES(target, image);
	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
#ifdef COREGL_TRACEPATH_TRACE_MEMUSE_INFO
	if (trace_mem_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;

		GET_MY_TSTATE(tstate, get_current_thread_state());
		AST(tstate != NULL);
		if (tstate->ctx != NULL)
		{
			int objidx = _COREGL_INT_INIT_VALUE;
			_orig_tracepath_glGetIntegerv(GL_RENDERBUFFER_BINDING, &objidx);
			AST(objidx != _COREGL_INT_INIT_VALUE);

			_add_glbuf_object(tstate->ctx->sostate->glbuf_rb, objidx, "Renderbuffer", 0, 0, 0, "Unknown");
		}
	}
#endif // COREGL_TRACEPATH_TRACE_MEMUSE_INFO
}

void
tracepath_glGetProgramBinaryOES(GLuint program, GLsizei bufsize, GLsizei* length, GLenum* binaryFormat, void* binary)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetProgramBinaryOES(program, bufsize, length, binaryFormat, binary);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramBinaryOES(GLuint program, GLenum binaryFormat, const void* binary, GLint length)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramBinaryOES(program, binaryFormat, binary, length);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glUseProgramStagesEXT(GLuint pipeline, GLbitfield stages, GLuint program)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glUseProgramStagesEXT(pipeline, stages, program);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glActiveShaderProgramEXT(GLuint pipeline, GLuint program)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glActiveShaderProgramEXT(pipeline, program);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

GLuint
tracepath_glCreateShaderProgramvEXT(GLenum type, GLsizei count, const char **strings)
{
	GLuint ret = _COREGL_INT_INIT_VALUE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glCreateShaderProgramvEXT(type, count, strings);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
   return ret;
}

void
tracepath_glBindProgramPipelineEXT(GLuint pipeline)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBindProgramPipelineEXT(pipeline);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDeleteProgramPipelinesEXT(GLsizei n, const GLuint *pipelines)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDeleteProgramPipelinesEXT(n, pipelines);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGenProgramPipelinesEXT(GLsizei n, GLuint *pipelines)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGenProgramPipelinesEXT(n, pipelines);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

GLboolean
tracepath_glIsProgramPipelineEXT(GLuint pipeline)
{
	GLboolean ret = _COREGL_INT_INIT_VALUE;

	_COREGL_TRACEPATH_FUNC_BEGIN();
	ret = _orig_tracepath_glIsProgramPipelineEXT(pipeline);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
   return ret;
}

void
tracepath_glProgramParameteriEXT(GLuint program, GLenum pname, GLint value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramParameteriEXT(program, pname, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetProgramPipelineivEXT(GLuint pipeline, GLenum pname, GLint *params)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetProgramPipelineivEXT(pipeline, pname, params);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform1iEXT(GLuint program, GLint location, GLint x)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform1iEXT(program, location, x);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform2iEXT(GLuint program, GLint location, GLint x, GLint y)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform2iEXT(program, location, x, y);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform3iEXT(GLuint program, GLint location, GLint x, GLint y, GLint z)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform3iEXT(program, location, x, y, z);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform4iEXT(GLuint program, GLint location, GLint x, GLint y, GLint z, GLint w)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform4iEXT(program, location, x, y, z, w);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform1fEXT(GLuint program, GLint location, GLfloat x)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform1fEXT(program, location, x);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform2fEXT(GLuint program, GLint location, GLfloat x, GLfloat y)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform2fEXT(program, location, x, y);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform3fEXT(GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform3fEXT(program, location, x, y, z);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform4fEXT(GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform4fEXT(program, location, x, y, z, w);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform1ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform1ivEXT(program, location, count, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform2ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform2ivEXT(program, location, count, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform3ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform3ivEXT(program, location, count, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform4ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform4ivEXT(program, location, count, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform1fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform1fvEXT(program, location, count, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform2fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform2fvEXT(program, location, count, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform3fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform3fvEXT(program, location, count, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniform4fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniform4fvEXT(program, location, count, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniformMatrix2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniformMatrix2fvEXT(program, location, count, transpose, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniformMatrix3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniformMatrix3fvEXT(program, location, count, transpose, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glProgramUniformMatrix4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glProgramUniformMatrix4fvEXT(program, location, count, transpose, value);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glValidateProgramPipelineEXT(GLuint pipeline)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glValidateProgramPipelineEXT(pipeline);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glGetProgramPipelineInfoLogEXT(GLuint pipeline, GLsizei bufSize, GLsizei *length, char *infoLog)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glGetProgramPipelineInfoLogEXT(pipeline, bufSize, length, infoLog);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}


void
tracepath_glRenderbufferStorageMultisampleEXT(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glRenderbufferStorageMultisampleEXT(target, samples, internalformat, width, height);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
#ifdef COREGL_TRACEPATH_TRACE_MEMUSE_INFO
	if (trace_mem_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;

		GET_MY_TSTATE(tstate, get_current_thread_state());
		AST(tstate != NULL);
		if (tstate->ctx != NULL)
		{
			int objidx = _COREGL_INT_INIT_VALUE;
			_orig_tracepath_glGetIntegerv(GL_RENDERBUFFER_BINDING, &objidx);
			AST(objidx != _COREGL_INT_INIT_VALUE);

			// Detect byte per pixel
			int bpp = 0;
			char formatment[80];
			switch (internalformat)
			{
				case GL_ALPHA: sprintf(formatment, "ALPHA"); bpp = 1; break;
				case GL_LUMINANCE: sprintf(formatment, "LUMINANCE"); bpp = 1; break;
				case GL_LUMINANCE_ALPHA: sprintf(formatment, "LUMINANCE_ALPHA"); bpp = 1; break;
				case GL_RGB: sprintf(formatment, "RGB"); bpp = 2; break;
				case GL_RGBA: sprintf(formatment, "RGBA"); bpp = 4; break;
				case 0x80E1: sprintf(formatment, "BGRA_EXT"); bpp = 4; break;
				case 0x84F9: sprintf(formatment, "DEPTH_STENCIL_OES"); bpp = 4; break;
				case GL_DEPTH_COMPONENT : sprintf(formatment, "DEPTH_COMPONENT"); bpp = 1; break;
				case 0x81A5: sprintf(formatment, "DEPTH_COMPONENT16_ARB"); bpp = 2; break;
				case 0x81A6: sprintf(formatment, "DEPTH_COMPONENT24_ARB"); bpp = 3; break;
				case 0x81A7: sprintf(formatment, "DEPTH_COMPONENT32_ARB"); bpp = 4; break;
				case 0x8D46 : sprintf(formatment, "STENCIL_INDEX1_OES"); bpp = 1; break;
				case 0x8D47 : sprintf(formatment, "STENCIL_INDEX4_OES"); bpp = 1; break;
				case 0x8D48 : sprintf(formatment, "STENCIL_INDEX8_OES"); bpp = 1; break;
				default: sprintf(formatment, "0x%X", internalformat); bpp = 0; break;
			}

			_add_glbuf_object(tstate->ctx->sostate->glbuf_rb, objidx, "Renderbuffer", width, height, bpp, formatment);
		}
	}
#endif // COREGL_TRACEPATH_TRACE_MEMUSE_INFO
#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	if (trace_surface_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;

		GET_MY_TSTATE(tstate, get_current_thread_state());
		AST(tstate != NULL);
		if (tstate->ctx != NULL)
		{
			int objidx = _COREGL_INT_INIT_VALUE;
			_orig_tracepath_glGetIntegerv(GL_RENDERBUFFER_BINDING, &objidx);
			AST(objidx != _COREGL_INT_INIT_VALUE);

			{
				int channel = 0;
				switch (internalformat)
				{
					case GL_ALPHA:
					case GL_LUMINANCE:
					case GL_DEPTH_COMPONENT :
					case 0x81A5:
					case 0x81A6:
					case 0x81A7:
					case 0x8D46 :
					case 0x8D47 :
					case 0x8D48 : channel = 1; break;
					case GL_LUMINANCE_ALPHA:
					case 0x84F9: channel = 2; break;
					case GL_RGB: channel = 3; break;
					case GL_RGBA:
					case 0x80E1: channel = 4; break;
				}

				char name[256];
				sprintf(name, "FBORB_0x%X", objidx);
				tracepath_surface_trace_add(name, tstate->ctx->dpy, tstate->ctx->handle, tstate->surf_draw, -1, 0, objidx, width, height, channel, NULL);
			}
		}
	}
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO
}

void
tracepath_glFramebufferTexture2DMultisampleEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	tracepath_fbdump_update(0);
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO

	_orig_tracepath_glFramebufferTexture2DMultisampleEXT(target, attachment, textarget, texture, level, samples);

#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	tracepath_fbdump_update(1);
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glDiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum *attachments)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glDiscardFramebufferEXT(target, numAttachments, attachments);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}
void
tracepath_glFramebufferTexture3DOES(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glFramebufferTexture3DOES(target, attachment, textarget, texture, level, zoffset);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glBlitFramebufferANGLE(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();
	_orig_tracepath_glBlitFramebufferANGLE(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
}

void
tracepath_glRenderbufferStorageMultisampleANGLE(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
	_COREGL_TRACEPATH_FUNC_BEGIN();

	_orig_tracepath_glRenderbufferStorageMultisampleANGLE(target, samples, internalformat, width, height);

	goto finish;

finish:
	_COREGL_TRACEPATH_FUNC_END();
#ifdef COREGL_TRACEPATH_TRACE_MEMUSE_INFO
	if (trace_mem_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;

		GET_MY_TSTATE(tstate, get_current_thread_state());
		AST(tstate != NULL);
		if (tstate->ctx != NULL)
		{
			int objidx = _COREGL_INT_INIT_VALUE;
			_orig_tracepath_glGetIntegerv(GL_RENDERBUFFER_BINDING, &objidx);
			AST(objidx != _COREGL_INT_INIT_VALUE);

			// Detect byte per pixel
			int bpp = 0;
			char formatment[80];
			switch (internalformat)
			{
				case GL_ALPHA: sprintf(formatment, "ALPHA"); bpp = 1; break;
				case GL_LUMINANCE: sprintf(formatment, "LUMINANCE"); bpp = 1; break;
				case GL_LUMINANCE_ALPHA: sprintf(formatment, "LUMINANCE_ALPHA"); bpp = 1; break;
				case GL_RGB: sprintf(formatment, "RGB"); bpp = 2; break;
				case GL_RGBA: sprintf(formatment, "RGBA"); bpp = 4; break;
				case 0x80E1: sprintf(formatment, "BGRA_EXT"); bpp = 4; break;
				case 0x84F9: sprintf(formatment, "DEPTH_STENCIL_OES"); bpp = 4; break;
				case GL_DEPTH_COMPONENT : sprintf(formatment, "DEPTH_COMPONENT"); bpp = 1; break;
				case 0x81A5: sprintf(formatment, "DEPTH_COMPONENT16_ARB"); bpp = 2; break;
				case 0x81A6: sprintf(formatment, "DEPTH_COMPONENT24_ARB"); bpp = 3; break;
				case 0x81A7: sprintf(formatment, "DEPTH_COMPONENT32_ARB"); bpp = 4; break;
				case 0x8D46 : sprintf(formatment, "STENCIL_INDEX1_OES"); bpp = 1; break;
				case 0x8D47 : sprintf(formatment, "STENCIL_INDEX4_OES"); bpp = 1; break;
				case 0x8D48 : sprintf(formatment, "STENCIL_INDEX8_OES"); bpp = 1; break;
				default: sprintf(formatment, "0x%X", internalformat); bpp = 0; break;
			}

			_add_glbuf_object(tstate->ctx->sostate->glbuf_rb, objidx, "Renderbuffer", width, height, bpp, formatment);
		}
	}
#endif // COREGL_TRACEPATH_TRACE_MEMUSE_INFO
#ifdef COREGL_TRACEPATH_TRACE_SURFACE_INFO
	if (trace_surface_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;

		GET_MY_TSTATE(tstate, get_current_thread_state());
		AST(tstate != NULL);
		if (tstate->ctx != NULL)
		{
			int objidx = _COREGL_INT_INIT_VALUE;
			_orig_tracepath_glGetIntegerv(GL_RENDERBUFFER_BINDING, &objidx);
			AST(objidx != _COREGL_INT_INIT_VALUE);

			{
				int channel = 0;
				switch (internalformat)
				{
					case GL_ALPHA:
					case GL_LUMINANCE:
					case GL_DEPTH_COMPONENT :
					case 0x81A5:
					case 0x81A6:
					case 0x81A7:
					case 0x8D46 :
					case 0x8D47 :
					case 0x8D48 : channel = 1; break;
					case GL_LUMINANCE_ALPHA:
					case 0x84F9: channel = 2; break;
					case GL_RGB: channel = 3; break;
					case GL_RGBA:
					case 0x80E1: channel = 4; break;
				}

				char name[256];
				sprintf(name, "FBORB_%d", objidx);
				tracepath_surface_trace_add(name, tstate->ctx->dpy, tstate->ctx->handle, tstate->surf_draw, -1, 0, objidx, width, height, channel, NULL);
			}
		}
	}
#endif // COREGL_TRACEPATH_TRACE_SURFACE_INFO
}


