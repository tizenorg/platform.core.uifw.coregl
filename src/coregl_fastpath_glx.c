#include "coregl_internal.h"
#include "coregl_fastpath.h"

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define INIT_FAST_GLX_FUNC() \
   LOG("WARNING : GLX fastpath is not implemented!!!!\n");

#ifdef COREGL_FASTPATH_TRACE_CONTEXT_INFO

typedef struct _General_Trace_List
{
	void                          *value;
	struct _General_Trace_List    *next;
} General_Trace_List;

General_Trace_List *glue_ctx_trace_list = NULL;
General_Trace_List *thread_trace_list = NULL;
Mutex               general_trace_lists_access_mutex = MUTEX_INITIALIZER;

static int
_add_to_general_trace_list(General_Trace_List **gtl, void *value)
{
	int ret = 0;
	General_Trace_List *newitm = NULL;

	AST(mutex_lock(&general_trace_lists_access_mutex) == 1);

	newitm = (General_Trace_List *)calloc(1, sizeof(General_Trace_List));
	newitm->value = value;
	newitm->next = *gtl;
	*gtl = newitm;
	ret = 1;
	goto finish;

finish:
	AST(mutex_unlock(&general_trace_lists_access_mutex) == 1);
	return ret;
}

static int
_remove_from_general_trace_list(General_Trace_List **gtl, void *value)
{
	int ret = 0;
	General_Trace_List *current = NULL;
	General_Trace_List *priv = NULL;

	AST(mutex_lock(&general_trace_lists_access_mutex) == 1);

	current = *gtl;

	while(current != NULL)
	{
		if (current->value == value)
		{
			if (priv == NULL)
				*gtl = current->next;
			else
				priv->next = current->next;

			free(current);
			ret = 1;
			goto finish;
		}
		priv = current;
		current = current->next;
	}
	goto finish;

finish:
	AST(mutex_unlock(&general_trace_lists_access_mutex) == 1);

	return ret;
}

static void
_dump_context_info(const char *ment, int force_output)
{
	GLThreadState *tstate = NULL;
	static struct timeval tv_last = { 0, 0 };

	AST(mutex_lock(&ctx_list_access_mutex) == 1);
	AST(mutex_lock(&general_trace_lists_access_mutex) == 1);

	if (!force_output)
	{
		struct timeval tv_now = { 0, 0 };
		AST(gettimeofday(&tv_now, NULL) == 0);
		if (tv_now.tv_sec - tv_last.tv_sec < 5)
		{
			goto finish;
		}
		tv_last = tv_now;
	}

	tstate = get_current_thread_state();

	LOG("\n");
	LOG("\E[0;40;34m===================================================================================================================\E[0m\n");
	LOG("\E[0;32;1m  Context info \E[1;37;1m: %s\E[0m\n", ment);
	LOG("\E[0;40;34m===================================================================================================================\E[0m\n");

	// Context State List
	{
		GLContextState *cstate = NULL;
		void *iter = NULL;

		iter = traverse_context_state_from_list(NULL, &cstate);
		while (cstate != NULL)
		{

			LOG("   RealCTX [%12p] : EGLDPY=[%12p] EGLCTX=[%12p] GlueCTX=[%12p] <[%2d] GlueCTXs>\E[0m\n",
			    cstate,
			    cstate->rdpy,
			    cstate->rctx,
			    cstate->data,
			    cstate->ref_count);

			if (iter == NULL) break;
			iter = traverse_context_state_from_list(iter, &cstate);
		}

	}

	LOG("\E[0;40;33m...................................................................................................................\E[0m\n");

	// Glue Context List
	{
		General_Trace_List *current = NULL;
		current = glue_ctx_trace_list;

		while(current != NULL)
		{
			GLGlueContext *cur_gctx = (GLGlueContext *)current->value;

			LOG(" %c GlueCTX [%12p] : EGLDPY=[%12p] TID=[%12d]",
			    (cur_gctx->cstate != NULL && cur_gctx->cstate->data == cur_gctx) ? '*' : ' ',
			    cur_gctx,
			    cur_gctx->rdpy,
			    cur_gctx->thread_id);

			if (cur_gctx->cstate != NULL)
			{
				LOG(" RealCTX=[%12p]\n",
				    cur_gctx->cstate);
			}
			else
			{
				LOG(" (NOT BINDED)        \E[0m\n");
			}

			current = current->next;
		}
	}

	LOG("\E[0;40;33m...................................................................................................................\E[0m\n");

	// Thread State List
	{
		General_Trace_List *current = NULL;
		current = thread_trace_list;

		while(current != NULL)
		{
			GLThreadState *cur_tstate = (GLThreadState *)current->value;

			LOG(" %c Thread  [%12d] : Surf <D=[%12p] R=[%12p]>",
			    (tstate == cur_tstate) ? '*' : ' ',
			    cur_tstate->thread_id,
			    cur_tstate->rsurf_draw,
			    cur_tstate->rsurf_read);

			if (cur_tstate->cstate != NULL)
			{
				LOG(" GlueCTX=[%12p] RealCTX=[%12p]\E[0m\n",
				    cur_tstate->cstate->data,
				    cur_tstate->cstate);
			}
			else
			{
				LOG(" (NOT BINDED TO THREAD)\E[0m\n");
			}

			current = current->next;
		}
	}

	LOG("\E[0;40;34m===================================================================================================================\E[0m\n");
	LOG("\n");

	goto finish;

finish:

	AST(mutex_unlock(&general_trace_lists_access_mutex) == 1);
	AST(mutex_unlock(&ctx_list_access_mutex) == 1);

}

