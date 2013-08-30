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

#define COREGL_OVERRIDE_API(mangle, func, funcalias, prefix) \
	mangle##funcalias = prefix##func

#define COREGL_INIT_ORIGINAL(orig_prefix, f, falias) \
{ \
	if (enable == 1) \
	{ \
		AST(orig_prefix##falias == NULL); \
		if (ovr##f != NULL) COREGL_OVERRIDE_API(orig_prefix, f, falias, ovr_); \
	} \
	else \
	{ \
		AST(ovr_##falias != NULL); \
		COREGL_OVERRIDE_API(ovr_, falias, falias, orig_prefix); \
		orig_prefix##falias = NULL; \
	} \
}

#define COREGL_OVERRIDE(prefix, f, falias) \
	if (enable == 1) \
	{ \
		COREGL_OVERRIDE_API(ovr_, f, falias, prefix); \
	}

#endif // COREGL_MODULE_H

