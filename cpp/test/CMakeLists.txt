set(TEST_FILES
	tests.cpp
        hexagon.cpp
        point.cpp
        edge.cpp
)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(cpp_tests ${TEST_FILES})
target_link_libraries(cpp_tests ${GTEST_LIBRARIES} hexagon)
gtest_discover_tests(cpp_tests)