#endif // COREGL_FASTPATH_TRACE_CONTEXT_INFO


typedef struct
{
	EGLint                        context_client_version;
} EGL_packed_attrib_list;

typedef struct
{
	EGLDisplay                    dpy;
	EGLConfig                     cfg;
	EGL_packed_attrib_list        attrib_list;
} EGL_packed_option;

typedef struct
{
	EGLContext                    share_context;
} EGL_packed_sharable_option;


static int
_pack_egl_context_option(EGL_packed_option *pack_data, EGLDisplay dpy, EGLConfig cfg, const EGLint *attrib_list)
{
	int ret = 0;

	pack_data->dpy = dpy;
	pack_data->cfg = cfg;

	// Default context attributes
	pack_data->attrib_list.context_client_version = EGL_DONT_CARE;

	// Apply specified attributes
	EGLint *attrib = (EGLint *)attrib_list;
	while(attrib[0] != EGL_NONE)
	{
		switch(attrib[0])
		{
			case EGL_CONTEXT_CLIENT_VERSION:
				pack_data->attrib_list.context_client_version = attrib[1];
				break;
			default:
				ERR("Invalid context attribute.\n");
				goto finish;
			}
		attrib += 2;
	}
	ret = 1;
	goto finish;

finish:
	return ret;
}

static int
_unpack_egl_context_option(EGL_packed_option *pack_data, EGLDisplay *dpy, EGLConfig *cfg, EGLint *attrib_list, const int attrib_list_size)
{
	int ret = 0;

	AST(dpy != NULL);
	AST(cfg != NULL);
	AST(attrib_list != NULL);
	AST(attrib_list_size < 1);

	*dpy = pack_data->dpy;
	*cfg = pack_data->cfg;

	{
		int attrib_list_index = 0;

		memset(attrib_list, 0x00, sizeof(int) * attrib_list_size);

		if (pack_data->attrib_list.context_client_version != EGL_DONT_CARE)
		{
			AST(attrib_list_index + 2 < attrib_list_size);
			attrib_list[attrib_list_index] = EGL_CONTEXT_CLIENT_VERSION;
			attrib_list[attrib_list_index + 1] = pack_data->attrib_list.context_client_version;
			attrib_list_index += 2;
		}

		attrib_list[attrib_list_index] = EGL_NONE;
	}
	ret = 1;
	goto finish;

finish:
	return ret;
}

static int
_pack_egl_context_sharable_option(EGL_packed_sharable_option *pack_data, EGLContext share_context)
{
	int ret = 0;

	pack_data->share_context = share_context;

	ret = 1;
	goto finish;

finish:
	return ret;
}

