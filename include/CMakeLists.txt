# cmake_minimum_required(VERSION 3.8)

add_library(bitmap INTERFACE)

target_include_directories(bitmap INTERFACE "${BEBUCH_BITMAP_SOURCE_DIR}/include")
