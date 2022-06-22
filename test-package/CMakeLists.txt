cmake_minimum_required(VERSION 3.23)

project(test_package)

find_package(bitmap 2.3 REQUIRED)

add_executable(${PROJECT_NAME} test.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_link_libraries(${PROJECT_NAME} PRIVATE tuiqbv::bitmap)

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
