

cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME CellmlMath)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX)

# Produces a target 'cellml'
find_package(libCellML REQUIRED)

# Old-school Find package for CURL
find_package(CURL REQUIRED)

# Find libXml2 - Not needed as it is publicly exposed by libCellML so we make sure
# we use the same one? Probably needed if using a released libCellML rather than one
# built locally?
#find_package(LibXml2 REQUIRED)

add_subdirectory(src)
