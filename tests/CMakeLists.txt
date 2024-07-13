find_package(GTest REQUIRED)

enable_testing()
add_executable(libxml2PerfTests Tests.cpp)
target_link_libraries(libxml2PerfTests libxml2PerfLib)
target_link_libraries(libxml2PerfTests GTest::Main)
