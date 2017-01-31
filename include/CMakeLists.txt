cmake_minimum_required (VERSION 2.8.11)

file(GLOB header "bitmap/*.hpp")
add_library(BEBUCH_BITMAP STATIC ${header})

set_target_properties(BEBUCH_BITMAP PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(BEBUCH_BITMAP PROPERTIES CXX_STANDARD 14)
