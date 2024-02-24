cmake_minimum_required(VERSION 3.10)

option(ENABLE_TESTS ON)

set(PROJECT_NAME "orderbook")
set(APPLICATION_NAME "${PROJECT_NAME}-app")
set(LIBRARY_NAME "${PROJECT_NAME}-lib")
set(TEST_NAME "${PROJECT_NAME}-test")

project(PROJECT_NAME CXX)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(core)