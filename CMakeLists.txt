cmake_minimum_required(VERSION 3.27)

project(units VERSION 0.2.0.1 LANGUAGES C CXX)


#[[ Setup unit testing framework. ]]
if(BUILD_TESTING)
    find_package(GTest REQUIRED)
else()
    find_package(GTest)
endif()

if((TARGET GTest::GTest) AND (TARGET GTest::Main))
    include(CTest)
endif()


#[[ Setup project level tools and external dependencies if and only if this project
    is the top-level project. If this project has been included with-in another
    project as a submodule, then the onus of setting up these requirement falls on that
    top-level project. This prevents this project from overreaching when it is used as a submodule
    in another project. ]]
if(PROJECT_IS_TOP_LEVEL)
    include(external/infraCommons/cmake/utilities/clangFormat.cmake)
    include(external/infraCommons/cmake/utilities/exportedTargets.cmake)
    include(external/infraCommons/cmake/utilities/requireArguments.cmake)

    add_clang_format(TARGET unitsClangFormat VERSION 19)

    add_subdirectory(docker)
endif()


#[[ Create an INTERFACE target as this library is header-only. ]]
add_exported_library(
    TARGET
      units

    TYPE
      INTERFACE

    NAMESPACE
      Units::

    EXPORT
      unitsTargets

    SOURCES
      ""

    HEADERS
      INTERFACE include/units/affineQuantity.hpp
      INTERFACE include/units/imperial.hpp
      INTERFACE include/units/physicalDimensions.hpp
      INTERFACE include/units/physicalUnits.hpp
      INTERFACE include/units/si.hpp

    INCLUDE_DIRECTORIES
      ${CMAKE_CURRENT_SOURCE_DIR}/include

    LINK_LIBRARIES
      ""

    COMPILE_FEATURES
      INTERFACE cxx_std_14

    COMPILE_OPTIONS
      INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
      INTERFACE $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>

    COMPILE_DEFINITIONS
      ""
)


#[[ Build unit tests if requested. ]]
if(BUILD_TESTING)
    add_subdirectory(test)
endif()


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
