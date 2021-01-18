#include <clog.h>

int main(void)
{
  int ierr=0;
  ierr=ClogInitialize();CHKERR(ierr);
  ierr=ClogSetLogLevel(CLOG_LEVEL_INFO);CHKERR(ierr);
  ierr=ClogLog(CLOG_LEVEL_WARN,"%s","This is a warning with the default format string.");CHKERR(ierr);
  ierr=ClogLog(CLOG_LEVEL_WARN,"%s","I'm about to change the logger to ouput JSON:");CHKERR(ierr);
  ierr=ClogSetFormat("{\n\t'time':'%s',\n\t'level':'%s',\n\t'message':'%s'\n}\n");CHKERR(ierr);
  ierr=ClogLog(CLOG_LEVEL_ERROR,"%s","Some logging info!");CHKERR(ierr);
  ierr=ClogFinalize();CHKERR(ierr);
  return 0;
}
