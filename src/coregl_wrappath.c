#include "coregl_wrappath.h"

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct _GLGlueFakeContext
{
	GLuint gl_num_tex_units[1];
	GLuint gl_num_vertex_attribs[1];
} GLGlueFakeContext;

GLGlueFakeContext initial_fake_ctx_real;
GLGlueFakeContext *initial_fake_ctx = &initial_fake_ctx_real;


static void
_get_texture_states(GLenum pname, GLint *params)
{
	GLuint cur_active_tex = 0;

	AST(initial_fake_ctx != NULL);

	_sym_glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint *)&cur_active_tex);
	int i;
	for (i = 0; i < initial_fake_ctx->gl_num_tex_units[0]; i++)
	{
		_sym_glActiveTexture(GL_TEXTURE0 + i);
		_sym_glGetIntegerv(pname, &(((GLint *)params)[i]));
	}
	_sym_glActiveTexture(cur_active_tex);
}

void
init_wrap_gl()
{
}

void
free_wrap_gl()
{
}

void
dump_wrap_context_states(int force_output)
{
	static struct timeval tv_last = { 0, 0 };

	if (unlikely(trace_state_flag != 1)) return;

	_sym_glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, (GLint *)initial_fake_ctx->gl_num_tex_units);
	_sym_glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, (GLint *)initial_fake_ctx->gl_num_vertex_attribs);

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
	TRACE("\E[0;40;34m===================================================================================================================\E[0m\n");
	TRACE("\E[0;32;1m  State info \E[1;37;1m: (CURRENT BINDED CONTEXT)\E[0m\n");
	TRACE("\E[0;40;34m===================================================================================================================\E[0m\n");

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

#define INITIAL_CTX initial_fake_ctx

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
         TRACE("["PRINTF_CHAR(TYPE)"]", value[i]); \
      } \
      TRACE(" \E[0;37;1m)\E[0m\n"); \
   }
# include "coregl_fastpath_state.h"
#undef GLUE_STATE

	TRACE("\E[0;40;34m===================================================================================================================\E[0m\n");
	TRACE("\n");

	TRACE_END();

finish:
	return;
}

