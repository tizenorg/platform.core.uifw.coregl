#ifndef COREGL_FASTPATH_H
#define COREGL_FASTPATH_H

#include "coregl_internal.h"

// Symbol definition for fastpath
#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (fpgl_##FUNC_NAME) PARAM_LIST;
# include "headers/sym.h"
#undef _COREGL_SYMBOL

#define FLAG_BIT_0      0x01
#define FLAG_BIT_1      0x02
#define FLAG_BIT_2      0x04
#define FLAG_BIT_3      0x08
#define FLAG_BIT_4      0x10
#define FLAG_BIT_5      0x20
#define FLAG_BIT_6      0x40
#define FLAG_BIT_7      0x80

#define MAX_TEXTURE_UNITS 32
#define MAX_VERTEX_ATTRIBS 64

typedef struct
{
	GLuint   tex_id;
} GL_Texture_State;

typedef struct
{
	GLboolean    modified;
	GLboolean    enabled;
	GLuint       buf_id;
	GLint        size;
	GLenum       type;
	GLboolean    normalized;
	GLsizei      stride;
	const void  *pointer;
} GL_Vertex_Array_State;

typedef struct
{
	GLboolean   modified;
	GLfloat     value[4];
} GL_Vertex_Attrib;


#define MAGIC_GLFAST                0x73777770
#define MAX_GL_OBJECT_SIZE         100000

typedef enum
{
    GL_OBJECT_TYPE_UNKNOWN       = 0x0,
    GL_OBJECT_TYPE_TEXTURE       = 0x1000000,
    GL_OBJECT_TYPE_BUFFER        = 0x2000000,
    GL_OBJECT_TYPE_FRAMEBUFFER   = 0x3000000,
    GL_OBJECT_TYPE_RENDERBUFFER  = 0x4000000,
    GL_OBJECT_TYPE_PROGRAM       = 0x5000000,
} GL_Object_Type;

typedef struct _GL_Object
{
	GLuint                            id;
	GLuint                            real_id;

	struct _GL_Shared_Object_State  *parent;
} GL_Object;

typedef struct _GL_Shared_Object_State
{
	int                    ref_count;

	GL_Object              *texture[MAX_GL_OBJECT_SIZE];
	GL_Object              *buffer[MAX_GL_OBJECT_SIZE];
	GL_Object              *framebuffer[MAX_GL_OBJECT_SIZE];
	GL_Object              *renderbuffer[MAX_GL_OBJECT_SIZE];
	GL_Object              *program[MAX_GL_OBJECT_SIZE];
} GL_Shared_Object_State;

typedef struct _GLGlueContext
{
	int                     magic;
	int                     initialized;
	int                     surface_attached;

	int							ref_count;
	int							is_destroyed;

	int							used_count;

	GLDisplay              *rdpy;
	GLContextState         *cstate;
	int                     thread_id;

	void                   *real_ctx_option;
	int                     real_ctx_option_len;

	void                   *real_ctx_sharable_option;
	int                     real_ctx_sharable_option_len;

	unsigned char           _bind_flag;
	unsigned char           _enable_flag1;
	unsigned char           _enable_flag2;
	unsigned char           _clear_flag1;
	unsigned char           _clear_flag2;
	unsigned char           _tex_flag1;
	unsigned char           _blend_flag;
	unsigned char           _stencil_flag1;
	unsigned char           _stencil_flag2;
	unsigned char           _misc_flag1;
	unsigned char           _misc_flag2;
	unsigned char           _vattrib_flag;

	GL_Shared_Object_State *sostate;

	GLenum                  gl_error;

	// General state
#define GLUE_STATE(TYPE, NAME, SIZE, ARRAY_SIZE, DEFAULT_STMT, GET_STMT)     TYPE NAME[ARRAY_SIZE];
# include "coregl_fastpath_state.h"
#undef GLUE_STATE

} GLGlueContext;

extern GLGlueContext *initial_ctx;

extern int            debug_nofp;

extern void     init_fast_gl();
extern void     free_fast_gl();

extern int      init_context_states(GLGlueContext *ctx);
extern void     make_context_current(GLGlueContext *oldctx, GLGlueContext *newctx);

#ifdef COREGL_TRACE_STATE_INFO
extern void     dump_context_states(GLGlueContext *ctx, int force_output);
#endif

extern GLuint   sostate_create_object(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint name);
extern GLuint   sostate_remove_object(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint glue_name);
extern GLuint   sostate_get_object(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint name);
extern GLuint   sostate_find_object(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint real_name);


#endif // COREGL_FASTPATH_H

