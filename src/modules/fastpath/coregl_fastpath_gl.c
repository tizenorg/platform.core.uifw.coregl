#include "coregl_fastpath.h"

#include <stdlib.h>
#include <execinfo.h>

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
int kill(pid_t pid, int sig);


#define CURR_STATE_COMPARE(curr_state, state ) \
   if ((current_ctx->curr_state[0]) != (state))

#define STATE_PROC_WITH_CHECK(gl_state, flagid, flagbit) \
	if (current_ctx->gl_state##_used == 1) \
	{ \
		STATE_PROC(gl_state, flagid, flagbit) \
	} \
	else \
		_set_gl_error(GL_INVALID_ENUM);

#define IF_GL_SUCCESS(orig_gl_func) \
	_get_gl_error(); \
	orig_gl_func; \
	if (_get_gl_error() == GL_NO_ERROR)

#define DEFINE_FASTPAH_GL_FUNC() \
   MY_MODULE_TSTATE *tstate = NULL; \
   GLGlueContext *current_ctx = NULL;

#define INIT_FASTPATH_GL_FUNC() \
   GET_MY_TSTATE(tstate, get_current_thread_state()); \
   if (tstate == NULL || tstate->cstate == NULL) \
   { \
		COREGL_WRN("\E[40;31;1m'%s' called when GLES context is not binded (Check MakeCurrent)!\E[0m\n", __func__); \
		goto finish; \
   } \
   current_ctx = (GLGlueContext *)tstate->cstate->data; \
   AST(current_ctx != NULL);

#define GET_REAL_OBJ(type, glue_handle, real_handle) \
	_get_real_obj(&current_ctx->ostate, type, glue_handle, real_handle)
#define GET_GLUE_OBJ(type, real_handle, glue_handle) \
	_get_glue_obj(&current_ctx->ostate, type, real_handle, glue_handle)

static inline int
_get_real_obj(GL_Object_State *ostate, GL_Object_Type type, GLuint glue_handle, GLuint *real_handle)
{
	if (glue_handle == 0)
	{
		*real_handle = 0;
	}
	else
	{
		AST(ostate != NULL);
		*real_handle = fastpath_ostate_get_object(ostate, type, glue_handle);
		if (*real_handle == 0)
			return 0;
	}
	return 1;
}

static inline int
_get_glue_obj(GL_Object_State *ostate, GL_Object_Type type, GLuint real_handle, GLuint *glue_handle)
{
	if (real_handle == 0)
	{
		*glue_handle = 0;
	}
	else
	{
		AST(ostate != NULL);
		*glue_handle = fastpath_ostate_find_object(ostate, type, real_handle);
		if (*glue_handle == 0)
			return 0;
	}
	return 1;
}

static inline GLenum
_get_gl_error()
{
	GLenum glerror = GL_NONE;
	DEFINE_FASTPAH_GL_FUNC();
	INIT_FASTPATH_GL_FUNC();

	glerror = _orig_fastpath_glGetError();

	if (current_ctx->gl_error == GL_NO_ERROR && glerror != GL_NO_ERROR)
	{
		current_ctx->gl_error = glerror;
	}
	goto finish;

finish:
	return glerror;
}

static inline void
_set_gl_error(GLenum error)
{
	DEFINE_FASTPAH_GL_FUNC();
	INIT_FASTPATH_GL_FUNC();

	_get_gl_error();

	if (current_ctx->gl_error == GL_NO_ERROR && error != GL_NO_ERROR)
	{
		current_ctx->gl_error = error;
	}
	goto finish;

finish:
	return;
}

typedef struct
{
	GLsizei shader_count;
	GLuint shaders[10];
	GLuint is_deleting;
} Program_object_attached_tag;

GLuint
_create_program_object(GL_Object_State *ostate, int is_program, GLenum shader_type)
{
	GLuint ret = 0;
	GLuint real_obj = 0;

	if (is_program == 1)
		real_obj = _orig_fastpath_glCreateProgram();
	else
		real_obj = _orig_fastpath_glCreateShader(shader_type);

	if (real_obj != 0)
	{
		ret = fastpath_ostate_create_object(ostate, GL_OBJECT_TYPE_PROGRAM, real_obj);

		Program_object_attached_tag *poat = NULL;
		poat = (Program_object_attached_tag *)calloc(1, sizeof(Program_object_attached_tag));
		AST(poat != NULL);

		poat->is_deleting = 0;
		poat->shader_count = 0;

		fastpath_ostate_set_object_tag(ostate, GL_OBJECT_TYPE_PROGRAM, ret, poat);
	}

	return ret;
}

static void
_update_program_attach_info(GL_Object_State *ostate, GLuint program)
{
	Program_object_attached_tag *poat = NULL;
	GLuint real_program = _COREGL_INT_INIT_VALUE;

	poat = (Program_object_attached_tag *)fastpath_ostate_get_object_tag(ostate, GL_OBJECT_TYPE_PROGRAM, program);
	AST(poat != NULL);

	real_program = fastpath_ostate_get_object(ostate, GL_OBJECT_TYPE_PROGRAM, program);
	AST(real_program > 0);

	_orig_fastpath_glGetAttachedShaders(real_program, 10, &poat->shader_count, poat->shaders);
}

static void
_attach_program_object(GL_Object_State *ostate, GLuint object)
{
	if (object != 0)
	{
		fastpath_ostate_use_object(ostate, GL_OBJECT_TYPE_PROGRAM, object);
	}
}

static int
_is_deleted_program_object(GL_Object_State *ostate, GLuint glue_object)
{
	Program_object_attached_tag *poat = NULL;
	poat = (Program_object_attached_tag *)fastpath_ostate_get_object_tag(ostate, GL_OBJECT_TYPE_PROGRAM, glue_object);
	AST(poat != NULL);
	return poat->is_deleting;
}

static void
_detach_program_object(GL_Object_State *ostate, GLuint real_object, int is_program, int is_deleting)
{
	if (real_object != 0)
	{
		GLuint object = _COREGL_INT_INIT_VALUE;
		Program_object_attached_tag *poat = NULL;

		object = fastpath_ostate_find_object(ostate, GL_OBJECT_TYPE_PROGRAM, real_object);
		AST(object != 0);

		poat = (Program_object_attached_tag *)fastpath_ostate_get_object_tag(ostate, GL_OBJECT_TYPE_PROGRAM, object);
		AST(poat != NULL);

		if (is_deleting == 1)
		{
			if (poat->is_deleting == 0)
			{
				poat->is_deleting = 1;
				fastpath_ostate_remove_object(ostate, GL_OBJECT_TYPE_PROGRAM, object);
			}
		}
		else
		{
			fastpath_ostate_remove_object(ostate, GL_OBJECT_TYPE_PROGRAM, object);
		}

		if (fastpath_ostate_get_object(ostate, GL_OBJECT_TYPE_PROGRAM, object) == 0)
		{
			// Is completely removed. De-referencing attached shader objects
			int i;
			for (i = 0; i < poat->shader_count; i++)
			{
				AST(is_program == 1);
				_detach_program_object(ostate, poat->shaders[i], 0, 0);
			}

			free(poat);
			poat = NULL;

			if (is_program == 1)
				_orig_fastpath_glDeleteProgram(real_object);
			else
				_orig_fastpath_glDeleteShader(real_object);
		}
	}
}


void
fastpath_release_gl_context(GLGlueContext *gctx)
{
	// Release program
	if (gctx->gl_current_program[0] != 0)
	{
		_detach_program_object(&gctx->ostate, gctx->gl_current_program[0], 1, 0);
		gctx->gl_current_program[0] = 0;
	}
}


static float
_get_gl_version()
{
	float GLver = 0.0;
	const char *vret;
	int vlen = _COREGL_INT_INIT_VALUE;
	int i = _COREGL_INT_INIT_VALUE;
	char vret_tmp[80 + 1] = { 0 };
	IF_GL_SUCCESS(vret = (const char *)_orig_fastpath_glGetString(GL_VERSION))
	{
		vlen = (int)strlen(vret);
		if (!strncmp(vret, "OpenGL ES", 9) && vlen >= 11)
		{
			int stp = 10;
			if (vret[9] == '-')
			{
				if (vlen < 14) return 0.0f;
				stp = 13;
			}

			for (i = stp; ; i++)
			{
				if (vret[i] == ' ' || vret[i] == 0x00 || i >= 80)
				{
					strncpy(vret_tmp, &vret[stp], i - stp);
					vret_tmp[i - stp] = 0x00;
					break;
				}
			}
			if (vret_tmp[0] != 0x00)
				GLver = atof(vret_tmp);
		}
	}
	return GLver;
}


Mutex extension_check_mutex = MUTEX_INITIALIZER;
char string_extensions[16384] = { 0x00 };
char string_each_extensions[128][64];
int gl_extension_count = 0;


static void
_valid_extension_string()
{
	char string_tmpbuf[2048];
	const char *res = NULL;

	AST(mutex_lock(&extension_check_mutex) == 1);

	if (gl_extension_count == 0)
	{
		IF_GL_SUCCESS(res = (const char *)_orig_fastpath_glGetString(GL_EXTENSIONS))
		{
			if (string_extensions[0] == 0x00)
			{
				double GLver = _get_gl_version();

				strcpy(string_tmpbuf, res);
				char *fstr = &string_tmpbuf[0], *estr = NULL;
				for (estr = fstr; ; estr++)
				{
					if (*estr == 0x00) break;
					if (*estr == ' ')
					{
						*estr = 0x00;

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)
#define _COREGL_FASTPATH_SUPPORTED_EXTENSION(NAME, MINVER, MAXVER) \
						if (!strcmp(fstr, NAME) && (MINVER < 0 || GLver >= MINVER) && (MAXVER < 0 || GLver <= MAXVER)) \
						{ \
							strcpy(string_each_extensions[gl_extension_count], fstr); \
							strcat(string_extensions, fstr); \
							strcat(string_extensions, " "); \
							gl_extension_count++; \
						}

# include "../../headers/sym_gl.h"

#undef _COREGL_FASTPATH_SUPPORTED_EXTENSION
#undef _COREGL_SYMBOL

						fstr = estr + 1;
					}
				}
			}
		}
	}

	AST(mutex_unlock(&extension_check_mutex) == 1);
}


