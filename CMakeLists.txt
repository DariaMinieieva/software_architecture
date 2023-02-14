cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)

project(microservices)


add_subdirectory(logging)
add_subdirectory(facade)

add_subdirectory(messages)