add_library(hexagon INTERFACE)

target_include_directories(hexagon INTERFACE 
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
	)

if(BUILD_TESTS)
	add_subdirectory(test)
endif()
