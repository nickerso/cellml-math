
set(CMATH_SRCS
    cmath.cpp
    )

set(CMATH_HDRS

    )

add_executable(cmath
    ${CMATH_SRCS}
    ${CMATH_HDRS}
    )
target_link_libraries(cmath cellml)
target_include_directories(cmath PRIVATE ${CMAKE_CURRENT_BINARY_DIR} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
