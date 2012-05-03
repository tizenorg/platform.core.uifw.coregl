#include "coregl_internal.h"

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX_TRACE_NAME_LENGTH  256
#define MAX_TRACE_TABLE_SIZE   65536

#define TIMEVAL_INIT            { 0, 0 }

struct _Trace_Data
{
	char                         name[MAX_TRACE_NAME_LENGTH];
	int                          call_count;
	int                          last_call_count;
	struct timeval              elapsed_time;
	struct timeval              last_elapsed_time;
	struct timeval              total_elapsed_time;
	struct timeval              last_total_elapsed_time;
	struct timeval              last_time;

	int                          traced;

	struct _Trace_Data          *next;
};

General_Trace_List *thread_trace_list = NULL;
Mutex               general_trace_lists_access_mutex = MUTEX_INITIALIZER;

struct timeval     initial_time = TIMEVAL_INIT;
struct timeval     last_initial_time = TIMEVAL_INIT;

struct timeval     last_trace_time = TIMEVAL_INIT;
struct timeval     other_elapsed_time = TIMEVAL_INIT;
struct timeval     traced_other_elapsed_time = TIMEVAL_INIT;


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
_get_trace_data(Trace_Data **ftd_table, const char *name)
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
		newitm = (Trace_Data *)calloc(1, sizeof(Trace_Data));
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

int
add_to_general_trace_list(General_Trace_List **gtl, void *value)
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

