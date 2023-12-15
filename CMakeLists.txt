cmake_minimum_required(VERSION 3.8.2)
project(aoc_2023 LANGUAGES C)

add_custom_target(libft.a ALL)
add_custom_command(TARGET libft.a POST_BUILD
        COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/lib
        COMMAND make all
        COMMAND cp -v libft.a ${CMAKE_CURRENT_BINARY_DIR}/
        #        BYPRODUCTS libft.a
        )
add_library(FTLIB STATIC IMPORTED)
#add_dependencies(FTLIB libft.a)
set_target_properties(FTLIB PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libft.a # Make sure to use absolute path here
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
        INTERFACE_COMPILE_DEFINITIONS "OPTIMISTIC"
        )

add_subdirectory(day1)
add_subdirectory(day2)