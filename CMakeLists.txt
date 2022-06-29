cmake_minimum_required(VERSION 3.23)


# generate project version from Git tags
find_package(Git REQUIRED)

execute_process(COMMAND ${GIT_EXECUTABLE} "describe" "--tags"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE GIT_RETURN_VALUE
    OUTPUT_VARIABLE GIT_VERSION_FROM_TAG)

if(GIT_RETURN_VALUE EQUAL 0)
    string(REGEX REPLACE "^v" "" GIT_VERSION_FROM_TAG "${GIT_VERSION_FROM_TAG}")
    string(REGEX REPLACE "\n$" "" GIT_VERSION_FROM_TAG "${GIT_VERSION_FROM_TAG}")
    string(REGEX REPLACE "\-........$" "" GIT_VERSION_FROM_TAG "${GIT_VERSION_FROM_TAG}")
    string(REGEX REPLACE "-" "." GIT_VERSION_FROM_TAG "${GIT_VERSION_FROM_TAG}")
else()
    execute_process(COMMAND ${GIT_EXECUTABLE} "rev-list" "--all" "--count"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE PATCH_VERSION)
    string(REGEX REPLACE "\n$" "" PATCH_VERSION "${PATCH_VERSION}")
    set(GIT_VERSION_FROM_TAG "0.0.${PATCH_VERSION}")
endif()


# project name and version
project(bitmap VERSION "${GIT_VERSION_FROM_TAG}" LANGUAGES CXX)

message(NOTICE "This is tuiqbv::${PROJECT_NAME} Version ${PROJECT_VERSION}")


# global build settings
set(DEFAULT_BUILD_TYPE "Release")

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror)
endif()


# interface target
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>)
target_include_directories(${PROJECT_NAME} SYSTEM INTERFACE $<INSTALL_INTERFACE:include>)


# Setup package config
set(INCLUDE_INSTALL_DIR include)
set(LIB_INSTALL_DIR lib)
set(CONFIG_PACKAGE_INSTALL_DIR ${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME})

# Install target
include(CMakePackageConfigHelpers)
configure_package_config_file(Config.cmake.in ${PROJECT_NAME}Config.cmake INSTALL_DESTINATION lib/cmake/${PROJECT_NAME} PATH_VARS INCLUDE_INSTALL_DIR)
write_basic_package_version_file(${PROJECT_NAME}ConfigVersion.cmake VERSION ${PROJECT_VERSION} COMPATIBILITY SameMinorVersion)
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets)
install(EXPORT ${PROJECT_NAME}Targets NAMESPACE tuiqbv:: DESTINATION lib/cmake/${PROJECT_NAME})
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake ${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake DESTINATION lib/cmake/${PROJECT_NAME})
install(DIRECTORY include/${PROJECT_NAME} DESTINATION ${INCLUDE_INSTALL_DIR})


# other subdirectories
include(CTest)
if(BUILD_TESTING)
    add_subdirectory(test)
endif()
