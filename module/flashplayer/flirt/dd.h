/*
 Flirt, an SWF rendering library
 Copyright (c) 2004-2006 Dave Hayden <dave@opaque.net>
 All rights reserved.
 
 http://www.opaque.net/flirt/

 This code is distributed under the two-clause BSD license.
 Read the LICENSE file or visit the URL above for details
*/

#ifndef DD_H_INCLUDED
#define DD_H_INCLUDED

#include <stdlib.h>

#include "config.h"
#include "types.h"

#if defined(WIN32)
// Visual Studio C 6++ ->
#pragma warning( disable : 4244 )  // Disable warning messages in simulation
#pragma warning( disable : 4761 )  // Disable warning "integral size mismatch in argument; conversion supplied"
#pragma warning( disable : 4305)   // truncation from 'const double ' to 'float '
#pragma warning( disable : 4049)   // compiler limit : terminating line number emission
// Visual Studio 2008 ->
#pragma warning( disable : 4996)   // 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#endif 

#ifdef DD_LOG

#ifndef DD_PLATFORM_SYMBIAN 

#include <stdio.h>
extern FILE* logfile ;
void dd_log(const char* msg, ...) ;

#else

#include <flogger.h>
extern RFileLogger flogger ; 
void dd_log(const char * msg, ...) ; 

#endif

#else

static void dd_log() {}

#endif

#define dd_malloc(l)     malloc(l)
#define dd_realloc(p,l)  realloc((p),(l))
#define dd_free(p)       free(p)

extern long dd_startTime;
extern void (*dd_error)(const char* msg, ...);
extern void (*dd_warn)(const char* msg, ...);


typedef  int boolean ; 

boolean
dd_init();

boolean
dd_close() ; 

void
dd_setErrorFunction(void (*error)(const char* msg, ...));

void
dd_setWarnFunction(void (*warn)(const char* msg, ...));

unsigned long dd_getTicks();

#endif /* DD_H_INCLUDED */
