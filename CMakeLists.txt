cmake_minimum_required(VERSION 3.8.2)
project(aoc_2023 LANGUAGES C)


add_custom_target(fclean ALL)
add_custom_command(TARGET fclean POST_BUILD
        COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/lib/libft
        COMMAND make fclean
        )

set(FT_HEADERS "")
set(FT_SOURCES "")
file(GLOB FT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/lib/libft/**/ft_*.h")
file(GLOB FT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lib/libft/**/ft_*.c")

add_custom_target(libft.a ALL)
target_sources(libft.a PRIVATE ${FT_HEADERS} ${FT_SOURCES})
add_custom_command(TARGET libft.a POST_BUILD
        COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/lib/libft
        COMMAND make all
        COMMAND cp -v libft.a ${CMAKE_CURRENT_BINARY_DIR}/
        )
add_library(FTLIB STATIC IMPORTED)

set_target_properties(FTLIB PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libft.a # Make sure to use absolute path here
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/lib/include
        INTERFACE_COMPILE_DEFINITIONS "OPTIMISTIC"
        )

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)