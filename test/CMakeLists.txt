project(tests)

find_package(GTest REQUIRED)
find_package(Boost REQUIRED)

file(GLOB SOURCE_FILES "*.cpp")
add_executable(tests ${SOURCE_FILES})

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/io_tools/include)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/colormap/include)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(tests PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(tests GTest::GTest GTest::Main)
