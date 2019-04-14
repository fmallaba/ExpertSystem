cmake_minimum_required(VERSION 3.13)
project(expert_system CXX)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(src SRC)
add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE src)