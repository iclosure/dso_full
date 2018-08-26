/*
 Flirt, an SWF rendering library
 Copyright (c) 2004-2006 Dave Hayden <dave@opaque.net>
 All rights reserved.
 
 http://www.opaque.net/flirt/

 This code is distributed under the two-clause BSD license.
 Read the LICENSE file or visit the URL above for details
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
//#include <sys/time.h>
//#include <sys/timeb.h>

#include "dd.h"

#ifdef DD_LOG

#ifndef DD_PLATFORM_SYMBIAN 
FILE* logfile = NULL;
#else
RFileLogger flogger ; 
#endif

static int enable_log = 0;
long dd_startTime = 0;

#endif

boolean
dd_init()
{
#ifdef DD_LOG

#ifndef DD_PLATFORM_SYMBIAN
	logfile = fopen("/tmp/dd.log", "w");

	if ( logfile == NULL )
		return DD_FALSE;

	setlinebuf(logfile);
#else
	flogger.Connect() ; 
	flogger.CreateLog(_L("FlashTest"), _L("swfcore.log"), EFileLoggingModeOverwrite) ;
#endif

#endif

	return DD_TRUE;
}

boolean 
dd_close()
{
#ifdef DD_LOG

#ifndef DD_PLATFORM_SYMBIAN
	if(logfile) fclose(logfile) ; 

#else
	flogger.CloseLog() ; 
	flogger.Close() ; 
#endif

#endif
	return DD_TRUE;
}

unsigned long
dd_getTicks()
{
	return 1;
/*
	struct timeval t;
	gettimeofday(&t, NULL);

	return (t.tv_sec - dd_startTime) * 1000 + t.tv_usec / 1000;
*/
}

#ifdef DD_LOG
void
dd_log(const char* msg, ...)
{
	va_list args;
	if ( enable_log == 0 )
		return;

#ifndef DD_PLATFORM_SYMBIAN	
	va_start(args, msg);
	vfprintf(logfile, msg, args);
	fprintf(logfile, "\n");
	va_end(args);
#else 
	char std_buf8[128] ; 
	TBuf8<128> buf8 ; 
	va_list args;
	va_start(args, msg);
	vsprintf(std_buf8, msg, args);
	buf8.Append((unsigned char *)(std_buf8), strlen(std_buf8)) ; 
	flogger.Write(buf8) ; 
	va_end(args);
#endif
}

static void dd_error_default(const char* msg, ...)
{
#ifndef DD_PLATFORM_SYMBIAN
	va_list args;
	va_start(args, msg);
	vprintf(msg, args);
	putchar('\n');
	va_end(args);
	exit(-1);
#endif
}

static void dd_warn_default(const char* msg, ...)
{
#ifndef DD_PLATFORM_SYMBIAN
	va_list args;
	va_start(args, msg);
	vprintf(msg, args);
	putchar('\n');
	va_end(args);
#endif
}

#endif
static void dd_error_default(const char* msg, ...)
{
}

static void dd_warn_default(const char* msg, ...)
{
}
void (*dd_error)(const char* msg, ...) =dd_error_default;
void (*dd_warn)(const char* msg, ...) =dd_warn_default;

void dd_setErrorFunction(void (*error)(const char* msg, ...))
{
	dd_error = error;
}

void dd_setWarnFunction(void (*warn)(const char* msg, ...))
{
	dd_warn = warn;
}
