/*
minibz2
libbz2.dll test program.
by Yoshioka Tsuneo (tsuneo@rr.iij4u.or.jp)
This file is Public Domain.  Welcome any email to me.

usage: minibz2 [-d] [-{1,2,..9}] [[srcfilename] destfilename]
*/

#define BZ_IMPORT
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <stdbool.h>
#include "bzlib.h"
#ifdef _WIN32
#include <io.h>
#endif

#ifdef _WIN32

#define BZ2_LIBNAME "libbz2.dll" 

#include <windows.h>
static int BZ2DLLLoaded = 0;
static HINSTANCE BZ2DLLhLib;
int BZ2DLLLoadLibrary(void);

int BZ2DLLFreeLibrary(void);
#endif /* WIN32 */

bool init();

bool destroy();

bool decompress(char *fn_r, char *fn_w, int level);

bool compress(char *fn_r, char *fn_w, int level);
