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

### Where is the source directory.

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
