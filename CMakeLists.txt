cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)

project(hazelcast_lab_task_1)
project(hazelcast_lab_task_2)
project(hazelcast_lab_task_3)

add_executable(hazelcast_lab_task_1 task_1.cpp)
add_executable(hazelcast_lab_task_2 task_2.cpp)
add_executable(hazelcast_lab_task_3 task_3.cpp)

find_package(Threads REQUIRED)

target_link_libraries(hazelcast_lab_task_1 Threads::Threads)
target_link_libraries(hazelcast_lab_task_2 Threads::Threads)
target_link_libraries(hazelcast_lab_task_3 Threads::Threads)

find_package(hazelcast-cpp-client CONFIG REQUIRED)

target_link_libraries(hazelcast_lab_task_1 hazelcast-cpp-client::hazelcast-cpp-client)
target_link_libraries(hazelcast_lab_task_2 hazelcast-cpp-client::hazelcast-cpp-client)
target_link_libraries(hazelcast_lab_task_3 hazelcast-cpp-client::hazelcast-cpp-client)
