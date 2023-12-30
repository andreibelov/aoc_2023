cmake_minimum_required(VERSION 3.8.2)
project(aoc_2023 LANGUAGES C)



set(FTLIB_name FTLIB)
set(FTLIB_filename libft.a)
set(FTLIB_dir ${CMAKE_CURRENT_SOURCE_DIR}/lib/libft)

file(GLOB FTLIB_HEADERS "${FTLIB_dir}/*.h")
file(GLOB FTLIB_SOURCES "${FTLIB_dir}/**/ft_*.c")
add_custom_command(OUTPUT ${FTLIB_dir}/${FTLIB_filename}
        COMMAND make -C ${FTLIB_dir})
add_custom_target(${FTLIB_filename} DEPENDS ${FTLIB_dir}/${FTLIB_filename})

add_library(${FTLIB_name} STATIC IMPORTED)
add_dependencies(${FTLIB_name} ${FTLIB_filename})
set_target_properties(${FTLIB_name} PROPERTIES
        IMPORTED_LOCATION ${FTLIB_dir}/${FTLIB_filename} # Make sure to use absolute path here
        INTERFACE_COMPILE_DEFINITIONS "OPTIMISTIC"
        INTERFACE_SOURCES "${FTLIB_HEADERS};${FTLIB_SOURCES}"
        INTERFACE_INCLUDE_DIRECTORIES "${FTLIB_dir};${CMAKE_CURRENT_SOURCE_DIR}/lib/include")
add_custom_target(fclean ALL)
add_custom_command(TARGET fclean POST_BUILD
        COMMAND make -C ${FTLIB_dir} fclean)

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)