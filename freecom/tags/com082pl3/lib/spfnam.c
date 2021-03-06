/* $Id: spfnam.c 364 2002-04-02 18:13:06Z skaus $

	skip filename token

	return the pointer of the next character that is no is_fnchar()

*/

#include "../config.h"

#include "../include/misc.h"


char *skipfnam(const char * const fnam)
{	const char *p;

	assert(fnam);
	p = fnam - 1;
	while(is_fnam(*++p));
	return p;
}
