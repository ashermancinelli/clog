#include "clog.h"

#ifdef CLOG_HAVE_PTHREAD
#include <pthread.h>
#endif

#ifdef CLOG_HAVE_THREAD
#include <stdlib.h>
#include <unistd.h>
#endif

static const char* ClogThreadStrategyName[CLOG_THREAD_STRATEGY_NUM_STRATEGIES] =
{
  "Process ID",
  "MPI Communicator",
  "Pthread",
};

static int (*ClogThreadFPs[CLOG_THREAD_STRATEGY_NUM_STRATEGIES])(int*);
static int (*ClogThreadFP)(int*);
static int ClogThreadLogId=-1;

int ClogThreadStrategy_MPI(int*id)
{
  int ierr=0,rank=0;
#ifdef CLOG_HAVE_MPI
  ierr=MPI_Comm_rank(MPI_COMM_WORLD,&rank);CHKERR(ierr);
#else
  /* MPI threading strategy was selected, but clog was not built with mpi! */
  return 1;
#endif
  *id=rank;
  return 0;
}

int ClogThreadStrategy_PTHREAD(int*id)
{
#ifdef CLOG_HAVE_PTHREAD
  *id=(int)pthread_self();
#else
  /* pthread threading strategy was selected, but clog was not built with mpi! */
  return 1;
#endif
  return 0;
}

int ClogThreadStrategy_GETPID(int*id)
{
  *id=(int)getpid();
  return 0;
}

int ClogThreadInitializeStrategies(void*arg)
{
  (void)arg;
  ClogThreadFPs[CLOG_THREAD_STRATEGY_GETPID]=&ClogThreadStrategy_GETPID;
  ClogThreadFPs[CLOG_THREAD_STRATEGY_MPI]=&ClogThreadStrategy_MPI;
  ClogThreadFPs[CLOG_THREAD_STRATEGY_PTHREAD]=&ClogThreadStrategy_PTHREAD;

#ifdef CLOG_HAVE_THREAD
  /** By default we use getpid for thread id checking */
  ClogThreadFP=&ClogThreadStrategy_GETPID;
#else
  ClogThreadFP=NULL;
#endif
  return 0;
}

int ClogThreadSetStrategy(ClogThreadStrategy strat)
{
  if(strat>=CLOG_THREAD_STRATEGY_NUM_STRATEGIES)
    return 1;
  ClogThreadFP=ClogThreadFPs[strat];
  return 0;
}

int ClogThreadGetId(int*id)
{
  int ierr=0;
  if(ClogThreadFP==NULL)
    return 1;
  ierr=(*ClogThreadFP)(id);
  return ierr;
}

/** Returns >0 if true, else 0 */
int ClogThreadShouldLog(int*shouldlog)
{
  int ierr=0;
#ifdef CLOG_HAVE_THREAD
  /** Try to get thread id from strategy */
  int id;
  ierr=ClogThreadGetId(&id);
  if(ierr)
    return ierr;

  /** If we're the calling thread, return true */
  if(id==ClogThreadLogId)
  {
    *shouldlog=1;
  }
  else
  {
    *shouldlog=0;
  }
#else
  *shouldlog=1;
#endif

  return 0;
}
