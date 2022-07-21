cmake_minimum_required(VERSION 3.0)

project(counter
	VERSION 1.7
	DESCRIPTION "counter - code line counter in source file of C projects"
	LANGUAGES C)

if(NOT UNIX)
	message(FATAL_ERROR "Your system is not unix. Fail to build.")
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_C_FLAGS_DEBUG "-std=c11 -Wall -Wextra -Werror -Wpedantic -Wshadow -Wformat=2 -Wconversion -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wunused-parameter -Wwrite-strings -Wstrict-prototypes -Wold-style-definition -Wredundant-decls -Wnested-externs -Wmissing-include-dirs -Wlogical-op -g -O0 -fstack-protector")
	set(CMAKE_C_FLAGS_RELEASE "-std=c11 -O1")
endif()

set(EXECUTABLE counter)
set(INSTALL_DIR bin)
set(INCLUDE_DIR include)
set(SOURCE
	src/check.c
	src/count.c
	src/main.c
	src/misc.c)

add_executable(${EXECUTABLE} ${SOURCE})

target_include_directories(${EXECUTABLE} PRIVATE ${INCLUDE_DIR})

install(TARGETS ${EXECUTABLE} DESTINATION ${CMAKE_INSTALL_PREFIX}/${INSTALL_DIR})
