find_package(GTest 1.11 REQUIRED)

file(GLOB SOURCE_FILES "*.cpp")
add_executable(${PROJECT_NAME}_tests ${SOURCE_FILES})

target_compile_features(${PROJECT_NAME}_tests PUBLIC cxx_std_23)
target_link_libraries(${PROJECT_NAME}_tests ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_tests GTest::GTest GTest::Main)

enable_testing()
add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
