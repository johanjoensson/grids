cmake_minimum_required(VERSION 3.14..)

project(
        Hexagon
	VERSION 
          0.1
	DESCRIPTION 
        "C++ implementation of Hexagonal grids, as describe at redblobgames 
         (www.redblobgames.com/grids/hexagons-v2)"
	LANGUAGES 
          CXX
)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

message( STATUS "-------- BUILD-TYPE: ${CMAKE_BUILD_TYPE}")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
        set(BUILD_TESTS TRUE)
        enable_testing()
        message( STATUS "-------- BUILDING TESTS")
endif()

add_subdirectory(cpp)

if(BUILD_PYTHON)
	find_package(pybind11)
	if(pybind11_FOUND)
		add_subdirectory(python)
	else()
		message(STATUS "pybind11 not found, not building python bindings.")
	endif()
endif()

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_CXX_EXTENSIONS OFF)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	find_package(Doxygen)
	if(Doxygen_FOUND)
		add_subdirectory(docs)
	else()
		message(STATUS "Doxygen not found, not building docs")
	endif()
endif() # Main project only part ends here

# IDEs should put the headers in a nice place
source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)

install(DIRECTORY include/ DESTINATION include/hexagon 
	FILES_MATCHING PATTERN "*.h")
install(TARGETS hexagon 
	EXPORT hexagon-targets
	INCLUDES DESTINATION include/hexagon)
install(EXPORT hexagon-targets
	NAMESPACE Hexagon::
	DESTINATION share/hexagon
	)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/hexagon/hexagon-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)
export(EXPORT hexagon-targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/hexagon/hexagon-targets.cmake"
  NAMESPACE Hexagon::
)
configure_file(cmake/hexagon-config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/hexagon/hexagon-config.cmake"
  COPYONLY
)

set(ConfigPackageLocation share/cmake/hexagon)
install(EXPORT hexagon-targets
  FILE
    hexagon-targets.cmake
  NAMESPACE
  Hexagon::
  DESTINATION
    ${ConfigPackageLocation}
)
install(
  FILES
    cmake/hexagon-config.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/hexagon/hexagon-config-version.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)
