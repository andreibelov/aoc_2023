cmake_minimum_required(VERSION 3.8.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-narrowing")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-narrowing")

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_C_STANDARD 90)

cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0075 NEW)
project("day3" VERSION 0.1.0 LANGUAGES C CXX ASM)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_REQUIRED_LIBRARIES "-lbsd")

include_directories(include)

set(TARGET_NAME day3)
set(TARGET_HEADERS
        "")
set(TARGET_SOURCES
        "")

file(GLOB TARGET_HEADERS "src/*.h")
file(GLOB TARGET_SOURCES "src/*.c")

set(TARGET_LINK_FLAGS "")
set(TARGET_CFLAGS
        -c
        -g3
        -fno-exceptions
        -ffunction-sections
        -fdata-sections
        -O0)
set(TARGET_LINK_FLAGS -w -lbsd -O0)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_SYSROOT "")

execute_process(COMMAND uname -r
        OUTPUT_VARIABLE INSTALLED_KERNEL
        OUTPUT_STRIP_TRAILING_WHITESPACE)

MESSAGE(STATUS "INSTALLED_KERNEL: ${INSTALLED_KERNEL}")

set(GLIB_name glib2)
set(GLIB_SOURCES_DIR "$ENV{HOME}/staging/glib2.0-2.64.6")
set(GLIB_FILE_PATH "/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0.6400.6")
set(GLIB_INCLUDE_DIRS
        /usr/lib/x86_64-linux-gnu/glib-2.0/include
        ${GLIB_SOURCES_DIR}
        ${GLIB_SOURCES_DIR}/glib
        ${GLIB_SOURCES_DIR}/gio
        ${GLIB_SOURCES_DIR}/build
        "${CMAKE_SYSROOT}/usr/src/linux-headers-${INSTALLED_KERNEL}/include"
        "${CMAKE_SYSROOT}/usr/src/linux-headers-${INSTALLED_KERNEL}/arch/x86/include")
file(GLOB_RECURSE GLIB_HEADERS "${GLIB_SOURCES_DIR}/glib/*.h")
file(GLOB_RECURSE GLIB_SOURCES "${GLIB_SOURCES_DIR}/glib/*.c")

file(GLOB_RECURSE GLIB_IO_HEADERS "${GLIB_SOURCES_DIR}/gio/*.h")
file(GLOB_RECURSE GLIB_IO_SOURCES "${GLIB_SOURCES_DIR}/gio/*.c")

list (APPEND GLIB_HEADERS ${GLIB_IO_HEADERS})
list (APPEND GLIB_SOURCES ${GLIB_IO_SOURCES})

add_library(${GLIB_name} SHARED IMPORTED)
set_target_properties(${GLIB_name} PROPERTIES
        IMPORTED_LOCATION ${GLIB_FILE_PATH} # Make sure to use absolute path here
        INTERFACE_SOURCES "${GLIB_HEADERS};${GLIB_SOURCES}"
        INTERFACE_INCLUDE_DIRECTORIES "${GLIB_INCLUDE_DIRS}"
        INTERFACE_COMPILE_DEFINITIONS "OPTIMISTIC"
        )
#message("==================")
#string (REPLACE ";" "\n" GLIB_SOURCES "${GLIB_SOURCES}")
#message("${GLIB_SOURCES}")
#message("==================")

add_executable(dummy /dev/null)
target_link_libraries(dummy ${GLIB_name})

find_package (Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)

add_executable(${TARGET_NAME} ${TARGET_HEADERS} ${TARGET_SOURCES})
target_include_directories(${TARGET_NAME}
        PRIVATE
            src
            include
            /usr/include/glib-2.0
            /usr/lib/x86_64-linux-gnu/glib-2.0/include)
target_compile_options(${TARGET_NAME} PRIVATE ${TARGET_CFLAGS})
target_link_options(${TARGET_NAME} PRIVATE ${TARGET_LINK_FLAGS})
target_link_libraries(${TARGET_NAME} bsd FTLIB Threads::Threads PkgConfig::deps)
target_compile_definitions(${TARGET_NAME} PRIVATE
        INPUT_FILE_NAME="${CMAKE_CURRENT_SOURCE_DIR}/include/input"
        )
