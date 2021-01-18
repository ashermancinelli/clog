# `clog`: Logging library in C99

Typical CMake installation process:
```console
$ git clone https://github.com/ashermancinelli/clog.git
$ cd clog
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_INSTALL_PREFIX
$ make
$ make test
$ make install
```

Example usage can be found in `tests/testLevels.c`:

```c
#include <clog.h>
#include <assert.h>
int main()
{
  int ierr=0;
  ierr=ClogInitialize();assert(!ierr);
  ierr=ClogSetLogLevel(CLOG_LEVEL_INFO);assert(!ierr);
  ierr=ClogLog(CLOG_LEVEL_WARN,"%s","This is a warning.");CHKERR(ierr);
  ierr=ClogLog(CLOG_LEVEL_INFO,"%s","This is info.");CHKERR(ierr);
  ierr=ClogLog(CLOG_LEVEL_ERROR,"%s","This is an error.");CHKERR(ierr);
  ierr=ClogLog(CLOG_LEVEL_ERROR,"%s","This is a multiline\nerror\nmessage.");CHKERR(ierr);
  ierr=ClogFinalize();assert(!ierr);
  return 0;
}
```

Output:
```console
$ ./build/tests/testLevels
[09:01:38] [WARNING]: This is a warning.
[09:01:38] [INFO]: This is info.
[09:01:38] [ERROR]: This is an error.
[09:01:38] [ERROR]: This is a multiline
[09:01:38] [ERROR]: error
[09:01:38] [ERROR]: message.
```
