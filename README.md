# What is this?
counter - is a program that counts lines in files in the current directory. There is also the possibility of recursive access to directories, that is, lines will be counted in files in subdirectories as well.

# How to launch
This program works only on linux.

Required tools: gcc, cmake, make, bash

Firstly, you need to download repository:
```shell
$ git clone https://github.com/hulkiedo17/counter.git
```

To compile program type this commands:
```shell
$ cd counter
$ ./build.sh
```

Or use cmake directly(check in docs/cmake.md).

After this steps, you can run program by typing this command:
```shell
$ counter
```

# Options

Enter the -h option to check all program options(or check in docs/counter.md):
```shell
$ counter -h
```

Also, you can check build options, by typing -h to build script(or check in docs/build.md):
```shell
$ ./build.sh -h
```

# Environment variables

You can also specify environment variables to specify file and directory comparsion patterns.

Example:
```shell
# in this var you specify the names of directories that are skipped, and separating this with '|' character
export DIR_PATTERN_COUNTER=".|build|bin"
# in this var you specify the file extensions or their names and only they will participate in the count, separating the, with '|' symbol.
export FILE_PATTERN_COUNTER=".c|.h|.sh|.mk"
```

# Documentation

You can check documentation to build options or command options in docs/ in files: build.md, cmake.md, counter.md.

# TODO list

You can see the TODO list for the near future in /docs/TODO.md.
