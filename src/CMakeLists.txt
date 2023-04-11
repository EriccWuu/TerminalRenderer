cmake_minimum_required(VERSION 3.5)

# project name
project(TerminalRenderer)


# include_directories("./src")
aux_source_directory(./src all_src)

# file(GLOB SOURCES ./src/*.h ./src/*.cpp)

# add executavle file
add_executable(${CMAKE_PROJECT_NAME} ${all_src})
# add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
