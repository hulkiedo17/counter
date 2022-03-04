#!/bin/bash

prefix=/usr/local/

Debug() {
	mkdir -p build
	cd build

	cmake "-DCMAKE_BUILD_TYPE=DEBUG" "-DCMAKE_INSTALL_PREFIX=$prefix" ".."
	make
}

Release() {
	mkdir -p build
	cd build

	cmake "-DCMAKE_BUILD_TYPE=RELEASE" "-DCMAKE_INSTALL_PREFIX=$prefix" ".."
	make
}

Install() {
	if [[ "$PWD" == *"/build" ]]; then
		sudo make install
		exit 0
	elif [ -d "build" ]; then
		cd build
		sudo make install
		exit 0
	else
		echo "build directory does not exists"
		exit 0
	fi
}

Clean() {
	if [ -d "build" ]; then
		cd build
		make clean
		exit 0
	else
		echo "build directory does not exists"
		exit 0
	fi
}

Help() {
	printf "[cli options]:\n"
	printf "\t-d - compile debug version\n"
	printf "\t-r - compile release version\n"
	printf "\t-i - install debug or release version\n"
	printf "\t-D - compile and install debug version\n"
	printf "\t-R - compile and install release version\n"
	printf "\t-c - delete compiled object files\n"
	printf "\t-h - prints help message\n"
}

ProcessOptions() {
	CurrentDir="$PWD"
	if [ -z $* ]; then
		Release
		Install $CurrentDir
		exit 0
	fi

	while getopts "driDRch" opt; do
		case $opt in
			d) Debug ;;
			r) Release ;;
			i) Install $CurrentDir ;;
			D)
				Debug
				Install $CurrentDir
				;;
			R)
				Release
				Install $CurrentDir
				;;
			c) Clean ;;
			h) Help ;;
			*) echo "unknown option" ;;
		esac
	done
}

ProcessOptions "$@"
