#include "clog.h"
#include <clog_config.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define CLOG_DEFAULT_BUF_SIZE 1024

/** Default minimum log level */
static ClogLevel lvl=CLOG_LEVEL_INFO;

/** Default names for logging message struct values */
static const char *ClogLogNames[3]={"INFO","WARNING","ERROR",};

/** Default format string for timestamps. */
static char *timefmt="%x - %I:%M%p";

/** Deafult format string for log messages. */
static char logfmt[CLOG_DEFAULT_BUF_SIZE]="[%s] [%s]: %s\n";

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

int ClogInitialize(){return 0;}
int ClogFinalize(){return 0;}
