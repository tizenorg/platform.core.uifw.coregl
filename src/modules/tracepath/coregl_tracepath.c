#include "coregl_tracepath.h"

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <sys/types.h>
#include <unistd.h>

#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     RET_TYPE (*_orig_tracepath_##FUNC_NAME) PARAM_LIST = NULL;
#include "../../headers/sym.h"
#undef _COREGL_SYMBOL

#define TIMEVAL_INIT            { 0, 0 }

struct _Trace_Data
{
	char                         name[MAX_TRACE_NAME_LENGTH];
	struct _Trace_Data          *next;
};

struct _Apicall_Data
{
	struct _Trace_Data          trace_data;

	int                          call_count;
	int                          last_call_count;
	struct timeval              elapsed_time;
	struct timeval              elapsed_time_max;
	struct timeval              last_elapsed_time;
	struct timeval              total_elapsed_time;
	struct timeval              last_total_elapsed_time;
	struct timeval              last_time;

	int                          traced;
};

struct _Memuse_Data
{
	struct _Trace_Data          trace_data;

	int                          memsize;
	int                          alloc_count;
	int                          remove_count;
};

typedef struct _GLGlueFakeContext
{
	GLuint gl_num_tex_units[1];
	GLuint gl_num_vertex_attribs[1];
} GLGlueFakeContext;

GLGlueFakeContext initial_fake_ctx_real;
GLGlueFakeContext *initial_fake_ctx = &initial_fake_ctx_real;

struct timeval     initial_time = TIMEVAL_INIT;
struct timeval     last_initial_time = TIMEVAL_INIT;

struct timeval     last_trace_time = TIMEVAL_INIT;
struct timeval     other_elapsed_time = TIMEVAL_INIT;
struct timeval     traced_other_elapsed_time = TIMEVAL_INIT;

Mutex               mtd_access_mutex = MUTEX_INITIALIZER;
Memuse_Data       **mtd_table;

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
init_modules_tracepath()
{
	{
		const char *output_file = NULL;
		output_file = get_env_setting("COREGL_LOG_FILE");
		if (strlen(output_file) > 0)
		{
			trace_fp = fopen(output_file, "w");
		}
		if (trace_fp == NULL)
			trace_fp = stderr;
	}

#ifdef COREGL_TRACEPATH_TRACE_APICALL_INFO
	trace_api_flag = atoi(get_env_setting("COREGL_TRACE_API"));
	trace_api_all_flag = atoi(get_env_setting("COREGL_TRACE_API_ALL"));
#endif
#ifdef COREGL_TRACEPATH_TRACE_MEMUSE_INFO
	trace_mem_flag = atoi(get_env_setting("COREGL_TRACE_MEM"));
#endif
#ifdef COREGL_TRACEPATH_TRACE_CONTEXT_INFO
	trace_ctx_flag = atoi(get_env_setting("COREGL_TRACE_CTX"));
	trace_ctx_force_flag = atoi(get_env_setting("COREGL_TRACE_CTX_FORCE"));
#endif
#ifdef COREGL_TRACEPATH_TRACE_STATE_INFO
	trace_state_flag = atoi(get_env_setting("COREGL_TRACE_STATE"));
#endif

	if (USE_TRACEPATH)
	{
		LOG("[CoreGL] \E[40;32;1m<Trace> \E[40;37;1m: ");

		if (trace_api_flag == 1)
		{
			LOG("\E[40;31;1m(API)\E[0m ");
			if (trace_api_all_flag == 1) LOG("\E[40;31;1m(API-ALL)\E[0m ");
		}
		if (trace_ctx_flag == 1) {
			LOG("\E[40;33;1m(CONTEXT)\E[0m ");
			if (trace_ctx_force_flag == 1) LOG("\E[40;33;1m(CONTEXT-FORCE)\E[0m ");
		}
		if (trace_state_flag == 1) LOG("\E[40;36;1m(STATE)\E[0m ");
		if (trace_mem_flag == 1)
		{
			LOG("\E[40;35;1m(MEM)\E[0m ");
		}

		LOG("\E[40;37;1menabled\E[0m\n");
	}

	tracepath_apply_overrides();

}

void
deinit_modules_tracepath()
{
}