static int
_unpack_egl_context_sharable_option(EGL_packed_sharable_option *pack_data, EGLContext *share_context)
{
	int ret = 0;

	*share_context = pack_data->share_context;

	ret = 1;
	goto finish;

finish:
	return ret;
}

static void
_link_context_state(GLContextState *cstate, GLGlueContext *gctx)
{
	cstate->ref_count++;
}

static void
_unlink_context_state(GLContextState *cstate, GLGlueContext *gctx)
{
	cstate->ref_count--;
	if (cstate->ref_count == 0)
	{
		GLThreadState *tstate = NULL;

		AST(remove_context_state_from_list(cstate) == 1);

		tstate = get_current_thread_state();
		if (tstate != NULL)
		{
			if (tstate->cstate == cstate)
			{
				_sym_glXMakeCurrent(gctx->rdpy, tstate->rsurf_draw, NULL);
				tstate->cstate = NULL;
			}
		}
		_sym_glXDestroyContext(gctx->rdpy, cstate->rctx);
		free(cstate);
		cstate = NULL;
	}
}





































//----------------------------------------------------------------//
//                   Fastpath GLX Functions                       //
//       The functions have prefix 'fpgl_' for (fastpath gl)      //
//----------------------------------------------------------------//
GLXContext
fpgl_glXCreateContext(Display* dpy, XVisualInfo* vis, GLXContext shareList, Bool direct)
{
	GLGlueContext *gctx = NULL;
	GLContextState *cstate = NULL;
	GLContextState *cstate_new = NULL;
	GLContext ctx = NULL;
	GLXContext real_share_context = NULL;

	EGL_packed_option *real_ctx_option = NULL;
	EGL_packed_sharable_option *real_ctx_sharable_option = NULL;

	_COREGL_FAST_FUNC_BEGIN();

	if (share_context != NULL)
	{
		GLGlueContext *share_gctx = NULL;
		share_gctx = (GLGlueContext *)share_context;
		if (share_gctx->cstate == NULL)
		{
			ERR("Invalid (not initialized) share context handle\n");
			goto finish;
		}
		real_share_context = share_gctx->cstate->rctx;
	}


	// Create a global context if it hasn't been created
	if (cstate == NULL)
	{
		// Create a global context if it hasn't been created yet
		ctx = _sym_glXCreateContext(dpy, vis, real_share_context, 1);
		if (ctx == NULL)
		{
			ERR("Failed creating a glx global context for Fastpath.\n");
			goto finish;
		}

		cstate_new = (GLContextState *)calloc(1, sizeof(GLContextState));
		if (cstate_new == NULL)
		{
			ERR("Error creating a new context state.\n");
			goto finish;
		}
		cstate_new->rctx = ctx;
		cstate_new->rdpy = dpy;
		cstate_new->data = NULL;

		ctx = NULL;

		AST(add_context_state_to_list(real_ctx_option, sizeof(EGL_packed_option), cstate_new) == 1);

		cstate = cstate_new;
	}

	// Allocate a new context
	gctx = (GLGlueContext *)calloc(1, sizeof(GLGlueContext));
	if (gctx == NULL)
	{
		ERR("Error creating a new GLGlueContext.\n");
		goto finish;
	}

	gctx->magic = MAGIC_GLFAST;
	gctx->initialized = 0;
	gctx->rdpy = dpy;
	gctx->thread_id = get_current_thread();

	gctx->real_ctx_option = real_ctx_option;
	gctx->real_ctx_option_len = sizeof(EGL_packed_option);
	gctx->real_ctx_sharable_option = real_ctx_sharable_option;
	gctx->real_ctx_sharable_option_len = sizeof(EGL_packed_sharable_option);

	gctx->cstate = cstate;

	_add_to_general_trace_list(&glue_ctx_trace_list, gctx);

	cstate->ref_count++;

#ifdef COREGL_FASTPATH_TRACE_CONTEXT_INFO
	{
		char ment[256];
		sprintf(ment, "eglCreateContext completed (GlueCTX=[%12p])", gctx);
		_dump_context_info(ment, 1);
	}
#endif // COREGL_FASTPATH_TRACE_CONTEXT_INFO

	goto finish;

finish:
	if (gctx == NULL)
	{
		if (ctx != NULL)
		{
			_sym_eglDestroyContext(dpy, ctx);
			ctx = NULL;
		}
		if (real_ctx_option != NULL)
		{
			free(real_ctx_option);
			real_ctx_option = NULL;
		}
		if (real_ctx_sharable_option != NULL)
		{
			free(real_ctx_sharable_option);
			real_ctx_sharable_option = NULL;
		}
		if (cstate_new != NULL)
		{
			remove_context_state_from_list(cstate_new);
			free(cstate_new);
			cstate_new = NULL;
		}
	}

	_COREGL_FAST_FUNC_END();
	return (GLXContext)gctx;
}



