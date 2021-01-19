find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(unitsTest physicalDimensionsTest.cpp physicalUnitsTest.cpp affineQuantityTest.cpp)
target_link_libraries(unitsTest PRIVATE Units::units GTest::GTest GTest::Main)

target_compile_options(units INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>)

gtest_discover_tests(unitsTest)
