#include <clog.h>

int main()
{
  int ierr=0;
  ierr=ClogInitialize();CHKERR(ierr);
  ierr=ClogSetLogLevel(CLOG_LEVEL_INFO);CHKERR(ierr);
  ierr=ClogLog(CLOG_LEVEL_WARN,"%s","This is a warning.");
  ierr=ClogLog(CLOG_LEVEL_INFO,"%s","This is info.");
  ierr=ClogLog(CLOG_LEVEL_ERROR,"%s","This is an error.");
  ierr=ClogLog(CLOG_LEVEL_ERROR,"%s","This is a multiline\nerror\nmessage.");
  ierr=ClogFinalize();CHKERR(ierr);
  return 0;
}
