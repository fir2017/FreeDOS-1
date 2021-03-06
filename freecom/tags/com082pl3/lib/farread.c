/*	$id$
	$Locker$	$Name$	$State$

 *	Read a block of data from a FILE* into far memory
 *	Return 0 on failure, otherwise the number of read bytes

	This file bases on MISC.C of FreeCOM v0.81 beta 1.

	$Log$
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

#include <assert.h>
#include <dos.h>
#include <io.h>
#include <stdio.h>

#include "../include/misc.h"

size_t farread(void far*buf, size_t length, FILE *f)
{	struct REGPACK r;

	/* synchronize FILE* with file descriptor in order to be able to
		call the DOS API */
	lseek(fileno(f), ftell(f), SEEK_SET);
	/* Use DOS API in order to read the strings directly to the
		far address */
	r.r_ax = 0x3f00;              /* read from file descriptor */
	r.r_bx = fileno(f);           /* file descriptor */
	r.r_cx = length;              /* size of block to read */
	r.r_ds = FP_SEG(buf);         /* segment of buffer to read block to */
	r.r_dx = FP_OFF(buf);         /* offset of buffer to read block to */
	intr(0x21, &r);               /* perform DOS API */
	if ((r.r_flags & 1) != 0)     /* read failed */
		return 0;

	return r.r_ax;
}
