add_library(${LIBRARY_NAME})

target_sources(${LIBRARY_NAME} PRIVATE 
"Configuration.cpp"
"Book.cpp"
"LimitTree.cpp"
"Limit.cpp")

include(FetchContent)
FetchContent_Declare(
    tomlplusplus
    URL "https://github.com/marzer/tomlplusplus/archive/v3.3.0.tar.gz"
    URL_HASH "SHA256=fc1a5eb410f3c67e90e5ad1264a1386d020067cfb01b633cc8c0441789aa6cf2"
)

FetchContent_MakeAvailable(tomlplusplus)
target_include_directories(${LIBRARY_NAME} PUBLIC "${tomlplusplus_SOURCE_DIR}/include")
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/external)
