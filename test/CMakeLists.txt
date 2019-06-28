# cmake_minimum_required(VERSION 3.8)

include_directories("../include")
include_directories("../3rdparty/io_tools/include")

find_package(GTest REQUIRED)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
add_executable(bitmap_lib_tests ${SOURCES})

target_link_libraries(bitmap_lib_tests GTest::GTest GTest::Main)

install(TARGETS bitmap_lib_tests DESTINATION bin)
