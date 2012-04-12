#include "coregl_fastpath.h"

#include <stdlib.h>

//----------------------------------------------------------------//
//                                                                //
//                      Fastpath GL Functions                     //
// The functions have prefix 'fpgl_' for (fastpath gl)            //
//                                                                //
//----------------------------------------------------------------//

#define CURR_STATE_COMPARE(curr_state, state ) \
   if ((current_ctx->curr_state[0]) != (state))

#define DEFINE_FAST_GL_FUNC() \
   GLThreadState *tstate = NULL; \
   GLGlueContext *current_ctx = NULL;

#define INIT_FAST_GL_FUNC() \
   tstate = get_current_thread_state(); \
   AST(tstate != NULL); \
   AST(tstate->cstate != NULL); \
   current_ctx = (GLGlueContext *)tstate->cstate->data; \
   AST(current_ctx != NULL);

#define GET_REAL_OBJ(type, glue_handle, real_handle) \
	_get_real_obj(current_ctx->sostate, type, glue_handle, real_handle)

static inline int
_get_real_obj(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint glue_handle, GLuint *real_handle)
{
	if (glue_handle == 0)
	{
		*real_handle = 0;
	}
	else
	{
		AST(sostate != NULL);
		*real_handle = sostate_get_object(sostate, type, glue_handle);
		if (*real_handle == 0)
			return 0;
	}
	return 1;
}

static void
_set_gl_error(GLenum error)
{
	GLenum glerror = GL_NONE;
	DEFINE_FAST_GL_FUNC();
	INIT_FAST_GL_FUNC();

	glerror = _sym_glGetError();

	if (current_ctx->gl_error == GL_NO_ERROR &&
	    glerror == GL_NO_ERROR &&
	    error != GL_NO_ERROR)
	{
		current_ctx->gl_error = error;
	}
}

