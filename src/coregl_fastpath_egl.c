#include "coregl_fastpath.h"

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <execinfo.h>

#ifdef COREGL_TRACE_CONTEXT_INFO

General_Trace_List *glue_ctx_trace_list = NULL;
General_Trace_List *context_state_trace_list = NULL;

static void
_dump_context_info(const char *ment, int force_output)
{
	GLThreadState *tstate = NULL;
	static struct timeval tv_last = { 0, 0 };

	if (trace_ctx_flag != 1) return;

	AST(mutex_lock(&ctx_list_access_mutex) == 1);
	AST(mutex_lock(&general_trace_lists_access_mutex) == 1);

	if (!force_output && !trace_ctx_force_flag)
	{
		struct timeval tv_now = { 0, 0 };
		AST(gettimeofday(&tv_now, NULL) == 0);
		if (tv_now.tv_sec - tv_last.tv_sec < _COREGL_TRACE_OUTPUT_INTERVAL_SEC)
		{
			goto finish;
		}
		tv_last = tv_now;
	}

	tstate = get_current_thread_state();

	TRACE("\n");
	TRACE("\E[40;34m========================================================================================================================\E[0m\n");
	TRACE("\E[40;32;1m  Context info \E[1;37;1m: %s\E[0m\n", ment);
	TRACE("\E[40;34m========================================================================================================================\E[0m\n");


	// Thread State List
	{
		General_Trace_List *current = NULL;
		current = thread_trace_list;

		while (current != NULL)
		{
			GLThreadState *cur_tstate = (GLThreadState *)current->value;

			TRACE(" %c Thread  [%12d] : Surf <D=[%12p] R=[%12p]>",
			      (tstate == cur_tstate) ? '*' : ' ',
			      cur_tstate->thread_id,
			      cur_tstate->rsurf_draw,
			      cur_tstate->rsurf_read);

			if (cur_tstate->cstate != NULL)
			{
				TRACE(" GlueCTX=[%12p] RealCTX=[%12p]\E[0m\n",
				      cur_tstate->cstate->data,
				      cur_tstate->cstate);
			}
			else
			{
				TRACE(" (NOT BINDED TO THREAD)\E[0m\n");
			}

			// Binded Context State List
			{
				General_Trace_List *current = NULL;
				current = context_state_trace_list;

				while (current != NULL)
				{
					GLContextState *cur_cstate = (GLContextState *)current->value;

					if (cur_tstate->cstate == cur_cstate)
					{
						TRACE("   -> RealCTX [%12p] : EGLDPY=[%12p] EGLCTX=[%12p] <[%2d] GlueCTXs>\E[0m\n",
						      cur_cstate,
						      cur_cstate->rdpy,
						      cur_cstate->rctx,
						      cur_cstate->ref_count);

						// Binded Glue Context List
						{
							General_Trace_List *current = NULL;
							current = glue_ctx_trace_list;

							while (current != NULL)
							{
								GLGlueContext *cur_gctx = (GLGlueContext *)current->value;

								if (cur_gctx->cstate == cur_cstate)
								{
									TRACE("    -%c GlueCTX [%12p] : EGLDPY=[%12p] TID=[%12d] <MC count [%10d]>",
									      (cur_cstate->data == cur_gctx) ? '>' : '-',
									      cur_gctx,
									      cur_gctx->rdpy,
									      cur_gctx->thread_id,
									      cur_gctx->used_count);

									TRACE(" <Ref [%2d]>\E[0m\n", cur_gctx->ref_count);
								}

								current = current->next;
							}
						}
					}

					current = current->next;
				}

			}


			current = current->next;
		}
	}

	TRACE("\E[40;33m........................................................................................................................\E[0m\n");

	// Not-binded Context State List
	{
		General_Trace_List *current = NULL;
		current = context_state_trace_list;

		while (current != NULL)
		{
			GLContextState *cur_cstate = (GLContextState *)current->value;

			int isbinded = 0;

			if (cur_cstate->data != NULL)
			{
				General_Trace_List *current_t = NULL;
				current_t = thread_trace_list;

				while (current_t != NULL)
				{
					GLThreadState *cur_tstate = (GLThreadState *)current_t->value;

					if (cur_tstate->thread_id == ((GLGlueContext *)cur_cstate->data)->thread_id)
					{
						if (cur_tstate->cstate == cur_cstate)
							isbinded = 1;
						break;
					}
					current_t = current_t->next;
				}
			}

			if (isbinded == 0)
			{
				TRACE("   RealCTX   [%12p] : EGLDPY=[%12p] EGLCTX=[%12p] <[%2d] GlueCTXs>\E[0m\n",
				      cur_cstate,
				      cur_cstate->rdpy,
				      cur_cstate->rctx,
				      cur_cstate->ref_count);

				// Binded Glue Context List
				{
					General_Trace_List *current = NULL;
					current = glue_ctx_trace_list;

					while (current != NULL)
					{
						GLGlueContext *cur_gctx = (GLGlueContext *)current->value;

						if (cur_gctx->cstate == cur_cstate)
						{
							TRACE("    -%c GlueCTX [%12p] : EGLDPY=[%12p] TID=[%12d] <MC count [%10d]>",
							      (cur_cstate->data == cur_gctx) ? '>' : '-',
							      cur_gctx,
							      cur_gctx->rdpy,
							      cur_gctx->thread_id,
							      cur_gctx->used_count);

							TRACE(" <Ref [%2d]>\E[0m\n", cur_gctx->ref_count);
						}

						current = current->next;
					}
				}
			}

			current = current->next;
		}

	}

	TRACE("\E[40;33m........................................................................................................................\E[0m\n");

	// Not-binded Glue Context List
	{
		General_Trace_List *current = NULL;
		current = glue_ctx_trace_list;

		while (current != NULL)
		{
			GLGlueContext *cur_gctx = (GLGlueContext *)current->value;

			if (cur_gctx->cstate == NULL)
			{
				TRACE("   GlueCTX [%12p]   : EGLDPY=[%12p] TID=[%12d] <MC count [%10d]>",
				      cur_gctx,
				      cur_gctx->rdpy,
				      cur_gctx->thread_id,
				      cur_gctx->used_count);

				TRACE(" <Ref [%2d]>\E[0m\n", cur_gctx->ref_count);
			}

			current = current->next;
		}
	}

	TRACE("\E[40;34m========================================================================================================================\E[0m\n");
	TRACE("\n");

	TRACE_END();

	goto finish;

finish:

	AST(mutex_unlock(&general_trace_lists_access_mutex) == 1);
	AST(mutex_unlock(&ctx_list_access_mutex) == 1);

}

