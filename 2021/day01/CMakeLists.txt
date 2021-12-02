cmake_minimum_required(VERSION 3.15)

#message("AOC Project file: ${CMAKE_CURRENT_LIST_FILE}")
get_filename_component(AOC_PROJECT_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH) #from the current CMakeLists.txt fqn get the path
get_filename_component(AOC_DAY "${AOC_PROJECT_DIR}" NAME) # last bit is the day
get_filename_component(AOC_YEAR_TMP "${AOC_PROJECT_DIR}" PATH) # parent dir full path
get_filename_component(AOC_YEAR "${AOC_YEAR_TMP}" NAME) # parent dir name
message("Configuring project ${AOC_YEAR}-${AOC_DAY}")

project(${AOC_YEAR}-${AOC_DAY})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_compile_definitions(INPUT_SRC_DIR="${PROJECT_SOURCE_DIR}")

add_subdirectory("../../aoccommon" cmake-build-debug)

add_executable(${PROJECT_NAME}
               main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC aoc)

