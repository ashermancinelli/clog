#ifndef _CLOG_H
#define _CLOG_H
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

typedef enum
{
  CLOG_LEVEL_INFO=0,
  CLOG_LEVEL_WARN,
  CLOG_LEVEL_ERROR,
} ClogLevel;
extern int ClogInitialize();
extern int ClogFinalize();
extern int ClogSetLogLevel(ClogLevel);
extern int ClogLog(ClogLevel,char*fmt,...);
#define CHKERR(ierr) assert(!ierr);

#endif
