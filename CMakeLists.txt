cmake_minimum_required(VERSION 3.16)

project(HttpServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(http_server
    src/main.cpp
    src/html.cpp
)

target_include_directories(http_server PRIVATE include)
