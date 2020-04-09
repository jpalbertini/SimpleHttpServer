project(QtHttpServer)
cmake_minimum_required(VERSION 3.11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS WebSockets REQUIRED)

add_executable(QtHttpServer
    src/main.cpp
)

target_link_libraries(QtHttpServer Qt5::Core)