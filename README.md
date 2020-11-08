# plc
Program to count lines in files in current directories

# How to launch
This program works only on linux(ubuntu)

Required tools: gcc, make, shell

To compile program type this commands:
```shell
$ ./configure.sh
$ make
$ sudo make install
```

# program description
plc - is a program that counts lines in files in the current directory.

There is also the possibility of recursive access to directories, that is, lines will be counted in files in subdirectories as well.

And yet, you can set a directory for search, though only in a full path (not in a relative one), that is, from / to the desired directory.

# options

--path <path> - set the specified directory as the default for count(-p)

--detail - print all files that program counted(-d).

--no-recursion - don't use recursive access to directories(-R).

