cmake_minimum_required(VERSION 3.15)
project(day01)

set(CMAKE_CXX_STANDARD 20)

IF (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
ENDIF (CMAKE_BUILD_TYPE MATCHES Debug)

add_compile_definitions(INPUT_SRC_DIR="${CMAKE_SOURCE_DIR}")
add_executable(${PROJECT_NAME}
        main.cpp)

set(AOCCOMMON "${CMAKE_SOURCE_DIR}/../../aoccommon")
add_library(aoc ${AOCCOMMON}/aoc.cpp)
set_target_properties(aoc PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${AOCCOMMON})

target_link_libraries(${PROJECT_NAME} PUBLIC aoc)