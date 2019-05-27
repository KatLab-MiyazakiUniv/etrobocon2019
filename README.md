# etrobocon2019
Presented by [KatLab](earth.cs.miyazaki-u.ac.jp).

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
### Where is coding conventions?
[Here.](
https://www.dropbox.com/sh/6u2tp0cw92aotq6/AADatBCUPQ87mDIAYwCnJrZKa/%E3%82%B3%E3%83%BC%E3%83%87%E3%82%A3%E3%83%B3%E3%82%B0%E3%82%B9%E3%82%BF%E3%82%A4%E3%83%AB?dl=0&preview=%E3%83%81%E3%82%A7%E3%83%83%E3%82%AF%E3%83%AA%E3%82%B9%E3%83%88.pdf&subfolder_nav_tracking=1)

### Where is the source directory?

It is `src`.

### What is how to add module?

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
