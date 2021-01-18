#include "clog.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define CLOG_DEFAULT_BUF_SIZE 1024
static ClogLevel lvl=CLOG_LEVEL_INFO;
static const char *ClogLogNames[3]={"INFO","WARNING","ERROR",};

int ClogSetLogLevel(ClogLevel lvl_)
{
  lvl=lvl_;
  return 0;
}

int ClogGetTimeBuf(char**timebuf)
{
  time_t rawtime=time(NULL);assert(rawtime!=-1);
  struct tm *ptm=localtime(&rawtime);assert(ptm);
  *timebuf=malloc(CLOG_DEFAULT_BUF_SIZE);
  sprintf(*timebuf,"%02d:%02d:%02d",ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
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
    fprintf(stdout,"[%s] [%s]: %s\n",timebuf,ClogLogNames[currlvl],endl);
    endl = strtok(NULL, "\n");
  }
  va_end(args);
  free(timebuf);
  return 0;
}

int ClogInitialize(){return 0;}
int ClogFinalize(){return 0;}
