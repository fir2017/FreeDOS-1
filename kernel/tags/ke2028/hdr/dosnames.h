/****************************************************************/
/*                                                              */
/*                          dosnames.h                          */
/*                                                              */
/*               FAT File System Name Parse Structure           */
/*                                                              */
/*                         March 5, 1995                        */
/*                                                              */
/*                      Copyright (c) 1995                      */
/*                      Pasquale J. Villani                     */
/*                      All Rights Reserved                     */
/*                                                              */
/* This file is part of DOS-C.                                  */
/*                                                              */
/* DOS-C is free software; you can redistribute it and/or       */
/* modify it under the terms of the GNU General Public License  */
/* as published by the Free Software Foundation; either version */
/* 2, or (at your option) any later version.                    */
/*                                                              */
/* DOS-C is distributed in the hope that it will be useful, but */
/* WITHOUT ANY WARRANTY; without even the implied warranty of   */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See    */
/* the GNU General Public License for more details.             */
/*                                                              */
/* You should have received a copy of the GNU General Public    */
/* License along with DOS-C; see the file COPYING.  If not,     */
/* write to the Free Software Foundation, 675 Mass Ave,         */
/* Cambridge, MA 02139, USA.                                    */
/****************************************************************/

#ifdef MAIN
#ifdef VERSION_STRINGS
static BYTE *dosnames_hRcsId =
    "$Id: dosnames.h 485 2002-12-09 00:17:15Z bartoldeman $";
#endif
#endif

#define PARSE_MAX 64

struct dosnames {
  UBYTE dn_drive;               /* the drive that was parsed    */
  UBYTE dn_network[PARSE_MAX];  /* specified network            */
  UBYTE dn_path[PARSE_MAX];     /* the path                     */
  UBYTE dn_name[FNAME_SIZE + FEXT_SIZE + 1];    /* the file name       */
};

