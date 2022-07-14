cmake_minimum_required(VERSION 3.0)

project(counter
	VERSION 1.4
	DESCRIPTION "counter - count source files"
	LANGUAGES C)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_C_FLAGS_DEBUG "-std=c11 -Wall -Wextra -Werror -Wpedantic -Wformat=2 -Wunused-parameter -Wwrite-strings -Wstrict-prototypes -Wold-style-definition -Wredundant-decls -Wnested-externs -Wmissing-include-dirs -Wlogical-op -g -O0")
	set(CMAKE_C_FLAGS_RELEASE "-std=c11 -O1")
endif()

set(EXECUTABLE counter)
set(SOURCE
	src/check.c
	src/count.c
	src/main.c
	src/misc.c)

add_executable(${EXECUTABLE} ${SOURCE})

target_include_directories(${EXECUTABLE} PRIVATE include/)

install(TARGETS ${EXECUTABLE} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
