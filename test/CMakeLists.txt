# cmake_minimum_required(VERSION 3.8)

include_directories("../include")
include_directories("../../io_tools/include")

find_package(GTest REQUIRED)

add_executable(subbitmap subbitmap.cpp)

target_link_libraries(subbitmap GTest::GTest GTest::Main)

set_target_properties(subbitmap PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(subbitmap PROPERTIES CXX_STANDARD 17)

add_executable(rect_transform rect_transform.cpp)

target_link_libraries(rect_transform GTest::GTest GTest::Main)

set_target_properties(rect_transform PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(rect_transform PROPERTIES CXX_STANDARD 17)

add_executable(binary_io binary_io.cpp)

target_link_libraries(binary_io GTest::GTest GTest::Main)

set_target_properties(binary_io PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(binary_io PROPERTIES CXX_STANDARD 17)

install(TARGETS subbitmap rect_transform binary_io DESTINATION bin)
