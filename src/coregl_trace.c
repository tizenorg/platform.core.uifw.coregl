#include "coregl_internal.h"

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX_TRACE_NAME_LENGTH 256
#define MAX_TRACE_TABLE_SIZE 65536

struct _Trace_Data
{
	char                         name[MAX_TRACE_NAME_LENGTH];
	int                          call_count;
	int                          last_call_count;
	long                         elapsed_time;
	long                         last_elapsed_time;
	struct timeval              last_time;

	int                          traced;

	struct _Trace_Data          *next;
};

General_Trace_List *thread_trace_list = NULL;
Mutex               general_trace_lists_access_mutex = MUTEX_INITIALIZER;

int                 trace_api_flag = 1;


static unsigned short
_generate_hash_short(const char *string)
{
	unsigned short hash = 0;
	int i;
	for (i = 0; i < strlen(string); i++)
	{
		hash = 253 * hash + string[i];
	}
	return hash ^ (hash >> 8);
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

	while (current != NULL)
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

void
trace_begin(const char *funcname)
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

	if (trace_api_flag == 1)
	{
		Trace_Data *ftd = _get_trace_data(tstate->ftd_table, funcname);
		AST(ftd != NULL);

		ftd->call_count++;
		AST(ftd->last_time.tv_sec == 0);

		AST(gettimeofday(&ftd->last_time, NULL) == 0);
	}
}

void
trace_end(const char *funcname)
{
	GLThreadState *tstate = NULL;
	struct timeval t = {0};

	AST(gettimeofday(&t, NULL) == 0);

	tstate = get_current_thread_state();

	if (tstate == NULL)
	{
		init_new_thread_state();

		tstate = get_current_thread_state();
		AST(tstate != NULL);
	}

	AST(tstate->ftd_table != NULL);

	if (trace_api_flag == 1)
	{
		Trace_Data *ftd = _get_trace_data(tstate->ftd_table, funcname);
		AST(ftd != NULL);

		ftd->elapsed_time +=
		    (t.tv_sec - ftd->last_time.tv_sec) * 100000 +
		    (t.tv_usec - ftd->last_time.tv_usec) / 10;
		ftd->last_time.tv_sec = 0;
	}
}

void
trace_output(int force_output)
{
	static struct timeval tv_last = { 0, 0 };
	GLThreadState *tstate = NULL;
	Trace_Data **ftd_table = NULL;
	int i;

	{
		char *fp_env = NULL;
		int fp_envi = 0;
		fp_env = getenv("COREGL_TRACE_API");
		if (fp_env) fp_envi = atoi(fp_env);
		else fp_envi = 0;
		if (fp_envi == 0) return;
	}

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

	tstate = get_current_thread_state();

	if (tstate == NULL)
	{
		init_new_thread_state();

		tstate = get_current_thread_state();
		AST(tstate != NULL);
	}


	ftd_table = tstate->ftd_table;
	if (ftd_table == NULL) return;

	LOG("\n");
	LOG("\E[0;40;34m========================================================================================================================\E[0m\n");
	LOG("\E[0;32;1m  API call info \E[1;37;1m: Thread ID = %d\E[0m\n", tstate->thread_id);
	LOG("\E[0;40;34m========================================================================================================================\E[0m\n");

	// highlighted
	for (i = 0; i < MAX_TRACE_TABLE_SIZE; i++)
	{
		if (ftd_table[i] != NULL)
		{
			Trace_Data *current = ftd_table[i];

			while (current != NULL)
			{
				double elapsed_time = current->elapsed_time / 100.0;
				double elapsed_time_per_call = elapsed_time / current->call_count;

				current->traced = 0;

				if (current->call_count > current->last_call_count)
				{
					double elapsed_time_period = (current->elapsed_time - current->last_elapsed_time) / 100.0;
					double elapsed_time_per_call_period = elapsed_time_period / (current->call_count - current->last_call_count);

					if (elapsed_time_per_call_period >= 0.01)
					{
						LOG("\E[0;37;1m %-42.42s : %10d call(s), %10.2f ms, %9.2f ms/API, %9.2f ms/API(P) \E[0m\n",
						    current->name, current->call_count, elapsed_time, elapsed_time_per_call, elapsed_time_per_call_period);
						current->traced = 1;
					}
				}
				current = current->next;
			}
		}
	}

	{
		char *fp_env = NULL;
		int fp_envi = 0;
		fp_env = getenv("COREGL_TRACE_API_ALL");
		if (fp_env) fp_envi = atoi(fp_env);
		else fp_envi = 0;
		if (fp_envi != 0)
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
							double elapsed_time = current->elapsed_time / 100.0;
							double elapsed_time_per_call = elapsed_time / current->call_count;

							LOG(" %-42.42s : %10d call(s), %10.2f ms, %9.2f ms/API\n",
							    current->name, current->call_count, elapsed_time, elapsed_time_per_call);
						}
						current = current->next;
					}
				}
			}
		}
	}

	for (i = 0; i < MAX_TRACE_TABLE_SIZE; i++)
	{
		if (ftd_table[i] != NULL)
		{
			Trace_Data *current = ftd_table[i];

			while (current != NULL)
			{
				current->last_call_count = current->call_count;
				current->last_elapsed_time = current->elapsed_time;
				current = current->next;
			}
		}
	}

	LOG("\E[0;40;34m========================================================================================================================\E[0m\n");
	LOG("\n");

	goto finish;

finish:
	return;
}

