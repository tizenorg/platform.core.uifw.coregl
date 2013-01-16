#include "coregl_internal.h"

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int                 trace_api_flag = 0;
int                 trace_api_all_flag = 0;
int                 trace_ctx_flag = 0;
int                 trace_ctx_force_flag = 0;
int                 trace_mem_flag = 0;
int                 trace_mem_all_flag = 0;
int                 trace_state_flag = 0;

General_Trace_List *thread_trace_list = NULL;
Mutex               general_trace_lists_access_mutex = MUTEX_INITIALIZER;


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

