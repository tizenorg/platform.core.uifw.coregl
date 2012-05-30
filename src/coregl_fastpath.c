#include "coregl_fastpath.h"

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

GLenum FPGL_Error = GL_NO_ERROR;

Mutex init_context_mutex = MUTEX_INITIALIZER;
GLGlueContext *initial_ctx = NULL;

static void
_get_texture_states(GLenum pname, GLint *params)
{
	GLuint cur_active_tex = 0;

	AST(initial_ctx != NULL);

	_sym_glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint *)&cur_active_tex);
	int i;
	for (i = 0; i < initial_ctx->gl_num_tex_units[0]; i++)
	{
		_sym_glActiveTexture(GL_TEXTURE0 + i);
		_sym_glGetIntegerv(pname, &(((GLint *)params)[i]));
	}
	_sym_glActiveTexture(cur_active_tex);
}

static GLuint
_get_stencil_max_mask()
{
	GLuint stencil_bit = 0;

	_sym_glGetIntegerv(GL_STENCIL_BITS, (GLint *)&stencil_bit);
	return (1 << stencil_bit) - 1;
}

void
init_fast_gl()
{
}

void
free_fast_gl()
{
}

static GL_Object **
_get_shared_object(GL_Shared_Object_State *sostate, GL_Object_Type type)
{
	switch (type)
	{
		case GL_OBJECT_TYPE_TEXTURE:
			return sostate->texture;
		case GL_OBJECT_TYPE_BUFFER:
			return sostate->buffer;
		case GL_OBJECT_TYPE_FRAMEBUFFER:
			return sostate->framebuffer;
		case GL_OBJECT_TYPE_RENDERBUFFER:
			return sostate->renderbuffer;
		case GL_OBJECT_TYPE_PROGRAM:
			return sostate->program;
		default:
			return NULL;
	}
}


GLuint
sostate_create_object(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint real_name)
{
	GL_Object **object = NULL;
	GLuint ret = _COREGL_INT_INIT_VALUE;
	int i;

	object = _get_shared_object(sostate, type);

	for (i = 1; i < MAX_GL_OBJECT_SIZE; i++)
	{
		if (object[i] == NULL)
		{
			GL_Object *newobj = (GL_Object *)calloc(1, sizeof(GL_Object));
			newobj->id = (int)type + i;
			newobj->real_id = real_name;
			object[i] = newobj;
			ret = newobj->id;
			goto finish;
		}
	}
	goto finish;

finish:
	return ret;
}

GLuint
sostate_remove_object(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint glue_name)
{
	GL_Object **object = NULL;
	GLuint ret = _COREGL_INT_INIT_VALUE;
	int hash = _COREGL_INT_INIT_VALUE;

	object = _get_shared_object(sostate, type);

	hash = glue_name - (int)type;
	if (hash < 0 ||
	    hash > MAX_GL_OBJECT_SIZE ||
	    object[hash] == NULL ||
	    object[hash]->id != glue_name)
	{
		ret = 0;
		goto finish;
	}

	free(object[hash]);
	object[hash] = NULL;
	ret = 1;
	goto finish;

finish:
	return ret;
}

GLuint
sostate_get_object(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint glue_name)
{
	GL_Object **object = NULL;
	GLuint ret = _COREGL_INT_INIT_VALUE;
	int hash = _COREGL_INT_INIT_VALUE;

	object = _get_shared_object(sostate, type);

	hash = glue_name - (int)type;
	if (hash < 0 ||
	    hash > MAX_GL_OBJECT_SIZE ||
	    object[hash] == NULL ||
	    object[hash]->id != glue_name)
	{
		ret = 0;
		goto finish;
	}
	ret = object[hash]->real_id;
	goto finish;

finish:
	return ret;
}