void
init_modules_tstate_tracepath(GLThreadState *tstate)
{
	MY_MODULE_TSTATE *tstate_mt = NULL;

	tstate_mt = (MY_MODULE_TSTATE *)calloc(1, sizeof(MY_MODULE_TSTATE));


	tstate->module_data[MY_MODULE_ID] = tstate_mt;
}

void
deinit_modules_tstate_tracepath(GLThreadState *tstate)
{
	if (tstate->module_data[MY_MODULE_ID] != NULL)
	{
		free(tstate->module_data[MY_MODULE_ID]);
		tstate->module_data[MY_MODULE_ID] = NULL;
	}
}

void
tracepath_apply_overrides()
{
	if (USE_TRACEPATH)
	{
		tracepath_apply_overrides_egl(1);
		tracepath_apply_overrides_gl(1);
	}
}

#define OVERRIDE(f) \
	if (enable == 1) \
	{ \
		COREGL_OVERRIDE_API(_orig_tracepath_, f, ovr_); \
		COREGL_OVERRIDE_API(ovr_, f, tracepath_); \
	} \
	else \
	{ \
		AST(ovr_##f != NULL); \
		COREGL_OVERRIDE_API(ovr_, f, _orig_tracepath_); \
		_orig_tracepath_##f = NULL; \
	}

void
tracepath_apply_overrides_egl(int enable)
{
#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     OVERRIDE(FUNC_NAME);
# include "../../headers/sym_egl.h"
#undef _COREGL_SYMBOL
}

void
tracepath_apply_overrides_gl(int enable)
{
#define _COREGL_SYMBOL(IS_EXTENSION, RET_TYPE, FUNC_NAME, PARAM_LIST)     OVERRIDE(FUNC_NAME);
# include "../../headers/sym_gl.h"
#undef _COREGL_SYMBOL

}

#undef OVERRIDE

void
tracepath_dump_context_states(int force_output)
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
	TRACE("\E[0;32;1m  State info \E[1;37;1m: <PID = %d> (CURRENT BINDED CONTEXT)\E[0m\n", getpid());
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
# include "../fastpath/coregl_fastpath_state.h"
#undef GLUE_STATE

	TRACE("\E[0;40;34m===================================================================================================================\E[0m\n");
	TRACE("\n");

	TRACE_END();

finish:
	return;
}


static inline void
_add_timeval_period(struct timeval *tv_dst, struct timeval tv_now, struct timeval tv_old)
{
	tv_dst->tv_sec += tv_now.tv_sec - tv_old.tv_sec;
	tv_dst->tv_usec += 1000000 + (tv_now.tv_usec - tv_old.tv_usec);
	tv_dst->tv_sec += (tv_dst->tv_usec / 1000000) - 1;
	tv_dst->tv_usec = tv_dst->tv_usec % 1000000;
}

static inline void
_add_timeval(struct timeval *tv_dst, struct timeval tv_src)
{
	tv_dst->tv_sec += tv_src.tv_sec;
	tv_dst->tv_usec += tv_src.tv_usec;
	if (tv_dst->tv_usec > 1000000)
	{
		tv_dst->tv_usec -= 1000000;
		tv_dst->tv_sec++;
	}
	else if (tv_dst->tv_usec < 0)
	{
		tv_dst->tv_usec += 1000000;
		tv_dst->tv_sec--;
	}
}

static inline double
_get_timeval_period(struct timeval time_now, struct timeval time_old)
{
	return ((time_now.tv_sec - time_old.tv_sec) * 1000) + ((time_now.tv_usec - time_old.tv_usec) / 1000.0);
}

static inline double
_get_timeval(struct timeval time)
{
	return (time.tv_sec * 1000) + (time.tv_usec / 1000.0);
}

static unsigned short
_generate_hash_short(const char *string)
{
	unsigned short hash = 0;
	int i;

	for (i = 0; i < strlen(string); i++)
	{
		hash = 253 * hash + string[i];
	}
	return (hash ^ (hash >> 8)) % MAX_TRACE_TABLE_SIZE;
}

