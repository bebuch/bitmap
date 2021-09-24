cmake_minimum_required(VERSION 3.20)

project(test_bitmap_package)

find_package(bitmap REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} test.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/io_tools/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/colormap/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${bitmap_INCLUDE_DIR})
