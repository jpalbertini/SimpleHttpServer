set(SIMPLEHTTPSERVER_VERSION 0.0.1)

cmake_policy(SET CMP0048 NEW)
project(SimpleHttpServer VERSION ${SIMPLEHTTPSERVER_VERSION} LANGUAGES CXX)
cmake_minimum_required(VERSION 3.11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS Core Network WebSockets REQUIRED)

enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(3rdparties/googletest)

file(GLOB_RECURSE INCLUDE_FILES include/SimpleHttpServer/* private/*)
file(GLOB_RECURSE SOURCE_FILES src/*)

SET(SimpleHttpServer_DEPENDENCIES Qt5::Core Qt5::Network)

add_library(SimpleHttpServer SHARED ${INCLUDE_FILES} ${SOURCE_FILES})
target_include_directories(SimpleHttpServer PUBLIC include)
target_include_directories(SimpleHttpServer PRIVATE private)

target_compile_definitions(SimpleHttpServer PRIVATE BUILD_SIMPLEHTTPSERVER)

if (MSVC)
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
endif()

target_link_libraries(SimpleHttpServer ${SimpleHttpServer_DEPENDENCIES})

file(GLOB_RECURSE TEST_FILES test/*)
add_executable(SimpleHttpServerTests ${TEST_FILES})
target_link_libraries(SimpleHttpServerTests SimpleHttpServer gtest)
add_test(SimpleHttpServer_Tests SimpleHttpServerTests --gtest_shuffle --gtest_output=xml:test_results.xml)

file(GLOB_RECURSE SERVER_SOURCE_FILES server-src/*)
add_executable(RunnableHttpServer ${SERVER_SOURCE_FILES})
target_link_libraries(RunnableHttpServer SimpleHttpServer)