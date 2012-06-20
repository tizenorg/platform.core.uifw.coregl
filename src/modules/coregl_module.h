#ifndef COREGL_MODULE_H
#define COREGL_MODULE_H

#define COREGL_USE_MODULE_TRACEPATH
#define COREGL_USE_MODULE_FASTPATH
#define COREGL_USE_MODULE_APPOPT


typedef enum
{
	COREGL_MODULE_TRACEPATH = 0,
	COREGL_MODULE_FASTPATH = 1,
	COREGL_MODULE_APPOPT = 2
} CoreGL_Modules;

#define COREGL_MAX_MODULES		5

#define GET_MY_TSTATE(val, stmt) \
	if (stmt != NULL) \
		val = ((MY_MODULE_TSTATE *)(stmt)->module_data[MY_MODULE_ID]); \
	else \
		val = NULL

#endif // COREGL_MODULE_H