static Trace_Data *
_get_trace_data(Trace_Data **ftd_table, size_t td_size, const char *name)
{
	Trace_Data *ret = NULL;
	Trace_Data *current = NULL;
	Trace_Data *prev = NULL;
	unsigned short hash = 0;

	AST(strlen(name) < MAX_TRACE_NAME_LENGTH);

	hash = _generate_hash_short(name);

	current = ftd_table[hash];

	while (current != NULL && current->next != NULL)
	{
		if (strcmp(current->name, name) == 0)
			break;
		prev = current;
		current = current->next;
	}

	if (current != NULL)
	{
		ret = current;
	}
	else
	{
		Trace_Data *newitm = NULL;
		newitm = (Trace_Data *)calloc(1, td_size);
		strcpy(newitm->name, name);
		newitm->next = NULL;

		if (prev != NULL)
		{
			prev->next = newitm;
		}
		else
		{
			ftd_table[hash] = newitm;
		}
		ret = newitm;
	}

	goto finish;

finish:
	return ret;
}

void
tracepath_mem_trace_add(const char *desc, int alloc_size)
{
	Memuse_Data *mtd = NULL;

	if (trace_mem_flag == 1)
	{
		AST(mutex_lock(&mtd_access_mutex) == 1);

		if (mtd_table == NULL)
		{
			mtd_table = (Memuse_Data **)calloc(1, sizeof(Memuse_Data *) * MAX_TRACE_TABLE_SIZE);
		}

		mtd = (Memuse_Data *)_get_trace_data((Trace_Data **)mtd_table, sizeof(Memuse_Data), desc);

		AST(mtd != NULL);

		mtd->alloc_count++;

		if (mtd->memsize == 0)
			mtd->memsize = alloc_size;

		AST(mtd->memsize == alloc_size);

		AST(mutex_unlock(&mtd_access_mutex) == 1);
	}

}

void
tracepath_mem_trace_remove(const char *desc, int alloc_size)
{
	Memuse_Data *mtd = NULL;

	if (trace_mem_flag == 1)
	{
		AST(mutex_lock(&mtd_access_mutex) == 1);

		if (mtd_table == NULL)
		{
			mtd_table = (Memuse_Data **)calloc(1, sizeof(Memuse_Data *) * MAX_TRACE_TABLE_SIZE);
		}

		mtd = (Memuse_Data *)_get_trace_data((Trace_Data **)mtd_table, sizeof(Memuse_Data), desc);

		AST(mtd != NULL);
		AST(mtd->memsize == alloc_size);

		AST(mtd->alloc_count > mtd->remove_count);
		mtd->remove_count++;

		AST(mutex_unlock(&mtd_access_mutex) == 1);
	}
}

void *
tracepath_api_trace_begin(const char *funcname, void *hint, int trace_total_time)
{
	Apicall_Data *ftd = NULL;
	struct timeval t = TIMEVAL_INIT;

	if (trace_api_flag == 1)
	{
		AST(gettimeofday(&t, NULL) == 0);

		ftd = (Apicall_Data *)hint;

		if (ftd == NULL)
		{
			MY_MODULE_TSTATE *tstate = NULL;
			GET_MY_TSTATE(tstate, get_current_thread_state());

			if (tstate == NULL)
			{
				init_new_thread_state();

				GET_MY_TSTATE(tstate, get_current_thread_state());
				AST(tstate != NULL);
			}

			if (tstate->ftd_table == NULL)
			{
				tstate->ftd_table = (Apicall_Data **)calloc(1, sizeof(Apicall_Data *) * MAX_TRACE_TABLE_SIZE);
			}

			ftd = (Apicall_Data *)_get_trace_data((Trace_Data **)tstate->ftd_table, sizeof(Apicall_Data), funcname);
		}

		AST(ftd != NULL);

		ftd->call_count++;
		AST(ftd->last_time.tv_sec == 0);

		AST(gettimeofday(&ftd->last_time, NULL) == 0);

		if (initial_time.tv_sec == 0)
		{
			initial_time = ftd->last_time;
			last_initial_time = ftd->last_time;
		}

		if (trace_total_time == 1)
		{
			if (last_trace_time.tv_sec != 0)
			{
				_add_timeval_period(&other_elapsed_time, t, last_trace_time);
				last_trace_time.tv_sec = 0;
			}
		}

	}

	return ftd;
}

