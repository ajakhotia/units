find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(unitsTest physicalDimensionsTest.cpp physicalUnitsTest.cpp affineQuantityTest.cpp)
target_link_libraries(unitsTest PRIVATE Units::units GTest::GTest GTest::Main)
target_compile_options(unitsTest PRIVATE -Wall -Wextra -pedantic -Werror)
gtest_discover_tests(unitsTest)
