
add_test(
    NAME localFile
    COMMAND ${EXE_NAME} ${CMAKE_SOURCE_DIR}/tests/resources/sin.xml
    )

add_test(
    NAME remoteFile
    COMMAND ${EXE_NAME} https://models.physiomeproject.org/workspace/4b1/rawfile/a984419d72b5dc4ef514f02defb70308fa57b09c/sin.xml
    )