void *
tracepath_api_trace_end(const char *funcname, void *hint, int trace_total_time)
{
	Apicall_Data *ftd = NULL;
	struct timeval t = TIMEVAL_INIT;

	if (trace_api_flag == 1)
	{
		MY_MODULE_TSTATE *tstate = NULL;
		struct timeval elapsed_time = TIMEVAL_INIT;

		AST(gettimeofday(&t, NULL) == 0);

		ftd = (Apicall_Data *)hint;

		if (ftd == NULL)
		{
			GET_MY_TSTATE(tstate, get_current_thread_state());

			if (tstate == NULL)
			{
				init_new_thread_state();

				GET_MY_TSTATE(tstate, get_current_thread_state());
				AST(tstate != NULL);
			}

			AST(tstate != NULL);
			AST(tstate->ftd_table != NULL);

			ftd = (Apicall_Data *)_get_trace_data((Trace_Data **)tstate->ftd_table, sizeof(Apicall_Data), funcname);
		}

		AST(ftd != NULL);

		_add_timeval_period(&elapsed_time, t, ftd->last_time);

		_add_timeval(&ftd->elapsed_time, elapsed_time);

		if (elapsed_time.tv_sec >= ftd->elapsed_time_max.tv_sec &&
			elapsed_time.tv_usec > ftd->elapsed_time_max.tv_usec)
		{
			ftd->elapsed_time_max.tv_sec = elapsed_time.tv_sec;
			ftd->elapsed_time_max.tv_usec = elapsed_time.tv_usec;
		}

		ftd->last_time.tv_sec = 0;

		if (trace_total_time == 1)
		{
			_add_timeval(&ftd->total_elapsed_time, elapsed_time);

			AST(gettimeofday(&last_trace_time, NULL) == 0);

			if (initial_time.tv_sec == 0)
			{
				initial_time = t;
				last_initial_time = t;
			}
		}

	}


	return ftd;
}

