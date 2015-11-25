#include "coregl_internal.h"

//////////////////////////////////////////////////////////////////////////
// Need implement this
int mutex_init(Mutex *mt);
int mutex_lock(Mutex *mt);
int mutex_unlock(Mutex *mt);
int get_current_thread();
int set_current_thread_state(GLThreadState *tstate);
GLThreadState * get_current_thread_state();
//////////////////////////////////////////////////////////////////////////

static __thread GLThreadState *per_thread_state = NULL;

int
mutex_init(Mutex *mt)
{
	int ret = 0;

	if (pthread_mutex_init(mt, NULL) == 0)
		ret = 1;
	else
		ret = 0;

	return ret;
}


int
mutex_lock(Mutex *mt)
{
	int ret = 0;

	if (pthread_mutex_lock(mt) == 0)
		ret = 1;
	else
		ret = 0;

	return ret;
}

int
mutex_unlock(Mutex *mt)
{
	int ret = 0;

	if (pthread_mutex_unlock(mt) == 0)
		ret = 1;
	else
		ret = 0;

	return ret;
}

int
get_current_thread()
{
	return pthread_self();
}

int
set_current_thread_state(GLThreadState *tstate)
{
	per_thread_state = tstate;
	return 1;
}

GLThreadState *
get_current_thread_state()
{
	return per_thread_state;
}


