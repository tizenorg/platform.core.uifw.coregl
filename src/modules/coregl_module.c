#include "../coregl_internal.h"

// TRACEPATH module
#include "tracepath/coregl_tracepath.h"
#undef MY_MODULE_ID
#undef MY_MODULE_TSTATE

// FASTPATH module
#include "fastpath/coregl_fastpath.h"
#undef MY_MODULE_ID
#undef MY_MODULE_TSTATE

// APIOPT module
#include "appopt/coregl_appopt.h"
#undef MY_MODULE_ID
#undef MY_MODULE_TSTATE

void
init_modules()
{
	// Step 1 : Initialization
	init_export();

	// Step 2 : User Define Modules : Sequence is important! (Last module's API is called first)
	init_modules_fastpath();
	init_modules_appopt();

	// Step 3 : Common Wrapping Modules
	init_modules_tracepath();
}

void
deinit_modules()
{
	// Step 1(rollback init 3) : Common Wrapping Modules
	deinit_modules_tracepath();

	// Step 2(rollback init 2) : User Define Modules : Sequence is important!
	deinit_modules_appopt();
	deinit_modules_fastpath();

	// Step 3(rollback init 1) : De-Initialization
	deinit_export();
}

void
init_modules_tstate(GLThreadState *tstate)
{
	// Initialization for each thread state : Sequence is important!
	init_modules_tstate_tracepath(tstate);
	init_modules_tstate_fastpath(tstate);
	init_modules_tstate_appopt(tstate);
}

void
deinit_modules_tstate(GLThreadState *tstate)
{
	// De-Initialization for each thread state(rollback) : Sequence is important!
	deinit_modules_tstate_appopt(tstate);
	deinit_modules_tstate_fastpath(tstate);
	deinit_modules_tstate_tracepath(tstate);
}

