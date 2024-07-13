find_package(libxml2 REQUIRED)

add_library(libxml2PerfLib
        libxml2Perf/NodeWriter.cpp
        libxml2Perf/NodeWriter.h
        libxml2Perf/DataGen.h
        libxml2Perf/DataGen.cpp)
target_include_directories(libxml2PerfLib PUBLIC .)
target_include_directories(libxml2PerfLib PUBLIC ${CPPCODEC_INCLUDE_DIR})
target_link_libraries(libxml2PerfLib PUBLIC LibXml2::LibXml2)