void
fpgl_glXDestroyContext(Display* dpy, GLXContext ctx)
{
	int ret = 0;
	GLGlueContext *gctx = NULL;

	_COREGL_FAST_FUNC_BEGIN();

	gctx = (GLGlueContext *)ctx;

	if (gctx != NULL)
	{
		GLContextState *cstate = NULL;
		if (gctx->magic != MAGIC_GLFAST)
		{
			ERR("Magic Check Failed!!!\n");
			ret = 0;
			goto finish;
		}
		cstate = gctx->cstate;
		AST(cstate != NULL);

		_unlink_context_state(cstate, gctx);

		_remove_from_general_trace_list(&glue_ctx_trace_list, gctx);

		if (gctx->real_ctx_option != NULL)
		{
			free(gctx->real_ctx_option);
			gctx->real_ctx_option = NULL;
		}
		if (gctx->real_ctx_sharable_option != NULL)
		{
			free(gctx->real_ctx_sharable_option);
			gctx->real_ctx_sharable_option = NULL;
		}
		free(gctx);
	}
	else
	{
		ERR("Invalid Context.\n");
		ret = 0;
		goto finish;
	}

#ifdef COREGL_FASTPATH_TRACE_CONTEXT_INFO
	{
		char ment[256];
		sprintf(ment, "eglDestroyContext completed (GlueCTX=[%12p])", ctx);
		_dump_context_info(ment, 1);
	}
#endif // COREGL_FASTPATH_TRACE_CONTEXT_INFO

	ret = 1;
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}









