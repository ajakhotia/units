cmake_minimum_required(VERSION 3.10.0)

#[[ Set the name of the project and provide language specification. ]]
project(units VERSION 0.2.0.1 LANGUAGES C CXX)

#[[ Find GTest as a required dependency if the user as requested building of unit tests. ]]
if(BUILD_TESTING)
	find_package(GTest REQUIRED)
else()
	find_package(GTest)
endif()

#[[ Enable testing only if gtest target is available. Include(CTest) should setup the build correctly and
    set BUILD_TESTING flag to true. BUILD_TESTING should be the only flag that should be used to figure out if
    or not to add tests sub-directory. ]]
if((TARGET GTest::GTest) AND (TARGET GTest::Main))
    include(CTest)
endif()

#[[ Create an INTERFACE target as this library is header-only. ]]
add_library(units INTERFACE)
add_library(Units::units ALIAS units)

target_include_directories(units INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>)

target_compile_features(units INTERFACE cxx_std_14)

target_compile_options(units INTERFACE
		$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>)


#[[ Build unit tests if requested. ]]
if (BUILD_TESTING)
	add_subdirectory(test)
endif()


find_program(DOCKER_EXECUTABLE docker)

if(DOCKER_EXECUTABLE)
	message(STATUS "Found docker executable at ${DOCKER_EXECUTABLE}. Adding targets for docker builds.")
	add_subdirectory(docker)
else()
	message(STATUS "Docker - not found. Skipping targets for docker builds.")
endif()


install(DIRECTORY include/units
		DESTINATION include
		FILES_MATCHING PATTERN "*.h")

install(TARGETS units EXPORT unitsTargets COMPONENT units
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
		INCLUDES DESTINATION include)


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