/*
 *  RES.C - Resource handling for FreeCOM
 *
 *	Contains all functions specific for FreeCOM
 *
 *	int enumResources(altFnam, res_majorid_t, int (*fct)(), void * arg)
 *		Searches for all resources of the specified major ID in the
 *		primary resource file, which is usually the execuatble itself.
 *		On "open error: (rc == -1) the alternate filename "altFnam" is
 *		tried, too.
 *		The callback function is called like this:
 *			int fct(res_majorid_t, res_minorid_t, length, FILE*, arg)
 *		The "length" parameter specifies the length of the data
 *		block (unsigned long), the file is the resource file opened
 *		in "r+b" modus <<be careful!!>>, "arg" is the pointer passed to
 *		enumREsources().
 *		The callback function may reposition the file, though, the file
 *		itself must not be closed.
 *
 *		If the callback function returns 0 (zero), the loop continues,
 *		otherwise enumResource() is terminated and this value is returned.
 *
 *
 *	Return:
 *		0: Nothing found or callback function always returned "0" itself
 *		else: return value of callback function
 *		-1: file open error
 *
 * 2000/07/13 ska
 * started
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "resource.h"
#include "debug.h"
#include "command.h"

int enumResources(const char * const altFNam
	, res_majorid_t id
	, int (*fct)()
	, void * const arg)
{	int rc;

		/* We use enumResoures() to load a resource we know it must there,
			and, if so, the callback function returns != 0
				--> If enumFR() returns == 0 --> is equal to "not found"
				--> we try the alternate file */
	if(((rc = enumFileResources(comFile(), id, fct, arg)) == -1 || rc == 0)
	 && altFNam && (rc = enumFileResources(altFNam, id, fct, arg)) == -1)
	 	dprintf( ("[No resource file %s found!]\n", altFNam? altFNam: "??") );

	return rc;
}