GLXContext
fpgl_glXGetCurrentContext(void)
{
	GLGlueContext *ret = NULL;
	GLThreadState *tstate = NULL;

	_COREGL_FAST_FUNC_BEGIN();

	tstate = get_current_thread_state();

	if (tstate != NULL)
	{
		if (tstate->cstate != NULL)
		{
			ret = (GLGlueContext *)tstate->cstate->data;
		}
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return (EGLContext)ret;
}


GLXDrawable
fpgl_glXGetCurrentDrawable(void)
{
	GLXDrawable ret = None;
	GLThreadState *tstate = NULL;

	_COREGL_FAST_FUNC_BEGIN();

	tstate = get_current_thread_state();

	if (tstate != NULL)
		ret = (GLGlueContext *)tstate->rsurf_draw;

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}

Bool
fpgl_glXMakeCurrent(Display* dpy, GLXDrawable draw, GLXContext ctx)
{
	Bool ret = False;
	Bool need_mc = False;
	GLGlueContext *gctx = NULL;

	GLThreadState *tstate = NULL;
	GLContextState *cstate = NULL;

	_COREGL_FAST_FUNC_BEGIN();

	gctx = (GLGlueContext *)ctx;

	tstate = get_current_thread_state();
	if (tstate == NULL)
	{
		// TODO : Move to Initialize
		tstate = (GLThreadState *)calloc(1, sizeof(GLThreadState));
		tstate->thread_id = get_current_thread();

		set_current_thread_state(&ctx_list_access_mutex, tstate);

		_add_to_general_trace_list(&thread_trace_list, tstate);

		tstate = get_current_thread_state();
		AST(tstate != NULL);
	}

	// Fast path for context deletion
	if (ctx == NULL)
	{
		AST(gctx == NULL);
		if (draw != None)
		{
			// BB : full makecurrent when draw/read is specified
			if (!_sym_glXMakeCurrent(dpy, draw, NULL))
			{
				ERR("Error making context current with the drawable.\n");
				ret = False;
				goto finish;
			}
			tstate->cstate = NULL;
		}

		tstate->rsurf_draw = draw;
		tstate->rsurf_read = draw;
		ret = True;
		goto finish;
	}

	AST(gctx != NULL);
	AST(gctx->cstate != NULL);

	if (gctx->rdpy != dpy)
	{
		ERR("Invalid context (or invalid Display)\n");
		ret = False;
		goto finish;
	}

	AST(gctx->real_ctx_option != NULL);
	AST(gctx->real_ctx_sharable_option != NULL);

	// Handle cross threading of context (when used by two or more gctx)
	if (gctx->thread_id != get_current_thread() && gctx->cstate->ref_count > 1)
	{
		GLContextState *cstate_new = NULL;
		GLXContext *new_real_ctx = NULL;

		// Create a new context
		{
#define ATTRIB_LIST_BUFFER_SIZE 8

			Display dpy = NULL;
			EGLConfig config = NULL;
			int attrib_list[ATTRIB_LIST_BUFFER_SIZE];
			GLXContext real_share_context = NULL;

			_unpack_egl_context_option(gctx->real_ctx_option, &dpy, &config, attrib_list, ATTRIB_LIST_BUFFER_SIZE);
			_unpack_egl_context_sharable_option(gctx->real_ctx_sharable_option, &real_share_context);

			AST(dpy == gctx->rdpy);

			new_real_ctx = _sym_glXCreateContext(dpy, config, real_share_context);
			if (new_real_ctx == NULL)
			{
				ERR("Failed creating a egl context.\n");
				goto finish;
			}
		}

		cstate_new = (GLContextState *)calloc(1, sizeof(GLContextState));
		if (cstate_new == NULL)
		{
			ERR("Error creating a new context state.\n");
			goto finish;
		}

		cstate_new->rctx = new_real_ctx;
		cstate_new->rdpy = gctx->rdpy;
		cstate_new->data = gctx;

		// TODO : Setup context state for new real ctx

		AST(add_context_state_to_list(gctx->real_ctx_option, gctx->real_ctx_option_len, cstate_new) == 1);

		_unlink_context_state(gctx->cstate, gctx);
		gctx->cstate = cstate_new;
		_link_context_state(gctx->cstate, gctx);

		// Apply to new thread
		gctx->thread_id = get_current_thread();

	}

	// Check if the object is correct
	if (gctx->magic != MAGIC_GLFAST)
	{
		ERR("Magic Check Failed!!!\n");
		ret = False;
		goto finish;

	}

	cstate = tstate->cstate;

	// If it's a first time or drawable changed, do a make current
	if (cstate == NULL)
	{
		cstate = get_context_state_from_list(gctx->real_ctx_option, gctx->real_ctx_option_len);

		if (cstate == NULL)
		{
			ERR("Error making context current because context not ready.\n");
			ret = False;
			goto finish;
		}
		need_mc = EGL_TRUE;
	}

	// If drawable changed, do a make current
	if ((tstate->rsurf_draw != draw) ||
	    (tstate->rsurf_read != read))
		need_mc = True;

	// If binded real context changed, do a make current
	if (gctx->cstate == NULL ||
	    gctx->cstate->rctx != cstate->rctx)
		need_mc = True;

	if (need_mc == True)
	{
		// BB : full makecurrent
		if (!_sym_glXMakeCurrent(dpy, draw, cstate->rctx))
		{
			ERR("Error making context current with the drawable.\n");
			ret = False;
			goto finish;
		}

		tstate->cstate = cstate;

		tstate->rsurf_draw = draw;
		tstate->rsurf_read = read;

		gctx->cstate = cstate;
	}

	// Initialize context states
	if (gctx->initialized == 0)
	{
		if (init_context_states(gctx) != 1)
		{
			ERR("Error intializing context\n");
			goto finish;
		}
		if (tstate->cstate->data == NULL)
			tstate->cstate->data = (void *)gctx;
	}

	AST(tstate->cstate->data != NULL);

	if (tstate->cstate->data != gctx)
	{
		// restore needed
		make_context_current((GLGlueContext *)tstate->cstate->data, gctx);
		tstate->cstate->data = (void *)gctx;
	}

	ret = True;
	goto finish;

finish:

#ifdef COREGL_FASTPATH_TRACE_CONTEXT_INFO
	{
		char ment[256];
		sprintf(ment, "eglMakeCurrent finished (GlueCTX=[%12p] Surf=[D:%12p R:%12p])", ctx, draw, read);
		_dump_context_info(ment, 0);
	}
#endif // COREGL_FASTPATH_TRACE_CONTEXT_INFO

	_COREGL_FAST_FUNC_END();
	return ret;
}












GLGlueContext ectx = (GLGlueContext)ctx;

_COREGL_FAST_FUNC_BEGIN();
INIT_FAST_GLX_FUNC();

// Check if the values are null
if ((draw == None) || (ctx == NULL))
{
	if (current_ctx)
		real_current_ctx = current_ctx;

	/*
	        if (!_sym_glXMakeCurrent(dpy, None, NULL))
	          {
	             ERR("Error making context current with the drawable.\n");
	             return False;
	          }
	          */

	current_ctx = NULL;
	current_surf = None;

	return 1;
}

// Check if the object is correct
if (ectx->magic != MAGIC_GLFAST)
{
	ERR("Magic Check Failed!!!\n");
	return 0;
}


// If it's the first time
if (!global_ctx_initted)
{
	if (!_sym_glXMakeCurrent(dpy, draw, global_ctx))
	{
		ERR("Error making context current with the drawable.\n");
		return False;
	}

	current_ctx  = ectx;
	current_surf = draw;

	real_current_ctx = current_ctx;

	global_ctx_initted = 1;
}


if (!current_ctx) current_ctx = real_current_ctx;

// If drawable changed, do a make current
if (current_surf != draw)
{
	if (!_sym_glXMakeCurrent(dpy, draw, global_ctx))
	{
		ERR("Error making context current with the drawable.\n");
		return False;
	}
	current_surf = draw;
}

// If it's first time...
if (ectx->first_time == 1)
{
	// FIXME!!!:
	// Actually, i need to query the drawable size...
	// Do some initializations that required make_current
	_sym_glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &ectx->num_tex_units);
	_sym_glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &ectx->num_vertex_attribs);
	_sym_glGetIntegerv(GL_VIEWPORT, ectx->gl_viewport);
	_sym_glGetIntegerv(GL_SCISSOR_BOX, ectx->gl_scissor_box);
	DBG("----Num Tex Units: %d, Num Vertex Attribs: %d \n", ectx->num_tex_units, ectx->num_vertex_attribs);

	ectx->first_time = 0;
}

