# counter
counter - is a program that counts lines in files in the current directory. There is also the possibility of recursive access to directories, that is, lines will be counted in files in subdirectories as well. And yet, you can set a directory for search, though only in a full path (not in a relative one), that is, from / to the desired directory.

## How to launch
This program works only on linux(ubuntu)

Required tools: gcc, make, shell

To compile program type this commands:
```shell
$ ./configure.sh
$ make
$ sudo make install
```

To run program type this command(after installation):
```shell
$ counter
```

## options

enter the -h option to check all program options:
```shell
$ counter -h
```

