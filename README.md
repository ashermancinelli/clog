# `clog`: Logging library in C99

Typical CMake installation process:
```console
$ git clone https://github.com/ashermancinelli/clog.git
$ cd clog
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_INSTALL_PREFIX=/install/prefix
$ make
$ make test
$ make install
```

Example usage can be found in the `tests` directory.

Simple example:

```c
#include <clog.h>
#include <assert.h>
int main()
{
  int ierr=0;
  ierr=ClogInitialize();assert(!ierr);
  ierr=ClogSetLogLevel(CLOG_LEVEL_INFO);assert(!ierr);
  ierr=ClogLog(CLOG_LEVEL_WARN,"%s","This is a warning.");assert(!ierr);
  ierr=ClogLog(CLOG_LEVEL_INFO,"%s","This is info.");assert(!ierr);
  ierr=ClogLog(CLOG_LEVEL_ERROR,"%s","This is an error.");assert(!ierr);
  ierr=ClogLog(CLOG_LEVEL_ERROR,"%s","This is a multiline\nerror\nmessage.");assert(!ierr);
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

Example of the format API:
```c
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
```

Output:
```console
$ ./tests/testFormat
[01/18/21 - 12:03PM] [WARNING]: This is a warning with the default format string.
[01/18/21 - 12:03PM] [WARNING]: I'm about to change the logger to ouput JSON:
{
	'time':'01/18/21 - 12:03PM',
	'level':'ERROR',
	'message':'Some logging info!'
}
```

We also have Pthread/fork join/mpi support if your application is threaded. See interface for details.
