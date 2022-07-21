#!/usr/bin/env bash

prefix=/usr/local/

debug() {
	mkdir -p build
	cd build || exit

	cmake "-DCMAKE_BUILD_TYPE=Debug" "-DCMAKE_INSTALL_PREFIX=$prefix" ".."
	make
	sudo make install
}

release() {
	mkdir -p build
	cd build || exit

	cmake "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_INSTALL_PREFIX=$prefix" ".."
	make
	sudo make install
}

clean() {
	if [ -d "build" ]; then
		cd build || exit
		make clean
		exit 0
	else
		echo "build directory does not exists"
		exit 0
	fi
}

help_msg() {
	printf "usage: ./build.sh [options...]\n\n"
	printf "options:\n"
	printf "\t-d - compile and install debug version\n"
	printf "\t-r - compile and install release version\n"
	printf "\t-c - delete compiled object files\n"
	printf "\t-h - prints help message\n"
}

check_options() {
	if [ -z "$*" ]; then
		release
		exit 0
	fi

	while getopts "drch" opt; do
		case $opt in
			d) debug ;;
			r) release ;;
			c) clean ;;
			h) help_msg ;;
			*) echo "unknown option" ;;
		esac
	done
}

check_options "$@"
exit 0
