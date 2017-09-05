

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

set(EXE_NAME "cellml-math")

add_subdirectory(src)
# enable testing here to get the 'test' target.
enable_testing()
add_subdirectory(tests)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen" VERBATIM
      )
endif(DOXYGEN_FOUND)
