/* $Id: dat.c 295 2001-08-27 01:33:10Z  $ */

/* Functions for reading and dealing with the DAT file. */

/* Copyright (C) 1998-1999 Jim Hall, jhall1@isd.net */

/*
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/


#include <stdio.h>
#include <string.h>				/* for strtok */
#include "dat.h"

/* Symbolic constants */

#define STRLEN 80				/* size of a string */


dat_t *
dat_fread (FILE *stream, int *count)
{
  /* reads a dat file, into an array pointed to by dat_ary.
     The number of elements in the array (0 may indicate an 
     error) is placed in count, returns dat_ary, the array
     which the user should free() when no longer needed. 
  */

  char str[STRLEN];				/* for reading the line */
  char *s;					/* temporary pointer */
  dat_t *dat_ary;				/* array to hold data */
  int dat_size = 0;			/* holds needed malloc'd size */
  fpos_t iFilePosition;             /* stores initial file position */

  /* Read the file until end of file */

  *count = 0;

  /* Do two reads, 1st time through just count how many there are */

  /* 1st get file position, so can reset after 1st time through,
     we could just seek to the beginning, but there is guarentee
     the stream is at the beginning.
  */
  if (fgetpos(stream, &iFilePosition)) return NULL;

  /* Do 1st pass on the file data, getting just the count */
  while (fgets (str, STRLEN, stream) != NULL) {

    /* Ignore the line if 1st character is a # */
    if (*str == '#') continue;

    /* Ignore blank lines */
    if ( (*str == '\0') || ((*str == '\n') && (*(str+1) == '\0')) ) continue;

    /* Increment counter */
    dat_size++;

  } /* while */

  /* Reset file position */
  if (fsetpos(stream, &iFilePosition)) return NULL;

  /* Allocate necessary space (should be all space that is needed) */
  if ( (dat_size == 0) || ((dat_ary = (dat_t *)malloc(sizeof(dat_t) * dat_size)) == NULL) )
    return NULL;

  /* Actually read in the data */
  while (fgets (str, STRLEN, stream) != NULL) {

    /* Ignore the line if 1st character is a # */
    if (*str == '#') continue;

    /* Ignore blank lines */
    if ( (*str == '\0') || ((*str == '\n') && (*(str+1) == '\0')) ) continue;

    /* Break up the string into tokens */

    s = strtok (str, " :");

    if (s == NULL)
      {
	strncpy (dat_ary[*count].name, "", 1);
      }

    else
      {
	strncpy (dat_ary[*count].name, s, DAT_NAME_LEN);
      }

    s = strtok (NULL, " :");

    if (s == NULL)
      {
	dat_ary[*count].rank = '?';
      }

    else
      {
	dat_ary[*count].rank = s[0];
      }
    
    /* Check on the length of the array */

    *count += 1;

    if (*count > dat_size) {
        printf("INTERNAL ERROR: 2nd processing of data file yielded extra entries!\n");
        exit(1);
    }
  } /* while */

  /* Return */

  return (dat_ary);
}

dat_t *
dat_read (const char *filename, int *count)
{
  /* reads a dat file, into an array pointed to by dat_ary.
     The number of elements in the array (0 may indicate an 
     error) is placed in count, returns dat_ary, the array
     which the user should free() when no longer needed. 
  */

  FILE *stream;
  dat_t *ret;

  /* Open the file */

  stream = fopen (filename, "r");
  if (stream == NULL) {
    /* Failed */

    return (0);
  }

  /* Read the file */

  ret = dat_fread (stream, count);

  /* Close the file, and quit */

  fclose (stream);
  return (ret);
}
