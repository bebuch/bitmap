# cmake_minimum_required(VERSION 3.8)

include_directories("../include")

find_package(GTest REQUIRED)

add_executable(subbitmap subbitmap.cpp)

target_link_libraries(subbitmap GTest::GTest GTest::Main)

set_target_properties(subbitmap PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(subbitmap PROPERTIES CXX_STANDARD 17)

install(TARGETS subbitmap DESTINATION bin)
