configure_file(buildInformationTest.cpp.template buildInformationTest.cpp @ONLY)

add_gtest(buildInformationTest
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/buildInformationTest.cpp>
        buildInformation)