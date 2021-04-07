#!/bin/sh

prefix=/usr/local
debug_flag=true
silence_flag=true

mkdir -p ./bin 
cd ./bin
mkdir -p release debug
cd ../

for arg in "$@"; do
    case "$arg" in
    --prefix=*)
        prefix=`echo $arg | sed 's/--prefix=/'`
        ;;
    --enable-debug)
        debug_flag=true
        ;;
    --disable-debug)
        debug_flag=false
        ;;
    --enable-silence)
        silence_flag=true
        ;;
    --disable-silence)
        silence_flag=false
        ;;
    --help)
        echo "usage: ./configure.sh [options]"
        echo "options:"
        echo "  --prefix=<path>:    installation path prefix"
        echo "  --enable-debug:     include debug symbols"
        echo "  --disable-debug:    do not include debug symbols"
        echo "  --enable-silence:   activate silence mode"
        echo "  --disable-silence:  activate non-silence mode"
        echo "all invalid options are silently ignored"
        ;;
    esac
done

echo "generating makefile..."

echo ".POSIX:" >Makefile
echo "PREFIX = $prefix" >>Makefile

if $debug_flag; then
    echo "DEBUG = TRUE" >>Makefile
else
    echo "DEBUG = FALSE" >>Makefile
fi

if $silence_flag; then
    echo "V = TRUE" >>Makefile
else
    echo "V = FALSE" >>Makefile
fi

cat Makefile.in >>Makefile

echo "configuration complete, type make to build"
