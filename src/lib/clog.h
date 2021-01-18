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
 * which can be set by ClogSetLogLevel. If using pthreads (with option
 * CLOG_USE_PTHREAD), then logging will only run on thread that called
 * `ClogInitialize`.
 */
extern int ClogLog(ClogLevel,char*fmt,...);

/**
 * Register function pointer as an initialization callback, to be called with
 * argument `arg`. Callback should return 0 on success, nonzero on failure.
 * This capability can be used to open/close a file pointer or create/free
 * resources when needed.
 *
 * Warning: there is no garuntee which order the callbacks will be ran in. If
 * you need callbacks to be ordered, call both of them in the correct order
 * from a single function and register *that* function as the callback.
 */
extern int ClogRegisterInitializeCallback(int (*fp)(),void*arg);

/**
 * Register function pointer as a finalization callback, to be called with
 * argument `arg`. Callback should return 0 on success, nonzero on failure.
 */
extern int ClogRegisterFinalizeCallback(int (*fp)(),void*arg);

/** Ignore pthread locking and log on each thread no matter what. */
extern int ClogIgnorePthread();

#define CHKERR(ierr) assert(!ierr);

#endif