#endif // COREGL_TRACE_CONTEXT_INFO


typedef struct
{
	EGLint                        context_client_version;
} EGL_packed_attrib_list;

typedef struct
{
	EGLDisplay                    dpy;
	EGLConfig                     cfg;
	EGL_packed_attrib_list        attrib_list;
	EGLint								debug;
} EGL_packed_option;

typedef struct
{
	EGLContext                    share_context;
} EGL_packed_sharable_option;


static int
_pack_egl_context_option(EGL_packed_option *pack_data, EGLDisplay dpy, EGLConfig cfg, EGLint debug, const EGLint *attrib_list)
{
	int ret = 0;

	pack_data->dpy = dpy;
	pack_data->cfg = cfg;
	pack_data->debug = debug;

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
_unpack_egl_context_option(EGL_packed_option *pack_data, EGLDisplay *dpy, EGLConfig *cfg, EGLint *debug, EGLint *attrib_list, const int attrib_list_size)
{
	int ret = 0;

	if (dpy != NULL) *dpy = pack_data->dpy;
	if (cfg != NULL) *cfg = pack_data->cfg;
	if (debug != NULL) *debug = pack_data->debug;

	if (attrib_list != NULL && attrib_list_size > 0)
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

#if 0
static int
_unpack_egl_context_sharable_option(EGL_packed_sharable_option *pack_data, EGLContext *share_context)
{
	int ret = 0;

	if (share_context != NULL) *share_context = pack_data->share_context;

	ret = 1;
	goto finish;

finish:
	return ret;
}
#endif

static void
_link_context_state(GLGlueContext *gctx, GLContextState *cstate)
{
	AST(gctx->cstate == NULL);
	cstate->ref_count++;
	gctx->cstate = cstate;
}

static void
_unlink_context_state(GLGlueContext *gctx, Mutex *ctx_list_mtx)
{
	GLContextState *cstate = NULL;

	cstate = gctx->cstate;
	AST(cstate != NULL);

	cstate->ref_count--;
	AST(cstate->ref_count >= 0);

	if (cstate->ref_count == 0)
	{
		GLThreadState *tstate = NULL;

		AST(cstate->data == NULL || cstate->data == initial_ctx);

#ifdef COREGL_TRACE_CONTEXT_INFO
		if (unlikely(trace_ctx_flag == 1))
			remove_from_general_trace_list(&context_state_trace_list, cstate);
#endif // COREGL_TRACE_CONTEXT_INFO

		AST(remove_context_states_from_list(cstate, ctx_list_mtx) == 1);

		tstate = get_current_thread_state();
		if (tstate != NULL)
		{
			if (tstate->cstate == cstate)
			{
				_sym_eglMakeCurrent(cstate->rdpy, tstate->rsurf_draw, tstate->rsurf_read, EGL_NO_CONTEXT);
				tstate->cstate = NULL;
			}
		}
		_sym_eglDestroyContext(cstate->rdpy, cstate->rctx);
		free(cstate);
		cstate = NULL;
	}
}

static void
_add_shared_obj_state_ref(GL_Shared_Object_State *sostate)
{
	AST(sostate->ref_count >= 0);
	sostate->ref_count++;
}

static void
_remove_shared_obj_state_ref(GL_Shared_Object_State *sostate)
{
	AST(sostate->ref_count > 0);
	sostate->ref_count--;
	if (sostate->ref_count == 0)
	{
		free(sostate);
	}
}

static void
_add_context_ref(GLGlueContext *gctx)
{
	if (gctx == initial_ctx) return;

	AST(gctx->ref_count >= 0);
	gctx->ref_count++;
}

static void
_remove_context_ref(GLGlueContext *gctx, Mutex *ctx_list_mtx)
{
	if (gctx == initial_ctx) return;

	AST(gctx->ref_count > 0);
	gctx->ref_count--;
	if (gctx->ref_count == 0)
	{
#ifdef COREGL_TRACE_CONTEXT_INFO
		if (unlikely(trace_ctx_flag == 1))
			remove_from_general_trace_list(&glue_ctx_trace_list, gctx);
#endif // COREGL_TRACE_CONTEXT_INFO

		_unlink_context_state(gctx, ctx_list_mtx);

		AST(gctx->sostate != NULL);
		_remove_shared_obj_state_ref(gctx->sostate);
		gctx->sostate = NULL;

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
}

static void
_bind_context_state(GLGlueContext *gctx, GLContextState *cstate, Mutex *ctx_list_mtx)
{
	if (gctx != NULL)
	{
		AST(gctx->cstate == cstate);
	}

	if (cstate->data != gctx)
	{
		GLGlueContext *curctx = (GLGlueContext *)cstate->data;
		GLGlueContext *newctx = gctx;

		if (newctx == NULL)
			newctx = initial_ctx;

		if (curctx == NULL)
			curctx = initial_ctx;

		AST(newctx != NULL);
		AST(curctx != NULL);

		make_context_current(curctx, newctx);
		cstate->data = (void *)newctx;
		_remove_context_ref(curctx, ctx_list_mtx);
		_add_context_ref(newctx);
	}

}

GLContextState *
_egl_create_context(EGL_packed_option *real_ctx_option, GLContextState **cstate_new, EGLContext *ctx,
                    EGLDisplay dpy, EGLConfig config, const EGLint* attrib_list)
{
	GLContextState *cstate = NULL;

	AST(real_ctx_option != NULL);
	AST(cstate_new != NULL);
	AST(ctx != NULL);

	// Pack context option
	AST(_pack_egl_context_option(real_ctx_option, dpy, config, 0, attrib_list) == 1);

	if (debug_nofp == 1)
	{
		static int debug_force_real = 100001;
		AST(_pack_egl_context_option(real_ctx_option, dpy, config, debug_force_real, attrib_list) == 1);
		debug_force_real++;
	}

	// Find context state
	cstate = get_context_state_from_list(real_ctx_option, sizeof(EGL_packed_option), &ctx_list_access_mutex);

	// Create a real context if it hasn't been created
	if (cstate == NULL)
	{
		EGLContext *real_share_context = EGL_NO_CONTEXT;

		AST(mutex_lock(&ctx_list_access_mutex) == 1);
		{
			GLContext_List *current = NULL;

			current = glctx_list;
			while (current != NULL)
			{
				EGLDisplay cur_dpy = EGL_NO_DISPLAY;
				AST(_unpack_egl_context_option(current->option, &cur_dpy, NULL, NULL, NULL, 0) == 1);
				if (cur_dpy == dpy)
				{
					AST(current->cstate != NULL);
					real_share_context = current->cstate->rctx;
					break;
				}
				current = current->next;
			}
		}
		AST(mutex_unlock(&ctx_list_access_mutex) == 1);

		*ctx = _sym_eglCreateContext(dpy, config, real_share_context, attrib_list);

		if (*ctx == EGL_NO_CONTEXT)
		{
			ERR("Failed creating a egl real context for Fastpath.\n");
			goto finish;
		}

		*cstate_new = (GLContextState *)calloc(1, sizeof(GLContextState));
		if (*cstate_new == NULL)
		{
			ERR("Error creating a new context state.\n");
			goto finish;
		}
		(*cstate_new)->rctx = *ctx;
		(*cstate_new)->rdpy = dpy;
		(*cstate_new)->data = NULL;

		AST(add_context_state_to_list(real_ctx_option, sizeof(EGL_packed_option), *cstate_new, &ctx_list_access_mutex) == 1);

#ifdef COREGL_TRACE_CONTEXT_INFO
		if (unlikely(trace_ctx_flag == 1))
			add_to_general_trace_list(&context_state_trace_list, *cstate_new);
#endif // COREGL_TRACE_CONTEXT_INFO

		cstate = *cstate_new;
	}

	goto finish;

finish:
	return cstate;

}




//----------------------------------------------------------------//
//                   Fastpath EGL Functions                       //
//    The functions have prefix 'fpgl_' for (fastpath gl)         //
//----------------------------------------------------------------//

extern EGLBoolean (*wrp_eglBindAPI)(EGLenum api);
extern EGLenum (*wrp_eglQueryAPI)(void);
extern EGLBoolean (*ovr_eglBindAPI)(EGLenum api);
extern EGLenum (*ovr_eglQueryAPI)(void);

EGLBoolean
fpgl_eglBindAPI(EGLenum api)
{
	EGLBoolean ret = EGL_FALSE;
	GLThreadState *tstate = NULL;

	_COREGL_FAST_FUNC_BEGIN();
	if (api_opt == COREGL_UNKNOWN_PATH)
	{
		ERR("\E[0;31;1mERROR : Invalid library link! (CoreGL path option is invalid)\E[0m\n");
		goto finish;
	}

	ret = _sym_eglBindAPI(api);

	tstate = get_current_thread_state();
	if (tstate == NULL)
	{
		AST(init_new_thread_state() == 1);

		tstate = get_current_thread_state();
		AST(tstate != NULL);
	}

	{
		EGLenum newapi = _sym_eglQueryAPI();
		if (tstate->binded_api != newapi)
		{
			if (newapi != EGL_OPENGL_ES_API)
			{
				// Fallback when binding other API
				// Fastpath restores when bind OPENGL_ES_API
				override_glue_normal_path();
				if (trace_api_flag == 1)
				{
					wrp_eglBindAPI = fpgl_eglBindAPI;
					wrp_eglQueryAPI = fpgl_eglQueryAPI;
				}
				else
				{
					ovr_eglBindAPI = fpgl_eglBindAPI;
					ovr_eglQueryAPI = fpgl_eglQueryAPI;
				}
			}
			else
			{
				override_glue_fast_path();
			}
			tstate->binded_api = newapi;
		}
	}

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}

EGLenum
fpgl_eglQueryAPI(void)
{
	EGLenum ret = 0;
	GLThreadState *tstate = NULL;

	_COREGL_FAST_FUNC_BEGIN();
	if (api_opt == COREGL_UNKNOWN_PATH)
	{
		ERR("\E[0;31;1mERROR : Invalid library link! (CoreGL path option is invalid)\E[0m\n");
		goto finish;
	}

	ret = _sym_eglQueryAPI();

	tstate = get_current_thread_state();
	if (tstate != NULL)
	{
		AST(tstate->binded_api == ret);
	}

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}

EGLContext
fpgl_eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint* attrib_list)
{
	GLGlueContext *gctx = NULL;
	GLThreadState *tstate = NULL;
	GLContextState *cstate = NULL;
	GLContextState *cstate_new = NULL;
	GL_Shared_Object_State *sostate_new = NULL;
	GLContext ctx = NULL;

	EGL_packed_option *real_ctx_option = NULL;
	EGL_packed_sharable_option *real_ctx_sharable_option = NULL;

	// Special eject condition for binding API
	tstate = get_current_thread_state();
	if (tstate != NULL && tstate->binded_api != EGL_OPENGL_ES_API)
	{
		return _sym_eglCreateContext(dpy, config, share_context, attrib_list);
	}

	_COREGL_FAST_FUNC_BEGIN();

	real_ctx_option = (EGL_packed_option *)calloc(1, sizeof(EGL_packed_option));
	if (real_ctx_option == NULL)
	{
		ERR("Error creating a new GLGlueContext(1)\n");
		goto finish;
	}
	cstate = _egl_create_context(real_ctx_option, &cstate_new, &ctx, dpy, config, attrib_list);
	AST(cstate != NULL);

	// Pack shared context options
	real_ctx_sharable_option = (EGL_packed_sharable_option *)calloc(1, sizeof(EGL_packed_sharable_option));
	if (real_ctx_sharable_option == NULL)
	{
		ERR("Error creating a new GLGlueContext(2)\n");
		goto finish;
	}
	AST(_pack_egl_context_sharable_option(real_ctx_sharable_option, share_context) == 1);

	// Allocate a new context
	gctx = (GLGlueContext *)calloc(1, sizeof(GLGlueContext));
	if (gctx == NULL)
	{
		ERR("Error creating a new GLGlueContext(3)\n");
		goto finish;
	}

	gctx->magic = MAGIC_GLFAST;
	gctx->initialized = 0;
	gctx->rdpy = dpy;
	gctx->thread_id = get_current_thread();

	if (share_context != EGL_NO_CONTEXT)
	{
		GLGlueContext *shared_gctx = (GLGlueContext *)share_context;
		AST(shared_gctx->magic == MAGIC_GLFAST);
		AST(shared_gctx->sostate != NULL);
		gctx->sostate = shared_gctx->sostate;
	}
	else
	{
		sostate_new = (GL_Shared_Object_State *)calloc(1, sizeof(GL_Shared_Object_State));
		if (sostate_new == NULL)
		{
			ERR("Error creating a new GLGlueContext(4)\n");
			goto finish;
		}
		gctx->sostate = sostate_new;
	}
	_add_shared_obj_state_ref(gctx->sostate);
	gctx->real_ctx_option = real_ctx_option;
	gctx->real_ctx_option_len = sizeof(EGL_packed_option);
	gctx->real_ctx_sharable_option = real_ctx_sharable_option;
	gctx->real_ctx_sharable_option_len = sizeof(EGL_packed_sharable_option);

	_link_context_state(gctx, cstate);
	_add_context_ref(gctx);

	gctx->cstate = cstate;

#ifdef COREGL_TRACE_CONTEXT_INFO
	if (unlikely(trace_ctx_flag == 1))
	{
		char ment[256];
		add_to_general_trace_list(&glue_ctx_trace_list, gctx);

		sprintf(ment, "eglCreateContext completed (GlueCTX=[%12p])", gctx);
		_dump_context_info(ment, 1);
	}
#endif // COREGL_TRACE_CONTEXT_INFO

	goto finish;

finish:
	if (gctx == NULL)
	{
		if (ctx != NULL)
		{
			_sym_eglDestroyContext(dpy, ctx);
			ctx = NULL;
		}
		if (sostate_new != NULL)
		{
			free(sostate_new);
			sostate_new = NULL;
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
#ifdef COREGL_TRACE_CONTEXT_INFO
			if (unlikely(trace_ctx_flag == 1))
				remove_from_general_trace_list(&context_state_trace_list, cstate_new);
#endif // COREGL_TRACE_CONTEXT_INFO

			remove_context_states_from_list(cstate_new, &ctx_list_access_mutex);
			free(cstate_new);
			cstate_new = NULL;
		}
	}

	_COREGL_FAST_FUNC_END();
	return (EGLContext)gctx;
}

EGLBoolean
fpgl_eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
	EGLBoolean ret = EGL_FALSE;
	GLGlueContext *gctx = NULL;

	_COREGL_FAST_FUNC_BEGIN();

	gctx = (GLGlueContext *)ctx;

	if (gctx != NULL && gctx != EGL_NO_CONTEXT)
	{
		GLContextState *cstate = NULL;

		if (gctx->magic != MAGIC_GLFAST)
		{
			ret = _sym_eglDestroyContext(dpy, ctx);
			goto finish;
		}

		cstate = gctx->cstate;
		AST(cstate != NULL);

		if (gctx->is_destroyed == 1)
		{
			ERR("\E[40;31;1mWARNING : Context [%p] is already destroyed!!!\E[0m\n", ctx);
		}
		else
		{
			gctx->is_destroyed = 1;
			_remove_context_ref(gctx, &ctx_list_access_mutex);
		}
	}
	else
	{
		ERR("Invalid Context.\n");
		ret = EGL_FALSE;
		goto finish;
	}

	ret = EGL_TRUE;
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();

#ifdef COREGL_TRACE_CONTEXT_INFO
	if (unlikely(trace_ctx_flag == 1))
	{
		char ment[256];
		sprintf(ment, "eglDestroyContext completed (GlueCTX=[%12p])", ctx);
		_dump_context_info(ment, 1);
	}
#endif // COREGL_TRACE_CONTEXT_INFO

	return ret;
}

EGLBoolean
fpgl_eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value)
{
	EGLBoolean ret = EGL_FALSE;
	EGLContext real_ctx = EGL_NO_CONTEXT;

	_COREGL_FAST_FUNC_BEGIN();

	if (ctx != EGL_NO_CONTEXT)
	{
		GLGlueContext *gctx = NULL;
		gctx = (GLGlueContext *)ctx;

		if (gctx->magic != MAGIC_GLFAST)
		{
			real_ctx = ctx;
		}
		else
		{
			AST(gctx->cstate != NULL);
			real_ctx = gctx->cstate->rctx;
		}
	}

	_COREGL_FAST_FUNC_SYMCALL_BEGIN();
	ret = _sym_eglQueryContext(dpy, real_ctx, attribute, value);
	_COREGL_FAST_FUNC_SYMCALL_END();
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}



