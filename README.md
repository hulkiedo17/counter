# counter
counter - is a program that counts lines in files in the current directory. There is also the possibility of recursive access to directories, that is, lines will be counted in files in subdirectories as well. And yet, you can set a directory for search.

## How to launch
This program works only on linux(ubuntu)

Required tools: gcc, cmake, make, bash

Firstly, you need to prepare compile, download repository:
```shell
$ git clone https://github.com/hulkiedo17/counter.git
$ cd counter
```

To compile program type this commands:
```shell
$ ./build.sh
```

Or use more familiar way(check docs/cmake.md):
```shell
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local/ ..
$ make
$ sudo make install
```

To run program type this command(after installation):
```shell
$ counter
```

## options

enter the -h option to check all program options(check docs/counter.md):
```shell
$ counter -h
```

also, you can check build options, by typing -h to build script:
```shell
$ ./build.sh -h
```

## docs
you can check documentation to build options or command options in docs/ in files: build.md, cmake.md, counter.md
