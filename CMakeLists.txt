cmake_minimum_required(VERSION 3.5.0)

#[[ Set the name of the project and provide language specification. ]]
project(cppYard VERSION 0.1.0.0 LANGUAGES C CXX)

#[[ Set CMAKE_CXX_STANDARD. ${CMAKE_CXX_STANDARD} sets the initial value for ${CXX_STANDARD} on
    all targets unless specified otherwise. ]]
set(CMAKE_CXX_STANDARD 14)

#[[ Set CMAKE_CXX_STANDARD_REQUIRED to ON. ${CMAKE_CXX_STANDARD_REQUITED} sets the initial value
    for ${CXX_STANDARD_REQUIRED} which ensures that cmake WILL FAIL if a target is not compiled
    using the specified C++ standard due to compiler limitations. ]]
set(CMAKE_CXX_STANDARD_REQUIRED ON BOOL)

#[[ Add gtest as external project. ]]
include(buildCore/GoogleTestExternalProject.cmake)

setup_gtest_external_project(
		https://github.com/google/googletest.git
		release-1.8.0
		${PROJECT_BINARY_DIR}/external/build
		${PROJECT_BINARY_DIR}/external/install)

#[[ Add sub-projects. ]]
add_subdirectory(buildInformation)
add_subdirectory(units)

#[[ Include cmake-default tools to help create export files. ]]
include(CMakePackageConfigHelpers)

#[[ Install ${CMAKE_INSTALL_PREFIX}/lib/cmake/cppYard/cppyardTargets.cmake for other projects to include the
    installation tree. ]]
install(EXPORT cppYardTargets NAMESPACE cppYard::
		FILE cppYardTargets.cmake
		DESTINATION lib/cmake/cppYard)

#[[ Generate a configuration and install it. ]]
write_basic_package_version_file(
		${CMAKE_CURRENT_BINARY_DIR}/cmake/cppYardConfigVersion.cmake
		COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cmake/cppYardConfigVersion.cmake
		DESTINATION lib/cmake/cppYard)

#[[ Configure and install cppYardConfig.cmake.in to enable other projects find cppYard from
    the install tree. ]]
configure_package_config_file(
		cmake/cppYardConfig.cmake.in cmake/cppYardConfig.cmake
		INSTALL_DESTINATION lib/cmake/cppYard)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cmake/cppYardConfig.cmake
		DESTINATION lib/cmake/cppYard)