EGLBoolean
fpgl_eglReleaseThread(void)
{
	EGLBoolean ret = EGL_FALSE;
	EGLDisplay dpy = EGL_NO_DISPLAY;
	GLThreadState *tstate = NULL;

	tstate = get_current_thread_state();

	// Special eject condition for binding API
	if (tstate != NULL && tstate->binded_api != EGL_OPENGL_ES_API)
	{
		return _sym_eglReleaseThread();
	}

	_COREGL_FAST_FUNC_BEGIN();

	dpy = _sym_eglGetCurrentDisplay();
	AST(dpy != EGL_NO_DISPLAY);
	fpgl_eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	ret = _sym_eglReleaseThread();
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}



EGLBoolean
fpgl_eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
	EGLBoolean ret = EGL_FALSE;
	EGLBoolean need_mc = EGL_FALSE;
	GLGlueContext *gctx = NULL;

	GLThreadState *tstate = NULL;
	GLContextState *cstate = NULL;

	tstate = get_current_thread_state();

	// Special eject condition for binding API
	if (tstate != NULL && tstate->binded_api != EGL_OPENGL_ES_API)
	{
		return _sym_eglMakeCurrent(dpy, draw, read, ctx);
	}

	_COREGL_FAST_FUNC_BEGIN();

	gctx = (GLGlueContext *)ctx;

	if (tstate == NULL)
	{
		AST(init_new_thread_state() == 1);

		tstate = get_current_thread_state();
		AST(tstate != NULL);
	}

	// Special path for context deletion
	if (ctx == EGL_NO_CONTEXT)
	{
		AST(gctx == NULL);

		if (tstate->cstate != NULL)
		{
			_bind_context_state(NULL, tstate->cstate, &ctx_list_access_mutex);
			tstate->cstate = NULL;
		}
		if (_sym_eglMakeCurrent(dpy, draw, read, ctx) != EGL_TRUE)
		{
			ERR("WARNING : Error making context [%p] current. (invalid EGL display [%p] or EGL surface [D:%p/R:%p])\n", ctx, dpy, draw, read);
			ret = EGL_FALSE;
			goto finish;
		}

		tstate->rsurf_draw = draw;
		tstate->rsurf_read = read;

		ret = EGL_TRUE;
		goto finish;
	}

	AST(gctx != NULL);
	AST(gctx->cstate != NULL);

	if (gctx->rdpy != dpy)
	{
		ERR("Invalid context (or invalid EGL display)\n");
		ret = EGL_FALSE;
		goto finish;
	}

	AST(gctx->real_ctx_option != NULL);
	AST(gctx->real_ctx_sharable_option != NULL);

	// Handle cross threading of context (when used by two or more gctx)
	if (gctx->thread_id != get_current_thread() && gctx->cstate->ref_count > 1)
	{
#define ATTRIB_LIST_BUFFER_SIZE 8

		GLContextState *cstate_new = NULL;
		EGLContext new_real_ctx = EGL_NO_CONTEXT;

		EGLDisplay dpy = EGL_NO_DISPLAY;
		EGLConfig config = NULL;
		int attrib_list[ATTRIB_LIST_BUFFER_SIZE];

		AST(_unpack_egl_context_option(gctx->real_ctx_option, &dpy, &config, NULL, attrib_list, ATTRIB_LIST_BUFFER_SIZE) == 1);
		AST(dpy == gctx->rdpy);

		_egl_create_context(gctx->real_ctx_option, &cstate_new, &new_real_ctx, dpy, config, attrib_list);

		AST(cstate_new != NULL);

		_bind_context_state(gctx, cstate_new, &ctx_list_access_mutex);

		// TODO : Setup context state for new real ctx
		ERR("\E[40;31;1mWARNING : Cross-thread usage(makecurrent) can cause a state-broken situation!\E[0m\n");

		_unlink_context_state(gctx, &ctx_list_access_mutex);
		_link_context_state(gctx, cstate_new);

		// Apply to new thread
		gctx->thread_id = get_current_thread();

	}

	// Check if the object is correct
	if (gctx->magic != MAGIC_GLFAST)
	{
		ERR("Glue-CTX Magic Check Failed!!!\n");
		ret = EGL_FALSE;
		goto finish;

	}

	cstate = tstate->cstate;

	// If it's a first time or drawable changed, do a make current
	if (cstate == NULL)
	{
		cstate = get_context_state_from_list(gctx->real_ctx_option, gctx->real_ctx_option_len, &ctx_list_access_mutex);

		if (cstate == NULL)
		{
			ERR("Error making context current because context not ready.\n");
			ret = EGL_FALSE;
			goto finish;
		}
		need_mc = EGL_TRUE;
	}

	// If drawable changed, do a make current
	if ((tstate->rsurf_draw != draw) ||
	    (tstate->rsurf_read != read))
		need_mc = EGL_TRUE;

	AST(gctx->cstate != NULL);

	// If binded real context changed, do a make current
	if (gctx->cstate->rctx != cstate->rctx)
		need_mc = EGL_TRUE;

	if (need_mc == EGL_TRUE)
	{
		// BB : full makecurrent
		if (_sym_eglMakeCurrent(dpy, draw, read, gctx->cstate->rctx) != EGL_TRUE)
		{
			ERR("Error making context current with the drawable.\n");
			ret = EGL_FALSE;
			goto finish;
		}

		tstate->cstate = gctx->cstate;

		tstate->rsurf_draw = draw;
		tstate->rsurf_read = read;
	}

	// Initialize context states
	if (gctx->initialized == 0)
	{
		if (init_context_states(gctx) != 1)
		{
			ERR("Error intializing context\n");
			goto finish;
		}
	}

	// Setup initial Viewport & Scissor
	if (gctx->surface_attached == 0 && draw != EGL_NO_SURFACE)
	{
		EGLint box_buffer[4];
		EGLint width = 0;
		EGLint height = 0;

		_sym_glGetIntegerv(GL_VIEWPORT, box_buffer);
		width = box_buffer[2];
		height = box_buffer[3];

		gctx->_clear_flag1 |= FLAG_BIT_0;
		gctx->gl_viewport[0] = 0;
		gctx->gl_viewport[1] = 0;
		gctx->gl_viewport[2] = width;
		gctx->gl_viewport[3] = height;

		_sym_glGetIntegerv(GL_SCISSOR_BOX, box_buffer);
		width = box_buffer[2];
		height = box_buffer[3];

		gctx->_misc_flag2 |= FLAG_BIT_0;
		gctx->gl_scissor_box[0] = 0;
		gctx->gl_scissor_box[1] = 0;
		gctx->gl_scissor_box[2] = width;
		gctx->gl_scissor_box[3] = height;

		gctx->surface_attached = 1;
	}

	_bind_context_state(gctx, tstate->cstate, &ctx_list_access_mutex);
	gctx->used_count++;

	ret = EGL_TRUE;
	goto finish;

