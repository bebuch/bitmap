project(tests)

find_package(io_tools REQUIRED)
find_package(GTest REQUIRED)
find_package(Boost REQUIRED)

file(GLOB SOURCE_FILES "*.cpp")
add_executable(tests ${SOURCE_FILES})

target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(tests PUBLIC ${Boost_INCLUDE_DIRS})
target_include_directories(tests PUBLIC ${io_tools_INCLUDE_DIRS})

target_link_libraries(tests GTest::GTest GTest::Main)
