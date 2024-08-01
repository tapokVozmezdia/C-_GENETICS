cmake_minimum_required(VERSION 3.5)

project(Genetics_C)

set(CMAKE_C_FLAGS "-O3 -Wall -Werror -Wno-missing-braces")

include_directories(include src)
link_directories(lib)

set(SOURCES ${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${SOURCES}/*.cpp")

add_executable(Genetics_C ${SOURCES}/main.cpp)
target_sources(Genetics_C PRIVATE ${PROJECT_SOURCES})
target_link_libraries(Genetics_C raylib)