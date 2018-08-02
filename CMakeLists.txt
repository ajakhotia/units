cmake_minimum_required(VERSION 3.5.0)

#[[ Set the name of the project and provide language specification. ]]
project(units VERSION 0.1.1.0 LANGUAGES C CXX)

#[[ Set CMAKE_CXX_STANDARD. ${CMAKE_CXX_STANDARD} sets the initial value for ${CXX_STANDARD} on
    all targets unless specified otherwise. ]]
set(CMAKE_CXX_STANDARD 14)

#[[ Set CMAKE_CXX_STANDARD_REQUIRED to ON. ${CMAKE_CXX_STANDARD_REQUITED} sets the initial value
    for ${CXX_STANDARD_REQUIRED} which ensures that cmake WILL FAIL if a target is not compiled
    using the specified C++ standard due to compiler limitations. ]]
set(CMAKE_CXX_STANDARD_REQUIRED ON BOOL)

#[[ Find gtest that is necessary for building tests. We will skip building tests if we fail to find gtest. ]]
find_package(GTest 1.8)

#[[ Enable testing only if gtest target is available. Include(CTest) should setup the build correctly and
    set BUILD_TESTING flag to true. BUILD_TESTING should be the only flag that should be used to figure out if
    or not to add tests sub-directory. ]]
if((TARGET GTest::GTest) AND (TARGET GTest::Main))
    include(CTest)
endif((TARGET GTest::GTest) AND (TARGET GTest::Main))

#[[ Create an INTERFACE target as this library is header-only. ]]
add_library(units INTERFACE)

target_include_directories(units INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>)

install(DIRECTORY include/units
		DESTINATION include
		FILES_MATCHING PATTERN "*.h")

install(TARGETS units EXPORT unitsTargets COMPONENT units
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib/static
		INCLUDES DESTINATION include)

if (BUILD_TESTING)
	add_subdirectory(test)
endif (BUILD_TESTING)


#[[ Include cmake-default tools to help create export files. ]]
include(CMakePackageConfigHelpers)

#[[ Install ${CMAKE_INSTALL_PREFIX}/lib/cmake/units/unitsTargets.cmake for other projects to include the
    installation tree. ]]
install(EXPORT unitsTargets NAMESPACE Units::
		FILE unitsTargets.cmake
		DESTINATION lib/cmake/units)

#[[ Generate a configuration and install it. ]]
write_basic_package_version_file(
		${CMAKE_CURRENT_BINARY_DIR}/cmake/unitsConfigVersion.cmake
		COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cmake/unitsConfigVersion.cmake
		DESTINATION lib/cmake/units)

#[[ Configure and install unitsConfig.cmake.in to enable other projects find units from
    the install tree. Even though the function configure_package_config_file takes the INSTALL_DESTINATION, it
    doesn't actually create a installation step for "make install". So, to install the generated config file, we
    are required to manually create a install step. ]]
configure_package_config_file(
		cmake/unitsConfig.cmake.in cmake/unitsConfig.cmake
		INSTALL_DESTINATION lib/cmake/units)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cmake/unitsConfig.cmake
		DESTINATION lib/cmake/units)