finish:

	_COREGL_FAST_FUNC_END();

#ifdef COREGL_TRACE_CONTEXT_INFO
	if (unlikely(trace_ctx_flag == 1))
	{
		char ment[256];
		sprintf(ment, "eglMakeCurrent finished (GlueCTX=[%12p] Surf=[D:%12p R:%12p])", ctx, draw, read);
		_dump_context_info(ment, 0);
	}
#endif // COREGL_TRACE_CONTEXT_INFO

	return ret;
}


EGLContext
fpgl_eglGetCurrentContext(void)
{
	GLGlueContext *ret = NULL;
	GLThreadState *tstate = NULL;

	tstate = get_current_thread_state();

	// Special eject condition for binding API
	if (tstate != NULL && tstate->binded_api != EGL_OPENGL_ES_API)
	{
		return _sym_eglGetCurrentContext();
	}

	_COREGL_FAST_FUNC_BEGIN();

	if (tstate != NULL)
	{
		if (tstate->cstate != NULL)
		{
			ret = (GLGlueContext *)tstate->cstate->data;
			AST(ret->magic == MAGIC_GLFAST);
		}
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return (EGLContext)ret;
}


EGLSurface
fpgl_eglGetCurrentSurface(EGLint readdraw)
{
	EGLSurface ret = EGL_NO_SURFACE;
	GLThreadState *tstate = NULL;

	tstate = get_current_thread_state();

	// Special eject condition for binding API
	if (tstate != NULL && tstate->binded_api != EGL_OPENGL_ES_API)
	{
		return _sym_eglGetCurrentSurface(readdraw);
	}

	_COREGL_FAST_FUNC_BEGIN();

	tstate = get_current_thread_state();

	if (tstate != NULL)
	{
		switch (readdraw)
		{
			case EGL_DRAW :
				ret = (GLGlueContext *)tstate->rsurf_draw;
				break;
			case EGL_READ :
				ret = (GLGlueContext *)tstate->rsurf_read;
				break;
		}
	}
	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}

EGLImageKHR
fpgl_eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list)
{
	void *ret = NULL;
	EGLContext real_ctx = EGL_NO_CONTEXT;

	_COREGL_FAST_FUNC_BEGIN();

	if (ctx != NULL && ctx != EGL_NO_CONTEXT)
	{
		GLGlueContext *gctx = (GLGlueContext *)ctx;

		if (gctx->magic != MAGIC_GLFAST)
		{
			real_ctx = ctx;
		}
		else
		{
			AST(gctx->cstate != NULL);
			real_ctx = gctx->cstate->rctx;
		}
	}
	ret = _sym_eglCreateImageKHR(dpy, real_ctx, target, buffer, attrib_list);

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}

_eng_fn
fpgl_eglGetProcAddress(const char* procname)
{
	_eng_fn ret = NULL;

	_COREGL_FAST_FUNC_BEGIN();

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST) \
	if (strcmp(procname, #FUNC_NAME) == 0) \
	{ \
		ret = (_eng_fn)FUNC_NAME; \
		goto finish; \
	}
#include "headers/sym_egl.h"
#include "headers/sym_gl.h"
#undef _COREGL_SYMBOL

	ret = _sym_eglGetProcAddress(procname);
	if (ret != NULL)
	{
		LOG("\E[40;31;1mWARNING : COREGL can't support '%s' (unmanaged situation may occur)\E[0m\n", procname);
	}

	goto finish;

finish:
	_COREGL_FAST_FUNC_END();
	return ret;
}

