cmake_minimum_required(VERSION 3.15)
project(day09)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(INPUT_SRC_DIR="${CMAKE_SOURCE_DIR}")

add_executable(${PROJECT_NAME}
        main.cpp)

set(AOCCOMMON "${CMAKE_SOURCE_DIR}/../../aoccommon")
add_library(aoc ${AOCCOMMON}/aoc.cpp)
set_target_properties(aoc PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${AOCCOMMON})


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})
find_package(TBB REQUIRED COMPONENTS tbb)
#target_link_libraries(${PROJECT_NAME} PUBLIC tbb)

target_link_libraries(${PROJECT_NAME} PUBLIC aoc tbb)
