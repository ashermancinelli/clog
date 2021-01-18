#include "clog.h"
#include <clog_config.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define CLOG_DEFAULT_BUF_SIZE 1024
#define CLOG_MAX_CALLBACKS 32

#ifdef CLOG_USE_PTHREAD
#include <pthread.h>
#endif

/** Default minimum log level */
static ClogLevel lvl=CLOG_LEVEL_INFO;

/** Default names for logging message struct values */
static const char *ClogLogNames[3]={"INFO","WARNING","ERROR",};

/** Default format string for timestamps. */
static char timefmt[CLOG_DEFAULT_BUF_SIZE]="%x - %I:%M%p";

/** Deafult format string for log messages. */
static char logfmt[CLOG_DEFAULT_BUF_SIZE]="[%s] [%s]: %s\n";

#ifdef CLOG_USE_PTHREAD
/**
 * PID which called `ClogInitialize`, eg the one in which logging occurs if
 * multithreaded.
 */
static pthread_t ClogParentThread=-1;
#endif

/**
 * Callbacks may be registered through api found in clog.h to perform setup
 * or teardown during initialization of logger.
 */
static int (*ClogInitializeCallbacks[CLOG_MAX_CALLBACKS])();
static void *ClogInitializeCallbackArgs[CLOG_MAX_CALLBACKS];
static int ClogNumInitializeCallbacks=0;

static int (*ClogFinalizeCallbacks[CLOG_MAX_CALLBACKS])();
static void *ClogFinalizeCallbackArgs[CLOG_MAX_CALLBACKS];
static int ClogNumFinalizeCallbacks=0;

int ClogIgnorePthread()
{
  ClogParentThread=-1;
  return 0;
}

int ClogRegisterInitializeCallback(int (*fp)(),void*arg)
{
  ClogInitializeCallbacks[ClogNumInitializeCallbacks]=fp;
  ClogInitializeCallbackArgs[ClogNumInitializeCallbacks++]=arg;
  return 0;
}

int ClogRegisterFinalizeCallback(int (*fp)(),void*arg)
{
  ClogFinalizeCallbacks[ClogNumFinalizeCallbacks]=fp;
  ClogFinalizeCallbackArgs[ClogNumFinalizeCallbacks++]=arg;
  return 0;
}

int ClogSetLogLevel(ClogLevel lvl_)
{
  lvl=lvl_;
  return 0;
}

int ClogGetLogLevel(ClogLevel *lvl_)
{
  *lvl_=lvl;
  return 0;
}

int ClogSetTimeFormat(char *fmt)
{
  strcpy(timefmt,fmt);
  return 0;
}

int ClogSetFormat(char *fmt)
{
  strcpy(logfmt,fmt);
  return 0;
}

int ClogGetTimeBuf(char**buf)
{
  time_t rawtime=time(NULL);assert(rawtime!=-1);
  struct tm *ptm=localtime(&rawtime);assert(ptm);
  *buf=malloc(CLOG_DEFAULT_BUF_SIZE);
  strftime(*buf,CLOG_DEFAULT_BUF_SIZE,timefmt,ptm);
  return 0;
}

int ClogLog(ClogLevel currlvl,char*fmt,...)
{
  if(currlvl<lvl)
    return 0;

#ifdef CLOG_USE_PTHREAD
  if(ClogParentThread!=-1 && pthread_self()!=ClogParentThread)
    return 0;
#endif
  
  int ierr=0;
  char buf[CLOG_DEFAULT_BUF_SIZE];
  char *timebuf;
  ierr=ClogGetTimeBuf(&timebuf);CHKERR(ierr);

  va_list args;
  va_start(args, fmt);
  vsprintf(buf, fmt, args);
  char *endl = strtok(buf, "\n");
  while (endl!=NULL)
  {
    fprintf(stdout,logfmt,timebuf,ClogLogNames[currlvl],endl);
    endl = strtok(NULL, "\n");
  }
  va_end(args);
  free(timebuf);
  return 0;
}

int ClogInitializeThreading(void*arg)
{
  (void)arg;
  ClogParentThread=pthread_self();
  return 0;
}

int ClogFinalizeThreading(void*arg)
{
  return 0;
}

int ClogInitialize()
{
  int ierr=0;

#ifdef CLOG_USE_PTHREAD
  ierr=ClogRegisterInitializeCallback(&ClogInitializeThreading,NULL);CHKERR(ierr);
  ierr=ClogRegisterFinalizeCallback(&ClogFinalizeThreading,NULL);CHKERR(ierr);
#endif

  for(int i=0;i<ClogNumInitializeCallbacks;i++)
  {
    ierr=ClogInitializeCallbacks[i](ClogInitializeCallbackArgs[i]);CHKERR(ierr);
  }
  return 0;
}

int ClogFinalize()
{
  int ierr=0;
  for(int i=0;i<ClogNumFinalizeCallbacks;i++)
  {
    ierr=ClogFinalizeCallbacks[i](ClogFinalizeCallbackArgs[i]);CHKERR(ierr);
  }
  return 0;
}
