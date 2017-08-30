

cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME CellmlMath)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX)

# Produces a target 'cellml'
find_package(libCellML REQUIRED)

# Documentation says you need the first line, but turning it
# on results in an error when linking due to duplicate symbols?
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)

add_subdirectory(src)
