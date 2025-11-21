find_package(GTest CONFIG REQUIRED)

add_executable(test_store test_store.cpp)

target_link_libraries(test_store
    PRIVATE
        FastJSONStore
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_store)