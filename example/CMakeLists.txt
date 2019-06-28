include_directories("../include")

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(colormap colormap.cpp)

install(TARGETS colormap DESTINATION bin)
