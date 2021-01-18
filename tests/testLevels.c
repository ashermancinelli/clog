#include <clog.h>

int main(void)
{
  int ierr=0;
  ierr=ClogInitialize();CHKERR(ierr);
  ierr=ClogSetLogLevel(CLOG_LEVEL_INFO);CHKERR(ierr);
  ierr=ClogLog(CLOG_LEVEL_WARN,"%s","This is a warning.");CHKERR(ierr);
  ierr=ClogLog(CLOG_LEVEL_INFO,"%s","This is info.");CHKERR(ierr);
  ierr=ClogLog(CLOG_LEVEL_ERROR,"%s","This is an error.");CHKERR(ierr);
  ierr=ClogLog(CLOG_LEVEL_ERROR,"%s","This is a multiline\nerror\nmessage.");CHKERR(ierr);
  ierr=ClogFinalize();CHKERR(ierr);
  return 0;
}
