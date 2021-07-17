cmake_minimum_required(VERSION 3.8)

project(bitmap)

set(DEFAULT_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# interface target
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_include_directories(${PROJECT_NAME}
    SYSTEM INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)
target_compile_definitions(${PROJECT_NAME} INTERFACE)


# Setup package config
set(INCLUDE_INSTALL_DIR include)
set(LIB_INSTALL_DIR lib)
set(CONFIG_PACKAGE_INSTALL_DIR ${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME})

include(CMakePackageConfigHelpers)
configure_package_config_file(${PROJECT_NAME}-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    INSTALL_DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}/cmake
    PATH_VARS INCLUDE_INSTALL_DIR)

# Install target
install(DIRECTORY include/${PROJECT_NAME}
    DESTINATION ${INCLUDE_INSTALL_DIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    DESTINATION ${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME})


# other subdirectories
option(BITMAP_BUILD_TESTS "build tests" OFF)
option(BITMAP_BUILD_EXAMPLES "build examples" OFF)

if(${BITMAP_BUILD_TESTS})
    enable_testing()
    add_subdirectory(test)
    add_test(NAME tests COMMAND tests)
endif()

if(${BITMAP_BUILD_EXAMPLES})
    add_subdirectory(example)
endif()
