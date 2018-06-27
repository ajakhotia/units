add_library(units INTERFACE)

target_include_directories(units INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>)

install(DIRECTORY include/units
		DESTINATION include
		FILES_MATCHING PATTERN "*.h")

install(TARGETS units EXPORT cppYardTargets COMPONENT units
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib/static
		INCLUDES DESTINATION include)

if (BUILD_TESTING)
	add_subdirectory(test)
endif (BUILD_TESTING)