GLenum
fastpath_glGetError(void)
{
	GLenum ret = GL_NONE;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (current_ctx->gl_error != GL_NO_ERROR)
	{
		ret = current_ctx->gl_error;
		current_ctx->gl_error = GL_NO_ERROR;
		_orig_fastpath_glGetError();
	}
	else
	{
		ret = _orig_fastpath_glGetError();
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


const GLubyte *
fastpath_glGetString(GLenum name)
{
	const char *ret = NULL;
	static const char *string_gles20 = "OpenGL ES 2.0";
	static const char *string_gles30 = "OpenGL ES 3.0";

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	switch (name)
	{
		case GL_VERSION:
			IF_GL_SUCCESS(ret = (const char *)_orig_fastpath_glGetString(name))
			{
				double GLver = _get_gl_version();
				if (GLver > 3.0)
				{
					COREGL_WRN("\E[40;31;1mFastpath can't support %s (Fixed to %s)\E[0m\n", ret, string_gles30);
					ret = string_gles30;
				}
				if (GLver < 2.0)
				{
					COREGL_WRN("\E[40;31;1mFastpath can't support %s (Fixed to %s)\E[0m\n", ret, string_gles20);
					ret = string_gles20;
				}
			}
			break;
		case GL_EXTENSIONS:
			_valid_extension_string();
			ret = string_extensions;
			break;
		default:
			IF_GL_SUCCESS(ret = (const char *)_orig_fastpath_glGetString(name))
			{
			}
			else
			{
				ret = NULL;
			}
			break;
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return (const GLubyte *)ret;
}

////////////////////////////////////////////////////////////////////////

void
fastpath_glActiveTexture(GLenum texture)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	CURR_STATE_COMPARE(gl_active_texture, texture)
	{
		IF_GL_SUCCESS(_orig_fastpath_glActiveTexture(texture))
		{
			current_ctx->_tex_flag1 |= _TEX_FLAG1_BIT_gl_active_texture;
			current_ctx->gl_active_texture[0] = texture;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGenTextures(GLsizei n, GLuint* textures)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (textures == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);

	IF_GL_SUCCESS(_orig_fastpath_glGenTextures(n, objid_array))
	{
		for (i = 0; i < n; i++)
		{
			textures[i] = fastpath_ostate_create_object(&current_ctx->ostate, GL_OBJECT_TYPE_TEXTURE, objid_array[i]);
		}
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glBindTexture(GLenum target, GLuint texture)
{
	int active_idx;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	active_idx = current_ctx->gl_active_texture[0] - GL_TEXTURE0;

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_TEXTURE, texture, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}


#define STATE_PROC(gl_state, flagid, flagbit) \
	if (current_ctx->gl_state[active_idx] != real_obj) \
	{ \
		IF_GL_SUCCESS(_orig_fastpath_glBindTexture(target, real_obj)) \
		{ \
			current_ctx->flagid |= flagbit##_##gl_state; \
			current_ctx->gl_state[active_idx] = real_obj; \
		} \
	}

	switch (target)
	{
		case GL_TEXTURE_2D:
			STATE_PROC(gl_tex_2d_state, _tex_flag1, _TEX_FLAG1_BIT);
			break;
		case GL_TEXTURE_3D:
			STATE_PROC_WITH_CHECK(gl_tex_3d_state, _tex_flag1, _TEX_FLAG1_BIT);
			break;
		case GL_TEXTURE_2D_ARRAY:
			STATE_PROC_WITH_CHECK(gl_tex_2d_array_state, _tex_flag1, _TEX_FLAG1_BIT);
			break;
		case GL_TEXTURE_CUBE_MAP:
			STATE_PROC(gl_tex_cube_state, _tex_flag1, _TEX_FLAG1_BIT);
			break;
		default:
			_set_gl_error(GL_INVALID_ENUM);
			break;
	}


#undef STATE_PROC

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_TEXTURE, texture, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	_orig_fastpath_glFramebufferTexture2D(target, attachment, textarget, real_obj, level);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glFramebufferTexture3DOES(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_TEXTURE, texture, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	_orig_fastpath_glFramebufferTexture3DOES(target, attachment, textarget, real_obj, level, zoffset);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glFramebufferTexture2DMultisampleEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_TEXTURE, texture, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	_orig_fastpath_glFramebufferTexture2DMultisampleEXT(target, attachment, textarget, real_obj, level, samples);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params)
{
	GLint real_obj, fa_type;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	switch (pname)
	{
		case GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME:
			params[0] = 0;
			_orig_fastpath_glGetFramebufferAttachmentParameteriv(target, attachment, pname, &real_obj);
			_orig_fastpath_glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fa_type);
			switch (fa_type)
			{
				case GL_TEXTURE:
					if (GET_GLUE_OBJ(GL_OBJECT_TYPE_TEXTURE, real_obj, (GLuint *)params) != 1)
					{
						params[0] = 0;
						goto finish;
					}
					break;
				case GL_RENDERBUFFER:
					if (GET_GLUE_OBJ(GL_OBJECT_TYPE_RENDERBUFFER, real_obj, (GLuint *)params) != 1)
					{
						params[0] = 0;
						goto finish;
					}
					break;
			}
			break;
		default:
			_orig_fastpath_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
			break;
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


GLboolean
fastpath_glIsTexture(GLuint texture)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_TEXTURE, texture, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _orig_fastpath_glIsTexture(real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


void
fastpath_glDeleteTextures(GLsizei n, const GLuint* textures)
{
	int i, j;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (textures == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);
	{
		int real_n = 0;

		for (i = 0; i < n; i++)
		{
			int real_objid = _COREGL_INT_INIT_VALUE;
			if (textures[i] == 0) continue;

			real_objid = fastpath_ostate_get_object(&current_ctx->ostate, GL_OBJECT_TYPE_TEXTURE, textures[i]);
			if (real_objid == 0) continue;

			AST(fastpath_ostate_remove_object(&current_ctx->ostate, GL_OBJECT_TYPE_TEXTURE, textures[i]) == 1);
			objid_array[real_n++] = real_objid;
		}

		IF_GL_SUCCESS(_orig_fastpath_glDeleteTextures(real_n, objid_array))
		{
			for (i = 0; i < real_n; i++)
			{
				General_Trace_List *current = NULL;
				current = current_ctx->ostate.shared->using_gctxs;

				while (current != NULL)
				{
					GLGlueContext *cur_gctx = (GLGlueContext *)current->value;

					for (j = 0; j < cur_gctx->gl_num_tex_units[0]; j++)
					{
						if (cur_gctx->gl_tex_2d_state[j] == objid_array[i])
							cur_gctx->gl_tex_2d_state[j] = 0;
						if (cur_gctx->gl_tex_3d_state[j] == objid_array[i])
							cur_gctx->gl_tex_3d_state[j] = 0;
						if (cur_gctx->gl_tex_2d_array_state[j] == objid_array[i])
							cur_gctx->gl_tex_2d_array_state[j] = 0;
						if (cur_gctx->gl_tex_cube_state[j] == objid_array[i])
							cur_gctx->gl_tex_cube_state[j] = 0;
					}

					current = current->next;
				}
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
	_COREGL_FASTPATH_FUNC_END();
}

////////////////////////////////////////////////////////////////////////

void
fastpath_glGenBuffers(GLsizei n, GLuint* buffers)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (buffers == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);

	IF_GL_SUCCESS(_orig_fastpath_glGenBuffers(n, objid_array))
	{
		for (i = 0; i < n; i++)
		{
			buffers[i] = fastpath_ostate_create_object(&current_ctx->ostate, GL_OBJECT_TYPE_BUFFER, objid_array[i]);
		}
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glBindBuffer(GLenum target, GLuint buffer)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_BUFFER, buffer, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}


#define STATE_PROC(gl_state, flagid, flagbit) \
	CURR_STATE_COMPARE(gl_state, real_obj) \
	{ \
		IF_GL_SUCCESS(_orig_fastpath_glBindBuffer(target, real_obj)) \
		{ \
			if (real_obj == 0) \
				current_ctx->flagid &= (~flagbit##_##gl_state); \
			else \
				current_ctx->flagid |= flagbit##_##gl_state; \
 \
			current_ctx->gl_state[0] = real_obj; \
		} \
	}


	switch (target)
	{
		case GL_ARRAY_BUFFER:
			STATE_PROC(gl_array_buffer_binding, _bind_flag, _BIND_FLAG_BIT);
			break;
		case GL_COPY_READ_BUFFER:
			STATE_PROC_WITH_CHECK(gl_copy_read_buffer_binding, _bind_flag, _BIND_FLAG_BIT);
			break;
		case GL_COPY_WRITE_BUFFER:
			STATE_PROC_WITH_CHECK(gl_copy_write_buffer_binding, _bind_flag, _BIND_FLAG_BIT);
			break;
		case GL_ELEMENT_ARRAY_BUFFER:
			STATE_PROC(gl_element_array_buffer_binding, _bind_flag, _BIND_FLAG_BIT);
			break;
		case GL_PIXEL_PACK_BUFFER:
			STATE_PROC_WITH_CHECK(gl_pixel_pack_buffer_binding, _bind_flag, _BIND_FLAG_BIT);
			break;
		case GL_PIXEL_UNPACK_BUFFER:
			STATE_PROC_WITH_CHECK(gl_pixel_unpack_buffer_binding, _bind_flag, _BIND_FLAG_BIT);
			break;
		case GL_TRANSFORM_FEEDBACK_BUFFER:
			STATE_PROC_WITH_CHECK(gl_transform_feedback_buffer_binding, _bind_flag, _BIND_FLAG_BIT);
			break;
		case GL_UNIFORM_BUFFER:
			STATE_PROC_WITH_CHECK(gl_uniform_buffer_binding, _bind_flag, _BIND_FLAG_BIT);
			break;
		default:
			_set_gl_error(GL_INVALID_ENUM);
			break;
	}


#undef STATE_PROC

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


GLboolean
fastpath_glIsBuffer(GLuint buffer)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_BUFFER, buffer, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _orig_fastpath_glIsBuffer(real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


void
fastpath_glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (buffers == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);
	{
		int real_n = 0;

		for (i = 0; i < n; i++)
		{
			int real_objid = _COREGL_INT_INIT_VALUE;
			if (buffers[i] == 0) continue;

			real_objid = fastpath_ostate_get_object(&current_ctx->ostate, GL_OBJECT_TYPE_BUFFER, buffers[i]);
			if (real_objid == 0) continue;

			AST(fastpath_ostate_remove_object(&current_ctx->ostate, GL_OBJECT_TYPE_BUFFER, buffers[i]) == 1);
			objid_array[real_n++] = real_objid;
		}

		IF_GL_SUCCESS(_orig_fastpath_glDeleteBuffers(real_n, objid_array))
		{
			for (i = 0; i < real_n; i++)
			{
				General_Trace_List *current = NULL;
				current = current_ctx->ostate.shared->using_gctxs;

				while (current != NULL)
				{
					GLGlueContext *cur_gctx = (GLGlueContext *)current->value;

					if (cur_gctx->gl_array_buffer_binding[0] == objid_array[i])
					{
						cur_gctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_array_buffer_binding);
						cur_gctx->gl_array_buffer_binding[0] = 0;
					}
					if (cur_gctx->gl_copy_read_buffer_binding[0] == objid_array[i])
					{
						cur_gctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_copy_read_buffer_binding);
						cur_gctx->gl_copy_read_buffer_binding[0] = 0;
					}
					if (cur_gctx->gl_copy_write_buffer_binding[0] == objid_array[i])
					{
						cur_gctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_copy_write_buffer_binding);
						cur_gctx->gl_copy_write_buffer_binding[0] = 0;
					}
					if (cur_gctx->gl_element_array_buffer_binding[0] == objid_array[i])
					{
						cur_gctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_element_array_buffer_binding);
						cur_gctx->gl_element_array_buffer_binding[0] = 0;
					}
					if (cur_gctx->gl_pixel_pack_buffer_binding[0] == objid_array[i])
					{
						cur_gctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_pixel_pack_buffer_binding);
						cur_gctx->gl_pixel_pack_buffer_binding[0] = 0;
					}
					if (cur_gctx->gl_pixel_unpack_buffer_binding[0] == objid_array[i])
					{
						cur_gctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_pixel_unpack_buffer_binding);
						cur_gctx->gl_pixel_unpack_buffer_binding[0] = 0;
					}
					if (cur_gctx->gl_transform_feedback_buffer_binding[0] == objid_array[i])
					{
						cur_gctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_transform_feedback_buffer_binding);
						cur_gctx->gl_transform_feedback_buffer_binding[0] = 0;
					}
					if (cur_gctx->gl_uniform_buffer_binding[0] == objid_array[i])
					{
						cur_gctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_uniform_buffer_binding);
						cur_gctx->gl_uniform_buffer_binding[0] = 0;
					}

					current = current->next;
				}
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
	_COREGL_FASTPATH_FUNC_END();
}

//////////////////////////////////////////////////////////////////////////////////

void
fastpath_glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (framebuffers == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);

	IF_GL_SUCCESS(_orig_fastpath_glGenFramebuffers(n, objid_array))
	{
		for (i = 0; i < n; i++)
		{
			framebuffers[i] = fastpath_ostate_create_object(&current_ctx->ostate, GL_OBJECT_TYPE_FRAMEBUFFER, objid_array[i]);
		}
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_FRAMEBUFFER, framebuffer, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	if (target == GL_FRAMEBUFFER)
	{
		if (current_ctx->gl_framebuffer_binding_read_used == 1)
		{
			CURR_STATE_COMPARE(gl_framebuffer_binding_read, real_obj)
			{
				IF_GL_SUCCESS(_orig_fastpath_glBindFramebuffer(target, real_obj))
				{
					if (real_obj == 0)
						current_ctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_framebuffer_binding_read);
					else
						current_ctx->_bind_flag |= _BIND_FLAG_BIT_gl_framebuffer_binding_read;
					current_ctx->gl_framebuffer_binding_read[0] = real_obj;
				}
			}
			CURR_STATE_COMPARE(gl_framebuffer_binding_draw, real_obj)
			{
				IF_GL_SUCCESS(_orig_fastpath_glBindFramebuffer(target, real_obj))
				{
					if (real_obj == 0)
						current_ctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_framebuffer_binding_draw);
					else
						current_ctx->_bind_flag |= _BIND_FLAG_BIT_gl_framebuffer_binding_draw;
					current_ctx->gl_framebuffer_binding_draw[0] = real_obj;
				}
			}
		}
		else
		{
			CURR_STATE_COMPARE(gl_framebuffer_binding, real_obj)
			{
				IF_GL_SUCCESS(_orig_fastpath_glBindFramebuffer(target, real_obj))
				{
					if (real_obj == 0)
						current_ctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_framebuffer_binding);
					else
						current_ctx->_bind_flag |= _BIND_FLAG_BIT_gl_framebuffer_binding;
					current_ctx->gl_framebuffer_binding[0] = real_obj;
				}
			}
		}
	}
	else if (target == GL_READ_FRAMEBUFFER && current_ctx->gl_framebuffer_binding_read_used)
	{
		CURR_STATE_COMPARE(gl_framebuffer_binding_read, real_obj)
		{
			IF_GL_SUCCESS(_orig_fastpath_glBindFramebuffer(target, real_obj))
			{
				if (real_obj == 0)
					current_ctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_framebuffer_binding_read);
				else
					current_ctx->_bind_flag |= _BIND_FLAG_BIT_gl_framebuffer_binding_read;
				current_ctx->gl_framebuffer_binding_read[0] = real_obj;
			}
		}
	}
	else if (target == GL_DRAW_FRAMEBUFFER && current_ctx->gl_framebuffer_binding_draw_used)
	{
		CURR_STATE_COMPARE(gl_framebuffer_binding_draw, real_obj)
		{
			IF_GL_SUCCESS(_orig_fastpath_glBindFramebuffer(target, real_obj))
			{
				if (real_obj == 0)
					current_ctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_framebuffer_binding_draw);
				else
					current_ctx->_bind_flag |= _BIND_FLAG_BIT_gl_framebuffer_binding_draw;
				current_ctx->gl_framebuffer_binding_draw[0] = real_obj;
			}
		}
	}
	else
	{
		_set_gl_error(GL_INVALID_ENUM);
		goto finish;
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


GLboolean
fastpath_glIsFramebuffer(GLuint framebuffer)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_FRAMEBUFFER, framebuffer, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _orig_fastpath_glIsFramebuffer(real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


void
fastpath_glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (framebuffers == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);
	{
		int real_n = 0;

		for (i = 0; i < n; i++)
		{
			int real_objid = _COREGL_INT_INIT_VALUE;
			if (framebuffers[i] == 0) continue;

			real_objid = fastpath_ostate_get_object(&current_ctx->ostate, GL_OBJECT_TYPE_FRAMEBUFFER, framebuffers[i]);
			if (real_objid == 0) continue;

			AST(fastpath_ostate_remove_object(&current_ctx->ostate, GL_OBJECT_TYPE_FRAMEBUFFER, framebuffers[i]) == 1);
			objid_array[real_n++] = real_objid;
		}

		IF_GL_SUCCESS(_orig_fastpath_glDeleteFramebuffers(real_n, objid_array))
		{
			for (i = 0; i < real_n; i++)
			{
				General_Trace_List *current = NULL;
				current = current_ctx->ostate.shared->using_gctxs;

				while (current != NULL)
				{
					GLGlueContext *cur_gctx = (GLGlueContext *)current->value;

					if (cur_gctx->gl_framebuffer_binding[0] == objid_array[i])
					{
						cur_gctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_framebuffer_binding);
						cur_gctx->gl_framebuffer_binding[0] = 0;
					}
					if (cur_gctx->gl_framebuffer_binding_read[0] == objid_array[i])
					{
						cur_gctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_framebuffer_binding_read);
						cur_gctx->gl_framebuffer_binding_read[0] = 0;
					}
					if (cur_gctx->gl_framebuffer_binding_draw[0] == objid_array[i])
					{
						cur_gctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_framebuffer_binding_draw);
						cur_gctx->gl_framebuffer_binding_draw[0] = 0;
					}

					current = current->next;
				}
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
	_COREGL_FASTPATH_FUNC_END();
}

//////////////////////////////////////////////////////////////////////////////////

void
fastpath_glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (renderbuffers == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);

	IF_GL_SUCCESS(_orig_fastpath_glGenRenderbuffers(n, objid_array))
	{
		for (i = 0; i < n; i++)
		{
			renderbuffers[i] = fastpath_ostate_create_object(&current_ctx->ostate, GL_OBJECT_TYPE_RENDERBUFFER, objid_array[i]);
		}
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_RENDERBUFFER, renderbuffer, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	if (target == GL_RENDERBUFFER)
	{
		CURR_STATE_COMPARE(gl_renderbuffer_binding, real_obj)
		{
			IF_GL_SUCCESS(_orig_fastpath_glBindRenderbuffer(target, real_obj))
			{
				if (real_obj == 0)
					current_ctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_renderbuffer_binding);
				else
					current_ctx->_bind_flag |= _BIND_FLAG_BIT_gl_renderbuffer_binding;
				current_ctx->gl_renderbuffer_binding[0] = real_obj;
			}
		}
	}
	else
	{
		_set_gl_error(GL_INVALID_ENUM);
		goto finish;
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_RENDERBUFFER, renderbuffer, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	_orig_fastpath_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


GLboolean
fastpath_glIsRenderbuffer(GLuint renderbuffer)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_RENDERBUFFER, renderbuffer, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _orig_fastpath_glIsRenderbuffer(real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


void
fastpath_glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (renderbuffers == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);
	{
		int real_n = 0;

		for (i = 0; i < n; i++)
		{
			int real_objid = _COREGL_INT_INIT_VALUE;
			if (renderbuffers[i] == 0) continue;

			real_objid = fastpath_ostate_get_object(&current_ctx->ostate, GL_OBJECT_TYPE_RENDERBUFFER, renderbuffers[i]);
			if (real_objid == 0) continue;

			AST(fastpath_ostate_remove_object(&current_ctx->ostate, GL_OBJECT_TYPE_RENDERBUFFER, renderbuffers[i]) == 1);
			objid_array[real_n++] = real_objid;
		}

		IF_GL_SUCCESS(_orig_fastpath_glDeleteRenderbuffers(real_n, objid_array))
		{
			for (i = 0; i < real_n; i++)
			{
				General_Trace_List *current = NULL;
				current = current_ctx->ostate.shared->using_gctxs;

				while (current != NULL)
				{
					GLGlueContext *cur_gctx = (GLGlueContext *)current->value;

					if (cur_gctx->gl_renderbuffer_binding[0] == objid_array[i])
					{
						cur_gctx->_bind_flag &= (~_BIND_FLAG_BIT_gl_renderbuffer_binding);
						cur_gctx->gl_renderbuffer_binding[0] = 0;
					}

					current = current->next;
				}
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
	_COREGL_FASTPATH_FUNC_END();
}


//////////////////////////////////////////////////////////////////////////////////

GLuint
fastpath_glCreateProgram(void)
{
	GLuint ret = 0;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	AST(current_ctx->ostate.shared != NULL);

	ret = _create_program_object(&current_ctx->ostate, 1, GL_NONE);

	_attach_program_object(&current_ctx->ostate, ret);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


GLuint
fastpath_glCreateShader(GLenum type)
{
	GLuint ret = 0;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	AST(current_ctx->ostate.shared != NULL);

	ret = _create_program_object(&current_ctx->ostate, 0, type);

	_attach_program_object(&current_ctx->ostate, ret);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


void
fastpath_glShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	_orig_fastpath_glShaderSource(real_obj, count, string, length);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (shaders == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);

	for (i = 0; i < n; i++)
	{
		if (shaders[i] == 0) continue;
		objid_array[i] = fastpath_ostate_get_object(&current_ctx->ostate, GL_OBJECT_TYPE_PROGRAM, shaders[i]);
	}

	_orig_fastpath_glShaderBinary(n, objid_array, binaryformat, binary, length);

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}

	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glCompileShader(GLuint shader)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glCompileShader(real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glBindAttribLocation(GLuint program, GLuint index, const char* name)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glBindAttribLocation(real_obj, index, name);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glAttachShader(GLuint program, GLuint shader)
{
	GLuint real_obj_program;
	GLuint real_obj_shader;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj_program) != 1 ||
	    GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj_shader) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	IF_GL_SUCCESS(_orig_fastpath_glAttachShader(real_obj_program, real_obj_shader))
	{
		_update_program_attach_info(&current_ctx->ostate, program);
		_attach_program_object(&current_ctx->ostate, shader);
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glDetachShader(GLuint program, GLuint shader)
{
	GLuint real_obj_program;
	GLuint real_obj_shader;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj_program) != 1 ||
	    GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj_shader) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	IF_GL_SUCCESS(_orig_fastpath_glDetachShader(real_obj_program, real_obj_shader))
	{
		_update_program_attach_info(&current_ctx->ostate, program);
		_detach_program_object(&current_ctx->ostate, real_obj_shader, 0, 0);
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


GLboolean
fastpath_glIsShader(GLuint shader)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _orig_fastpath_glIsShader(real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


GLboolean
fastpath_glIsProgram(GLuint program)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _orig_fastpath_glIsProgram(real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


void
fastpath_glLinkProgram(GLuint program)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glLinkProgram(real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glValidateProgram(GLuint program)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glValidateProgram(real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glUseProgram(GLuint program)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	CURR_STATE_COMPARE(gl_current_program, real_obj)
	{
		IF_GL_SUCCESS(_orig_fastpath_glUseProgram(real_obj))
		{
			_attach_program_object(&current_ctx->ostate, program);
			_detach_program_object(&current_ctx->ostate, current_ctx->gl_current_program[0], 1, 0);

			current_ctx->_clear_flag1 |= _CLEAR_FLAG1_BIT_gl_current_program;
			current_ctx->gl_current_program[0] = real_obj;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glGetActiveAttrib(real_obj, index, bufsize, length, size, type, name);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glGetActiveUniform(real_obj, index, bufsize, length, size, type, name);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
{
	int i;
	GLsizei real_count = _COREGL_INT_INIT_VALUE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	IF_GL_SUCCESS(_orig_fastpath_glGetAttachedShaders(real_obj, maxcount, &real_count, shaders))
	{
		for (i = 0; i < real_count; i++)
		{
			if (shaders[i] != 0)
				shaders[i] = fastpath_ostate_find_object(&current_ctx->ostate, GL_OBJECT_TYPE_PROGRAM, shaders[i]);
		}
		if (count != NULL) *count = real_count;
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


int
fastpath_glGetAttribLocation(GLuint program, const char* name)
{
	int ret = _COREGL_INT_INIT_VALUE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	ret = _orig_fastpath_glGetAttribLocation(real_obj, name);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


void
fastpath_glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	switch (pname)
	{
		case GL_DELETE_STATUS:
			*params = GL_FALSE;
			if (_is_deleted_program_object(&current_ctx->ostate, shader) == 1)
				*params = GL_TRUE;
			break;
		default:
			_orig_fastpath_glGetShaderiv(real_obj, pname, params);
			break;
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glGetShaderInfoLog(real_obj, bufsize, length, infolog);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	switch (pname)
	{
		case GL_DELETE_STATUS:
			*params = GL_FALSE;
			if (_is_deleted_program_object(&current_ctx->ostate, program) == 1)
				*params = GL_TRUE;
			break;
		default:
			_orig_fastpath_glGetProgramiv(real_obj, pname, params);
			break;
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glGetProgramInfoLog(real_obj, bufsize, length, infolog);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, char* source)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glGetShaderSource(real_obj, bufsize, length, source);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetUniformfv(GLuint program, GLint location, GLfloat* params)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glGetUniformfv(real_obj, location, params);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetUniformiv(GLuint program, GLint location, GLint* params)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glGetUniformiv(real_obj, location, params);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glUseProgramStagesEXT(GLuint pipeline, GLbitfield stages, GLuint program)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glUseProgramStagesEXT(pipeline, stages, real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glActiveShaderProgramEXT(GLuint pipeline, GLuint program)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glActiveShaderProgramEXT(pipeline, real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramParameteriEXT(GLuint program, GLenum pname, GLint value)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramParameteriEXT(real_obj, pname, value);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform1iEXT(GLuint program, GLint location, GLint x)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform1iEXT(real_obj, location, x);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform2iEXT(GLuint program, GLint location, GLint x, GLint y)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform2iEXT(real_obj, location, x, y);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform3iEXT(GLuint program, GLint location, GLint x, GLint y, GLint z)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform3iEXT(real_obj, location, x, y, z);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform4iEXT(GLuint program, GLint location, GLint x, GLint y, GLint z, GLint w)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform4iEXT(real_obj, location, x, y, z, w);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform1fEXT(GLuint program, GLint location, GLfloat x)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform1fEXT(real_obj, location, x);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform2fEXT(GLuint program, GLint location, GLfloat x, GLfloat y)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform2fEXT(real_obj, location, x, y);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform3fEXT(GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform3fEXT(real_obj, location, x, y, z);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform4fEXT(GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform4fEXT(real_obj, location, x, y, z, w);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform1ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform1ivEXT(real_obj, location, count, value);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform2ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform2ivEXT(real_obj, location, count, value);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform3ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform3ivEXT(real_obj, location, count, value);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform4ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform4ivEXT(real_obj, location, count, value);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform1fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform1fvEXT(real_obj, location, count, value);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform2fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform2fvEXT(real_obj, location, count, value);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform3fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform3fvEXT(real_obj, location, count, value);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniform4fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniform4fvEXT(real_obj, location, count, value);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniformMatrix2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniformMatrix2fvEXT(real_obj, location, count, transpose, value);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniformMatrix3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniformMatrix3fvEXT(real_obj, location, count, transpose, value);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramUniformMatrix4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramUniformMatrix4fvEXT(real_obj, location, count, transpose, value);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


int
fastpath_glGetUniformLocation(GLuint program, const char* name)
{
	int ret = _COREGL_INT_INIT_VALUE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		ret = -1;
		goto finish;
	}

	ret = _orig_fastpath_glGetUniformLocation(real_obj, name);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}

void
fastpath_glDeleteShader(GLuint shader)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, shader, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_detach_program_object(&current_ctx->ostate, real_obj, 0, 1);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

void
fastpath_glDeleteProgram(GLuint program)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_detach_program_object(&current_ctx->ostate, real_obj, 1, 1);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}



//////////////////////////////////////////////////////////////////////////////////

void
fastpath_glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((current_ctx->gl_blend_color[0] != red) ||
	    (current_ctx->gl_blend_color[1] != green) ||
	    (current_ctx->gl_blend_color[2] != blue) ||
	    (current_ctx->gl_blend_color[3] != alpha))
	{
		IF_GL_SUCCESS(_orig_fastpath_glBlendColor(red, green, blue, alpha))
		{
			current_ctx->_blend_flag |= _BLEND_FLAG_BIT_gl_blend_color;
			current_ctx->gl_blend_color[0] = red;
			current_ctx->gl_blend_color[1] = green;
			current_ctx->gl_blend_color[2] = blue;
			current_ctx->gl_blend_color[3] = alpha;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glBlendEquation(GLenum mode)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glBlendEquation(mode))
	{
		current_ctx->_blend_flag |=
			_BLEND_FLAG_BIT_gl_blend_equation_rgb |
			_BLEND_FLAG_BIT_gl_blend_equation_alpha;

		_orig_fastpath_glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint*) & (current_ctx->gl_blend_equation_rgb));
		_orig_fastpath_glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint*) & (current_ctx->gl_blend_equation_alpha));
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((current_ctx->gl_blend_equation_rgb[0] != modeRGB) ||
	    (current_ctx->gl_blend_equation_alpha[0] != modeAlpha))
	{
		IF_GL_SUCCESS(_orig_fastpath_glBlendEquationSeparate(modeRGB, modeAlpha))
		{
			current_ctx->_blend_flag |=
				_BLEND_FLAG_BIT_gl_blend_equation_rgb |
				_BLEND_FLAG_BIT_gl_blend_equation_alpha;

			current_ctx->gl_blend_equation_rgb[0]    = modeRGB;
			current_ctx->gl_blend_equation_alpha[0]  = modeAlpha;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glBlendFunc(sfactor, dfactor))
	{
		current_ctx->_blend_flag |=
			_BLEND_FLAG_BIT_gl_blend_src_rgb |
			_BLEND_FLAG_BIT_gl_blend_src_alpha |
			_BLEND_FLAG_BIT_gl_blend_dst_rgb |
			_BLEND_FLAG_BIT_gl_blend_dst_alpha;

		_orig_fastpath_glGetIntegerv(GL_BLEND_SRC_RGB, (GLint*) & (current_ctx->gl_blend_src_rgb));
		_orig_fastpath_glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint*) & (current_ctx->gl_blend_src_alpha));
		_orig_fastpath_glGetIntegerv(GL_BLEND_DST_RGB, (GLint*) & (current_ctx->gl_blend_dst_rgb));
		_orig_fastpath_glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint*) & (current_ctx->gl_blend_dst_alpha));
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((current_ctx->gl_blend_src_rgb[0] != srcRGB) ||
	    (current_ctx->gl_blend_dst_rgb[0] != dstRGB) ||
	    (current_ctx->gl_blend_src_alpha[0] != srcAlpha) ||
	    (current_ctx->gl_blend_dst_alpha[0] != dstAlpha))
	{
		IF_GL_SUCCESS(_orig_fastpath_glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha))
		{
			current_ctx->_blend_flag |=
			_BLEND_FLAG_BIT_gl_blend_src_rgb |
			_BLEND_FLAG_BIT_gl_blend_src_alpha |
			_BLEND_FLAG_BIT_gl_blend_dst_rgb |
			_BLEND_FLAG_BIT_gl_blend_dst_alpha;

			current_ctx->gl_blend_src_rgb[0]   = srcRGB;
			current_ctx->gl_blend_dst_rgb[0]   = dstRGB;
			current_ctx->gl_blend_src_alpha[0] = srcAlpha;
			current_ctx->gl_blend_dst_alpha[0] = dstAlpha;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((current_ctx->gl_color_clear_value[0] != red) ||
	    (current_ctx->gl_color_clear_value[1] != green) ||
	    (current_ctx->gl_color_clear_value[2] != blue) ||
	    (current_ctx->gl_color_clear_value[3] != alpha))
	{
		IF_GL_SUCCESS(_orig_fastpath_glClearColor(red, green, blue, alpha))
		{
			current_ctx->_clear_flag1 |= _CLEAR_FLAG1_BIT_gl_color_clear_value;
			current_ctx->gl_color_clear_value[0] = red;
			current_ctx->gl_color_clear_value[1] = green;
			current_ctx->gl_color_clear_value[2] = blue;
			current_ctx->gl_color_clear_value[3] = alpha;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glClearDepthf(GLclampf depth)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	CURR_STATE_COMPARE(gl_depth_clear_value, depth)
	{
		IF_GL_SUCCESS(_orig_fastpath_glClearDepthf(depth))
		{
			current_ctx->_clear_flag2 |= _CLEAR_FLAG2_BIT_gl_depth_clear_value;
			current_ctx->gl_depth_clear_value[0] = depth;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glClearStencil(GLint s)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	CURR_STATE_COMPARE(gl_stencil_clear_value, s)
	{
		IF_GL_SUCCESS(_orig_fastpath_glClearStencil(s))
		{
			current_ctx->_stencil_flag2 |= _STENCIL_FLAG2_BIT_gl_stencil_clear_value;
			current_ctx->gl_stencil_clear_value[0] = s;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((current_ctx->gl_color_writemask[0] != red) ||
	    (current_ctx->gl_color_writemask[1] != green) ||
	    (current_ctx->gl_color_writemask[2] != blue) ||
	    (current_ctx->gl_color_writemask[3] != alpha))
	{
		IF_GL_SUCCESS(_orig_fastpath_glColorMask(red, green, blue, alpha))
		{
			current_ctx->_clear_flag2 |= _CLEAR_FLAG2_BIT_gl_color_writemask;
			current_ctx->gl_color_writemask[0] = red;
			current_ctx->gl_color_writemask[1] = green;
			current_ctx->gl_color_writemask[2] = blue;
			current_ctx->gl_color_writemask[3] = alpha;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glCullFace(GLenum mode)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	CURR_STATE_COMPARE(gl_cull_face_mode, mode)
	{
		IF_GL_SUCCESS(_orig_fastpath_glCullFace(mode))
		{
			current_ctx->_clear_flag2 |= _CLEAR_FLAG2_BIT_gl_cull_face_mode;
			current_ctx->gl_cull_face_mode[0] = mode;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glDepthFunc(GLenum func)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	CURR_STATE_COMPARE(gl_depth_func, func)
	{
		IF_GL_SUCCESS(_orig_fastpath_glDepthFunc(func))
		{
			current_ctx->_clear_flag2 |= _CLEAR_FLAG2_BIT_gl_depth_func;
			current_ctx->gl_depth_func[0] = func;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glDepthMask(GLboolean flag)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	CURR_STATE_COMPARE(gl_depth_writemask, flag)
	{
		IF_GL_SUCCESS(_orig_fastpath_glDepthMask(flag))
		{
			current_ctx->_clear_flag2 |= _CLEAR_FLAG2_BIT_gl_depth_writemask;
			current_ctx->gl_depth_writemask[0] = flag;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glDepthRangef(GLclampf zNear, GLclampf zFar)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((current_ctx->gl_depth_range[0] != zNear) ||
	    (current_ctx->gl_depth_range[1] != zFar))
	{
		IF_GL_SUCCESS(_orig_fastpath_glDepthRangef(zNear, zFar))
		{
			current_ctx->_clear_flag2 |= _CLEAR_FLAG2_BIT_gl_depth_range;
			current_ctx->gl_depth_range[0] = zNear;
			current_ctx->gl_depth_range[1] = zFar;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glDisable(GLenum cap)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

#define STATE_PROC(gl_state, flagid, flagbit) \
	CURR_STATE_COMPARE(gl_state, GL_FALSE) \
	{ \
		_orig_fastpath_glDisable(cap); \
		current_ctx->flagid &= (~flagbit##_##gl_state); \
		current_ctx->gl_state[0] = GL_FALSE; \
	}


	switch (cap)
	{
		case GL_BLEND:
			STATE_PROC(gl_blend, _enable_flag1, _ENABLE_FLAG1_BIT);
			break;
		case GL_CULL_FACE:
			STATE_PROC(gl_cull_face, _enable_flag1, _ENABLE_FLAG1_BIT);
			break;
		case GL_DEPTH_TEST:
			STATE_PROC(gl_depth_test, _enable_flag1, _ENABLE_FLAG1_BIT);
			break;
		case GL_DITHER:
			STATE_PROC(gl_dither, _enable_flag1, _ENABLE_FLAG1_BIT);
			break;
		case GL_POLYGON_OFFSET_FILL:
			STATE_PROC(gl_polygon_offset_fill, _enable_flag2, _ENABLE_FLAG2_BIT);
			break;
		case GL_PRIMITIVE_RESTART_FIXED_INDEX:
			STATE_PROC_WITH_CHECK(gl_primitive_restart_fixed_index, _enable_flag3, _ENABLE_FLAG3_BIT);
			break;
		case GL_RASTERIZER_DISCARD:
			STATE_PROC_WITH_CHECK(gl_rasterizer_discard, _enable_flag3, _ENABLE_FLAG3_BIT);
			break;
		case GL_SAMPLE_ALPHA_TO_COVERAGE:
			STATE_PROC(gl_sample_alpha_to_coverage, _enable_flag2, _ENABLE_FLAG2_BIT);
			break;
		case GL_SAMPLE_COVERAGE:
			STATE_PROC(gl_sample_coverage, _enable_flag2, _ENABLE_FLAG2_BIT);
			break;
		case GL_SCISSOR_TEST:
			STATE_PROC(gl_scissor_test, _enable_flag2, _ENABLE_FLAG2_BIT);
			break;
		case GL_STENCIL_TEST:
			STATE_PROC(gl_stencil_test, _enable_flag2, _ENABLE_FLAG2_BIT);
			break;
		default:
			_set_gl_error(GL_INVALID_ENUM);
			break;
	}
	goto finish;


#undef STATE_PROC

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glDisableVertexAttribArray(GLuint index)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glDisableVertexAttribArray(index))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_array;
			current_ctx->gl_vertex_array_enabled[index] = GL_FALSE;
		}
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

void
fastpath_glEnable(GLenum cap)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

#define STATE_PROC(gl_state, flagid, flagbit) \
	CURR_STATE_COMPARE(gl_state, GL_TRUE) \
	{ \
		_orig_fastpath_glEnable(cap); \
		current_ctx->flagid |= flagbit##_##gl_state; \
		current_ctx->gl_state[0] = GL_TRUE; \
	}


	switch (cap)
	{
		case GL_BLEND:
			STATE_PROC(gl_blend, _enable_flag1, _ENABLE_FLAG1_BIT);
			break;
		case GL_CULL_FACE:
			STATE_PROC(gl_cull_face, _enable_flag1, _ENABLE_FLAG1_BIT);
			break;
		case GL_DEPTH_TEST:
			STATE_PROC(gl_depth_test, _enable_flag1, _ENABLE_FLAG1_BIT);
			break;
		case GL_DITHER:
			STATE_PROC(gl_dither, _enable_flag1, _ENABLE_FLAG1_BIT);
			break;
		case GL_POLYGON_OFFSET_FILL:
			STATE_PROC(gl_polygon_offset_fill, _enable_flag2, _ENABLE_FLAG2_BIT);
			break;
		case GL_PRIMITIVE_RESTART_FIXED_INDEX:
			STATE_PROC_WITH_CHECK(gl_primitive_restart_fixed_index, _enable_flag3, _ENABLE_FLAG3_BIT);
			break;
		case GL_RASTERIZER_DISCARD:
			STATE_PROC_WITH_CHECK(gl_rasterizer_discard, _enable_flag3, _ENABLE_FLAG3_BIT);
			break;
		case GL_SAMPLE_ALPHA_TO_COVERAGE:
			STATE_PROC(gl_sample_alpha_to_coverage, _enable_flag2, _ENABLE_FLAG2_BIT);
			break;
		case GL_SAMPLE_COVERAGE:
			STATE_PROC(gl_sample_coverage, _enable_flag2, _ENABLE_FLAG2_BIT);
			break;
		case GL_SCISSOR_TEST:
			STATE_PROC(gl_scissor_test, _enable_flag2, _ENABLE_FLAG2_BIT);
			break;
		case GL_STENCIL_TEST:
			STATE_PROC(gl_stencil_test, _enable_flag2, _ENABLE_FLAG2_BIT);
			break;
		default:
			_set_gl_error(GL_INVALID_ENUM);
			break;
	}
	goto finish;


#undef STATE_PROC

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glEnableVertexAttribArray(GLuint index)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glEnableVertexAttribArray(index))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_array;
			current_ctx->gl_vertex_array_enabled[index] = GL_TRUE;
		}
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glFrontFace(GLenum mode)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	CURR_STATE_COMPARE(gl_front_face, mode)
	{
		IF_GL_SUCCESS(_orig_fastpath_glFrontFace(mode))
		{
			current_ctx->_misc_flag1 |= _MISC_FLAG1_BIT_gl_front_face;
			current_ctx->gl_front_face[0] = mode;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

void
fastpath_glHint(GLenum target, GLenum mode)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();


#define STATE_PROC(gl_state, flagid, flagbit) \
	CURR_STATE_COMPARE(gl_state, mode) \
	{ \
		IF_GL_SUCCESS(_orig_fastpath_glHint(target, mode)) \
		{ \
			current_ctx->flagid |= flagbit##_##gl_state; \
			current_ctx->gl_state[0] = mode; \
		} \
	}


	switch (target)
	{
		case GL_FRAGMENT_SHADER_DERIVATIVE_HINT:
			STATE_PROC_WITH_CHECK(gl_fragment_shader_derivative_hint, _misc_flag1, _MISC_FLAG1_BIT);
			break;
		case GL_GENERATE_MIPMAP_HINT:
			STATE_PROC(gl_generate_mipmap_hint, _tex_flag1, _TEX_FLAG1_BIT);
			break;
		default:
			_set_gl_error(GL_INVALID_ENUM);
			break;
	}
	goto finish;


#undef STATE_PROC

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glLineWidth(GLfloat width)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	CURR_STATE_COMPARE(gl_line_width, width)
	{
		IF_GL_SUCCESS(_orig_fastpath_glLineWidth(width))
		{
			current_ctx->_misc_flag1 |= _MISC_FLAG1_BIT_gl_line_width;
			current_ctx->gl_line_width[0] = width;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glPixelStorei(GLenum pname, GLint param)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

#define STATE_PROC(gl_state, flagid, flagbit) \
	CURR_STATE_COMPARE(gl_state, param) \
	{ \
		IF_GL_SUCCESS(_orig_fastpath_glPixelStorei(pname, param)) \
		{ \
			current_ctx->flagid |= flagbit##_##gl_state; \
			current_ctx->gl_state[0] = param; \
		} \
	}


	switch (pname)
	{
		case GL_PACK_ROW_LENGTH:
			STATE_PROC_WITH_CHECK(gl_pack_row_length, _pixel_flag1, _PIXEL_FLAG1_BIT);
			break;
		case GL_PACK_SKIP_PIXELS:
			STATE_PROC_WITH_CHECK(gl_pack_skip_pixels, _pixel_flag1, _PIXEL_FLAG1_BIT);
			break;
		case GL_PACK_SKIP_ROWS:
			STATE_PROC_WITH_CHECK(gl_pack_skip_rows, _pixel_flag1, _PIXEL_FLAG1_BIT);
			break;
		case GL_PACK_ALIGNMENT:
			STATE_PROC(gl_pack_alignment, _pixel_flag1, _PIXEL_FLAG1_BIT);
			break;
		case GL_UNPACK_ROW_LENGTH:
			STATE_PROC_WITH_CHECK(gl_unpack_row_length, _pixel_flag2, _PIXEL_FLAG2_BIT);
			break;
		case GL_UNPACK_IMAGE_HEIGHT:
			STATE_PROC_WITH_CHECK(gl_unpack_image_height, _pixel_flag2, _PIXEL_FLAG2_BIT);
			break;
		case GL_UNPACK_SKIP_PIXELS:
			STATE_PROC_WITH_CHECK(gl_unpack_skip_pixels, _pixel_flag2, _PIXEL_FLAG2_BIT);
			break;
		case GL_UNPACK_SKIP_IMAGES:
			STATE_PROC_WITH_CHECK(gl_unpack_skip_images, _pixel_flag2, _PIXEL_FLAG2_BIT);
			break;
		case GL_UNPACK_ALIGNMENT:
			STATE_PROC(gl_unpack_alignment, _pixel_flag2, _PIXEL_FLAG2_BIT);
			break;
		default:
			_set_gl_error(GL_INVALID_ENUM);
			break;
	}


#undef STATE_PROC

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glPolygonOffset(GLfloat factor, GLfloat units)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((current_ctx->gl_polygon_offset_factor[0] != factor) ||
	    (current_ctx->gl_polygon_offset_units[0] != units))
	{
		IF_GL_SUCCESS(_orig_fastpath_glPolygonOffset(factor, units))
		{
			current_ctx->_misc_flag1 |=
				_MISC_FLAG1_BIT_gl_polygon_offset_factor |
				_MISC_FLAG1_BIT_gl_polygon_offset_units;

			current_ctx->gl_polygon_offset_factor[0] = factor;
			current_ctx->gl_polygon_offset_units[0]  = units;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glSampleCoverage(GLclampf value, GLboolean invert)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((current_ctx->gl_sample_coverage_value[0] != value) ||
	    (current_ctx->gl_sample_coverage_invert[0] != invert))
	{
		IF_GL_SUCCESS(_orig_fastpath_glSampleCoverage(value, invert))
		{
			current_ctx->_misc_flag1 |=
				_MISC_FLAG1_BIT_gl_sample_coverage_value |
				_MISC_FLAG1_BIT_gl_sample_coverage_invert;

			current_ctx->gl_sample_coverage_value[0]  = value;
			current_ctx->gl_sample_coverage_invert[0] = invert;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((current_ctx->gl_scissor_box[0] != x) ||
	    (current_ctx->gl_scissor_box[1] != y) ||
	    (current_ctx->gl_scissor_box[2] != width) ||
	    (current_ctx->gl_scissor_box[3] != height))
	{
		IF_GL_SUCCESS(_orig_fastpath_glScissor(x, y, width, height))
		{
			current_ctx->_misc_flag2 |= _MISC_FLAG2_BIT_gl_scissor_box;
			current_ctx->gl_scissor_box[0] = x;
			current_ctx->gl_scissor_box[1] = y;
			current_ctx->gl_scissor_box[2] = width;
			current_ctx->gl_scissor_box[3] = height;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((current_ctx->gl_stencil_func[0] != func) ||
	    (current_ctx->gl_stencil_ref[0] != ref) ||
	    (current_ctx->gl_stencil_value_mask[0] != mask) ||
	    (current_ctx->gl_stencil_back_func[0] != func) ||
	    (current_ctx->gl_stencil_back_ref[0] != ref) ||
	    (current_ctx->gl_stencil_back_value_mask[0] != mask))
	{
		IF_GL_SUCCESS(_orig_fastpath_glStencilFunc(func, ref, mask))
		{
			current_ctx->_stencil_flag1 |=
				_STENCIL_FLAG1_BIT_gl_stencil_func |
				_STENCIL_FLAG1_BIT_gl_stencil_ref |
				_STENCIL_FLAG1_BIT_gl_stencil_value_mask;

			current_ctx->gl_stencil_func[0]             = func;
			current_ctx->gl_stencil_ref[0]              = ref;
			current_ctx->gl_stencil_value_mask[0]       = mask;

			current_ctx->_stencil_flag2 |=
				_STENCIL_FLAG2_BIT_gl_stencil_back_func |
				_STENCIL_FLAG2_BIT_gl_stencil_back_ref |
				_STENCIL_FLAG2_BIT_gl_stencil_back_value_mask;

			current_ctx->gl_stencil_back_func[0]        = func;
			current_ctx->gl_stencil_back_ref[0]         = ref;
			current_ctx->gl_stencil_back_value_mask[0]  = mask;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((face == GL_FRONT) || (face == GL_FRONT_AND_BACK))
	{
		if ((current_ctx->gl_stencil_func[0] != func) ||
		    (current_ctx->gl_stencil_ref[0] != ref) ||
		    (current_ctx->gl_stencil_value_mask[0] != mask))
		{
			IF_GL_SUCCESS(_orig_fastpath_glStencilFuncSeparate(face, func, ref, mask))
			{
				current_ctx->_stencil_flag1 |=
					_STENCIL_FLAG1_BIT_gl_stencil_func |
					_STENCIL_FLAG1_BIT_gl_stencil_ref |
					_STENCIL_FLAG1_BIT_gl_stencil_value_mask;

				current_ctx->gl_stencil_func[0]             = func;
				current_ctx->gl_stencil_ref[0]              = ref;
				current_ctx->gl_stencil_value_mask[0]       = mask;
			}
		}
	}
	else if ((face == GL_BACK) || (face == GL_FRONT_AND_BACK))
	{
		if ((current_ctx->gl_stencil_back_func[0] != func) ||
		    (current_ctx->gl_stencil_back_ref[0] != ref) ||
		    (current_ctx->gl_stencil_back_value_mask[0] != mask))
		{
			IF_GL_SUCCESS(_orig_fastpath_glStencilFuncSeparate(face, func, ref, mask))
			{
				current_ctx->_stencil_flag2 |=
					_STENCIL_FLAG2_BIT_gl_stencil_back_func |
					_STENCIL_FLAG2_BIT_gl_stencil_back_ref |
					_STENCIL_FLAG2_BIT_gl_stencil_back_value_mask;

				current_ctx->gl_stencil_back_func[0]        = func;
				current_ctx->gl_stencil_back_ref[0]         = ref;
				current_ctx->gl_stencil_back_value_mask[0]  = mask;
			}
		}
	}
	else
	{
		_set_gl_error(GL_INVALID_ENUM);
		goto finish;
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glStencilMask(GLuint mask)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((current_ctx->gl_stencil_writemask[0] != mask) ||
	    (current_ctx->gl_stencil_back_writemask[0] != mask))
	{
		IF_GL_SUCCESS(_orig_fastpath_glStencilMask(mask))
		{
			current_ctx->_stencil_flag1 |= _STENCIL_FLAG1_BIT_gl_stencil_writemask;
			current_ctx->_stencil_flag2 |= _STENCIL_FLAG2_BIT_gl_stencil_back_writemask;

			current_ctx->gl_stencil_writemask[0]        = mask;
			current_ctx->gl_stencil_back_writemask[0]   = mask;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glStencilMaskSeparate(GLenum face, GLuint mask)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((face == GL_FRONT) || (face == GL_FRONT_AND_BACK))
	{
		if (current_ctx->gl_stencil_writemask[0] != mask)
		{
			IF_GL_SUCCESS(_orig_fastpath_glStencilMaskSeparate(face, mask))
			{
				current_ctx->_stencil_flag1 |= _STENCIL_FLAG1_BIT_gl_stencil_writemask;
				current_ctx->gl_stencil_writemask[0] = mask;
			}
		}
	}
	else if ((face == GL_BACK) || (face == GL_FRONT_AND_BACK))
	{
		if (current_ctx->gl_stencil_back_writemask[0] != mask)
		{
			IF_GL_SUCCESS(_orig_fastpath_glStencilMaskSeparate(face, mask))
			{
				current_ctx->_stencil_flag2 |= _STENCIL_FLAG2_BIT_gl_stencil_back_writemask;
				current_ctx->gl_stencil_back_writemask[0]   = mask;
			}
		}
	}
	else
	{
		_set_gl_error(GL_INVALID_ENUM);
		goto finish;
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((current_ctx->gl_stencil_fail[0] != fail) ||
	    (current_ctx->gl_stencil_pass_depth_fail[0] != zfail) ||
	    (current_ctx->gl_stencil_pass_depth_pass[0] != zpass) ||
	    (current_ctx->gl_stencil_back_fail[0] != fail) ||
	    (current_ctx->gl_stencil_back_pass_depth_fail[0] != zfail) ||
	    (current_ctx->gl_stencil_back_pass_depth_pass[0] != zpass))
	{
		IF_GL_SUCCESS(_orig_fastpath_glStencilOp(fail, zfail, zpass))
		{
			current_ctx->_stencil_flag1 |=
				_STENCIL_FLAG1_BIT_gl_stencil_fail |
				_STENCIL_FLAG1_BIT_gl_stencil_pass_depth_fail |
				_STENCIL_FLAG1_BIT_gl_stencil_pass_depth_pass;

			current_ctx->gl_stencil_fail[0]              = fail;
			current_ctx->gl_stencil_pass_depth_fail[0]   = zfail;
			current_ctx->gl_stencil_pass_depth_pass[0]   = zpass;

			current_ctx->_stencil_flag2 |=
				_STENCIL_FLAG2_BIT_gl_stencil_back_fail |
				_STENCIL_FLAG2_BIT_gl_stencil_back_pass_depth_fail |
				_STENCIL_FLAG2_BIT_gl_stencil_back_pass_depth_pass;

			current_ctx->gl_stencil_back_fail[0]         = fail;
			current_ctx->gl_stencil_back_pass_depth_fail[0]   = zfail;
			current_ctx->gl_stencil_back_pass_depth_pass[0]   = zpass;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((face == GL_FRONT) || (face == GL_FRONT_AND_BACK))
	{
		if ((current_ctx->gl_stencil_fail[0] != fail) ||
		    (current_ctx->gl_stencil_pass_depth_fail[0] != zfail) ||
		    (current_ctx->gl_stencil_pass_depth_pass[0] != zpass))
		{
			IF_GL_SUCCESS(_orig_fastpath_glStencilOpSeparate(face, fail, zfail, zpass))
			{
				current_ctx->_stencil_flag1 |=
				_STENCIL_FLAG1_BIT_gl_stencil_fail |
				_STENCIL_FLAG1_BIT_gl_stencil_pass_depth_fail |
				_STENCIL_FLAG1_BIT_gl_stencil_pass_depth_pass;

				current_ctx->gl_stencil_fail[0]              = fail;
				current_ctx->gl_stencil_pass_depth_fail[0]   = zfail;
				current_ctx->gl_stencil_pass_depth_pass[0]   = zpass;
			}
		}
	}
	else if ((face == GL_BACK) || (face == GL_FRONT_AND_BACK))
	{
		if ((current_ctx->gl_stencil_back_fail[0] != fail) ||
		    (current_ctx->gl_stencil_back_pass_depth_fail[0] != zfail) ||
		    (current_ctx->gl_stencil_back_pass_depth_pass[0] != zpass))
		{
			IF_GL_SUCCESS(_orig_fastpath_glStencilOpSeparate(face, fail, zfail, zpass))
			{
				current_ctx->_stencil_flag2 |=
				_STENCIL_FLAG2_BIT_gl_stencil_back_fail |
				_STENCIL_FLAG2_BIT_gl_stencil_back_pass_depth_fail |
				_STENCIL_FLAG2_BIT_gl_stencil_back_pass_depth_pass;

				current_ctx->gl_stencil_back_fail[0]              = fail;
				current_ctx->gl_stencil_back_pass_depth_fail[0]   = zfail;
				current_ctx->gl_stencil_back_pass_depth_pass[0]   = zpass;
			}
		}
	}
	else
	{
		_set_gl_error(GL_INVALID_ENUM);
		goto finish;
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttrib1f(GLuint index, GLfloat x)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttrib1f(index, x))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_attrib_value;
			current_ctx->gl_vertex_array_size[index] = 0;
			current_ctx->gl_vertex_array_integer[index] = GL_FALSE;

			current_ctx->gl_vertex_attrib_value[index * 4 + 0] = x;
			current_ctx->gl_vertex_attrib_value[index * 4 + 1] = 0;
			current_ctx->gl_vertex_attrib_value[index * 4 + 2] = 0;
			current_ctx->gl_vertex_attrib_value[index * 4 + 3] = 1;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttrib1fv(GLuint index, const GLfloat* values)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttrib1fv(index, values))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_attrib_value;
			current_ctx->gl_vertex_array_size[index] = 0;
			current_ctx->gl_vertex_array_integer[index] = GL_FALSE;

			current_ctx->gl_vertex_attrib_value[index * 4 + 0] = values[0];
			current_ctx->gl_vertex_attrib_value[index * 4 + 1] = 0;
			current_ctx->gl_vertex_attrib_value[index * 4 + 2] = 0;
			current_ctx->gl_vertex_attrib_value[index * 4 + 3] = 1;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttrib2f(index, x, y))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_attrib_value;
			current_ctx->gl_vertex_array_size[index] = 0;
			current_ctx->gl_vertex_array_integer[index] = GL_FALSE;

			current_ctx->gl_vertex_attrib_value[index * 4 + 0] = x;
			current_ctx->gl_vertex_attrib_value[index * 4 + 1] = y;
			current_ctx->gl_vertex_attrib_value[index * 4 + 2] = 0;
			current_ctx->gl_vertex_attrib_value[index * 4 + 3] = 1;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttrib2fv(GLuint index, const GLfloat* values)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttrib2fv(index, values))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_attrib_value;
			current_ctx->gl_vertex_array_size[index] = 0;
			current_ctx->gl_vertex_array_integer[index] = GL_FALSE;

			current_ctx->gl_vertex_attrib_value[index * 4 + 0] = values[0];
			current_ctx->gl_vertex_attrib_value[index * 4 + 1] = values[1];
			current_ctx->gl_vertex_attrib_value[index * 4 + 2] = 0;
			current_ctx->gl_vertex_attrib_value[index * 4 + 3] = 1;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttrib3f(index, x, y, z))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_attrib_value;
			current_ctx->gl_vertex_array_size[index] = 0;
			current_ctx->gl_vertex_array_integer[index] = GL_FALSE;

			current_ctx->gl_vertex_attrib_value[index * 4 + 0] = x;
			current_ctx->gl_vertex_attrib_value[index * 4 + 1] = y;
			current_ctx->gl_vertex_attrib_value[index * 4 + 2] = z;
			current_ctx->gl_vertex_attrib_value[index * 4 + 3] = 1;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttrib3fv(GLuint index, const GLfloat* values)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttrib3fv(index, values))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_attrib_value;
			current_ctx->gl_vertex_array_size[index] = 0;
			current_ctx->gl_vertex_array_integer[index] = GL_FALSE;

			current_ctx->gl_vertex_attrib_value[index * 4 + 0] = values[0];
			current_ctx->gl_vertex_attrib_value[index * 4 + 1] = values[1];
			current_ctx->gl_vertex_attrib_value[index * 4 + 2] = values[2];
			current_ctx->gl_vertex_attrib_value[index * 4 + 3] = 1;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttrib4f(index, x, y, z, w))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_attrib_value;
			current_ctx->gl_vertex_array_size[index] = 0;
			current_ctx->gl_vertex_array_integer[index] = GL_FALSE;

			current_ctx->gl_vertex_attrib_value[index * 4 + 0] = x;
			current_ctx->gl_vertex_attrib_value[index * 4 + 1] = y;
			current_ctx->gl_vertex_attrib_value[index * 4 + 2] = z;
			current_ctx->gl_vertex_attrib_value[index * 4 + 3] = w;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttrib4fv(GLuint index, const GLfloat* values)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttrib4fv(index, values))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_attrib_value;
			current_ctx->gl_vertex_array_size[index] = 0;
			current_ctx->gl_vertex_array_integer[index] = GL_FALSE;

			current_ctx->gl_vertex_attrib_value[index * 4 + 0] = values[0];
			current_ctx->gl_vertex_attrib_value[index * 4 + 1] = values[1];
			current_ctx->gl_vertex_attrib_value[index * 4 + 2] = values[2];
			current_ctx->gl_vertex_attrib_value[index * 4 + 3] = values[3];
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttribPointer(index, size, type, normalized, stride, pointer))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_array;

			current_ctx->gl_vertex_array_buf_id[index]       = current_ctx->gl_array_buffer_binding[0];
			current_ctx->gl_vertex_array_size[index]         = size;
			current_ctx->gl_vertex_array_type[index]         = type;
			current_ctx->gl_vertex_array_normalized[index]   = normalized;
			current_ctx->gl_vertex_array_integer[index]      = GL_FALSE;
			current_ctx->gl_vertex_array_stride[index]       = stride;
			current_ctx->gl_vertex_array_pointer[index]      = (GLvoid *)pointer;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if ((current_ctx->gl_viewport[0] != x) ||
	    (current_ctx->gl_viewport[1] != y) ||
	    (current_ctx->gl_viewport[2] != width) ||
	    (current_ctx->gl_viewport[3] != height))
	{
		IF_GL_SUCCESS(_orig_fastpath_glViewport(x, y, width, height))
		{
			current_ctx->_clear_flag1 |= _CLEAR_FLAG1_BIT_gl_viewport;
			current_ctx->gl_viewport[0] = x;
			current_ctx->gl_viewport[1] = y;
			current_ctx->gl_viewport[2] = width;
			current_ctx->gl_viewport[3] = height;
		}
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

void
fastpath_glEGLImageTargetTexture2DOES(GLenum target, GLeglImageOES image)
{
	int tex_idx;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	tex_idx = current_ctx->gl_active_texture[0] - GL_TEXTURE0;

	switch (target)
	{
		case GL_TEXTURE_2D:
			current_ctx->gl_tex_2d_state[tex_idx] = -1;
			break;
		case GL_TEXTURE_CUBE_MAP:
			current_ctx->gl_tex_cube_state[tex_idx] = -1;
			break;
		default:
			_set_gl_error(GL_INVALID_ENUM);
			goto finish;
	}

	_orig_fastpath_glEGLImageTargetTexture2DOES(target, image);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

#define TRANS_VALUE(index, value) \
{ \
	switch (get_type) \
	{ \
		case GL_INT: if (!is64) ((GLint *)ptr)[index] = value; else ((GLint64 *)ptr)[index] = value; break; \
		case GL_FLOAT: ((GLfloat *)ptr)[index] = (GLfloat)value; break; \
		case GL_BOOL: ((GLboolean *)ptr)[index] = (value == 0) ? GL_FALSE : GL_TRUE; break; \
	} \
}

#define EXTRACT_VALUE(index, value) \
{ \
	switch (get_type) \
	{ \
		case GL_INT: if (!is64) value = ((GLint *)ptr)[index]; else value = ((GLint64 *)ptr)[index]; break; \
		case GL_FLOAT: value = ((GLfloat *)ptr)[index]; break; \
		case GL_BOOL: value = ((GLboolean *)ptr)[index]; break; \
	} \
}

static GLboolean
_modify_get_value(GLenum pname, GLvoid *ptr, GLenum get_type, GLboolean is64)
{
	GLboolean ret = GL_FALSE;

	DEFINE_FASTPAH_GL_FUNC();
	INIT_FASTPATH_GL_FUNC();

	switch (pname)
	{
		case GL_NUM_EXTENSIONS:
			_valid_extension_string();
			TRANS_VALUE(0, gl_extension_count);
			break;

		case GL_TEXTURE_BINDING_2D:
		case GL_TEXTURE_BINDING_CUBE_MAP:
		case GL_ARRAY_BUFFER_BINDING:
		case GL_ELEMENT_ARRAY_BUFFER_BINDING:
		case GL_COPY_READ_BUFFER_BINDING:
		case GL_COPY_WRITE_BUFFER_BINDING:
		case GL_PIXEL_PACK_BUFFER_BINDING:
		case GL_PIXEL_UNPACK_BUFFER_BINDING:
		case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING:
		case GL_UNIFORM_BUFFER_BINDING:
		case GL_DRAW_FRAMEBUFFER_BINDING:
		case GL_READ_FRAMEBUFFER_BINDING:
		case GL_RENDERBUFFER_BINDING:
		case GL_CURRENT_PROGRAM:
		case GL_VERTEX_ARRAY_BINDING:
		case GL_SAMPLER_BINDING:
		case GL_TRANSFORM_FEEDBACK_BINDING:
		{
			GLint real_obj_id = _COREGL_INT_INIT_VALUE;
			GLuint glue_obj_id = _COREGL_INT_INIT_VALUE;
			GL_Object_Type obj_type = GL_OBJECT_TYPE_UNKNOWN;
			EXTRACT_VALUE(0, real_obj_id);

			switch (pname)
			{
				case GL_TEXTURE_BINDING_2D:
				case GL_TEXTURE_BINDING_CUBE_MAP:
					obj_type = GL_OBJECT_TYPE_TEXTURE;
					break;
				case GL_ARRAY_BUFFER_BINDING:
				case GL_ELEMENT_ARRAY_BUFFER_BINDING:
				case GL_COPY_READ_BUFFER_BINDING:
				case GL_COPY_WRITE_BUFFER_BINDING:
				case GL_PIXEL_PACK_BUFFER_BINDING:
				case GL_PIXEL_UNPACK_BUFFER_BINDING:
				case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING:
				case GL_UNIFORM_BUFFER_BINDING:
					obj_type = GL_OBJECT_TYPE_BUFFER;
					break;
				case GL_DRAW_FRAMEBUFFER_BINDING:
				case GL_READ_FRAMEBUFFER_BINDING:
					obj_type = GL_OBJECT_TYPE_FRAMEBUFFER;
					break;
				case GL_RENDERBUFFER_BINDING:
					obj_type = GL_OBJECT_TYPE_RENDERBUFFER;
					break;
				case GL_CURRENT_PROGRAM:
					obj_type = GL_OBJECT_TYPE_PROGRAM;
					break;
				case GL_VERTEX_ARRAY_BINDING:
					obj_type = GL_OBJECT_TYPE_VERTEXARRAY;
					break;
				case GL_SAMPLER_BINDING:
					obj_type = GL_OBJECT_TYPE_SAMPLER;
					break;
				case GL_TRANSFORM_FEEDBACK_BINDING:
					obj_type = GL_OBJECT_TYPE_TRANSFORMFEEDBACK;
					break;
			}
			AST(obj_type != GL_OBJECT_TYPE_UNKNOWN);
			AST(GET_GLUE_OBJ(obj_type, real_obj_id, &glue_obj_id) == 1);
			TRANS_VALUE(0, glue_obj_id);

			ret = GL_TRUE;
			break;
		}
	}
	goto finish;

finish:
	return ret;
}

void
fastpath_glGetBooleanv(GLenum pname, GLboolean* params)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glGetBooleanv(pname, params))
	{
		_modify_get_value(pname, params, GL_BOOL, GL_FALSE);
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

void
fastpath_glGetFloatv(GLenum pname, GLfloat* params)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glGetFloatv(pname, params))
	{
		_modify_get_value(pname, params, GL_FLOAT, GL_FALSE);
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

void
fastpath_glGetIntegerv(GLenum pname, GLint* params)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glGetIntegerv(pname, params))
	{
		_modify_get_value(pname, params, GL_INT, GL_FALSE);
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}



/* ES 3.0 PASS (SUPPORT) */
void
fastpath_glGetProgramBinary(GLuint program, GLsizei bufsize, GLsizei* length, GLenum* binaryFormat, void* binary)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glGetProgramBinary(real_obj, bufsize, length, binaryFormat, binary);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramBinary(GLuint program, GLenum binaryFormat, const void* binary, GLint length)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramBinary(real_obj, binaryFormat, binary, length);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glReadBuffer(GLenum mode)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	CURR_STATE_COMPARE(gl_read_buffer, mode)
	{
		IF_GL_SUCCESS(_orig_fastpath_glReadBuffer(mode))
		{
			current_ctx->_misc_flag3 |= _MISC_FLAG3_BIT_gl_read_buffer;
			current_ctx->gl_read_buffer[0] = mode;
		}
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGenQueries(GLsizei n, GLuint* ids)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (ids == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);

	IF_GL_SUCCESS(_orig_fastpath_glGenQueries(n, objid_array))
	{
		for (i = 0; i < n; i++)
		{
			ids[i] = fastpath_ostate_create_object(&current_ctx->ostate, GL_OBJECT_TYPE_QUERY, objid_array[i]);
		}
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glDeleteQueries(GLsizei n, const GLuint* ids)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (ids == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);
	{
		int real_n = 0;

		for (i = 0; i < n; i++)
		{
			int real_objid = _COREGL_INT_INIT_VALUE;
			if (ids[i] == 0) continue;

			real_objid = fastpath_ostate_get_object(&current_ctx->ostate, GL_OBJECT_TYPE_QUERY, ids[i]);
			if (real_objid == 0) continue;

			AST(fastpath_ostate_remove_object(&current_ctx->ostate, GL_OBJECT_TYPE_QUERY, ids[i]) == 1);
			objid_array[real_n++] = real_objid;
		}

		_orig_fastpath_glDeleteQueries(real_n, objid_array);
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FASTPATH_FUNC_END();
}


GLboolean
fastpath_glIsQuery(GLuint id)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_QUERY, id, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _orig_fastpath_glIsQuery(real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


void
fastpath_glBeginQuery(GLenum target, GLuint id)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_QUERY, id, &real_obj) != 1)
	{
		// TODO : Begin - Context Switch
		_set_gl_error(GL_INVALID_OPERATION);
		goto finish;
	}

	_orig_fastpath_glBeginQuery(target, real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetQueryiv(GLenum target, GLenum pname, GLint* params)
{
	GLuint glue_obj_id = _COREGL_INT_INIT_VALUE;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	_orig_fastpath_glGetQueryiv(target, pname, params);

	switch (pname)
	{
		case GL_CURRENT_QUERY:
			if (params[0] != 0)
			{
				AST(GET_GLUE_OBJ(GL_OBJECT_TYPE_QUERY, params[0], &glue_obj_id) == 1);
				params[0] = glue_obj_id;
			}
			break;
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint* params)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_QUERY, id, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_OPERATION);
		goto finish;
	}

	_orig_fastpath_glGetQueryObjectuiv(real_obj, pname, params);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glDrawBuffers(GLsizei n, const GLenum* bufs)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glDrawBuffers(n, bufs))
	{
		current_ctx->_misc_flag3 |= _MISC_FLAG3_BIT_gl_draw_buffers;
		fastpath_state_get_draw_buffers(current_ctx->gl_draw_buffers);
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_TEXTURE, texture, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	_orig_fastpath_glFramebufferTextureLayer(target, attachment, texture, level, layer);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


////////////////////////////////////////////////////////////////////////

void
fastpath_glGenVertexArrays(GLsizei n, GLuint* arrays)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (arrays == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);

	IF_GL_SUCCESS(_orig_fastpath_glGenVertexArrays(n, objid_array))
	{
		for (i = 0; i < n; i++)
		{
			arrays[i] = fastpath_ostate_create_object(&current_ctx->ostate, GL_OBJECT_TYPE_VERTEXARRAY, objid_array[i]);
		}
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glBindVertexArray(GLuint array)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_VERTEXARRAY, array, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_OPERATION);
		goto finish;
	}

	if (current_ctx->gl_vertex_array_binding[0] != real_obj)
	{
		IF_GL_SUCCESS(_orig_fastpath_glBindVertexArray(real_obj))
		{
			current_ctx->_misc_flag3 |= _MISC_FLAG3_BIT_gl_vertex_array_binding;
			current_ctx->gl_vertex_array_binding[0] = real_obj;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


GLboolean
fastpath_glIsVertexArray(GLuint array)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_VERTEXARRAY, array, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _orig_fastpath_glIsVertexArray(real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


void
fastpath_glDeleteVertexArrays(GLsizei n, const GLuint* arrays)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (arrays == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);
	{
		int real_n = 0;

		for (i = 0; i < n; i++)
		{
			int real_objid = _COREGL_INT_INIT_VALUE;
			if (arrays[i] == 0) continue;

			real_objid = fastpath_ostate_get_object(&current_ctx->ostate, GL_OBJECT_TYPE_VERTEXARRAY, arrays[i]);
			if (real_objid == 0) continue;

			AST(fastpath_ostate_remove_object(&current_ctx->ostate, GL_OBJECT_TYPE_VERTEXARRAY, arrays[i]) == 1);
			objid_array[real_n++] = real_objid;
		}

		IF_GL_SUCCESS(_orig_fastpath_glDeleteVertexArrays(real_n, objid_array))
		{
			for (i = 0; i < real_n; i++)
			{
				General_Trace_List *current = NULL;
				current = current_ctx->ostate.shared->using_gctxs;

				while (current != NULL)
				{
					GLGlueContext *cur_gctx = (GLGlueContext *)current->value;

					if (cur_gctx->gl_vertex_array_binding[0] == objid_array[i])
						cur_gctx->gl_vertex_array_binding[0] = 0;

					current = current->next;
				}
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
	_COREGL_FASTPATH_FUNC_END();
}

////////////////////////////////////////////////////////////////////////

void
fastpath_glGetIntegeri_v(GLenum target, GLuint index, GLint* data)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glGetIntegeri_v(target, index, data))
	{
		_modify_get_value(target, data, GL_INT, GL_FALSE);
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

////////////////////////////////////////////////////////////////////////

void
fastpath_glGenTransformFeedbacks(GLsizei n, GLuint* ids)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (ids == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);

	IF_GL_SUCCESS(_orig_fastpath_glGenTransformFeedbacks(n, objid_array))
	{
		for (i = 0; i < n; i++)
		{
			ids[i] = fastpath_ostate_create_object(&current_ctx->ostate, GL_OBJECT_TYPE_TRANSFORMFEEDBACK, objid_array[i]);
		}
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glBindTransformFeedback(GLenum target, GLuint id)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_TRANSFORMFEEDBACK, id, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	if (current_ctx->gl_transform_feedback_binding[0] != real_obj)
	{
		IF_GL_SUCCESS(_orig_fastpath_glBindTransformFeedback(target, real_obj))
		{
			current_ctx->_misc_flag3 |= _MISC_FLAG3_BIT_gl_transform_feedback_binding;
			current_ctx->gl_transform_feedback_binding[0] = real_obj;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glBeginTransformFeedback(GLenum primitiveMode)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glBeginTransformFeedback(primitiveMode))
	{
		current_ctx->_misc_flag3 |= _MISC_FLAG3_BIT_gl_transform_feedback;

		current_ctx->gl_transform_feedback_active[0] = GL_TRUE;
		current_ctx->gl_transform_feedback_paused[0] = GL_FALSE;
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glEndTransformFeedback()
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glEndTransformFeedback())
	{
		current_ctx->_misc_flag3 |= _MISC_FLAG3_BIT_gl_transform_feedback;

		current_ctx->gl_transform_feedback_active[0] = GL_FALSE;
		current_ctx->gl_transform_feedback_paused[0] = GL_FALSE;
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glPauseTransformFeedback()
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glPauseTransformFeedback())
	{
		current_ctx->_misc_flag3 |= _MISC_FLAG3_BIT_gl_transform_feedback;

		current_ctx->gl_transform_feedback_active[0] = GL_TRUE;
		current_ctx->gl_transform_feedback_paused[0] = GL_TRUE;
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

void
fastpath_glResumeTransformFeedback()
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glResumeTransformFeedback())
	{
		current_ctx->_misc_flag3 |= _MISC_FLAG3_BIT_gl_transform_feedback;

		current_ctx->gl_transform_feedback_active[0] = GL_TRUE;
		current_ctx->gl_transform_feedback_paused[0] = GL_FALSE;
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


GLboolean
fastpath_glIsTransformFeedback(GLuint id)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_TRANSFORMFEEDBACK, id, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _orig_fastpath_glIsTransformFeedback(real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


void
fastpath_glDeleteTransformFeedbacks(GLsizei n, const GLuint* ids)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (ids == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);
	{
		int real_n = 0;

		for (i = 0; i < n; i++)
		{
			int real_objid = _COREGL_INT_INIT_VALUE;
			if (ids[i] == 0) continue;

			real_objid = fastpath_ostate_get_object(&current_ctx->ostate, GL_OBJECT_TYPE_TRANSFORMFEEDBACK, ids[i]);
			if (real_objid == 0) continue;

			AST(fastpath_ostate_remove_object(&current_ctx->ostate, GL_OBJECT_TYPE_TRANSFORMFEEDBACK, ids[i]) == 1);
			objid_array[real_n++] = real_objid;
		}

		IF_GL_SUCCESS(_orig_fastpath_glDeleteTransformFeedbacks(real_n, objid_array))
		{
			for (i = 0; i < real_n; i++)
			{
				General_Trace_List *current = NULL;
				current = current_ctx->ostate.shared->using_gctxs;

				while (current != NULL)
				{
					GLGlueContext *cur_gctx = (GLGlueContext *)current->value;

					if (cur_gctx->gl_transform_feedback_binding[0] == objid_array[i])
						cur_gctx->gl_transform_feedback_binding[0] = 0;

					current = current->next;
				}
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
	_COREGL_FASTPATH_FUNC_END();
}

////////////////////////////////////////////////////////////////////////


void
fastpath_glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_BUFFER, buffer, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

#define STATE_PROC(gl_state, flagid, flagbit) \
	{ \
		CURR_STATE_COMPARE(gl_state, real_obj) \
		{ \
			IF_GL_SUCCESS(_orig_fastpath_glBindBufferBase(target, index, real_obj)) \
			{ \
				current_ctx->flagid |= flagbit##_##gl_state; \
				current_ctx->gl_state##_array[index] = real_obj; \
				current_ctx->gl_state##_array_offset[index] = 0; \
				current_ctx->gl_state##_array_size[index] = 0; \
			} \
		} \
		break; \
	}


	switch (target)
	{
		case GL_TRANSFORM_FEEDBACK_BUFFER:
			STATE_PROC(gl_transform_feedback_buffer_binding, _bind_flag, _BIND_FLAG_BIT);
			break;
		case GL_UNIFORM_BUFFER:
			STATE_PROC(gl_uniform_buffer_binding, _bind_flag, _BIND_FLAG_BIT);
			break;
		default:
			_set_gl_error(GL_INVALID_ENUM);
			break;
 	}


#undef STATE_PROC

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}



void
fastpath_glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_BUFFER, buffer, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

#define STATE_PROC(gl_state, flagnum) \
	{ \
		CURR_STATE_COMPARE(gl_state, real_obj) \
		{ \
			IF_GL_SUCCESS(_orig_fastpath_glBindBufferRange(target, index, real_obj, offset, size)) \
			{ \
				current_ctx->_bind_flag |= _BIND_FLAG_BIT_##gl_state; \
				current_ctx->gl_state##_array[index] = real_obj; \
				current_ctx->gl_state##_array_offset[index] = offset; \
				current_ctx->gl_state##_array_size[index] = size; \
			} \
		} \
		break; \
	}


	switch (target)
	{
		case GL_TRANSFORM_FEEDBACK_BUFFER: STATE_PROC(gl_transform_feedback_buffer_binding, 0); break;
		case GL_UNIFORM_BUFFER: STATE_PROC(gl_uniform_buffer_binding, 0); break;
		default: _set_gl_error(GL_INVALID_ENUM); break;
 	}


#undef STATE_PROC

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glTransformFeedbackVaryings(real_obj, count, varyings, bufferMode);
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glGetTransformFeedbackVarying(real_obj, index, bufSize, length, size, type, name);
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttribIPointer(index, size, type, stride, pointer))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_array;

			current_ctx->gl_vertex_array_buf_id[index]      = current_ctx->gl_array_buffer_binding[0];
			current_ctx->gl_vertex_array_size[index]        = size;
			current_ctx->gl_vertex_array_type[index]        = type;
			current_ctx->gl_vertex_array_normalized[index]  = GL_FALSE;
			current_ctx->gl_vertex_array_integer[index]     = GL_TRUE;
			current_ctx->gl_vertex_array_stride[index]      = stride;
			current_ctx->gl_vertex_array_pointer[index]     = (GLvoid *)pointer;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttribI4i(index, x, y, z, w))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_attrib_value;
			current_ctx->gl_vertex_array_size[index] = 0;
			current_ctx->gl_vertex_array_integer[index] = GL_TRUE;

			current_ctx->gl_vertex_array_type[index] = GL_INT;
			current_ctx->gl_vertex_attrib_value_integer[index * 4 + 0] = x;
			current_ctx->gl_vertex_attrib_value_integer[index * 4 + 1] = y;
			current_ctx->gl_vertex_attrib_value_integer[index * 4 + 2] = z;
			current_ctx->gl_vertex_attrib_value_integer[index * 4 + 3] = w;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttribI4ui(index, x, y, z, w))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_attrib_value;
			current_ctx->gl_vertex_array_size[index] = 0;
			current_ctx->gl_vertex_array_integer[index] = GL_TRUE;

			current_ctx->gl_vertex_array_type[index] = GL_UNSIGNED_INT;
			current_ctx->gl_vertex_attrib_value_unsigned_integer[index * 4 + 0] = x;
			current_ctx->gl_vertex_attrib_value_unsigned_integer[index * 4 + 1] = y;
			current_ctx->gl_vertex_attrib_value_unsigned_integer[index * 4 + 2] = z;
			current_ctx->gl_vertex_attrib_value_unsigned_integer[index * 4 + 3] = w;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttribI4iv(GLuint index, const GLint* v)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttribI4iv(index, v))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_attrib_value;
			current_ctx->gl_vertex_array_size[index] = 0;
			current_ctx->gl_vertex_array_integer[index] = GL_TRUE;

			current_ctx->gl_vertex_array_type[index] = GL_INT;
			current_ctx->gl_vertex_attrib_value_integer[index * 4 + 0] = v[0];
			current_ctx->gl_vertex_attrib_value_integer[index * 4 + 1] = v[1];
			current_ctx->gl_vertex_attrib_value_integer[index * 4 + 2] = v[2];
			current_ctx->gl_vertex_attrib_value_integer[index * 4 + 3] = v[3];
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttribI4uiv(GLuint index, const GLuint* v)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttribI4uiv(index, v))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_attrib_value;
			current_ctx->gl_vertex_array_size[index] = 0;
			current_ctx->gl_vertex_array_integer[index] = GL_TRUE;

			current_ctx->gl_vertex_array_type[index] = GL_UNSIGNED_INT;
			current_ctx->gl_vertex_attrib_value_unsigned_integer[index * 4 + 0] = v[0];
			current_ctx->gl_vertex_attrib_value_unsigned_integer[index * 4 + 1] = v[1];
			current_ctx->gl_vertex_attrib_value_unsigned_integer[index * 4 + 2] = v[2];
			current_ctx->gl_vertex_attrib_value_unsigned_integer[index * 4 + 3] = v[3];
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetUniformuiv(GLuint program, GLint location, GLuint* params)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glGetUniformuiv(real_obj, location, params);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


GLint
fastpath_glGetFragDataLocation(GLuint program, const GLchar *name)
{
	GLint ret = _COREGL_INT_INIT_VALUE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	ret = _orig_fastpath_glGetFragDataLocation(real_obj, name);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


const GLubyte*
fastpath_glGetStringi(GLenum name, GLuint index)
{
	const char *ret = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	switch (name)
	{
		case GL_VERSION:
			_set_gl_error(GL_INVALID_ENUM);
			goto finish;
		case GL_EXTENSIONS:
			_valid_extension_string();
			if (index < 0 || index >= gl_extension_count)
			{
				_set_gl_error(GL_INVALID_VALUE);
				goto finish;
			}
			ret = string_each_extensions[index];
			break;
		default:
			IF_GL_SUCCESS(ret = (const char *)_orig_fastpath_glGetStringi(name, index))
			{
			}
			else
			{
				ret = NULL;
			}
			break;
	}

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return (const GLubyte *)ret;
}


void
fastpath_glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames, GLuint* uniformIndices)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glGetUniformIndices(real_obj, uniformCount, uniformNames, uniformIndices);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glGetActiveUniformsiv(real_obj, uniformCount, uniformIndices, pname, params);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


GLuint
fastpath_glGetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName)
{
	GLuint ret = _COREGL_INT_INIT_VALUE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	ret = _orig_fastpath_glGetUniformBlockIndex(real_obj, uniformBlockName);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}

void
fastpath_glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glGetActiveUniformBlockiv(real_obj, uniformBlockIndex, pname, params);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

void
fastpath_glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glGetActiveUniformBlockName(real_obj, uniformBlockIndex, bufSize, length, uniformBlockName);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glUniformBlockBinding(real_obj, uniformBlockIndex, uniformBlockBinding);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetInteger64v(GLenum pname, GLint64* params)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glGetInteger64v(pname, params))
	{
		_modify_get_value(pname, params, GL_INT, GL_TRUE);
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glGetInteger64i_v(GLenum target, GLuint index, GLint64* data)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glGetInteger64i_v(target, index, data))
	{
		_modify_get_value(target, data, GL_INT, GL_TRUE);
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


////////////////////////////////////////////////////////////////////////

void
fastpath_glGenSamplers(GLsizei n, GLuint* samplers)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (samplers == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);

	IF_GL_SUCCESS(_orig_fastpath_glGenSamplers(n, objid_array))
	{
		for (i = 0; i < n; i++)
		{
			samplers[i] = fastpath_ostate_create_object(&current_ctx->ostate, GL_OBJECT_TYPE_SAMPLER, objid_array[i]);
		}
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glBindSampler(GLuint unit, GLuint sampler)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_SAMPLER, sampler, &real_obj) != 1)
	{
		_set_gl_error(GL_OUT_OF_MEMORY);
		goto finish;
	}

	_orig_fastpath_glBindSampler(unit, real_obj);
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


GLboolean
fastpath_glIsSampler(GLuint sampler)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_SAMPLER, sampler, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	ret = _orig_fastpath_glIsSampler(real_obj);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
	return ret;
}


void
fastpath_glDeleteSamplers(GLsizei n, const GLuint* samplers)
{
	int i;
	GLuint *objid_array = NULL;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (n < 0)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}
	if (n == 0) goto finish;
	if (samplers == NULL) goto finish;

	AST(current_ctx->ostate.shared != NULL);

	objid_array = (GLuint *)calloc(1, sizeof(GLuint) * n);
	{
		int real_n = 0;

		for (i = 0; i < n; i++)
		{
			int real_objid = _COREGL_INT_INIT_VALUE;
			if (samplers[i] == 0) continue;

			real_objid = fastpath_ostate_get_object(&current_ctx->ostate, GL_OBJECT_TYPE_SAMPLER, samplers[i]);
			if (real_objid == 0) continue;

			AST(fastpath_ostate_remove_object(&current_ctx->ostate, GL_OBJECT_TYPE_SAMPLER, samplers[i]) == 1);
			objid_array[real_n++] = real_objid;
		}

		_orig_fastpath_glDeleteSamplers(real_n, objid_array);
	}

	goto finish;

finish:
	if (objid_array != NULL)
	{
		free(objid_array);
		objid_array = NULL;
	}
	_COREGL_FASTPATH_FUNC_END();
}

////////////////////////////////////////////////////////////////////////


void
fastpath_glSamplerParameteri(GLuint sampler, GLenum pname, GLint param)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_SAMPLER, sampler, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	_orig_fastpath_glSamplerParameteri(real_obj, pname, param);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

void
fastpath_glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint* param)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_SAMPLER, sampler, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	_orig_fastpath_glSamplerParameteriv(real_obj, pname, param);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

void
fastpath_glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_SAMPLER, sampler, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	_orig_fastpath_glSamplerParameterf(real_obj, pname, param);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

void
fastpath_glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat* param)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_SAMPLER, sampler, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	_orig_fastpath_glSamplerParameterfv(real_obj, pname, param);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

void
fastpath_glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint* params)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_SAMPLER, sampler, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	_orig_fastpath_glGetSamplerParameteriv(real_obj, pname, params);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}

void
fastpath_glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat* params)
{
	GLboolean ret = GL_FALSE;
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_SAMPLER, sampler, &real_obj) != 1)
	{
		ret = GL_FALSE;
		goto finish;
	}

	_orig_fastpath_glGetSamplerParameterfv(real_obj, pname, params);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glVertexAttribDivisor(GLuint index, GLuint divisor)
{
	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	IF_GL_SUCCESS(_orig_fastpath_glVertexAttribDivisor(index, divisor))
	{
		if (current_ctx->gl_vertex_array_binding[0] == 0)
		{
			current_ctx->_vattrib_flag |= _VATTRIB_FLAG_BIT_gl_vertex_array;
			current_ctx->gl_vertex_array_divisor[index] = divisor;
		}
	}
	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


void
fastpath_glProgramParameteri(GLuint program, GLenum pname, GLint value)
{
	GLuint real_obj;

	DEFINE_FASTPAH_GL_FUNC();
	_COREGL_FASTPATH_FUNC_BEGIN();
	INIT_FASTPATH_GL_FUNC();

	if (GET_REAL_OBJ(GL_OBJECT_TYPE_PROGRAM, program, &real_obj) != 1)
	{
		_set_gl_error(GL_INVALID_VALUE);
		goto finish;
	}

	_orig_fastpath_glProgramParameteri(real_obj, pname, value);

	goto finish;

finish:
	_COREGL_FASTPATH_FUNC_END();
}


