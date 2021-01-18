#include <clog.h>

int incrementValue(void*arg)
{
  int *variable=(int*)arg;
  *variable+=1;
  return 0;
}

int printValue(void*arg)
{
  int *variable=(int*)arg;
  printf("This is being called from a finalization callback.\n"
      "The callback `incrementVariable` incremented variable `variable` twice during\n"
      "initialization and once during finalization phase, and `variable` started with\n"
      "value=0. Now, variable=%d.\n",*variable);
  return 0;
}

int returnError(void*arg)
{
  (void)arg;
  puts("This callback will return an error and cause clog to fail if used.");
  return 1;
}

int main(void)
{
  int ierr=0,value=0;
  ierr=ClogRegisterInitializeCallback(&incrementValue,(void*)&value);CHKERR(ierr);
  ierr=ClogRegisterInitializeCallback(&incrementValue,(void*)&value);CHKERR(ierr);
  ierr=ClogRegisterFinalizeCallback(&incrementValue,(void*)&value);CHKERR(ierr);
  ierr=ClogRegisterFinalizeCallback(&printValue,(void*)&value);CHKERR(ierr);

  // This callback is left out for CI, but is left as an example for error handling.
  // ierr=ClogRegisterFinalizeCallback(&returnError,(void*)NULL);CHKERR(ierr);

  ierr=ClogInitialize();CHKERR(ierr);
  ierr=ClogLog(CLOG_LEVEL_WARN,"Value=%d",value);CHKERR(ierr);
  ierr=ClogFinalize();CHKERR(ierr);

  int fail=0;
  if(value!=3)
    return 1;
  return 0;
}
