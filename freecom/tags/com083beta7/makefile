# $Id: makefile 189 2001-04-12 00:09:06Z skaus $
#
# Makefile for the FreeDOS kernel's command interpreter
#
# $Log$
# Revision 1.14  2001/04/12 00:09:06  skaus
# chg: New structure
# chg: If DEBUG enabled, no available commands are displayed on startup
# fix: PTCHSIZE also patches min extra size to force to have this amount
#    of memory available on start
# bugfix: CALL doesn't reset options
# add: PTCHSIZE to patch heap size
# add: VSPAWN, /SWAP switch, .SWP resource handling
# bugfix: COMMAND.COM A:\
# bugfix: CALL: if swapOnExec == ERROR, no change of swapOnExec allowed
# add: command MEMORY
# bugfix: runExtension(): destroys command[-2]
# add: clean.bat
# add: localized CRITER strings
# chg: use LNG files for hard-coded strings (hangForEver(), init.c)
# 	via STRINGS.LIB
# add: DEL.C, COPY.C, CBREAK.C: STRINGS-based prompts
# add: fixstrs.c: prompts & symbolic keys
# add: fixstrs.c: backslash escape sequences
# add: version IDs to DEFAULT.LNG and validation to FIXSTRS.C
# chg: splitted code apart into LIB\*.c and CMD\*.c
# bugfix: IF is now using error system & STRINGS to report errors
# add: CALL: /N
#
#

.IMPORT : FREEDOS
.IMPORT .IGNORE : LNG DEBUG NDEBUG

INCDIR +=;$(FREEDOS)\SRC\INCLUDE;$(PWD)\\INCLUDE
LIBDIR +=;$(FREEDOS)\SRC\LIB\$(_COMPILER)
LDLIBS = $(FREEDOS)\SRC\LIB\$(_COMPILER)\Suppl_$(_MODEL).lib CMD\\CMDS.LIB LIB\\FREECOM.LIB STRINGS\\STRINGS.LIB
LDFLAGS += /msl
NASM *= c:\TOOL\NASMW.EXE

# Use BC5 linker in order to use TD of BC5
LD_TLINK != D:\BC5\BIN\TLINK.EXE

# Project specific C compiler flags
MYCFLAGS_DBG = -UNDEBUG $(null,$(DEBUG) $(NULL) -DDEBUG=1)
MYCFLAGS_NDBG = -DNDEBUG=1 -UDEBUG
MYCFLAGS = $(null,$(NDEBUG) $(MYCFLAGS_DBG) $(MYCFLAGS_NDBG))

# Project specific NASM compiler flags
NASMFLAGS_DBG = $(null,$(DEBUG) $(NULL) -DDEBUG=1) -s
NASMFLAGS_NDBG = -s
NASMFLAGS = $(null,$(NDEBUG) $(NASMFLAGS_DBG) $(NASMFLAGS_NDBG))

RUNMAKE = $(MAKE) LNG=$(LNG) NASM=$(NASM) DEBUG=$(DEBUG) NDEBUG=$(NDEBUG) MODEL=$(MODEL)

GLOBAL_DEPS = err_fcts.h

.SOURCE.lib := $(LIBDIR:s/;/ /:u)

# Sources of this make target
SRC = 


.INCLUDE .IGNORE : lastmake.mk

THISMAKE !:= $(_COMPILER):$(_MODEL):$(LNG):$(null,$(NDEBUG) DBG NDBG):$(LNG)

#	Default target
all: com.com tools

.INIT .PHONY .SEQUENTIAL : verscheck $(CFG) __errl tags

tags :
	ctags cmd\*.c lib\*.c shell\*.c

.IF $(THISMAKE) == $(LASTMAKE)
verscheck :;
.ELSE
verscheck : 
	@+-echo Changed Make parameters, already made files invalid!
	+-echo LASTMAKE = $(THISMAKE) >lastmake.mk
	$(RUNMAKE) clobber
.IF $(CFG)
	$(RUNMAKE) $(CFG)
.ENDIF
.ENDIF

__errl:
	@+-if exist errlist del errlist >nul
#	-ctags *.c

com.com .SEQUENTIAL : utils strings criter lib cmd shell\\com.exe infores
	@+copy /b shell\\com.exe + infores + criter\\criter + criter\\criter1 + strings\\strings.dat $@

infores : config.h include/command.h shell\\com.exe shell/com.map
	utils\mkinfres.exe /T$@.txt $@ shell\\com.map shell\\com.exe

context : criter

shell\\com.exe : shell

subdirs.mk : makefile
	perl mksubmk.pl >$@

.INCLUDE : subdirs.mk

err_fcts.h : lib\\err*.c ; perl lib\\scanerr.pl lib\\err*.c >$@

#MAKEDEP START
#MAKEDEP STOP

clobber : $(CLOBBER_DEPENDENCIES) my_clean
	$(RM) $(RMFLAGS) *.com *.cln subdirs.mk err_fcts.h *.cfg

clean : $(CLEAN_DEPENDENCIES) 

dist : err_fcts.h utils $(DIST_DEPENDENCIES)

command.lsm : command.com
	perl get_vers.pl $<


my_clean :
	$(RM) $(RMFLAGS) *.lst *.map *.bin *.bak *.las *.obj *.exe $(CFG) *.dmp
	$(RM) $(RMFLAGS) strings.dat strings.h context.h_c criter1 criter2 context.inc infores

