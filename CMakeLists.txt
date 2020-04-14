set(QTHTTPSERVER_VERSION 0.0.1)

cmake_policy(SET CMP0048 NEW)
project(QtHttpServer VERSION ${QTHTTPSERVER_VERSION} LANGUAGES CXX)
cmake_minimum_required(VERSION 3.11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 14)

find_package(Qt5 COMPONENTS WebSockets REQUIRED)

enable_testing()

SET(gtest_force_shared_crt ON)
add_subdirectory(3rdparties/googletest)

file(GLOB_RECURSE INCLUDE_FILES include/QtHttpServer/*)
file(GLOB_RECURSE SOURCE_FILES src/*)

add_library(QtHttpServer SHARED ${INCLUDE_FILES} ${SOURCE_FILES})
target_include_directories(QtHttpServer PUBLIC include)
target_include_directories(QtHttpServer PRIVATE private)
target_compile_definitions(QtHttpServer PRIVATE BUILD_QTHTTPSERVER)
target_link_libraries(QtHttpServer Qt5::Core)

file(GLOB_RECURSE TEST_FILES test/*)
add_executable(QtHttpServerTests ${INCLUDE_FILES} ${SOURCE_FILES} ${TEST_FILES})
target_include_directories(QtHttpServerTests PRIVATE include)
target_link_libraries(QtHttpServerTests Qt5::Core gtest)
target_compile_definitions(QtHttpServerTests PRIVATE BUILD_QTHTTPSERVER_TESTS)
add_test(QtHttpServer_Tests QtHttpServerTests)

file(GLOB_RECURSE SERVER_SOURCE_FILES server-src/*)
add_executable(RunnableHttpServer ${SERVER_SOURCE_FILES})
target_link_libraries(RunnableHttpServer QtHttpServer)