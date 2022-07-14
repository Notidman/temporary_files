cmake_minimum_required(VERSION 3.2)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(learn VERSION 0.1 LANGUAGES C)
set(CMAKE_C_STANDARD 11) 

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lpthread -Wall -Wextra -Wpedantic -fPIC -march=native -g")
set(CMAKE_C_FLAGS_RELEASE " -lpthread -O2 -fPIC -march=native")

include_directories(src)
set(PROJECT_SOURCES_DIR src)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})

