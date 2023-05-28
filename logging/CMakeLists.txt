cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)

project(logging)

add_executable(logging logging_service.h logging_main.cpp logging_controller.h)

if(LIBHTTPSERVER_INCLUDE_DIRS AND LIBHTTPSERVER_LIBRARIES)
    set(LIBHTTPSERVER_FOUND TRUE)

else(LIBHTTPSERVER_INCLUDE_DIRS AND LIBHTTPSERVER_LIBRARIES)
    find_path(LIBHTTPSERVER_INCLUDE_DIRS httpserverpp
            /usr/include
            /usr/include/httpserver
            /usr/local/include/
            /usr/local/include/httpserver
            )

    find_library(LIBHTTPSERVER_LIBRARIES NAMES httpserver
            PATHS
            /usr/lib
            /usr/local/lib
            /opt/local/lib
            )

    if(LIBHTTPSERVER_INCLUDE_DIRS AND LIBHTTPSERVER_LIBRARIES)
        set(LIBHTTPSERVER_FOUND TRUE)
        message(STATUS "Found libhttpserver: ${LIBHTTPSERVER_INCLUDE_DIRS}, ${LIBHTTPSERVER_LIBRARIES}")
    else(LIBHTTPSERVER_INCLUDE_DIRS AND LIBHTTPSERVER_LIBRARIES)
        set(LIBHTTPSERVER_FOUND FALSE)
        message(STATUS "libhttpserver not found.")
    endif(LIBHTTPSERVER_INCLUDE_DIRS AND LIBHTTPSERVER_LIBRARIES)

    mark_as_advanced(LIBHTTPSERVER_INCLUDE_DIRS LIBHTTPSERVER_LIBRARIES)

endif(LIBHTTPSERVER_INCLUDE_DIRS AND LIBHTTPSERVER_LIBRARIES)

target_include_directories(logging PRIVATE ${LIBHTTPSERVER_INCLUDE_DIRS})

find_package(cpr REQUIRED)
target_include_directories(logging PRIVATE ${LIBCPR_INCLUDE_DIRS})
target_link_libraries(logging ${LIBHTTPSERVER_LIBRARIES} cpr::cpr)

find_package(hazelcast-cpp-client CONFIG REQUIRED)
target_link_libraries(logging hazelcast-cpp-client::hazelcast-cpp-client)

find_package(ppconsul)
target_link_libraries(logging ppconsul)