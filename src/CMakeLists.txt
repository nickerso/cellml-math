
set(CMATH_SRCS
    modelloader.cpp
    modelresolver.cpp
    mathextractor.cpp
    mathtree.cpp
    xmlutils.cpp
    cmath.cpp
    )

set(CMATH_HDRS
    modelloader.h
    modelresolver.h
    mathextractor.h
    mathtree.h
    mathelement.h
    xmlutils.h
    )

add_executable(${EXE_NAME}
    ${CMATH_SRCS}
    ${CMATH_HDRS}
    )
target_link_libraries(${EXE_NAME} cellml ${LIBXML2_LIBRARIES} ${CURL_LIBRARIES})
target_include_directories(${EXE_NAME}
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${LIBXML2_INCLUDE_DIR}
    ${CURL_INCLUDE_DIRS}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${EXE_NAME} PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  )
