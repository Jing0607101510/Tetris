cmake_minimum_required(VERSION 3.4.1)

project(Tetris)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

aux_source_directory(. src)

add_executable(${PROJECT_NAME} ${src})
