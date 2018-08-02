add_executable(physicalDimensionsTest physicalDimensionsTest.cpp)
target_link_libraries(physicalDimensionsTest PRIVATE units GTest::GTest GTest::Main)
gtest_add_tests(TARGET physicalDimensionsTest)

add_executable(physicalUnitsTest physicalUnitsTest.cpp)
target_link_libraries(physicalUnitsTest PRIVATE units GTest::GTest GTest::Main)
gtest_add_tests(TARGET physicalUnitsTest)

add_executable(physicalQuantityVectorTest physicalQuantityVectorTest.cpp)
target_link_libraries(physicalQuantityVectorTest PRIVATE units GTest::GTest GTest::Main)
gtest_add_tests(TARGET physicalQuantityVectorTest)