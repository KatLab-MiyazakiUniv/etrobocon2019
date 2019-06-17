# etrobocon2019
Presented by [KatLab](http://earth.cs.miyazaki-u.ac.jp).

[![CircleCI](https://circleci.com/gh/KatLab-MiyazakiUniv/etrobocon2019/tree/master.svg?style=svg)](https://circleci.com/gh/KatLab-MiyazakiUniv/etrobocon2019/tree/master) [![codecov](https://codecov.io/gh/KatLab-MiyazakiUniv/etrobocon2019/branch/master/graph/badge.svg)](https://codecov.io/gh/KatLab-MiyazakiUniv/etrobocon2019)

## BUILD

Execution command.
```bash
$ ./make.sh
```

Built the executable file.
```bash
$ ls
et2019
```

## DEVELOP
### Where is reference?

[Here](https://katlab-miyazakiuniv.github.io/etrobocon2019/annotated.html).


### Where should you add your source files?

```
/              // Working directory.
|
|-src          // Don't add here.
| |-module     // Add source codes.
|   |-api      // Add source codes(api).
|     |-core   // Don't add here.
|
|-test         // Add test codes.
```

Normaly, please put source codes to `/src/module`.


### Where is coding conventions?
[Here.](
https://www.dropbox.com/sh/6u2tp0cw92aotq6/AADatBCUPQ87mDIAYwCnJrZKa/%E3%82%B3%E3%83%BC%E3%83%87%E3%82%A3%E3%83%B3%E3%82%B0%E3%82%B9%E3%82%BF%E3%82%A4%E3%83%AB?dl=0&preview=%E3%83%81%E3%82%A7%E3%83%83%E3%82%AF%E3%83%AA%E3%82%B9%E3%83%88.pdf&subfolder_nav_tracking=1)

### Where is the source directory?

It is `src`.

### How to add module.

If add `Example class`, append object name to `src/Makefile.inc`.

#### before

```
APPL_CXXOBJS += 
```

#### after
```
APPL_CXXOBJS += \
    Example.o
```

### How to add test cases.
If you add/modify source code, you should add test cases.

1. Create a file named (class name) + "Test".
2. Put the test file to `/test`.

#### for example
Create source codes that implement Example class.
(`/src/Example.cpp`, `/src/Example.h`)

Create a test file for Example class.
(`ExampleTest.cpp`)

Put `ExampleTest.cpp` to `/test`.

#### Execute test cases.
Do `./gtest_all.sh`.

### Use Remote Development of Visual Studio Code.

You can use Remote Development of Visual Studio Code.