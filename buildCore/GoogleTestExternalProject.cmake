#[[ Include CTest to provide "$ make test" capability. ]]
include(CTest)

# [[ Include extrenal projects module. ]]
include(ExternalProject)

#[[ Function that sets the google tests external project per user specified arguments. ]]
function(setup_gtest_external_project
        GIT_SOURCE_REPOSITORY
        GIT_SOURCE_TAG
        EXTERNAL_PROJECT_BUILD_DIRECTORY
        EXTERNAL_PROJECT_INSTALL_DIRECTORY)

    ## Pull in googletest framework as GoogleTestExternalProject target.
    externalproject_add(GoogleTestExternalProject
            GIT_REPOSITORY ${GIT_SOURCE_REPOSITORY}
            GIT_TAG ${GIT_SOURCE_TAG}
            PREFIX ${EXTERNAL_PROJECT_BUILD_DIRECTORY}/GoogleTest
            CMAKE_ARGS
			""
            CMAKE_CACHE_ARGS
			-DCMAKE_INSTALL_PREFIX:STRING=${EXTERNAL_PROJECT_INSTALL_DIRECTORY}
			-DCMAKE_PREFIX_PATH:STRING=${EXTERNAL_PROJECT_INSTALL_DIRECTORY}
			-DCMAKE_CXX_STANDARD:STRING=${CMAKE_CXX_STANDARD}
			-DCMAKE_CXX_STANDARD_REQUIRED:BOOL=${CMAKE_CXX_STANDARD_REQUIRED}
			-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
			-DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS}
            UPDATE_DISCONNECTED 1)

    #[[ Get properties of the external project. ]]
    externalproject_get_property(GoogleTestExternalProject SOURCE_DIR BINARY_DIR)

    #[[ Create the directory to prevent INTERFACE_INCLUDE_DIRECTORIES from failing fatally. It is important as
        cmake currently has a bug that prevents specifying non-existing directories as INTERFACE_INCLUDE_DIRECTORIES for
        imported targets. This is a safe work-around until this issue is addressed by kitware. ]]
    file(MAKE_DIRECTORY ${EXTERNAL_PROJECT_INSTALL_DIRECTORY}/include)

    #[[ Add duck library for gtest. ]]
    add_library(gtest UNKNOWN IMPORTED)
    set_target_properties(gtest PROPERTIES
            IMPORTED_LOCATION ${EXTERNAL_PROJECT_INSTALL_DIRECTORY}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
            INTERFACE_INCLUDE_DIRECTORIES ${EXTERNAL_PROJECT_INSTALL_DIRECTORY}/include)
    add_dependencies(gtest GoogleTestExternalProject)

    #[[ Add duck library for gtest_main. ]]
    add_library(gtest_main UNKNOWN IMPORTED)
    set_target_properties(gtest_main PROPERTIES
            IMPORTED_LOCATION ${EXTERNAL_PROJECT_INSTALL_DIRECTORY}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
            INTERFACE_INCLUDE_DIRECTORIES ${EXTERNAL_PROJECT_INSTALL_DIRECTORY}/include)
    add_dependencies(gtest_main GoogleTestExternalProject)

    #[[ Add duck library for gmock. ]]
    add_library(gmock UNKNOWN IMPORTED)
    set_target_properties(gtest PROPERTIES
            IMPORTED_LOCATION ${EXTERNAL_PROJECT_INSTALL_DIRECTORY}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX}
            INTERFACE_INCLUDE_DIRECTORIES ${EXTERNAL_PROJECT_INSTALL_DIRECTORY}/include)
    add_dependencies(gmock GoogleTestExternalProject)

    #[[ Add duck library for gmock_main. ]]
    add_library(gmock_main UNKNOWN IMPORTED)
    set_target_properties(gtest_main PROPERTIES
            IMPORTED_LOCATION ${EXTERNAL_PROJECT_INSTALL_DIRECTORY}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gmock_main${CMAKE_STATIC_LIBRARY_SUFFIX}
            INTERFACE_INCLUDE_DIRECTORIES ${EXTERNAL_PROJECT_INSTALL_DIRECTORY}/include)
    add_dependencies(gmock_main GoogleTestExternalProject)

endfunction()

## Create a function to make adding gtests easy and consistent
function(add_gtest test_name test_file)
	# Create an executable
	add_executable(${test_name} ${test_file})

	# Set all compiler warnings to ON
	target_compile_options(${test_name} PRIVATE -Wall -Werror)

	# Link the test against gtest pthreads
	target_link_libraries(${test_name} ${ARGN} gtest_main gtest pthread)

	# Add the test to the Ctest to enable running of "$ make test".
	add_test(NAME ${test_name}_gtest COMMAND ${test_name})
endfunction()

## Create a function to make adding gmock easy and consistent
function(add_gmock test_name test_file)
    # Create an executable
    add_executable(${test_name} ${test_file})

    # Set all compiler warnings to ON
    target_compile_options(${test_name} PRIVATE -Wall -Werror)

    # Link the test against gtest pthreads
    target_link_libraries(${test_name} ${ARGN} gmock_main gmock pthread)

    # Add the test to the Ctest to enable running of "$ make test".
    add_test(NAME ${test_name}_gmock COMMAND ${test_name})
endfunction()