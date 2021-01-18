#ifndef _CLOG_H
#define _CLOG_H
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

/** Possible levels of logging available */
typedef enum
{
  CLOG_LEVEL_INFO=0,
  CLOG_LEVEL_WARN,
  CLOG_LEVEL_ERROR,
} ClogLevel;

/** Creates logger; must be called before anything can be logged. */
extern int ClogInitialize();

/**
 * Destroys logger; please call before returning from main to prevent memory
 * leaks
 */
extern int ClogFinalize();

/**
 * Set minimum loglevel a log must be to be printed. By default, this is
 * CLOG_LEVEL_INFO.
 */
extern int ClogSetLogLevel(ClogLevel);

/**
 * Set minimum loglevel a log must be to be printed. By default, this is
 * CLOG_LEVEL_INFO.
 */
extern int ClogGetLogLevel(ClogLevel*);

/** Set format string used to format dates internally in the logger */
extern int ClogSetTimeFormat(char*);

/**
 * Set format string used to format time and log message. String should have
 * three occurances of '%s', one for the time string, one for the
 * logging type, and another for the message.
 */
extern int ClogSetFormat(char*);

/**
 * Logs information if given ClogLevel is at least the minimum logging level,
 * which can be set by ClogSetLogLevel.
 */
extern int ClogLog(ClogLevel,char*fmt,...);

#define CHKERR(ierr) assert(!ierr);

#endif
