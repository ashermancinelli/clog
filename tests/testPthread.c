#include <clog.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void childThread(void*arg)
{
  int ierr=0;
  ierr=ClogLog(CLOG_LEVEL_INFO,"This is being logged from child thread, pid=%d.",(int)pthread_self());
}

int main(void)
{
  int ierr=0;
  ierr=ClogInitialize();CHKERR(ierr);
  ierr=ClogLog(CLOG_LEVEL_INFO,"This is the parent thread, tid=%d.",(int)pthread_self());CHKERR(ierr);
  ierr=ClogThreadSetStrategy(CLOG_THREAD_STRATEGY_PTHREAD);CHKERR(ierr);

  /** This will not be logged if build with CLOG_USE_PTHREAD */
  pthread_t t;
  pthread_create(&t,NULL,&childThread,NULL);
  pthread_join(t,NULL);

  /** Even if built with CLOG_USE_PTHREAD, this will log to every thread */
  ierr=ClogIgnoreThread();CHKERR(ierr);
  pthread_create(&t,NULL,&childThread,NULL);
  pthread_join(t,NULL);

  ierr=ClogFinalize();CHKERR(ierr);
  return 0;
}
