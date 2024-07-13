find_package(GTest REQUIRED)

add_executable(libxml2PerfTests Tests.cpp)
add_test(Tests libxml2PerfTests)
target_link_libraries(libxml2PerfTests libxml2PerfLib)
target_link_libraries(libxml2PerfTests GTest::Main)
