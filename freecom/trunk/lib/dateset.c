/*	$Id: dateset.c 1580 2011-04-27 15:51:33Z bartoldeman $

	Set DOS date (for Turbo C prior v3)

	This file bases on DATEFUNC.C of FreeCOM v0.81 beta 1.

	$Log$
	Revision 1.2  2004/02/01 13:52:17  skaus
	add/upd: CVS $id$ keywords to/of files

	Revision 1.1  2001/04/12 00:33:53  skaus
	chg: new structure
	chg: If DEBUG enabled, no available commands are displayed on startup
	fix: PTCHSIZE also patches min extra size to force to have this amount
	   of memory available on start
	bugfix: CALL doesn't reset options
	add: PTCHSIZE to patch heap size
	add: VSPAWN, /SWAP switch, .SWP resource handling
	bugfix: COMMAND.COM A:\
	bugfix: CALL: if swapOnExec == ERROR, no change of swapOnExec allowed
	add: command MEMORY
	bugfix: runExtension(): destroys command[-2]
	add: clean.bat
	add: localized CRITER strings
	chg: use LNG files for hard-coded strings (hangForEver(), init.c)
		via STRINGS.LIB
	add: DEL.C, COPY.C, CBREAK.C: STRINGS-based prompts
	add: fixstrs.c: prompts & symbolic keys
	add: fixstrs.c: backslash escape sequences
	add: version IDs to DEFAULT.LNG and validation to FIXSTRS.C
	chg: splitted code apart into LIB\*.c and CMD\*.c
	bugfix: IF is now using error system & STRINGS to report errors
	add: CALL: /N
	
 */

#include "../config.h"

#ifdef _NO__DOS_DATE
	/* Use this source only if the compiler does no provide this
		function of its own. */

#include <assert.h>

#include <assert.h>
#include <dos.h>
#include <portable.h>
#include "../include/datefunc.h"

unsigned _dos_setdate(struct dosdate_t *d)
{
  IREGS r;

  assert(d);
  r.r_ax = 0x2B00;
  r.r_cx = d->year;
  r.r_dx = d->month << 8;
  r.r_dx += d->day & 0xFF;

  intrpt(0x21, &r);

  if (r.r_ax & 0x00FF)
    return 1;
  return 0;
}


#endif                          /* _NO_DATE */