// if context is same, return
if ((current_ctx == ectx) && (current_surf == draw))
{
	return True;
}

make_context_current(current_ctx, ectx);

current_ctx = ectx;
current_surf = draw;

return True;
goto finish;

finish:
_COREGL_FAST_FUNC_END();
}














//----------------------------------------------------------------//
//                   Fastpath GLX Functions                       //
//       The functions have prefix 'fpgl_' for (fastpath gl)      //
//----------------------------------------------------------------//
GLXContext
fpgl_glXCreateContext(Display* dpy, XVisualInfo* vis, GLXContext shareList, Bool direct)
{
	GLGlueContext ctx;

	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GLX_FUNC();

	// Create a global context if it hasn't been created
	if (!global_ctx)
	{
		global_dpy = dpy;
		// Create a global context if it hasn't been created yet
		global_ctx = _sym_glXCreateContext(dpy, vis, NULL, 1);
		if (!global_ctx)
		{
			ERR("Failed creating a glX global context for FastPath.\n");
			return 0;
		}
		ctx_ref_count++;
	}

	// Allocate a new context
	ctx = calloc(1, sizeof(struct _GLGlueContext));
	if (!ctx)
	{
		ERR("Error creating a new GLGlueContext.\n");
		return NULL;
	}

	if (!init_context_states(ctx))
	{
		ERR("Error intialing intial context\n");
		free(ctx);
		return NULL;
	}

	ctx_ref_count++;

	return (GLXContext)ctx;

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


void
fpgl_glXDestroyContext(Display* dpy, GLXContext ctx)
{
	GLGlueContext ectx = (GLGlueContext)ctx;

	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GLX_FUNC();

	if (ctx != NULL)
	{
		if (ectx->magic != MAGIC_GLFAST)
		{
			ERR("Magic Check Failed!!!\n");
			return;
		}

		if (ectx == current_ctx)
		{
			DBG("Destroying current context... %d\n", ctx_ref_count);
			real_current_ctx = current_ctx;
			current_ctx = NULL;
		}

		if (ectx)
			free(ectx);

		if (!(--ctx_ref_count))
		{
			DBG("Destroying the global context...\n");
			_sym_glXDestroyContext(dpy, global_ctx);
			global_ctx = NULL;
			current_ctx = NULL;
			real_current_ctx = NULL;
		}
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}



GLXContext
fpgl_glXGetCurrentContext(void)
{
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GLX_FUNC();

	return (GLXContext)current_ctx;
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


GLXDrawable
fpgl_glXGetCurrentDrawable(void)
{
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GLX_FUNC();

	//return _sym_glXGetCurrentDrawable();
	return (GLXDrawable)current_surf;
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}



Bool
fpgl_glXMakeCurrent(Display* dpy, GLXDrawable draw, GLXContext ctx)
{
	GLGlueContext ectx = (GLGlueContext)ctx;

	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GLX_FUNC();

	// Check if the values are null
	if ((draw == None) || (ctx == NULL))
	{
		if (current_ctx)
			real_current_ctx = current_ctx;

		/*
		if (!_sym_glXMakeCurrent(dpy, None, NULL))
		  {
		     ERR("Error making context current with the drawable.\n");
		     return False;
		  }
		  */

		current_ctx = NULL;
		current_surf = None;

		return 1;
	}

	// Check if the object is correct
	if (ectx->magic != MAGIC_GLFAST)
	{
		ERR("Magic Check Failed!!!\n");
		return 0;
	}


	// If it's the first time
	if (!global_ctx_initted)
	{
		if (!_sym_glXMakeCurrent(dpy, draw, global_ctx))
		{
			ERR("Error making context current with the drawable.\n");
			return False;
		}

		current_ctx  = ectx;
		current_surf = draw;

		real_current_ctx = current_ctx;

		global_ctx_initted = 1;
	}


	if (!current_ctx) current_ctx = real_current_ctx;

	// If drawable changed, do a make current
	if (current_surf != draw)
	{
		if (!_sym_glXMakeCurrent(dpy, draw, global_ctx))
		{
			ERR("Error making context current with the drawable.\n");
			return False;
		}
		current_surf = draw;
	}

	// If it's first time...
	if (ectx->first_time == 1)
	{
		// FIXME!!!:
		// Actually, i need to query the drawable size...
		// Do some initializations that required make_current
		_sym_glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &ectx->num_tex_units);
		_sym_glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &ectx->num_vertex_attribs);
		_sym_glGetIntegerv(GL_VIEWPORT, ectx->gl_viewport);
		_sym_glGetIntegerv(GL_SCISSOR_BOX, ectx->gl_scissor_box);
		DBG("----Num Tex Units: %d, Num Vertex Attribs: %d \n", ectx->num_tex_units, ectx->num_vertex_attribs);

		ectx->first_time = 0;
	}

	// if context is same, return
	if ((current_ctx == ectx) && (current_surf == draw))
	{
		return True;
	}

	make_context_current(current_ctx, ectx);

	current_ctx = ectx;
	current_surf = draw;

	return True;
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}


Bool
fpgl_glXMakeContextCurrent(Display* dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx)
{
	_COREGL_FAST_FUNC_BEGIN();
	INIT_FAST_GLX_FUNC();

	ERR("NOT IMPLEMENTED YET!!! GLX Function Wrapped. Not fastpathed yet...\n");
	return _sym_glXMakeContextCurrent(dpy, draw, read, ctx);
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
}

#endif

