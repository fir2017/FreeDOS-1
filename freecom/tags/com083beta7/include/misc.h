/*
 * MISC.C -- Misc. Functions declarations
 *
 * 2000/07/13 ska
 *	started
 */

#ifndef MISC_H
#define MISC_H

#include <stdio.h>
#include <portable.h>

#include "../include/datefunc.h"
#include "../include/timefunc.h"

enum OnOff {		/* ON/OFF tester */
	OO_Empty = 0,		/* Empty line */
	OO_Null,			/* NULL line */
	OO_On,				/* "ON" */
	OO_Off,				/* "OFF" */
	OO_Other			/* else */
};

#define BREAK_BATCHFILE 1
#define BREAK_ENDOFBATCHFILES 2
#define BREAK_INPUT 3
#define BREAK_IGNORE 4
#define BREAK_FORCMD 5

#define cbreak chkCBreak(0)

#define MAXARGS 20
#define MAXLEN  256
#define exist dfnstat


int cgetchar(void);
int vcgetchar(void);
int vcgetcstr(const char *const legalCh);
int keypressed(void);
int cgetchar_timed(int secs);
int chkCBreak(int mode);
void beep(void);
void beep_low(void);
char *comFile(void);
char *comPathFile(const char * fnam);
char *comResFile(void);
#define comRespawnFile comResFile
void dispCount(int cnt, unsigned base_id);
int drvNum(int drive);
char *cwd(int drive);
int changeDrive(int drive);
int mk_rd_dir(char *param, int (*func) (const char *), char *fctname);
void cutBackslash(char * const s);
int cd_dir(char *param, int cdd, const char * const fctname);
enum OnOff onoffStr(char *line);
size_t farread(void far*buf, size_t length, FILE *f);
unsigned allocPermBlk(const unsigned size, const unsigned mode);
unsigned allocSysBlk(const unsigned size, const unsigned mode);
void freeSysBlk(const unsigned segm);

char far *_fstpcpy(char far *dst, const char far *src);
void partstrlower(char *str);
void readcommandDOS(char * const str, int maxlen);
void readcommandEnhanced(char * const str, const int maxlen);
void convert(unsigned long num, char * const des);

void goxy(const unsigned char x, const unsigned char y);
void clrcmdline(char * const str, const int maxlen
 , const unsigned orgx, const unsigned orgy);

int decode_exec_result(int rc);
int exec(const char *, char *, const unsigned);

int samefile(const char * const f1, const char * const f2);
/* void fillComp(char * const dst, const char *pattern, const char *src, int len); */
char *fillFnam(const char * const pattern, const char * const fnam);
int is_fnchar(const int c);
int is_fnstr(const char * const s);
int is_pathdelim(const int c);
int is_empty(const char *s);
// int is_quote(const int c);
#define is_quote(c)	((c) == '"')

FILE *tempfile(void);
void rmtmpfile(void);


/************* Imported from LH.ASM        */

int dosGetUMBLinkState(void);
void dosSetUMBLinkState(int newState);
int dosGetAllocStrategy(void);
void dosSetAllocStrategy(int newState);
word GetFirstMCB(void);



char *curTime(void);
char *curDateLong(void);
int parsedate(const char * s, struct dosdate_t * const datep);
int parsetime(const char * s, struct dostime_t * const timep);

void displayPrompt(const char *pr);
void printprompt(void);
int showcmds(char *rest);
void grabComFilename(const int warn, const char far * const fnam);

void displayString(unsigned id,...);
int userprompt(unsigned id,...);
int getPromptString(unsigned id, char ** const chars, char ** const fmt);
#define freePromptString(chars,fmt)	free(chars)
int mapMetakey(const char * const chars, int ch);
char *getMessage(unsigned id);
char *defaultMessage(unsigned id);
char *getString(unsigned id);
void unloadMsgs(void);
unsigned msgSegment(void);

char *tmpfn(void);
char *mktempfile(const char * const path, const char *ext);
void killtmpfn(char * const);

char *find_which(const char * const fname);
int getbreak(void);
void setbreak(const int OnOff);

char *getEnv(char *);
int chgEnv(const char[], const char[]);
int chgEnvRemove(const char[], const char[]);
int chgEnvCase(const int, char[], const char[]);

char *trim(char *str);
char *ltrim(const char *str);
void rtrim(char * const str);
char *parsenum(const char *s, int maxCnt, int *cnt, int nums[]);
char *textlineEnd(const char * const buf, const size_t buflen);

/*
void aliasprint(void);
void aliaschange(const char * const name, const char * const value);

char *alias_mangleFNam(const char * const name);
word alias_find(char * const tagged_name);
*/


/* wrapper functions for ..\include\context.h
	- may disapeear in the future */
/* history wrapper: negative idx --> from end of buffer;
	currently no non-negative idx used */
int histGet(const int num, char * const str, const unsigned len);
void histSet(const int num, const char * const str);

void lastDirSet(void);
void lastDirGet(char ** const buf);


#endif
