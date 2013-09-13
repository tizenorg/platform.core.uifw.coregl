#ifndef COREGL_FASTPATH_H
#define COREGL_FASTPATH_H

#include "../coregl_module.h"

#ifndef COREGL_USE_MODULE_FASTPATH
#error "COREGL_USE_MODULE_FASTPATH must defined!!!"
#endif

#define MY_MODULE_ID              COREGL_MODULE_FASTPATH
#define MY_MODULE_TSTATE         Fastpath_ThreadState

#include "../../coregl_internal.h"
#include "../../coregl_export.h"

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (*_orig_fastpath_##FUNC_NAME) PARAM_LIST;
# include "../../headers/sym.h"
#undef _COREGL_SYMBOL

// Symbol definition for fastpath
#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     extern RET_TYPE (fastpath_##FUNC_NAME) PARAM_LIST;
# include "../../headers/sym.h"
#undef _COREGL_SYMBOL

#define COREGL_FASTPATH_TRACE_ALL

#ifdef COREGL_FASTPATH_TRACE_ALL
#define COREGL_FASTPATH_TRACE_CONTEXT_INFO   // Context state & thread state & Glue-context info
#define COREGL_FASTPATH_TRACE_STATE_INFO     // Glue-context state info
#endif


#define _COREGL_FASTPATH_FUNC_BEGIN()

#define _COREGL_FASTPATH_FUNC_END()


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

typedef enum _Fastpath_Opt_Flag
{
    FP_UNKNOWN_PATH,
    FP_NORMAL_PATH,
    FP_FAST_PATH
} Fastpath_Opt_Flag;

extern Fastpath_Opt_Flag   fp_opt;
extern int                 debug_nofp;

typedef struct _GLContextState
{
	int                      ref_count;
	GLContext               *rctx;
	GLDisplay               *rdpy;
	void                    *data;
} GLContextState;

typedef struct _Fastpath_ThreadState
{
	EGLenum                  binded_api;
	GLContextState          *cstate;
	GLSurface               *rsurf_draw;
	GLSurface               *rsurf_read;
} Fastpath_ThreadState;

typedef struct _GLContext_List
{
	void                    *option;
	int                      option_len;
	int                      thread_id;
	GLContextState          *cstate;
	struct _GLContext_List *next;
} GLContext_List;

extern GLContext_List      *glctx_list;

extern Mutex                ctx_list_access_mutex;

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
#define GL_OBJECT_HASH_BASE        (1 << 10)

#define GL_OBJECT_ID_LIMIT         0xFFFFFF

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
	GLint                             ref_count;
	GLvoid                            *tag;

	struct _GL_Shared_Object_State  *parent;
} GL_Object;

typedef struct _GL_Object_Hash
{
	GLuint                           hash_key;
	GL_Object                        *item;
	struct _GL_Object_Hash          *next;
} GL_Object_Hash;

typedef struct _GL_Object_Hash_Base
{
	GLuint                            hash_size;
	GLuint                            item_size;
	GLuint                            last_id;
	GLuint                            is_looped;
	GL_Object_Hash                  **hash_field;
} GL_Object_Hash_Base;

typedef struct _GL_Shared_Object_State
{
	int                      ref_count;
	General_Trace_List      *using_gctxs;

	GL_Object_Hash_Base      texture;
	GL_Object_Hash_Base      buffer;
	GL_Object_Hash_Base      framebuffer;
	GL_Object_Hash_Base      renderbuffer;
	GL_Object_Hash_Base      program;

	GL_Object_Hash_Base      texture_real;
	GL_Object_Hash_Base      buffer_real;
	GL_Object_Hash_Base      framebuffer_real;
	GL_Object_Hash_Base      renderbuffer_real;
	GL_Object_Hash_Base      program_real;
} GL_Shared_Object_State;

typedef struct _GLGlueContext
{
	int                     magic;
	int                     initialized;
	int                     surface_attached;

	int							ref_count;
	int							is_destroyed;

	double                  glversion;

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

typedef struct _GLGlueContext_List
{
	GLGlueContext              *gctx;
	struct _GLGlueContext_List *prev;
	struct _GLGlueContext_List *next;
} GLGlueContext_List;

extern GLGlueContext_List *gctx_list;

extern GLGlueContext *initial_ctx;

extern void                init_modules_fastpath();
extern void                deinit_modules_fastpath();
extern void                init_modules_tstate_fastpath(GLThreadState *tstate);
extern void                deinit_modules_tstate_fastpath(GLThreadState *tstate);

extern void                fastpath_apply_overrides();
extern void                fastpath_apply_overrides_egl(int enable);
extern void                fastpath_apply_overrides_gl(int enable);

extern int                 fastpath_init_context_states(GLGlueContext *ctx);
extern int                 fastpath_make_context_current(GLGlueContext *oldctx, GLGlueContext *newctx);

#ifdef COREGL_FASTPATH_TRACE_STATE_INFO
extern void                fastpath_dump_context_states(GLGlueContext *ctx, int force_output);
#endif // COREGL_FASTPATH_TRACE_STATE_INFO

// Context state functions
extern int                 fastpath_add_context_state_to_list(const void *data, const int datalen, GLContextState *cstate, Mutex *mtx);
extern int                 fastpath_remove_context_states_from_list(GLContextState *cstate, Mutex *mtx);
extern GLContextState     *fastpath_get_context_state_from_list(const void *data, const int datalen, Mutex *mtx);

// Shared object state functions
extern void                fastpath_sostate_init(GL_Shared_Object_State *sostate);
extern void                fastpath_sostate_deinit(GL_Shared_Object_State *sostate);
extern GLuint              fastpath_sostate_create_object(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint name);
extern GLuint              fastpath_sostate_remove_object(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint glue_name);
extern GLuint              fastpath_sostate_get_object(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint name);
extern GLuint              fastpath_sostate_find_object(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint real_name);
extern GLint               fastpath_sostate_use_object(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint glue_name);
extern GLint               fastpath_sostate_set_object_tag(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint glue_name, GLvoid *tag);
extern GLvoid             *fastpath_sostate_get_object_tag(GL_Shared_Object_State *sostate, GL_Object_Type type, GLuint glue_name);

// GL context management functions
extern void                fastpath_release_gl_context(GLGlueContext *gctx);

#endif // COREGL_FASTPATH_H

