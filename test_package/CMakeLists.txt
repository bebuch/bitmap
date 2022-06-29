cmake_minimum_required(VERSION 3.23)

project(test_package)

find_package(bitmap 2.4 REQUIRED)
find_package(GTest 1.11 REQUIRED)

file(GLOB SOURCE_FILES "${CMAKE_SOURCE_DIR}/../test/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_link_libraries(${PROJECT_NAME} tuiqbv::bitmap)
target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main)

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
