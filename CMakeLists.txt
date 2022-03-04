cmake_minimum_required(VERSION 3.0)

project(counter
	VERSION 1.3
	DESCRIPTION "Counter - count source files"
	LANGUAGES C)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_C_FLAGS_DEBUG "-std=c11 -Wall -Wextra -Werror -Wpedantic -Wformat=2 -Wunused-parameter -Wwrite-strings -Wstrict-prototypes -Wold-style-definition -Wredundant-decls -Wnested-externs -Wmissing-include-dirs -Wlogical-op -g -O0")
	set(CMAKE_C_FLAGS_RELEASE "-std=c11 -O1")
endif()

set(BIN_DIR /bin)
set(SOURCE src/check.c src/count.c src/main.c src/misc.c)
set(HEADER include/check.h include/count.h include/misc.h)
set(EXECUTABLE counter)

add_executable(${EXECUTABLE} ${HEADER} ${SOURCE})

INSTALL_TARGETS(/bin ${EXECUTABLE})

