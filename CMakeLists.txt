cmake_minimum_required(VERSION 3.10)
add_definitions(-w)

option(ENABLE_TESTS ON)

set(PROJECT_NAME "orderbook")
set(APPLICATION_NAME "${PROJECT_NAME}-app")
set(LIBRARY_NAME "${PROJECT_NAME}-lib")
set(TEST_NAME "${PROJECT_NAME}-test")

project(PROJECT_NAME CXX)
set(CMAKE_CXX_STANDARD 23)

message(${CMAKE_CXX_COMPILER_ID})
message(${CMAKE_CXX_COMPILER_VERSION})

add_subdirectory(core)