int
remove_from_general_trace_list(General_Trace_List **gtl, void *value)
{
	int ret = 0;
	General_Trace_List *current = NULL;
	General_Trace_List *priv = NULL;

	AST(mutex_lock(&general_trace_lists_access_mutex) == 1);

	current = *gtl;

	while (current != NULL)
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

void *
trace_begin(const char *funcname, void *hint, int trace_total_time)
{
	Trace_Data *ftd = NULL;
	struct timeval t = TIMEVAL_INIT;

	if (trace_api_flag == 1)
	{
		AST(gettimeofday(&t, NULL) == 0);

		ftd = (Trace_Data *)hint;

		if (ftd == NULL)
		{
			GLThreadState *tstate = NULL;
			tstate = get_current_thread_state();

			if (tstate == NULL)
			{
				init_new_thread_state();

				tstate = get_current_thread_state();
				AST(tstate != NULL);
			}

			if (tstate->ftd_table == NULL)
			{
				tstate->ftd_table = (Trace_Data **)calloc(1, sizeof(Trace_Data *) * MAX_TRACE_TABLE_SIZE);
			}

			ftd = _get_trace_data(tstate->ftd_table, funcname);
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
trace_end(const char *funcname, void *hint, int trace_total_time)
{
	Trace_Data *ftd = NULL;
	struct timeval t = TIMEVAL_INIT;

	if (trace_api_flag == 1)
	{
		GLThreadState *tstate = NULL;
		struct timeval elapsed_time = TIMEVAL_INIT;

		AST(gettimeofday(&t, NULL) == 0);

		ftd = (Trace_Data *)hint;

		if (ftd == NULL)
		{
			tstate = get_current_thread_state();

			if (tstate == NULL)
			{
				init_new_thread_state();

				tstate = get_current_thread_state();
				AST(tstate != NULL);
			}
			AST(tstate->ftd_table != NULL);

			ftd = _get_trace_data(tstate->ftd_table, funcname);
		}

		AST(ftd != NULL);

		_add_timeval_period(&elapsed_time, t, ftd->last_time);

		_add_timeval(&ftd->elapsed_time, elapsed_time);


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
trace_output(int force_output)
{
	static struct timeval tv_last = TIMEVAL_INIT;
	struct timeval total_now = TIMEVAL_INIT;
	GLThreadState *tstate = NULL;
	Trace_Data **ftd_table = NULL;

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


	ftd_table = tstate->ftd_table;
	if (ftd_table == NULL) return;

	{
		static Trace_Data *trace_hint_swap = NULL;
		if (trace_hint_swap == NULL)
			trace_hint_swap = _get_trace_data(ftd_table, "eglSwapBuffers");

		if (trace_hint_swap != NULL && total_elapsed_time_period > 0)
		{
			swaps_per_sec = (trace_hint_swap->call_count - trace_hint_swap->last_call_count) / (total_elapsed_time_period / 1000);
		}
	}


	TRACE("\n");
	TRACE("\E[40;34m========================================================================================================================\E[0m\n");
	TRACE("\E[40;32;1m  API call info \E[1;37;1m: Thread ID = %d  [Swaps per Second(P) = %7.2f]\E[0m\n", tstate->thread_id, swaps_per_sec);
	TRACE("\E[40;34m========================================================================================================================\E[0m\n");

	// highlighted
	for (i = 0; i < MAX_TRACE_TABLE_SIZE; i++)
	{
		if (ftd_table[i] != NULL)
		{
			Trace_Data *current = ftd_table[i];

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
					double elapsed_time_per_call_period = elapsed_time_period / (current->call_count - current->last_call_count);

					if (elapsed_time_per_call_period >= 0.01 || current->call_count - current->last_call_count > 1000)
					{
						TRACE("\E[40;37;1m %-42.42s : %10d call(s), %10.2f ms, %9.3f ms/API, %9.3f ms/API(P) \E[0m\n",
						      current->name, current->call_count, elapsed_time, elapsed_time_per_call, elapsed_time_per_call_period);
						current->traced = 1;
					}
				}
				current = current->next;
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
					Trace_Data *current = ftd_table[i];

					while (current != NULL)
					{
						if (current->traced == 0)
						{
							double elapsed_time = _get_timeval(current->elapsed_time);
							double elapsed_time_per_call = elapsed_time / current->call_count;

							TRACE(" %-42.42s : %10d call(s), %10.2f ms, %9.3f ms/API\n",
							      current->name, current->call_count, elapsed_time, elapsed_time_per_call);
						}
						current = current->next;
					}
				}
			}
		}
	}

	TRACE("\E[40;34m========================================================================================================================\E[0m\n");

	TRACE("\E[40;36;1m %-42.42s : %13.2f ms[%6.2f%%], %13.2f ms(P)[%6.2f%%]\E[0m\n",
	      "TOTAL elapsed Time",
	      total_elapsed_time,
	      100.0,
	      total_elapsed_time_period,
	      100.0);


	TRACE("\E[40;36;1m %-42.42s : %13.2f ms[%6.2f%%], %13.2f ms(P)[%6.2f%%]\E[0m\n",
	      "OpenGL elapsed Time",
	      total_opengl_elapsed_time,
	      total_opengl_elapsed_time * 100.0 / total_elapsed_time,
	      total_opengl_elapsed_time_period,
	      total_opengl_elapsed_time_period * 100.0 / total_elapsed_time_period);

	TRACE("\E[40;36;1m %-42.42s : %13.2f ms[%6.2f%%], %13.2f ms(P)[%6.2f%%]\E[0m\n",
	      "Out of OpenGL elapsed time",
	      total_other_elapsed_time,
	      total_other_elapsed_time * 100.0 / total_elapsed_time,
	      total_other_elapsed_time_period,
	      total_other_elapsed_time_period * 100.0 / total_elapsed_time_period);

	TRACE("\E[40;36;1m %-42.42s : %13.2f ms[%6.2f%%], %13.2f ms(P)[%6.2f%%]\E[0m\n",
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
			Trace_Data *current = ftd_table[i];

			while (current != NULL)
			{
				current->last_call_count = current->call_count;
				current->last_elapsed_time = current->elapsed_time;
				current->last_total_elapsed_time = current->total_elapsed_time;
				current = current->next;
			}
		}
	}

	TRACE_END();

	goto finish;

finish:
	return;
}

