include_directories("../include")

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(colormap colormap.cpp)

set_target_properties(colormap PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(colormap PROPERTIES CXX_STANDARD 17)

install(TARGETS colormap DESTINATION bin)