void
tracepath_api_trace_output(int force_output)
{
	static struct timeval tv_last = TIMEVAL_INIT;
	struct timeval total_now = TIMEVAL_INIT;
	GLThreadState *tstate = NULL;
	MY_MODULE_TSTATE *tstate_tm = NULL;
	Apicall_Data **ftd_table = NULL;

	double total_elapsed_time = 0.0;
	double total_elapsed_time_period = 0.0;
	double total_opengl_elapsed_time = 0.0;
	double total_opengl_elapsed_time_period = 0.0;
	double total_other_elapsed_time = 0.0;
	double total_other_elapsed_time_period = 0.0;

	double swaps_per_sec = 0.0;

	int i;

	if (trace_api_flag != 1)
	{
		goto finish;
	}

	if (!force_output)
	{
		struct timeval tv_now = TIMEVAL_INIT;
		AST(gettimeofday(&tv_now, NULL) == 0);
		if (tv_now.tv_sec - tv_last.tv_sec < _COREGL_TRACE_OUTPUT_INTERVAL_SEC)
		{
			goto finish;
		}
		tv_last = tv_now;
	}

	AST(gettimeofday(&total_now, NULL) == 0);

	total_elapsed_time = _get_timeval_period(total_now, initial_time);
	total_elapsed_time_period = _get_timeval_period(total_now, last_initial_time);
	last_initial_time = total_now;

	total_other_elapsed_time = _get_timeval(other_elapsed_time);
	total_other_elapsed_time_period = _get_timeval_period(other_elapsed_time, traced_other_elapsed_time);
	traced_other_elapsed_time = other_elapsed_time;

	tstate = get_current_thread_state();

	if (tstate == NULL)
	{
		init_new_thread_state();

		tstate = get_current_thread_state();
		AST(tstate != NULL);
	}

	GET_MY_TSTATE(tstate_tm, tstate);
	if (tstate_tm == NULL) return;

	ftd_table = tstate_tm->ftd_table;
	if (ftd_table == NULL) return;

	{
		static Apicall_Data *trace_hint_swap = NULL;
		if (trace_hint_swap == NULL)
			trace_hint_swap = (Apicall_Data *)_get_trace_data((Trace_Data **)ftd_table, sizeof(Apicall_Data), "tracepath_eglSwapBuffers");

		if (trace_hint_swap != NULL && total_elapsed_time_period > 0)
		{
			swaps_per_sec = (trace_hint_swap->call_count - trace_hint_swap->last_call_count) / (total_elapsed_time_period / 1000);
		}
	}


	TRACE("\n");
	TRACE("\E[40;34m========================================================================================================================\E[0m\n");
	TRACE("\E[40;32;1m  API call info \E[1;37;1m: <PID = %d> Thread ID = %d  [Swaps per Second(P) = %7.2f]\E[0m\n", getpid(), tstate->thread_id, swaps_per_sec);
	TRACE("\E[40;34m========================================================================================================================\E[0m\n");

	// highlighted
	for (i = 0; i < MAX_TRACE_TABLE_SIZE; i++)
	{
		if (ftd_table[i] != NULL)
		{
			Apicall_Data *current = ftd_table[i];

			while (current != NULL)
			{
				double elapsed_time = _get_timeval(current->elapsed_time);
				double elapsed_time_per_call = elapsed_time / current->call_count;

				total_opengl_elapsed_time += _get_timeval(current->total_elapsed_time);
				total_opengl_elapsed_time_period += _get_timeval(current->total_elapsed_time) - _get_timeval(current->last_total_elapsed_time);

				current->traced = 0;

				if (current->call_count > current->last_call_count)
				{
					double elapsed_time_period = _get_timeval_period(current->elapsed_time, current->last_elapsed_time);
					double elapsed_time_max = _get_timeval(current->elapsed_time_max);
					double elapsed_time_per_call_period = elapsed_time_period / (current->call_count - current->last_call_count);
					char *fname = current->trace_data.name;

					if (!strncmp(fname, "tracepath_", 10))
						fname = &current->trace_data.name[10];

					if (elapsed_time_per_call_period >= 0.01 || current->call_count - current->last_call_count > 1000)
					{
						TRACE("\E[40;37;1m %-39.39s : %10d call(s), %9.3f ms/API, %9.2f ms(MAX), %9.3f ms/API(P)\E[0m\n",
						      fname, current->call_count, elapsed_time_per_call, elapsed_time_max, elapsed_time_per_call_period);
						current->traced = 1;
					}
				}
				current = (Apicall_Data *)current->trace_data.next;
			}
		}
	}

	{
		int fp_env = 0;
		fp_env = atoi(get_env_setting("COREGL_TRACE_API_ALL"));
		if (fp_env == 1)
		{
			// other
			for (i = 0; i < MAX_TRACE_TABLE_SIZE; i++)
			{
				if (ftd_table[i] != NULL)
				{
					Apicall_Data *current = ftd_table[i];

					while (current != NULL)
					{
						if (current->traced == 0)
						{
							double elapsed_time = _get_timeval(current->elapsed_time);
							double elapsed_time_per_call = elapsed_time / current->call_count;
							double elapsed_time_max = _get_timeval(current->elapsed_time_max);
							char *fname = current->trace_data.name;

							if (!strncmp(fname, "tracepath_", 10))
								fname = &current->trace_data.name[10];

							TRACE(" %-39.39s : %10d call(s), %9.3f ms/API, %9.2f ms(MAX)\n",
							      fname, current->call_count, elapsed_time_per_call, elapsed_time_max);
						}
						current = (Apicall_Data *)current->trace_data.next;
					}
				}
			}
		}
	}

	TRACE("\E[40;34m========================================================================================================================\E[0m\n");

	TRACE("\E[40;36;1m %-39.39s : %13.2f ms[%6.2f%%], %13.2f ms(P)[%6.2f%%]\E[0m\n",
	      "TOTAL elapsed Time",
	      total_elapsed_time,
	      100.0,
	      total_elapsed_time_period,
	      100.0);


	TRACE("\E[40;36;1m %-39.39s : %13.2f ms[%6.2f%%], %13.2f ms(P)[%6.2f%%]\E[0m\n",
	      "OpenGL elapsed Time",
	      total_opengl_elapsed_time,
	      total_opengl_elapsed_time * 100.0 / total_elapsed_time,
	      total_opengl_elapsed_time_period,
	      total_opengl_elapsed_time_period * 100.0 / total_elapsed_time_period);

	TRACE("\E[40;36;1m %-39.39s : %13.2f ms[%6.2f%%], %13.2f ms(P)[%6.2f%%]\E[0m\n",
	      "Out of OpenGL elapsed time",
	      total_other_elapsed_time,
	      total_other_elapsed_time * 100.0 / total_elapsed_time,
	      total_other_elapsed_time_period,
	      total_other_elapsed_time_period * 100.0 / total_elapsed_time_period);

	TRACE("\E[40;36;1m %-39.39s : %13.2f ms[%6.2f%%], %13.2f ms(P)[%6.2f%%]\E[0m\n",
	      "CoreGL API tracing overhead",
	      total_elapsed_time - total_opengl_elapsed_time - total_other_elapsed_time,
	      (total_elapsed_time - total_opengl_elapsed_time - total_other_elapsed_time) * 100.0 / total_elapsed_time,
	      total_elapsed_time_period - total_opengl_elapsed_time_period - total_other_elapsed_time_period,
	      (total_elapsed_time_period - total_opengl_elapsed_time_period - total_other_elapsed_time_period) * 100.0 / total_elapsed_time_period);

	TRACE("\E[40;34m========================================================================================================================\E[0m\n");
	TRACE("\n");

	for (i = 0; i < MAX_TRACE_TABLE_SIZE; i++)
	{
		if (ftd_table[i] != NULL)
		{
			Apicall_Data *current = ftd_table[i];

			while (current != NULL)
			{
				current->last_call_count = current->call_count;
				current->last_elapsed_time = current->elapsed_time;
				current->last_total_elapsed_time = current->total_elapsed_time;
				current = (Apicall_Data *)current->trace_data.next;
			}
		}
	}

	TRACE_END();

	goto finish;

finish:
	return;
}

