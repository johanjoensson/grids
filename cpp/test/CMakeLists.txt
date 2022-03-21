set(TEST_FILES
	tests.cpp
)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(cpp_tests ${TEST_FILES})
target_link_libraries(cpp_test ${GTEST_LIBRARIES} hexagon)
gtest_discover_tests(cpp_tests)
