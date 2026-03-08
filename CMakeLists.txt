cmake_minimum_required(VERSION 3.10)
project(http-server VERSION 1.0)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Build webserver lib
add_library(http_server src/http-server.cpp)

# Header location
target_include_directories(http_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# WS if on windows
if(WIN32)
    target_link_libraries(http_server PUBLIC ws2_32)
endif()

# 2. Build example
add_executable(basic_server example/example.cpp)

# Linker actions
target_link_libraries(basic_server PRIVATE http_server)