configure_file(include/buildInformation/buildInformation.h.template
		include/buildInformation/buildInformation.h @ONLY)

add_library(buildInformation SHARED src/buildInformation.cpp)

target_include_directories(buildInformation PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
		$<INSTALL_INTERFACE:include>)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/buildInformation
		DESTINATION include
		FILES_MATCHING PATTERN "*.h")

install(TARGETS buildInformation EXPORT cppYardTargets COMPONENT buildInformation
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib/static
		INCLUDES DESTINATION include)

if (BUILD_TESTING)
	add_subdirectory(test)
endif (BUILD_TESTING)