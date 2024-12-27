# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(compiler C)

# Find required packages
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# Additional source files (based on your Makefile)
set(ADDITIONAL_SOURCES
        symbol_table.c
        operations.c
)

# Generate lexer and parser
FLEX_TARGET(Scanner lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
BISON_TARGET(Parser parser.y
        ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h
)
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

# Add executable
add_executable(compiler.out
        ${FLEX_Scanner_OUTPUTS}
        ${BISON_Parser_OUTPUTS}
        ${ADDITIONAL_SOURCES}
)

# Optional: Add include directories if needed
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Optional: Add a custom clean target
add_custom_target(clean-all
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/compiler.out
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h
)