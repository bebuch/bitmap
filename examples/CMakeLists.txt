project(examples)

find_package(Boost REQUIRED)
find_package(colormap REQUIRED)

add_executable(colormap colormap.cpp)

target_include_directories(colormap PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(colormap PUBLIC ${Boost_INCLUDE_DIRS})
target_include_directories(colormap PUBLIC ${colormap_INCLUDE_DIR})
