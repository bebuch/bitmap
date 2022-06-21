cmake_minimum_required(VERSION 3.23)


find_package(Git REQUIRED)

execute_process(COMMAND ${GIT_EXECUTABLE} "describe"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE GIT_RETURN_VALUE
    OUTPUT_VARIABLE GIT_VERSION_FROM_TAG)

if(GIT_RETURN_VALUE EQUAL 0)
    string(REGEX REPLACE "^v" "" GIT_VERSION_FROM_TAG "${GIT_VERSION_FROM_TAG}")
    string(REGEX REPLACE "\n$" "" GIT_VERSION_FROM_TAG "${GIT_VERSION_FROM_TAG}")
else()
    execute_process(COMMAND ${GIT_EXECUTABLE} "rev-list" "--all" "--count"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE PATCH_VERSION)
    string(REGEX REPLACE "\n$" "" PATCH_VERSION "${PATCH_VERSION}")
    set(GIT_VERSION_FROM_TAG "0.0.${PATCH_VERSION}")
endif()


project(bitmap VERSION "${GIT_VERSION_FROM_TAG}" LANGUAGES CXX)

message(STATUS "This is bebuch::${PROJECT_NAME} Version ${PROJECT_VERSION}")


set(DEFAULT_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 23)
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

# Install target
install(DIRECTORY include/${PROJECT_NAME} DESTINATION ${INCLUDE_INSTALL_DIR})
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)
install(EXPORT ${PROJECT_NAME}Targets
    NAMESPACE bebuch::
    DESTINATION lib/cmake/${PROJECT_NAME})
configure_package_config_file(Config.cmake.in ${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
    PATH_VARS INCLUDE_INSTALL_DIR)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION lib/cmake/${PROJECT_NAME})


# other subdirectories
option(BITMAP_BUILD_TESTS "build tests" OFF)

if(${BITMAP_BUILD_TESTS})
    enable_testing()
    add_subdirectory(test)
    add_test(NAME tests COMMAND tests)
endif()
