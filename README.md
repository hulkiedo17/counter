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

Enter the -h option to check all program options:
```shell
$ counter -h
usage: counter [options...]

options:
	-h        - prints this help message
	-v        - prints files that counted
	-p [path] - specifying another directory for counting lines in files
	-f [file] - specifying file to count lines
	-D [dir]  - ignore specifed directory (directory path will be discarded)
	-r        - do not use files in nested directories
	-s        - do not count the empty lines in files
	-z        - do not show emply files
	-t        - do not show total lines count of files
	-e        - do not use global environment variables
```

Also, you can check build options, by typing -h to build script:
```shell
$ ./build.sh -h
usage: ./build.sh [options...]

options:
	-d - compile and install debug version
	-r - compile and install release version
	-c - delete compiled object files
	-h - print help message
```

it is recommended to use build script from the main repository directory, not a build or other nested directories.

# Environment variables

You can also specify environment variables to specify file and directory comparsion patterns.

Example:
```shell
# in this var you specify the names of directories that are skipped, and separating this with '|' character
export DIR_SKIP_COUNTER=".|build|bin"
# in this var you specify the file extensions or their names and only they will participate in the count, separating the, with '|' symbol.
export FILE_COUNT_COUNTER=".c|.h|.sh|.mk"
```

# TODO list

- [x] remake program structure
- [x] add new options
- [x] add config file and environment variables
- [x] add to -D option basename() function to discard path to dir
- [ ] add -c option which excludes configuration files from the count
- [ ] add option to output program version
- [ ] add option with excludes comments in source files from the count
- [ ] add -V option to show only filenames and count