void
tracepath_mem_trace_output(int force_output)
{
	static struct timeval tv_last = TIMEVAL_INIT;

	int i;

	if (trace_mem_flag != 1)
	{
		goto finish;
	}

	if (!force_output)
	{
		struct timeval tv_now = TIMEVAL_INIT;
		AST(gettimeofday(&tv_now, NULL) == 0);
		if (tv_now.tv_sec - tv_last.tv_sec < _COREGL_TRACE_OUTPUT_INTERVAL_SEC)
		{
			goto finish;
		}
		tv_last = tv_now;
	}

	TRACE("\n");
	TRACE("\E[40;34m========================================================================================================================\E[0m\n");
	TRACE("\E[40;32;1m  Memory usage info \E[1;37;1m: <PID = %d>\E[0m\n", getpid());
	TRACE("\E[40;34m========================================================================================================================\E[0m\n");

	if (mtd_table != NULL)
	{
		for (i = 0; i < MAX_TRACE_TABLE_SIZE; i++)
		{
			if (mtd_table[i] != NULL)
			{
				Memuse_Data *current = mtd_table[i];

				while (current != NULL)
				{
					int obj_count = current->alloc_count - current->remove_count;
					if (obj_count > 0)
					{
						TRACE("\E[40;37;1m %-46.46s : %12d byte(s)(E), %9d object(s) [%9d+/%9d-]\E[0m\n",
						      current->trace_data.name, current->memsize, obj_count, current->alloc_count, current->remove_count);
					}
					current = (Memuse_Data *)current->trace_data.next;
				}
			}
		}

		for (i = 0; i < MAX_TRACE_TABLE_SIZE; i++)
		{
			if (mtd_table[i] != NULL)
			{
				Memuse_Data *current = mtd_table[i];

				while (current != NULL)
				{
					int obj_count = current->alloc_count - current->remove_count;
					if (obj_count == 0)
					{
						TRACE(" %-46.46s : %12d byte(s)(E), %9d object(s) [%9d+/%9d-]\n",
						      current->trace_data.name, current->memsize, obj_count, current->alloc_count, current->remove_count);
					}
					current = (Memuse_Data *)current->trace_data.next;
				}
			}
		}
	}

	TRACE("\E[40;34m========================================================================================================================\E[0m\n");
	TRACE("\n");

	TRACE_END();

	goto finish;

finish:
	return;
}

