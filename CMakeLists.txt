cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 23)

option(ENABLE_TESTS ON)

set(APPLICATION_NAME "Orderbook")
set(TEST_NAME "Orderbook-Tests")

project(${APPLICATION_NAME})

add_executable(${APPLICATION_NAME})

include(FetchContent)
FetchContent_Declare(
    tomlplusplus
    URL "https://github.com/marzer/tomlplusplus/archive/v3.3.0.tar.gz"
    URL_HASH "SHA256=fc1a5eb410f3c67e90e5ad1264a1386d020067cfb01b633cc8c0441789aa6cf2"
)
FetchContent_MakeAvailable(tomlplusplus)
target_include_directories(${APPLICATION_NAME} PRIVATE "${tomlplusplus_SOURCE_DIR}/include")

target_include_directories(${APPLICATION_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external")
target_include_directories(${APPLICATION_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/core/src")

if(${ENABLE_TESTS})
  enable_testing()
  add_executable(${TEST_NAME})
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  target_link_libraries(
      ${TEST_NAME}
      GTest::gtest_main
  )
  include(GoogleTest)
  target_include_directories(${TEST_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/external")
endif()

add_subdirectory(core)