GLenum
fpgl_glGetError(void)
{
	GLenum ret = GL_NONE;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (current_ctx->gl_error != GL_NO_ERROR)
	{
		ret = current_ctx->gl_error;
	}
	else
	{
		ret = _sym_glGetError();
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}

////////////////////////////////////////////////////////////////////////

void
fpgl_glActiveTexture(GLenum texture)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	CURR_STATE_COMPARE(gl_active_texture, texture)
	{
		_sym_glActiveTexture(texture);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_tex_flag1 |= FLAG_BIT_1;
		current_ctx->gl_active_texture[0] = texture;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glGenTextures(GLsizei n, GLuint* textures)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (textures == NULL) goto finish;

	AST(current_ctx->sostate != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);

	_sym_glGenTextures(n, objid_array);

	for (i = 0; i < n; i++)
	{
		textures[i] = sostate_create_object(current_ctx->sostate, GL_OBJECT_TYPE_TEXTURE, objid_array[i]);
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glBindTexture(GLenum target, GLuint texture)
{
	int active_idx;
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	active_idx = current_ctx->gl_active_texture[0] - GL_TEXTURE0;

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_TEXTURE, texture, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	if (target == GL_TEXTURE_2D)
	{
		if (current_ctx->gl_tex_2d_state[active_idx] != real_obj)
		{
			_sym_glBindTexture(target, real_obj);

			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			current_ctx->_tex_flag1 |= FLAG_BIT_3;

			current_ctx->gl_tex_2d_state[active_idx] = real_obj;
		}
	}
	else if (target == GL_TEXTURE_CUBE_MAP)
	{
		if (current_ctx->gl_tex_cube_state[active_idx] != real_obj)
		{
			_sym_glBindTexture(target, real_obj);

			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			current_ctx->_tex_flag1 |= FLAG_BIT_4;

			current_ctx->gl_tex_cube_state[active_idx] = real_obj;
		}
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_TEXTURE, texture, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	_sym_glFramebufferTexture2D(target, attachment, textarget, real_obj, level);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glFramebufferTexture2DMultisampleEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_TEXTURE, texture, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	_sym_glFramebufferTexture2DMultisampleEXT(target, attachment, textarget, real_obj, level, samples);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

GLboolean
fpgl_glIsTexture(GLuint texture)
{
	GLboolean ret;
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_TEXTURE, texture, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _sym_glIsTexture(real_obj);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}


void
fpgl_glDeleteTextures(GLsizei n, const GLuint* textures)
{
	int i, j;
	GLuint *objid_array = NULL;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (textures == NULL) goto finish;

	AST(current_ctx->sostate != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);
	{
		int real_n = 0;

		for (i = 0; i < n; i++)
		{
			int real_objid = _COREGL_INT_INIT_VALUE;
			if (textures[i] == 0) continue;

			real_objid = sostate_get_object(current_ctx->sostate, GL_OBJECT_TYPE_TEXTURE, textures[i]);
			if (real_objid == 0) continue;

			sostate_remove_object(current_ctx->sostate, GL_OBJECT_TYPE_TEXTURE, textures[i]);
			objid_array[real_n++] = real_objid;
		}

		_sym_glDeleteTextures(real_n, objid_array);
		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		for (i = 0; i < real_n; i++)
		{
			for (j = 0; j < current_ctx->gl_num_tex_units[0]; j++)
			{
				if (current_ctx->gl_tex_2d_state[j] == objid_array[i])
					current_ctx->gl_tex_2d_state[j] = 0;
				if (current_ctx->gl_tex_cube_state[j] == objid_array[i])
					current_ctx->gl_tex_cube_state[j] = 0;
			}
		}
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FAST_FUNC_END();
}

////////////////////////////////////////////////////////////////////////

void
fpgl_glGenBuffers(GLsizei n, GLuint* buffers)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (buffers == NULL) goto finish;

	AST(current_ctx->sostate != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);

	_sym_glGenBuffers(n, objid_array);

	for (i = 0; i < n; i++)
	{
		buffers[i] = sostate_create_object(current_ctx->sostate, GL_OBJECT_TYPE_BUFFER, objid_array[i]);
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glBindBuffer(GLenum target, GLuint buffer)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_BUFFER, buffer, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	if (target == GL_ARRAY_BUFFER)
	{
		CURR_STATE_COMPARE(gl_array_buffer_binding, real_obj)
		{
			_sym_glBindBuffer(target, real_obj);

			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			if (real_obj == 0)
				current_ctx->_bind_flag &= (~FLAG_BIT_0);
			else
				current_ctx->_bind_flag |= FLAG_BIT_0;
			current_ctx->gl_array_buffer_binding[0] = real_obj;
		}
	}
	else if (target == GL_ELEMENT_ARRAY_BUFFER)
	{
		CURR_STATE_COMPARE(gl_element_array_buffer_binding, real_obj)
		{
			_sym_glBindBuffer(target, real_obj);
			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			if (real_obj == 0)
				current_ctx->_bind_flag &= (~FLAG_BIT_1);
			else
				current_ctx->_bind_flag |= FLAG_BIT_1;
			current_ctx->gl_element_array_buffer_binding[0] = real_obj;
		}
	}
	else
	{
		// For error recording
		_sym_glBindBuffer(target, real_obj);
		GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

GLboolean
fpgl_glIsBuffer(GLuint buffer)
{
	GLboolean ret;
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_BUFFER, buffer, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _sym_glIsBuffer(real_obj);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}


void
fpgl_glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (buffers == NULL) goto finish;

	AST(current_ctx->sostate != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);
	{
		int real_n = 0;

		for (i = 0; i < n; i++)
		{
			int real_objid = _COREGL_INT_INIT_VALUE;
			if (buffers[i] == 0) continue;

			real_objid = sostate_get_object(current_ctx->sostate, GL_OBJECT_TYPE_BUFFER, buffers[i]);
			if (real_objid == 0) continue;

			sostate_remove_object(current_ctx->sostate, GL_OBJECT_TYPE_BUFFER, buffers[i]);
			objid_array[real_n++] = real_objid;
		}

		_sym_glDeleteBuffers(real_n, objid_array);
		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		for (i = 0; i < real_n; i++)
		{
			if (current_ctx->gl_array_buffer_binding[0] == objid_array[i])
			{
				current_ctx->_bind_flag &= (~FLAG_BIT_0);
				current_ctx->gl_array_buffer_binding[0] = 0;
			}
			if (current_ctx->gl_element_array_buffer_binding[0] == objid_array[i])
			{
				current_ctx->_bind_flag &= (~FLAG_BIT_1);
				current_ctx->gl_element_array_buffer_binding[0] = 0;
			}
		}
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FAST_FUNC_END();
}

//////////////////////////////////////////////////////////////////////////////////

void
fpgl_glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (framebuffers == NULL) goto finish;

	AST(current_ctx->sostate != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);

	_sym_glGenFramebuffers(n, objid_array);

	for (i = 0; i < n; i++)
	{
		framebuffers[i] = sostate_create_object(current_ctx->sostate, GL_OBJECT_TYPE_FRAMEBUFFER, objid_array[i]);
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_FRAMEBUFFER, framebuffer, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	if (target == GL_FRAMEBUFFER)
	{
		CURR_STATE_COMPARE(gl_framebuffer_binding, real_obj)
		{
			_sym_glBindFramebuffer(target, real_obj);
			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			if (real_obj == 0)
				current_ctx->_bind_flag &= (~FLAG_BIT_2);
			else
				current_ctx->_bind_flag |= FLAG_BIT_2;
			current_ctx->gl_framebuffer_binding[0] = real_obj;
		}
	}
	else
	{
		// For error recording
		_sym_glBindFramebuffer(target, real_obj);
		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

GLboolean
fpgl_glIsFramebuffer(GLuint framebuffer)
{
	GLboolean ret;
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_FRAMEBUFFER, framebuffer, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _sym_glIsFramebuffer(real_obj);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}


void
fpgl_glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (framebuffers == NULL) goto finish;

	AST(current_ctx->sostate != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);
	{
		int real_n = 0;

		for (i = 0; i < n; i++)
		{
			int real_objid = _COREGL_INT_INIT_VALUE;
			if (framebuffers[i] == 0) continue;

			real_objid = sostate_get_object(current_ctx->sostate, GL_OBJECT_TYPE_FRAMEBUFFER, framebuffers[i]);
			if (real_objid == 0) continue;

			sostate_remove_object(current_ctx->sostate, GL_OBJECT_TYPE_FRAMEBUFFER, framebuffers[i]);
			objid_array[real_n++] = real_objid;
		}

		_sym_glDeleteFramebuffers(real_n, objid_array);
		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		for (i = 0; i < real_n; i++)
		{
			if (current_ctx->gl_framebuffer_binding[0] == framebuffers[i])
			{
				current_ctx->_bind_flag &= (~FLAG_BIT_2);
				current_ctx->gl_framebuffer_binding[0] = 0;
			}
		}
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FAST_FUNC_END();
}

//////////////////////////////////////////////////////////////////////////////////

void
fpgl_glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (renderbuffers == NULL) goto finish;

	AST(current_ctx->sostate != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);

	_sym_glGenRenderbuffers(n, objid_array);

	for (i = 0; i < n; i++)
	{
		renderbuffers[i] = sostate_create_object(current_ctx->sostate, GL_OBJECT_TYPE_RENDERBUFFER, objid_array[i]);
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_RENDERBUFFER, renderbuffer, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	if (target == GL_RENDERBUFFER)
	{
		CURR_STATE_COMPARE(gl_renderbuffer_binding, real_obj)
		{
			_sym_glBindRenderbuffer(target, real_obj);
			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			if (real_obj == 0)
				current_ctx->_bind_flag &= (~FLAG_BIT_3);
			else
				current_ctx->_bind_flag |= FLAG_BIT_3;
			current_ctx->gl_renderbuffer_binding[0] = real_obj;
		}
	}
	else
	{
		// For error recording
		_sym_glBindRenderbuffer(target, real_obj);
		GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_RENDERBUFFER, renderbuffer, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	_sym_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, real_obj);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

GLboolean
fpgl_glIsRenderbuffer(GLuint renderbuffer)
{
	GLboolean ret;
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_RENDERBUFFER, renderbuffer, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _sym_glIsRenderbuffer(real_obj);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}


void
fpgl_glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (renderbuffers == NULL) goto finish;

	AST(current_ctx->sostate != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);
	{
		int real_n = 0;

		for (i = 0; i < n; i++)
		{
			int real_objid = _COREGL_INT_INIT_VALUE;
			if (renderbuffers[i] == 0) continue;

			real_objid = sostate_get_object(current_ctx->sostate, GL_OBJECT_TYPE_RENDERBUFFER, renderbuffers[i]);
			if (real_objid == 0) continue;

			sostate_remove_object(current_ctx->sostate, GL_OBJECT_TYPE_RENDERBUFFER, renderbuffers[i]);
			objid_array[real_n++] = real_objid;
		}

		_sym_glDeleteRenderbuffers(real_n, objid_array);
		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		for (i = 0; i < real_n; i++)
		{
			if (current_ctx->gl_renderbuffer_binding[0] == renderbuffers[i])
			{
				current_ctx->_bind_flag &= (~FLAG_BIT_3);
				current_ctx->gl_renderbuffer_binding[0] = 0;
			}
		}
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FAST_FUNC_END();
}

//////////////////////////////////////////////////////////////////////////////////

GLuint
fpgl_glCreateProgram(void)
{
	GLuint ret = _COREGL_INT_INIT_VALUE;
	GLuint real_obj = _COREGL_INT_INIT_VALUE;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	AST(current_ctx->sostate != NULL);

	real_obj = _sym_glCreateProgram();
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	ret = sostate_create_object(current_ctx->sostate, GL_OBJECT_TYPE_PROGRAM, real_obj);

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}

GLuint
fpgl_glCreateShader(GLenum type)
{
	GLuint ret = _COREGL_INT_INIT_VALUE;
	GLuint real_obj = _COREGL_INT_INIT_VALUE;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	AST(current_ctx->sostate != NULL);

	real_obj = _sym_glCreateShader(type);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	ret = sostate_create_object(current_ctx->sostate, GL_OBJECT_TYPE_PROGRAM, real_obj);

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}

void
fpgl_glShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	_sym_glShaderSource(real_obj, count, string, length);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (shaders == NULL) goto finish;

	AST(current_ctx->sostate != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);

	for (i = 0; i < n; i++)
	{
		if (shaders[i] == 0) continue;
		objid_array[i] = sostate_get_object(current_ctx->sostate, GL_OBJECT_TYPE_PROGRAM, shaders[i]);
	}

#ifndef _COREGL_DESKTOP_GL
	_sym_glShaderBinary(n, objid_array, binaryformat, binary, length);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
#else
// FIXME: need to dlsym/getprocaddress for this
	/*
	   n = binaryformat = length = 0;
	   shaders = binary = 0;
	*/
#endif
	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}

	_COREGL_FAST_FUNC_END();
}

void
fpgl_glCompileShader(GLuint shader)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glCompileShader(real_obj);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glBindAttribLocation(GLuint program, GLuint index, const char* name)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glBindAttribLocation(real_obj, index, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glAttachShader(GLuint program, GLuint shader)
{
	GLuint real_obj_program;
	GLuint real_obj_shader;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj_program) != 1 ||
	    GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj_shader) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glAttachShader(real_obj_program, real_obj_shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glDetachShader(GLuint program, GLuint shader)
{
	GLuint real_obj_program;
	GLuint real_obj_shader;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj_program) != 1 ||
	    GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj_shader) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glDetachShader(real_obj_program, real_obj_shader);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

GLboolean
fpgl_glIsShader(GLuint shader)
{
	GLboolean ret;
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _sym_glIsShader(real_obj);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}

GLboolean
fpgl_glIsProgram(GLuint program)
{
	GLboolean ret;
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _sym_glIsProgram(real_obj);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}

void
fpgl_glLinkProgram(GLuint program)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glLinkProgram(real_obj);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glValidateProgram(GLuint program)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glValidateProgram(real_obj);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glUseProgram(GLuint program)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	CURR_STATE_COMPARE(gl_current_program, real_obj)
	{
		_sym_glUseProgram(real_obj);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_clear_flag1 |= FLAG_BIT_1;
		current_ctx->gl_current_program[0] = real_obj;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glGetActiveAttrib(real_obj, index, bufsize, length, size, type, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glGetActiveUniform(real_obj, index, bufsize, length, size, type, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
{
	int i;
	GLsizei real_count = _COREGL_INT_INIT_VALUE;
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glGetAttachedShaders(real_obj, maxcount, &real_count, shaders);

	for (i = 0; i < real_count; i++)
	{
		if (shaders[i] != 0)
			shaders[i] = sostate_find_object(current_ctx->sostate, GL_OBJECT_TYPE_PROGRAM, shaders[i]);
	}
	if (count != NULL) *count = real_count;

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

int
fpgl_glGetAttribLocation(GLuint program, const char* name)
{
	int ret = _COREGL_INT_INIT_VALUE;
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	ret = _sym_glGetAttribLocation(real_obj, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}

void
fpgl_glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glGetShaderiv(real_obj, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glGetShaderInfoLog(real_obj, bufsize, length, infolog);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glGetProgramiv(real_obj, pname, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glGetProgramInfoLog(real_obj, bufsize, length, infolog);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, char* source)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glGetShaderSource(real_obj, bufsize, length, source);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glGetUniformfv(GLuint program, GLint location, GLfloat* params)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glGetUniformfv(real_obj, location, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glGetUniformiv(GLuint program, GLint location, GLint* params)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glGetUniformiv(real_obj, location, params);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glGetProgramBinary(GLuint program, GLsizei bufsize, GLsizei* length, GLenum* binaryFormat, void* binary)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glGetProgramBinary(real_obj, bufsize, length, binaryFormat, binary);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glProgramBinary(GLuint program, GLenum binaryFormat, const void* binary, GLint length)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glProgramBinary(real_obj, binaryFormat, binary, length);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glProgramParameteri(GLuint program, GLuint pname, GLint value)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glProgramParameteri(real_obj, pname, value);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

int
fpgl_glGetUniformLocation(GLuint program, const char* name)
{
	int ret = _COREGL_INT_INIT_VALUE;
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		ret = -1;
		goto finish;
	}

	ret = _sym_glGetUniformLocation(real_obj, name);
	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}

void
fpgl_glDeleteShader(GLuint shader)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glDeleteShader(real_obj);
	if (real_obj != 0)
	{
		AST(sostate_remove_object(current_ctx->sostate, GL_OBJECT_TYPE_PROGRAM, shader) == 1);
	}

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glDeleteProgram(GLuint program)
{
	GLuint real_obj;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_sym_glDeleteProgram(real_obj);
	if (real_obj != 0)
	{
		AST(sostate_remove_object(current_ctx->sostate, GL_OBJECT_TYPE_PROGRAM, program) == 1);
	}

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}



//////////////////////////////////////////////////////////////////////////////////

void
fpgl_glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((current_ctx->gl_blend_color[0] != red) ||
	    (current_ctx->gl_blend_color[1] != green) ||
	    (current_ctx->gl_blend_color[2] != blue) ||
	    (current_ctx->gl_blend_color[3] != alpha))
	{
		_sym_glBlendColor(red, green, blue, alpha);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_blend_flag |= FLAG_BIT_0;
		current_ctx->gl_blend_color[0] = red;
		current_ctx->gl_blend_color[1] = green;
		current_ctx->gl_blend_color[2] = blue;
		current_ctx->gl_blend_color[3] = alpha;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


//!!! Optimze?
void
fpgl_glBlendEquation(GLenum mode)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glBlendEquation(mode);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	current_ctx->_blend_flag |= (FLAG_BIT_5 | FLAG_BIT_6);
	_sym_glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint*) & (current_ctx->gl_blend_equation_rgb));
	_sym_glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint*) & (current_ctx->gl_blend_equation_alpha));
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((current_ctx->gl_blend_equation_rgb[0] != modeRGB) ||
	    (current_ctx->gl_blend_equation_alpha[0] != modeAlpha))
	{
		_sym_glBlendEquationSeparate(modeRGB, modeAlpha);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_blend_flag |= (FLAG_BIT_5 | FLAG_BIT_6);
		current_ctx->gl_blend_equation_rgb[0]    = modeRGB;
		current_ctx->gl_blend_equation_alpha[0]  = modeAlpha;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


//!!! Optimze?
void
fpgl_glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glBlendFunc(sfactor, dfactor);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	current_ctx->_blend_flag |= (FLAG_BIT_1 | FLAG_BIT_2 | FLAG_BIT_3 | FLAG_BIT_4);
	_sym_glGetIntegerv(GL_BLEND_SRC_RGB, (GLint*) & (current_ctx->gl_blend_src_rgb));
	_sym_glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint*) & (current_ctx->gl_blend_src_alpha));
	_sym_glGetIntegerv(GL_BLEND_DST_RGB, (GLint*) & (current_ctx->gl_blend_dst_rgb));
	_sym_glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint*) & (current_ctx->gl_blend_dst_alpha));
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((current_ctx->gl_blend_src_rgb[0] != srcRGB) ||
	    (current_ctx->gl_blend_dst_rgb[0] != dstRGB) ||
	    (current_ctx->gl_blend_src_alpha[0] != srcAlpha) ||
	    (current_ctx->gl_blend_dst_alpha[0] != dstAlpha))
	{
		_sym_glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_blend_flag |= (FLAG_BIT_1 | FLAG_BIT_2 | FLAG_BIT_3 | FLAG_BIT_4);
		current_ctx->gl_blend_src_rgb[0]   = srcRGB;
		current_ctx->gl_blend_dst_rgb[0]   = dstRGB;
		current_ctx->gl_blend_src_alpha[0] = srcAlpha;
		current_ctx->gl_blend_dst_alpha[0] = dstAlpha;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((current_ctx->gl_color_clear_value[0] != red) ||
	    (current_ctx->gl_color_clear_value[1] != green) ||
	    (current_ctx->gl_color_clear_value[2] != blue) ||
	    (current_ctx->gl_color_clear_value[3] != alpha))
	{
		_sym_glClearColor(red, green, blue, alpha);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_clear_flag1 |= (FLAG_BIT_2);
		current_ctx->gl_color_clear_value[0] = red;
		current_ctx->gl_color_clear_value[1] = green;
		current_ctx->gl_color_clear_value[2] = blue;
		current_ctx->gl_color_clear_value[3] = alpha;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glClearDepthf(GLclampf depth)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	CURR_STATE_COMPARE(gl_depth_clear_value, depth)
	{
		_sym_glClearDepthf(depth);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_clear_flag2 |= FLAG_BIT_2;
		current_ctx->gl_depth_clear_value[0] = depth;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glClearStencil(GLint s)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	CURR_STATE_COMPARE(gl_stencil_clear_value, s)
	{
		_sym_glClearStencil(s);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_stencil_flag2 |= FLAG_BIT_7;
		current_ctx->gl_stencil_clear_value[0] = s;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((current_ctx->gl_color_writemask[0] != red) ||
	    (current_ctx->gl_color_writemask[1] != green) ||
	    (current_ctx->gl_color_writemask[2] != blue) ||
	    (current_ctx->gl_color_writemask[3] != alpha))
	{
		_sym_glColorMask(red, green, blue, alpha);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_clear_flag2 |= FLAG_BIT_0;
		current_ctx->gl_color_writemask[0] = red;
		current_ctx->gl_color_writemask[1] = green;
		current_ctx->gl_color_writemask[2] = blue;
		current_ctx->gl_color_writemask[3] = alpha;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glCullFace(GLenum mode)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	CURR_STATE_COMPARE(gl_cull_face_mode, mode)
	{
		_sym_glCullFace(mode);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_clear_flag2 |= FLAG_BIT_5;
		current_ctx->gl_cull_face_mode[0] = mode;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glDepthFunc(GLenum func)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	CURR_STATE_COMPARE(gl_depth_func, func)
	{
		_sym_glDepthFunc(func);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_clear_flag2 |= FLAG_BIT_3;
		current_ctx->gl_depth_func[0] = func;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glDepthMask(GLboolean flag)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	CURR_STATE_COMPARE(gl_depth_writemask, flag)
	{
		_sym_glDepthMask(flag);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_clear_flag2 |= FLAG_BIT_4;
		current_ctx->gl_depth_writemask[0] = flag;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glDepthRangef(GLclampf zNear, GLclampf zFar)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((current_ctx->gl_depth_range[0] != zNear) ||
	    (current_ctx->gl_depth_range[1] != zFar))
	{
		_sym_glDepthRangef(zNear, zFar);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_clear_flag2 |= FLAG_BIT_1;
		current_ctx->gl_depth_range[0] = zNear;
		current_ctx->gl_depth_range[1] = zFar;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glDisable(GLenum cap)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	switch (cap)
	{
		case GL_BLEND:
			CURR_STATE_COMPARE(gl_blend, GL_FALSE)
			{
				_sym_glDisable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");
				current_ctx->_enable_flag1 &= (~FLAG_BIT_0);
				current_ctx->gl_blend[0] = GL_FALSE;
			}
			break;
		case GL_CULL_FACE:
			CURR_STATE_COMPARE(gl_cull_face, GL_FALSE)
			{
				_sym_glDisable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");
				current_ctx->_enable_flag1 &= (~FLAG_BIT_1);
				current_ctx->gl_cull_face[0] = GL_FALSE;
			}
			break;
		case GL_DEPTH_TEST:
			CURR_STATE_COMPARE(gl_depth_test, GL_FALSE)
			{
				_sym_glDisable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");
				current_ctx->_enable_flag1 &= (~FLAG_BIT_2);
				current_ctx->gl_depth_test[0] = GL_FALSE;
			}
			break;
		case GL_DITHER:
			CURR_STATE_COMPARE(gl_dither, GL_FALSE)
			{
				_sym_glDisable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");
				current_ctx->_enable_flag1 &= (~FLAG_BIT_3);
				current_ctx->gl_dither[0] = GL_FALSE;
			}
			break;
		case GL_POLYGON_OFFSET_FILL:
			CURR_STATE_COMPARE(gl_polygon_offset_fill, GL_FALSE)
			{
				_sym_glDisable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");
				current_ctx->_enable_flag2 &= (~FLAG_BIT_0);
				current_ctx->gl_polygon_offset_fill[0] = GL_FALSE;
			}
			break;
		case GL_SAMPLE_ALPHA_TO_COVERAGE:
			CURR_STATE_COMPARE(gl_sample_alpha_to_coverage, GL_FALSE)
			{
				_sym_glDisable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");
				current_ctx->_enable_flag2 &= (~FLAG_BIT_1);
				current_ctx->gl_sample_alpha_to_coverage[0] = GL_FALSE;
			}
			break;
		case GL_SAMPLE_COVERAGE:
			CURR_STATE_COMPARE(gl_sample_coverage, GL_FALSE)
			{
				_sym_glDisable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");
				current_ctx->_enable_flag2 &= (~FLAG_BIT_2);
				current_ctx->gl_sample_coverage[0] = GL_FALSE;
			}
			break;
		case GL_SCISSOR_TEST:
			CURR_STATE_COMPARE(gl_scissor_test, GL_FALSE)
			{
				_sym_glDisable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");
				current_ctx->_enable_flag2 &= (~FLAG_BIT_3);
				current_ctx->gl_scissor_test[0] = GL_FALSE;
			}
			break;
		case GL_STENCIL_TEST:
			CURR_STATE_COMPARE(gl_stencil_test, GL_FALSE)
			{
				_sym_glDisable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");
				current_ctx->_enable_flag2 &= (~FLAG_BIT_4);
				current_ctx->gl_stencil_test[0] = GL_FALSE;
			}
			break;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glDisableVertexAttribArray(GLuint index)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glDisableVertexAttribArray(index);

	current_ctx->_vattrib_flag |= FLAG_BIT_1;
	current_ctx->gl_vertex_array_enabled[index]    = GL_FALSE;

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glDrawArrays(mode, first, count);
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glDrawElements(mode, count, type, indices);
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glEnable(GLenum cap)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	switch (cap)
	{
		case GL_BLEND:
			CURR_STATE_COMPARE(gl_blend, GL_TRUE)
			{
				_sym_glEnable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");

				current_ctx->_enable_flag1 |= FLAG_BIT_0;
				current_ctx->gl_blend[0] = GL_TRUE;
			}
			break;
		case GL_CULL_FACE:
			CURR_STATE_COMPARE(gl_cull_face, GL_TRUE)
			{
				_sym_glEnable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");


				current_ctx->_enable_flag1 |= FLAG_BIT_1;
				current_ctx->gl_cull_face[0] = GL_TRUE;
			}
			break;
		case GL_DEPTH_TEST:
			CURR_STATE_COMPARE(gl_depth_test, GL_TRUE)
			{
				_sym_glEnable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");


				current_ctx->_enable_flag1 |= FLAG_BIT_2;
				current_ctx->gl_depth_test[0] = GL_TRUE;
			}
			break;
		case GL_DITHER:
			CURR_STATE_COMPARE(gl_dither, GL_TRUE)
			{
				_sym_glEnable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");


				current_ctx->_enable_flag1 |= FLAG_BIT_3;
				current_ctx->gl_dither[0] = GL_TRUE;
			}
			break;
		case GL_POLYGON_OFFSET_FILL:
			CURR_STATE_COMPARE(gl_polygon_offset_fill, GL_TRUE)
			{
				_sym_glEnable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");


				current_ctx->_enable_flag2 |= FLAG_BIT_0;
				current_ctx->gl_polygon_offset_fill[0] = GL_TRUE;
			}
			break;
		case GL_SAMPLE_ALPHA_TO_COVERAGE:
			CURR_STATE_COMPARE(gl_sample_alpha_to_coverage, GL_TRUE)
			{
				_sym_glEnable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");


				current_ctx->_enable_flag2 |= FLAG_BIT_1;
				current_ctx->gl_sample_alpha_to_coverage[0] = GL_TRUE;
			}
			break;
		case GL_SAMPLE_COVERAGE:
			CURR_STATE_COMPARE(gl_sample_coverage, GL_TRUE)
			{
				_sym_glEnable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");


				current_ctx->_enable_flag2 |= FLAG_BIT_2;
				current_ctx->gl_sample_coverage[0] = GL_TRUE;
			}
			break;
		case GL_SCISSOR_TEST:
			CURR_STATE_COMPARE(gl_scissor_test, GL_TRUE)
			{
				_sym_glEnable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");


				current_ctx->_enable_flag2 |= FLAG_BIT_3;
				current_ctx->gl_scissor_test[0] = GL_TRUE;
			}
			break;
		case GL_STENCIL_TEST:
			CURR_STATE_COMPARE(gl_stencil_test, GL_TRUE)
			{
				_sym_glEnable(cap);
				GLERR(__FUNCTION__, __FILE__, __LINE__, "");


				current_ctx->_enable_flag2 |= FLAG_BIT_4;
				current_ctx->gl_stencil_test[0] = GL_TRUE;
			}
			break;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


// Optimze?
void
fpgl_glEnableVertexAttribArray(GLuint index)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glEnableVertexAttribArray(index);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	current_ctx->_vattrib_flag |= FLAG_BIT_1;
	current_ctx->gl_vertex_array_enabled[index]    = GL_TRUE;

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glFrontFace(GLenum mode)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	CURR_STATE_COMPARE(gl_front_face, mode)
	{
		_sym_glFrontFace(mode);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_misc_flag1 |= FLAG_BIT_0;
		current_ctx->gl_front_face[0] = mode;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glGetVertexAttribfv(index, pname, params);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glGetVertexAttribiv(index, pname, params);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glGetVertexAttribPointerv(index, pname, pointer);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

// Fix Maybe?
void
fpgl_glHint(GLenum target, GLenum mode)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (target == GL_GENERATE_MIPMAP_HINT)
	{
		CURR_STATE_COMPARE(gl_generate_mipmap_hint, mode)
		{
			_sym_glHint(target, mode);

			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			current_ctx->_tex_flag1 |= FLAG_BIT_2;
			current_ctx->gl_generate_mipmap_hint[0] = mode;
		}
	}
	else
	{
		// For GL Error to be picked up
		_sym_glHint(target, mode);
		GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glLineWidth(GLfloat width)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	CURR_STATE_COMPARE(gl_line_width, width)
	{
		_sym_glLineWidth(width);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_misc_flag1 |= FLAG_BIT_1;
		current_ctx->gl_line_width[0] = width;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glPixelStorei(GLenum pname, GLint param)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (pname == GL_PACK_ALIGNMENT)
	{
		CURR_STATE_COMPARE(gl_pack_alignment, param)
		{
			_sym_glPixelStorei(pname, param);

			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			current_ctx->_misc_flag2 |= FLAG_BIT_1;
			current_ctx->gl_pack_alignment[0] = param;
		}
	}
	else if (pname == GL_UNPACK_ALIGNMENT)
	{
		CURR_STATE_COMPARE(gl_unpack_alignment, param)
		{
			_sym_glPixelStorei(pname, param);

			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			current_ctx->_misc_flag2 |= FLAG_BIT_2;
			current_ctx->gl_unpack_alignment[0] = param;
		}
	}
	else
	{
		// For GL Error to be picked up
		_sym_glPixelStorei(pname, param);
		GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glPolygonOffset(GLfloat factor, GLfloat units)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((current_ctx->gl_polygon_offset_factor[0] != factor) ||
	    (current_ctx->gl_polygon_offset_units[0] != units))
	{
		_sym_glPolygonOffset(factor, units);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_misc_flag1 |= (FLAG_BIT_2 | FLAG_BIT_3);
		current_ctx->gl_polygon_offset_factor[0] = factor;
		current_ctx->gl_polygon_offset_units[0]  = units;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glSampleCoverage(GLclampf value, GLboolean invert)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((current_ctx->gl_sample_coverage_value[0] != value) ||
	    (current_ctx->gl_sample_coverage_invert[0] != invert))
	{
		_sym_glSampleCoverage(value, invert);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_misc_flag1 |= (FLAG_BIT_4 | FLAG_BIT_5);
		current_ctx->gl_sample_coverage_value[0]  = value;
		current_ctx->gl_sample_coverage_invert[0] = invert;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((current_ctx->gl_scissor_box[0] != x) ||
	    (current_ctx->gl_scissor_box[1] != y) ||
	    (current_ctx->gl_scissor_box[2] != width) ||
	    (current_ctx->gl_scissor_box[3] != height))
	{
		_sym_glScissor(x, y, width, height);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_misc_flag2 |= FLAG_BIT_0;
		current_ctx->gl_scissor_box[0] = x;
		current_ctx->gl_scissor_box[1] = y;
		current_ctx->gl_scissor_box[2] = width;
		current_ctx->gl_scissor_box[3] = height;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((current_ctx->gl_stencil_func[0] != func) ||
	    (current_ctx->gl_stencil_ref[0] != ref) ||
	    (current_ctx->gl_stencil_value_mask[0] != mask) ||
	    (current_ctx->gl_stencil_back_func[0] != func) ||
	    (current_ctx->gl_stencil_back_ref[0] != ref) ||
	    (current_ctx->gl_stencil_back_value_mask[0] != mask))
	{
		_sym_glStencilFunc(func, ref, mask);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_stencil_flag1 |= (FLAG_BIT_0 | FLAG_BIT_1 | FLAG_BIT_2);
		current_ctx->gl_stencil_func[0]             = func;
		current_ctx->gl_stencil_ref[0]              = ref;
		current_ctx->gl_stencil_value_mask[0]       = mask;

		current_ctx->_stencil_flag2 |= (FLAG_BIT_0 | FLAG_BIT_1 | FLAG_BIT_2);
		current_ctx->gl_stencil_back_func[0]        = func;
		current_ctx->gl_stencil_back_ref[0]         = ref;
		current_ctx->gl_stencil_back_value_mask[0]  = mask;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((face == GL_FRONT) || (face == GL_FRONT_AND_BACK))
	{
		if ((current_ctx->gl_stencil_func[0] != func) ||
		    (current_ctx->gl_stencil_ref[0] != ref) ||
		    (current_ctx->gl_stencil_value_mask[0] != mask))
		{
			_sym_glStencilFuncSeparate(face, func, ref, mask);

			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			current_ctx->_stencil_flag1 |= (FLAG_BIT_0 | FLAG_BIT_1 | FLAG_BIT_2);

			current_ctx->gl_stencil_func[0]             = func;
			current_ctx->gl_stencil_ref[0]              = ref;
			current_ctx->gl_stencil_value_mask[0]       = mask;
		}
	}
	else if ((face == GL_BACK) || (face == GL_FRONT_AND_BACK))
	{
		if ((current_ctx->gl_stencil_back_func[0] != func) ||
		    (current_ctx->gl_stencil_back_ref[0] != ref) ||
		    (current_ctx->gl_stencil_back_value_mask[0] != mask))
		{
			_sym_glStencilFuncSeparate(face, func, ref, mask);

			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			current_ctx->_stencil_flag2 |= (FLAG_BIT_0 | FLAG_BIT_1 | FLAG_BIT_2);

			current_ctx->gl_stencil_back_func[0]        = func;
			current_ctx->gl_stencil_back_ref[0]         = ref;
			current_ctx->gl_stencil_back_value_mask[0]  = mask;
		}
	}
	else
	{
		// Have GL pick up the error
		_sym_glStencilFuncSeparate(face, func, ref, mask);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glStencilMask(GLuint mask)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((current_ctx->gl_stencil_writemask[0] != mask) ||
	    (current_ctx->gl_stencil_back_writemask[0] != mask))
	{
		_sym_glStencilMask(mask);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_stencil_flag1 |= (FLAG_BIT_6);
		current_ctx->_stencil_flag2 |= (FLAG_BIT_6);

		current_ctx->gl_stencil_writemask[0]        = mask;
		current_ctx->gl_stencil_back_writemask[0]   = mask;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glStencilMaskSeparate(GLenum face, GLuint mask)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((face == GL_FRONT) || (face == GL_FRONT_AND_BACK))
	{
		if (current_ctx->gl_stencil_writemask[0] != mask)
		{
			_sym_glStencilMaskSeparate(face, mask);

			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			current_ctx->_stencil_flag1 |= (FLAG_BIT_6);
			current_ctx->gl_stencil_writemask[0] = mask;
		}
	}
	else if ((face == GL_BACK) || (face == GL_FRONT_AND_BACK))
	{
		if (current_ctx->gl_stencil_back_writemask[0] != mask)
		{
			_sym_glStencilMaskSeparate(face, mask);

			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			current_ctx->_stencil_flag2 |= (FLAG_BIT_6);
			current_ctx->gl_stencil_back_writemask[0]   = mask;
		}
	}
	else
	{
		// Have GL pick up the error
		_sym_glStencilMaskSeparate(face, mask);
		GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((current_ctx->gl_stencil_fail[0] != fail) ||
	    (current_ctx->gl_stencil_pass_depth_fail[0] != zfail) ||
	    (current_ctx->gl_stencil_pass_depth_pass[0] != zpass) ||
	    (current_ctx->gl_stencil_back_fail[0] != fail) ||
	    (current_ctx->gl_stencil_back_pass_depth_fail[0] != zfail) ||
	    (current_ctx->gl_stencil_back_pass_depth_pass[0] != zpass))
	{
		_sym_glStencilOp(fail, zfail, zpass);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_stencil_flag1 |= (FLAG_BIT_3 | FLAG_BIT_4 | FLAG_BIT_5);
		current_ctx->gl_stencil_fail[0]              = fail;
		current_ctx->gl_stencil_pass_depth_fail[0]   = zfail;
		current_ctx->gl_stencil_pass_depth_pass[0]   = zpass;

		current_ctx->_stencil_flag2 |= (FLAG_BIT_3 | FLAG_BIT_4 | FLAG_BIT_5);
		current_ctx->gl_stencil_back_fail[0]         = fail;
		current_ctx->gl_stencil_back_pass_depth_fail[0]   = zfail;
		current_ctx->gl_stencil_back_pass_depth_pass[0]   = zpass;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((face == GL_FRONT) || (face == GL_FRONT_AND_BACK))
	{
		if ((current_ctx->gl_stencil_fail[0] != fail) ||
		    (current_ctx->gl_stencil_pass_depth_fail[0] != zfail) ||
		    (current_ctx->gl_stencil_pass_depth_pass[0] != zpass))
		{
			_sym_glStencilOpSeparate(face, fail, zfail, zpass);
			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			current_ctx->_stencil_flag1 |= (FLAG_BIT_3 | FLAG_BIT_4 | FLAG_BIT_5);
			current_ctx->gl_stencil_fail[0]              = fail;
			current_ctx->gl_stencil_pass_depth_fail[0]   = zfail;
			current_ctx->gl_stencil_pass_depth_pass[0]   = zpass;
		}
	}
	else if ((face == GL_BACK) || (face == GL_FRONT_AND_BACK))
	{
		if ((current_ctx->gl_stencil_back_fail[0] != fail) ||
		    (current_ctx->gl_stencil_back_pass_depth_fail[0] != zfail) ||
		    (current_ctx->gl_stencil_back_pass_depth_pass[0] != zpass))
		{
			_sym_glStencilOpSeparate(face, fail, zfail, zpass);
			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			current_ctx->_stencil_flag2 |= (FLAG_BIT_3 | FLAG_BIT_4 | FLAG_BIT_5);
			current_ctx->gl_stencil_back_fail[0]         = fail;
			current_ctx->gl_stencil_back_pass_depth_fail[0]   = zfail;
			current_ctx->gl_stencil_back_pass_depth_pass[0]   = zpass;
		}
	}
	else
	{
		// For picking up error purpose
		_sym_glStencilOpSeparate(face, fail, zfail, zpass);
		GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

// Optmize?
void
fpgl_glVertexAttrib1f(GLuint indx, GLfloat x)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glVertexAttrib1f(indx, x);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	current_ctx->_vattrib_flag |= FLAG_BIT_0;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 0] = x;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 1] = 0;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 2] = 0;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 3] = 1;
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


// Optmize?
void
fpgl_glVertexAttrib1fv(GLuint indx, const GLfloat* values)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glVertexAttrib1fv(indx, values);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	current_ctx->_vattrib_flag |= FLAG_BIT_0;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 0] = values[0];
	current_ctx->gl_vertex_attrib_value[indx * 4 + 1] = 0;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 2] = 0;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 3] = 1;
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


// Optmize?
void
fpgl_glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glVertexAttrib2f(indx, x, y);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	current_ctx->_vattrib_flag |= FLAG_BIT_0;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 0] = x;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 1] = y;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 2] = 0;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 3] = 1;
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


// Optmize?
void
fpgl_glVertexAttrib2fv(GLuint indx, const GLfloat* values)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glVertexAttrib2fv(indx, values);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	current_ctx->_vattrib_flag |= FLAG_BIT_0;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 0] = values[0];
	current_ctx->gl_vertex_attrib_value[indx * 4 + 1] = values[1];
	current_ctx->gl_vertex_attrib_value[indx * 4 + 2] = 0;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 3] = 1;
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


// Optmize?
void
fpgl_glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glVertexAttrib3f(indx, x, y, z);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	current_ctx->_vattrib_flag |= FLAG_BIT_0;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 0] = x;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 1] = y;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 2] = z;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 3] = 1;
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


// Optmize?
void
fpgl_glVertexAttrib3fv(GLuint indx, const GLfloat* values)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glVertexAttrib3fv(indx, values);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	current_ctx->_vattrib_flag |= FLAG_BIT_0;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 0] = values[0];
	current_ctx->gl_vertex_attrib_value[indx * 4 + 1] = values[1];
	current_ctx->gl_vertex_attrib_value[indx * 4 + 2] = values[2];
	current_ctx->gl_vertex_attrib_value[indx * 4 + 3] = 1;
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


// Optmize?
void
fpgl_glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glVertexAttrib4f(indx, x, y, z, w);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	current_ctx->_vattrib_flag |= FLAG_BIT_0;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 0] = x;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 1] = y;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 2] = z;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 3] = w;
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


// Optmize?
void
fpgl_glVertexAttrib4fv(GLuint indx, const GLfloat* values)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glVertexAttrib4fv(indx, values);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	current_ctx->_vattrib_flag |= FLAG_BIT_0;
	current_ctx->gl_vertex_attrib_value[indx * 4 + 0] = values[0];
	current_ctx->gl_vertex_attrib_value[indx * 4 + 1] = values[1];
	current_ctx->gl_vertex_attrib_value[indx * 4 + 2] = values[2];
	current_ctx->gl_vertex_attrib_value[indx * 4 + 3] = values[3];
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}



// Optmize?
void
fpgl_glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	_sym_glVertexAttribPointer(indx, size, type, normalized, stride, ptr);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	current_ctx->_vattrib_flag |= FLAG_BIT_1;

	current_ctx->gl_vertex_array_buf_id[indx]     = current_ctx->gl_array_buffer_binding[0];
	current_ctx->gl_vertex_array_size[indx]       = size;
	current_ctx->gl_vertex_array_type[indx]       = type;
	current_ctx->gl_vertex_array_normalized[indx] = normalized;
	current_ctx->gl_vertex_array_stride[indx]     = stride;
	current_ctx->gl_vertex_array_pointer[indx]    = (GLvoid *)ptr;
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if ((current_ctx->gl_viewport[0] != x) ||
	    (current_ctx->gl_viewport[1] != y) ||
	    (current_ctx->gl_viewport[2] != width) ||
	    (current_ctx->gl_viewport[3] != height))
	{
		_sym_glViewport(x, y, width, height);

		GLERR(__FUNCTION__, __FILE__, __LINE__, "");

		current_ctx->_clear_flag1 |= FLAG_BIT_0;
		current_ctx->gl_viewport[0] = x;
		current_ctx->gl_viewport[1] = y;
		current_ctx->gl_viewport[2] = width;
		current_ctx->gl_viewport[3] = height;
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glEGLImageTargetTexture2DOES(GLenum target, GLeglImageOES image)
{
	int tex_idx;

	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	tex_idx = current_ctx->gl_active_texture[0] - GL_TEXTURE0;

	switch (target)
	{
		case GL_TEXTURE_2D:
			current_ctx->gl_tex_2d_state[tex_idx] = -1;
			break;
		case GL_TEXTURE_CUBE_MAP:
			current_ctx->gl_tex_cube_state[tex_idx] = -1;
			break;
	}

	_sym_glEGLImageTargetTexture2DOES(target, image);

	GLERR(__FUNCTION__, __FILE__, __LINE__, "");

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

static GLboolean
_process_getfunc(GLenum pname, GLvoid *ptr, GLenum get_type)
{
	GLboolean ret = GL_FALSE;

	DEFINE_FAST_GL_FUNC();
	INIT_FAST_GL_FUNC();

	switch (pname)
	{
		case GL_TEXTURE_BINDING_2D:
		{
			GLint real_tex_id = _COREGL_INT_INIT_VALUE;
			GLuint glue_tex_id = _COREGL_INT_INIT_VALUE;
			_sym_glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)real_tex_id);

			GLERR(__FUNCTION__, __FILE__, __LINE__, "");

			if (real_tex_id == 0)
			{
				glue_tex_id = 0;
			}
			else
			{
				AST(current_ctx->sostate != NULL);
				glue_tex_id = sostate_find_object(current_ctx->sostate, GL_OBJECT_TYPE_TEXTURE, real_tex_id);
			}

			switch (get_type)
			{
				case GL_INT:
					((GLint *)ptr)[0] = glue_tex_id;
					break;
				case GL_FLOAT:
					((GLfloat *)ptr)[0] = (GLfloat)glue_tex_id;
					break;
				case GL_BOOL:
					((GLboolean *)ptr)[0] = (glue_tex_id == 0) ? GL_FALSE : GL_TRUE;
					break;
			}
			ret = GL_TRUE;
			break;
		}
	}
	goto finish;

finish:
	return ret;
}


void
fpgl_glGetBooleanv(GLenum pname, GLboolean* params)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (_process_getfunc(pname, params, GL_BOOL) != GL_TRUE)
	{
		_sym_glGetBooleanv(pname, params);
		GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glGetFloatv(GLenum pname, GLfloat* params)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (_process_getfunc(pname, params, GL_FLOAT) != GL_TRUE)
	{
		_sym_glGetFloatv(pname, params);
		GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

void
fpgl_glGetIntegerv(GLenum pname, GLint* params)
{
	DEFINE_FAST_GL_FUNC();
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GL_FUNC();

	if (_process_getfunc(pname, params, GL_INT) != GL_TRUE)
	{
		_sym_glGetIntegerv(pname, params);
		GLERR(__FUNCTION__, __FILE__, __LINE__, "");
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

