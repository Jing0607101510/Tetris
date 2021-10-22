cmake_minimum_required(VERSION 3.4.1)

project(Tetris)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# 全静态链接
set(CMAKE_EXE_LINKER_FLAGS "-static")

aux_source_directory(. src)

add_executable(${PROJECT_NAME} ${src})