GLuint
sostate_find_object(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint real_name)
{
	GL_Object **object = NULL;
	GLuint ret = _COREGL_INT_INIT_VALUE;
	int i;

	object = _get_shared_object(sostate, type);

	for (i = 1; i < MAX_GL_OBJECT_SIZE; i++)
	{
		if (object[i] != NULL && object[i]->real_id == real_name)
		{
			ret = object[i]->id;
			goto finish;
		}
	}
	ret = 0;
	goto finish;

finish:
	return ret;
}

void
dump_context_states(GLGlueContext *ctx, int force_output)
{
	static struct timeval tv_last = { 0, 0 };

	if (unlikely(trace_state_flag != 1)) return;

	if (!force_output)
	{
		struct timeval tv_now = { 0, 0 };
		AST(gettimeofday(&tv_now, NULL) == 0);
		if (tv_now.tv_sec - tv_last.tv_sec < _COREGL_TRACE_OUTPUT_INTERVAL_SEC)
		{
			goto finish;
		}
		tv_last = tv_now;
	}

	TRACE("\n");
	TRACE("\E[0;40;34m========================================================================================================================\E[0m\n");
	TRACE("\E[0;32;1m  State info \E[1;37;1m: GlueCTX = %p\E[0m\n", ctx);
	TRACE("\E[0;40;34m========================================================================================================================\E[0m\n");

#define PRINTF_CHAR_GLenum "%10d"
#define PRINTF_CHAR_GLboolean "%10d"
#define PRINTF_CHAR_GLint "%10d"
#define PRINTF_CHAR_GLsizei "%10u"
#define PRINTF_CHAR_GLuint "%10u"
#define PRINTF_CHAR_GLuintmask "0x%8X"

#define PRINTF_CHAR_GLclampf "%10.6f"
#define PRINTF_CHAR_GLfloat "%10.6f"

#define PRINTF_CHAR_GLvoidptr "%10p"

#define PRINTF_CHAR(type) PRINTF_CHAR_##type

#define INITIAL_CTX initial_ctx
#define GLUE_STATE(TYPE, NAME, SIZE, ARRAY_SIZE, DEFAULT_STMT, GET_STMT)  \
   { \
      TYPE valuedata[SIZE]; \
      TYPE *value = NULL; \
      value = valuedata; GET_STMT; value = valuedata; \
      TRACE("\E[0;37;1m %-30.30s : (\E[0m ", #NAME); \
      for (int i = 0; i < SIZE; i++) \
      { \
         if (i > 0) { \
            if (i % 4 == 0) \
               TRACE("\n %-30.30s     ", "");\
            else \
               TRACE(", "); \
         } \
         TRACE(PRINTF_CHAR(TYPE), ctx->NAME[i]); \
         TRACE("["PRINTF_CHAR(TYPE)"]", value[i]); \
      } \
      TRACE(" \E[0;37;1m)\E[0m\n"); \
   }
# include "coregl_fastpath_state.h"
#undef GLUE_STATE
#undef INITIAL_CTX

	TRACE("\E[0;40;34m========================================================================================================================\E[0m\n");
	TRACE("\n");

	TRACE_END();

finish:
	return;
}

int
init_context_states(GLGlueContext *ctx)
{
	int ret = 0;

	AST(mutex_lock(&init_context_mutex) == 1);

	if (ctx == NULL)
	{
		ERR("Context NULL\n");
		ret = 0;
		goto finish;
	}

	AST(ctx->initialized == 0);
	AST(ctx->sostate != NULL);

	if (initial_ctx == NULL)
	{
		initial_ctx = (GLGlueContext *)calloc(1, sizeof(GLGlueContext));
		AST(initial_ctx != NULL);

//#define FORCE_DEFAULT_VALUE
#ifdef FORCE_DEFAULT_VALUE
# define INITIAL_CTX initial_ctx
# define GLUE_STATE(TYPE, NAME, SIZE, ARRAY_SIZE, DEFAULT_STMT, GET_STMT)  \
      { \
         int i; \
         TYPE valuedata[SIZE]; \
         TYPE *value = NULL; \
         memset(valuedata, 0xcc, sizeof(TYPE) * SIZE); \
         value = valuedata; DEFAULT_STMT; value = valuedata; \
         for (i = 0; i < SIZE; i++) \
         { \
            if (*((char *)(&value[i])) == 0xcc) \
            { \
               memset(&value[i], 0xaa, sizeof(TYPE)); \
               value = valuedata; DEFAULT_STMT; value = valuedata; \
               if (*((char *)(&value[i])) == 0xaa) \
               { \
                  ERR("\E[0;31;1mWARNING : GL-state '"#NAME"' cannot be retrieved\E[0m\n"); \
                  break; \
               } \
            } \
            initial_ctx->NAME[i] = value[i]; \
         } \
      }
#  include "coregl_fastpath_state.h"
# undef GLUE_STATE
# undef INITIAL_CTX
#else
# define INITIAL_CTX initial_ctx
# define SET_GLUE_VALUE(DEFAULT_STMT, FALLBACK_STMT) \
      if (try_step == 1) \
      { \
         value = valuedata; DEFAULT_STMT; value = valuedata; \
      } \
      else \
      { \
         value = valuedata; FALLBACK_STMT; value = valuedata; \
      }

# define GLUE_STATE(TYPE, NAME, SIZE, ARRAY_SIZE, DEFAULT_STMT, GET_STMT)  \
      { \
         int i; \
         int try_step = 0;\
         TYPE valuedata[SIZE]; \
         TYPE *value = NULL; \
         memset(valuedata, 0xcc, sizeof(TYPE) * SIZE); \
         do { \
            try_step++; \
            SET_GLUE_VALUE(GET_STMT, DEFAULT_STMT); \
            for (i = 0; i < SIZE; i++) \
            { \
               if (*((char *)(&value[i])) == 0xcc) \
               { \
                  memset(&value[i], 0xaa, sizeof(TYPE)); \
                  SET_GLUE_VALUE(GET_STMT, DEFAULT_STMT); \
                  if (*((char *)(&value[i])) == 0xaa) \
                  { \
                     try_step++; \
                     if (try_step == 2) \
                     { \
                        ERR("\E[0;31;1mWARNING : GL-state '"#NAME"' cannot be retrieved\E[0m\n"); \
                     } \
                     break; \
                  } \
               } \
               initial_ctx->NAME[i] = value[i]; \
            } \
            if (try_step != 2) \
            { \
               value = valuedata; DEFAULT_STMT; value = valuedata; \
               for (i = 0; i < SIZE; i++) \
               { \
                  if (initial_ctx->NAME[i] != value[i]) \
                  { \
                     ERR("WARNING : GL-state '"#NAME"'[%d] value ["PRINTF_CHAR(TYPE)"] is different from SPEC-DEFAULT ["PRINTF_CHAR(TYPE)"]\n", i, ctx->NAME[i], value[i]); \
                  } \
               } \
            } \
         } \
         while (try_step == 2); \
      }
#  include "coregl_fastpath_state.h"
# undef SET_GLUE_VALUE
# undef GLUE_STATE
# undef INITIAL_CTX
#endif

		if (initial_ctx->gl_num_vertex_attribs[0] > MAX_VERTEX_ATTRIBS)
		{
			ERR("\E[0;31;1mWARNING : Number of vertex attrib is too big! (%d-%d)\E[0m\n", MAX_VERTEX_ATTRIBS, initial_ctx->gl_num_vertex_attribs[0]);
		}
		if (initial_ctx->gl_num_tex_units[0] > MAX_TEXTURE_UNITS)
		{
			ERR("\E[0;31;1mWARNING : Number of texture unit is too big! (%d-%d)\E[0m\n", MAX_TEXTURE_UNITS, initial_ctx->gl_num_tex_units[0]);
		}
	}

	{
		int i;
#define INITIAL_CTX initial_ctx
#define GLUE_STATE(TYPE, NAME, SIZE, ARRAY_SIZE, DEFAULT_STMT, GET_STMT)  \
         for (i = 0; i < SIZE; i++) \
         { \
            ctx->NAME[i] = initial_ctx->NAME[i]; \
         }
# include "coregl_fastpath_state.h"
#undef GLUE_STATE
#undef INITIAL_CTX
	}

	ctx->initialized = 1;
	ret = 1;
	goto finish;

finish:
	AST(mutex_unlock(&init_context_mutex) == 1);

	return ret;
}

void
make_context_current(GLGlueContext *oldctx, GLGlueContext *newctx)
{
	unsigned char flag = 0;
	int i = 0;

	if (debug_nofp == 1) goto finish;

	// Return if they're the same
	if (oldctx == newctx) goto finish;

#ifdef EVAS_GL_DEBUG
#  define STATE_COMPARE(state)
#  define STATES_COMPARE(state_ptr, bytes)
#else
#  define STATE_COMPARE(state) \
   if ((oldctx->state) != (newctx->state))
#  define STATES_COMPARE(state_ptr, bytes) \
   if ((memcmp((oldctx->state_ptr), (newctx->state_ptr), (bytes))) != 0)
#endif

	static void *trace_hint_glfinish = NULL;
	trace_hint_glfinish = _COREGL_TRACE_API_BEGIN("eglMakeCurrent(FP glFinish)", trace_hint_glfinish, 0);
	_sym_glFlush();
	_COREGL_TRACE_API_END("eglMakeCurrent(FP glFinish)", trace_hint_glfinish, 0);


	static void *trace_hint_bindbuffers = NULL;
	trace_hint_bindbuffers = _COREGL_TRACE_API_BEGIN("eglMakeCurrent(FP bind buffers)", trace_hint_bindbuffers, 0);

	//------------------//
	// _bind_flag
	flag = oldctx->_bind_flag | newctx->_bind_flag;
	if (flag)
	{
		STATE_COMPARE(gl_array_buffer_binding[0])
		{
			_sym_glBindBuffer(GL_ARRAY_BUFFER, newctx->gl_array_buffer_binding[0]);
		}
		STATE_COMPARE(gl_element_array_buffer_binding[0])
		{
			_sym_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newctx->gl_element_array_buffer_binding[0]);
		}
		STATE_COMPARE(gl_framebuffer_binding[0])
		{
			_sym_glBindFramebuffer(GL_FRAMEBUFFER, newctx->gl_framebuffer_binding[0]);
		}
		STATE_COMPARE(gl_renderbuffer_binding[0])
		{
			_sym_glBindRenderbuffer(GL_RENDERBUFFER, newctx->gl_renderbuffer_binding[0]);
		}
	}

	_COREGL_TRACE_API_END("eglMakeCurrent(FP bind buffers)", trace_hint_bindbuffers, 0);


	//------------------//
	// Enable States
	// _enable_flag1
	static void *trace_hint_enable_states = NULL;
	trace_hint_enable_states = _COREGL_TRACE_API_BEGIN("eglMakeCurrent(FP enable states)", trace_hint_enable_states, 0);

	flag = oldctx->_enable_flag1 | newctx->_enable_flag1;
	if (flag)
	{
		STATE_COMPARE(gl_blend[0])
		{
			if (newctx->gl_blend[0])
				_sym_glEnable(GL_BLEND);
			else
				_sym_glDisable(GL_BLEND);
		}
		STATE_COMPARE(gl_cull_face[0])
		{
			if (newctx->gl_cull_face[0])
				_sym_glEnable(GL_CULL_FACE);
			else
				_sym_glDisable(GL_CULL_FACE);
		}
		STATE_COMPARE(gl_depth_test[0])
		{
			if (newctx->gl_depth_test[0])
				_sym_glEnable(GL_DEPTH_TEST);
			else
				_sym_glDisable(GL_DEPTH_TEST);
		}
		STATE_COMPARE(gl_dither[0])
		{
			if (newctx->gl_dither[0])
				_sym_glEnable(GL_DITHER);
			else
				_sym_glDisable(GL_DITHER);
		}
	}

	// _enable_flag2
	flag = oldctx->_enable_flag2 | newctx->_enable_flag2;
	if (flag)
	{
		STATE_COMPARE(gl_polygon_offset_fill[0])
		{
			if (newctx->gl_polygon_offset_fill[0])
				_sym_glEnable(GL_POLYGON_OFFSET_FILL);
			else
				_sym_glDisable(GL_POLYGON_OFFSET_FILL);
		}
		STATE_COMPARE(gl_sample_alpha_to_coverage[0])
		{
			if (newctx->gl_sample_alpha_to_coverage[0])
				_sym_glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
			else
				_sym_glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		}
		STATE_COMPARE(gl_sample_coverage[0])
		{
			if (newctx->gl_sample_coverage[0])
				_sym_glEnable(GL_SAMPLE_COVERAGE);
			else
				_sym_glDisable(GL_SAMPLE_COVERAGE);
		}
		STATE_COMPARE(gl_scissor_test[0])
		{
			if (newctx->gl_scissor_test[0])
				_sym_glEnable(GL_SCISSOR_TEST);
			else
				_sym_glDisable(GL_SCISSOR_TEST);
		}
		STATE_COMPARE(gl_stencil_test[0])
		{
			if (newctx->gl_stencil_test[0])
				_sym_glEnable(GL_STENCIL_TEST);
			else
				_sym_glDisable(GL_STENCIL_TEST);
		}
	}

	_COREGL_TRACE_API_END("eglMakeCurrent(FP enable states)", trace_hint_enable_states, 0);

	//------------------//
	// _clear_flag1
	static void *trace_hint_clear_viewport = NULL;
	trace_hint_clear_viewport = _COREGL_TRACE_API_BEGIN("eglMakeCurrent(FP clear/viewport)", trace_hint_clear_viewport, 0);

	flag = oldctx->_clear_flag1 | newctx->_clear_flag1;
	if (flag)
	{
		// Viewport.
		STATES_COMPARE(gl_viewport, 4 * sizeof(GLint))
		{
			_sym_glViewport(newctx->gl_viewport[0],
			                newctx->gl_viewport[1],
			                newctx->gl_viewport[2],
			                newctx->gl_viewport[3]);
		}

		STATE_COMPARE(gl_current_program[0])
		{
			_sym_glUseProgram(newctx->gl_current_program[0]);
		}
		STATES_COMPARE(gl_color_clear_value, 4 * sizeof(GLclampf))
		{
			_sym_glClearColor(newctx->gl_color_clear_value[0],
			                  newctx->gl_color_clear_value[1],
			                  newctx->gl_color_clear_value[2],
			                  newctx->gl_color_clear_value[3]);
		}
	}


	// _clear_flag2
	flag = oldctx->_clear_flag2 | newctx->_clear_flag2;
	if (flag)
	{
		STATES_COMPARE(gl_color_writemask, 4 * sizeof(GLboolean))
		{
			_sym_glColorMask(newctx->gl_color_writemask[0],
			                 newctx->gl_color_writemask[1],
			                 newctx->gl_color_writemask[2],
			                 newctx->gl_color_writemask[3]);
		}
		STATES_COMPARE(gl_depth_range, 2 * sizeof(GLclampf))
		{
			_sym_glDepthRangef(newctx->gl_depth_range[0],
			                   newctx->gl_depth_range[1]);
		}
		STATE_COMPARE(gl_depth_clear_value[0])
		{
			_sym_glClearDepthf(newctx->gl_depth_clear_value[0]);
		}
		STATE_COMPARE(gl_depth_func[0])
		{
			_sym_glDepthFunc(newctx->gl_depth_func[0]);
		}
		STATE_COMPARE(gl_depth_writemask[0])
		{
			_sym_glDepthMask(newctx->gl_depth_writemask[0]);
		}
		STATE_COMPARE(gl_cull_face_mode[0])
		{
			_sym_glCullFace(newctx->gl_cull_face_mode[0]);
		}

	}

	_COREGL_TRACE_API_END("eglMakeCurrent(FP clear/viewport)", trace_hint_clear_viewport, 0);

	//------------------//
	// Texture here...
	static void *trace_hint_bind_textures = NULL;
	trace_hint_bind_textures = _COREGL_TRACE_API_BEGIN("eglMakeCurrent(FP bind textures)", trace_hint_bind_textures, 0);

	flag = oldctx->_tex_flag1 | newctx->_tex_flag1;
	if (flag)
	{

		for (i = 0; i < oldctx->gl_num_tex_units[0]; i++)
		{
			STATE_COMPARE(gl_tex_2d_state[i])
			{
				_sym_glActiveTexture(GL_TEXTURE0 + i);
				_sym_glBindTexture(GL_TEXTURE_2D, newctx->gl_tex_2d_state[i]);
			}

			STATE_COMPARE(gl_tex_cube_state[i])
			{
				_sym_glActiveTexture(GL_TEXTURE0 + i);
				_sym_glBindTexture(GL_TEXTURE_CUBE_MAP, newctx->gl_tex_cube_state[i]);
			}
		}

		// Restore active texture
		_sym_glActiveTexture(newctx->gl_active_texture[0]);

		STATE_COMPARE(gl_generate_mipmap_hint[0])
		{
			_sym_glHint(GL_GENERATE_MIPMAP_HINT, newctx->gl_generate_mipmap_hint[0]);
		}
	}
	_COREGL_TRACE_API_END("eglMakeCurrent(FP bind textures)", trace_hint_bind_textures, 0);

	//------------------//
	static void *trace_hint_etc = NULL;
	trace_hint_etc = _COREGL_TRACE_API_BEGIN("eglMakeCurrent(FP etc.)", trace_hint_etc, 0);

	flag = oldctx->_blend_flag | newctx->_blend_flag;
	if (flag)
	{
		STATES_COMPARE(gl_blend_color, 4 * sizeof(GLclampf))
		{
			_sym_glBlendColor(newctx->gl_blend_color[0],
			                  newctx->gl_blend_color[1],
			                  newctx->gl_blend_color[2],
			                  newctx->gl_blend_color[3]);
		}
		if ((oldctx->gl_blend_src_rgb[0] != newctx->gl_blend_src_rgb[0]) ||
		    (oldctx->gl_blend_dst_rgb[0] != newctx->gl_blend_dst_rgb[0]) ||
		    (oldctx->gl_blend_src_alpha[0] != newctx->gl_blend_src_alpha[0]) ||
		    (oldctx->gl_blend_dst_alpha[0] != newctx->gl_blend_dst_alpha[0]))
		{
			_sym_glBlendFuncSeparate(newctx->gl_blend_src_rgb[0],
			                         newctx->gl_blend_dst_rgb[0],
			                         newctx->gl_blend_src_alpha[0],
			                         newctx->gl_blend_dst_alpha[0]);
		}
		if ((oldctx->gl_blend_equation_rgb[0] != newctx->gl_blend_equation_rgb[0]) ||
		    (oldctx->gl_blend_equation_alpha[0] != newctx->gl_blend_equation_alpha[0]))
		{
			_sym_glBlendEquationSeparate(newctx->gl_blend_equation_rgb[0], newctx->gl_blend_equation_alpha[0]);
		}

	}

	//------------------//
	// _stencil_flag1
	flag = oldctx->_stencil_flag1 | newctx->_stencil_flag1;
	if (flag)
	{
		if ((oldctx->gl_stencil_func[0] != newctx->gl_stencil_func[0]) ||
		    (oldctx->gl_stencil_ref[0]  != newctx->gl_stencil_ref[0])  ||
		    (oldctx->gl_stencil_value_mask[0] != newctx->gl_stencil_value_mask[0]))
		{
			_sym_glStencilFuncSeparate(GL_FRONT,
			                           newctx->gl_stencil_func[0],
			                           newctx->gl_stencil_ref[0],
			                           newctx->gl_stencil_value_mask[0]);
		}
		if ((oldctx->gl_stencil_fail[0] != newctx->gl_stencil_fail[0]) ||
		    (oldctx->gl_stencil_pass_depth_fail[0] != newctx->gl_stencil_pass_depth_fail[0]) ||
		    (oldctx->gl_stencil_pass_depth_pass[0] != newctx->gl_stencil_pass_depth_pass[0]))
		{
			_sym_glStencilOpSeparate(GL_FRONT,
			                         newctx->gl_stencil_fail[0],
			                         newctx->gl_stencil_pass_depth_fail[0],
			                         newctx->gl_stencil_pass_depth_pass[0]);
		}

		STATE_COMPARE(gl_stencil_writemask[0])
		{
			_sym_glStencilMaskSeparate(GL_FRONT, newctx->gl_stencil_writemask[0]);
		}
	}


	// _stencil_flag1
	flag = oldctx->_stencil_flag2 | newctx->_stencil_flag2;
	if (flag)
	{
		if ((oldctx->gl_stencil_back_func[0] != newctx->gl_stencil_back_func[0]) ||
		    (oldctx->gl_stencil_back_ref[0]  != newctx->gl_stencil_back_ref[0])  ||
		    (oldctx->gl_stencil_back_value_mask[0] != newctx->gl_stencil_back_value_mask[0]))
		{
			_sym_glStencilFuncSeparate(GL_BACK,
			                           newctx->gl_stencil_back_func[0],
			                           newctx->gl_stencil_back_ref[0],
			                           newctx->gl_stencil_back_value_mask[0]);
		}
		if ((oldctx->gl_stencil_back_fail[0] != newctx->gl_stencil_back_fail[0]) ||
		    (oldctx->gl_stencil_back_pass_depth_fail[0] != newctx->gl_stencil_back_pass_depth_fail[0]) ||
		    (oldctx->gl_stencil_back_pass_depth_pass[0] != newctx->gl_stencil_back_pass_depth_pass[0]))
		{
			_sym_glStencilOpSeparate(GL_BACK,
			                         newctx->gl_stencil_back_fail[0],
			                         newctx->gl_stencil_back_pass_depth_fail[0],
			                         newctx->gl_stencil_back_pass_depth_pass[0]);
		}

		STATE_COMPARE(gl_stencil_back_writemask[0])
		{
			_sym_glStencilMaskSeparate(GL_BACK, newctx->gl_stencil_back_writemask[0]);
		}
		STATE_COMPARE(gl_stencil_clear_value[0])
		{
			_sym_glClearStencil(newctx->gl_stencil_clear_value[0]);
		}
	}

	//------------------//
	// _misc_flag1
	flag = oldctx->_misc_flag1 | newctx->_misc_flag1;
	if (flag)
	{
		STATE_COMPARE(gl_front_face[0])
		{
			_sym_glFrontFace(newctx->gl_front_face[0]);
		}
		STATE_COMPARE(gl_line_width[0])
		{
			_sym_glLineWidth(newctx->gl_line_width[0]);
		}
		if ((oldctx->gl_polygon_offset_factor[0] != newctx->gl_polygon_offset_factor[0]) ||
		    (oldctx->gl_polygon_offset_units[0]  != newctx->gl_polygon_offset_units[0]))
		{
			_sym_glPolygonOffset(newctx->gl_polygon_offset_factor[0],
			                     newctx->gl_polygon_offset_units[0]);
		}
		if ((oldctx->gl_sample_coverage_value[0]  != newctx->gl_sample_coverage_value[0]) ||
		    (oldctx->gl_sample_coverage_invert[0] != newctx->gl_sample_coverage_invert[0]))
		{
			_sym_glSampleCoverage(newctx->gl_sample_coverage_value[0],
			                      newctx->gl_sample_coverage_invert[0]);
		}
	}

	// _misc_flag2
	flag = oldctx->_misc_flag2 | newctx->_misc_flag2;
	if (flag)
	{
		STATES_COMPARE(gl_scissor_box, 4 * sizeof(GLint))
		{
			_sym_glScissor(newctx->gl_scissor_box[0],
			               newctx->gl_scissor_box[1],
			               newctx->gl_scissor_box[2],
			               newctx->gl_scissor_box[3]);
		}
		STATE_COMPARE(gl_pack_alignment[0])
		{
			_sym_glPixelStorei(GL_PACK_ALIGNMENT, newctx->gl_pack_alignment[0]);
		}
		STATE_COMPARE(gl_unpack_alignment[0])
		{
			_sym_glPixelStorei(GL_UNPACK_ALIGNMENT, newctx->gl_unpack_alignment[0]);
		}
	}
	_COREGL_TRACE_API_END("eglMakeCurrent(FP etc.)", trace_hint_etc, 0);

	// _varray_flag
	static void *trace_hint_vertex_attrib = NULL;
	trace_hint_vertex_attrib = _COREGL_TRACE_API_BEGIN("eglMakeCurrent(FP vertex attrib)", trace_hint_vertex_attrib, 0);
	flag = oldctx->_vattrib_flag | newctx->_vattrib_flag;
	if (flag)
	{
		for (i = 0; i < oldctx->gl_num_vertex_attribs[0]; i++)
		{
			if (newctx->gl_vertex_array_buf_id[i] != oldctx->gl_vertex_array_buf_id[i])
			{
				_sym_glBindBuffer(GL_ARRAY_BUFFER, newctx->gl_vertex_array_buf_id[i]);
			}
			else _sym_glBindBuffer(GL_ARRAY_BUFFER, 0);

			_sym_glVertexAttribPointer(i,
			                           newctx->gl_vertex_array_size[i],
			                           newctx->gl_vertex_array_type[i],
			                           newctx->gl_vertex_array_normalized[i],
			                           newctx->gl_vertex_array_stride[i],
			                           newctx->gl_vertex_array_pointer[i]);

			STATES_COMPARE(gl_vertex_attrib_value + 4 * i, 4 * sizeof(GLfloat))
			{
				_sym_glVertexAttrib4fv(i, &newctx->gl_vertex_attrib_value[4 * i]);
			}

			if (newctx->gl_vertex_array_enabled[i] == GL_TRUE)
			{
				_sym_glEnableVertexAttribArray(i);
			}
			else
			{
				_sym_glDisableVertexAttribArray(i);
			}
		}

		STATE_COMPARE(gl_array_buffer_binding[0])
		{
			_sym_glBindBuffer(GL_ARRAY_BUFFER, newctx->gl_array_buffer_binding[0]);
		}
		STATE_COMPARE(gl_element_array_buffer_binding[0])
		{
			_sym_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newctx->gl_element_array_buffer_binding[0]);
		}

	}

	_COREGL_TRACE_API_END("eglMakeCurrent(FP vertex attrib)", trace_hint_vertex_attrib, 0);
	goto finish;

finish:

#ifdef COREGL_TRACE_STATE_INFO
	if (unlikely(trace_state_flag == 1))
		dump_context_states(newctx, 0);
#endif // COREGL_TRACE_STATE_INFO
	return;
#undef STATE_COMPARE
#undef STATES_COMPARE
}

