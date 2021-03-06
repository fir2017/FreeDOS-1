/* $Id: alloc_ed.c 254 2001-06-25 20:06:36Z skaus $

	as _fdupstr(), but runs error_out_of_memory() on error
*/

#include <stdlib.h>

#include <assert.h>

#include <fmemory.h>

#include "../err_fcts.h"
#include "../include/misc.h"

char *edupstr(const char far* const s)
{	void *h;

	if((h = _fdupstr(s)) == 0)
		error_out_of_memory();

	return h;
}
