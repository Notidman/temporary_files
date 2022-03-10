cmake_minimum_required(VERSION 3.2)

include_directories(inc)
project(help_car)

set( SRC 
	src/main.c
	src/car.c)

add_executable(${PROJECT_NAME} ${SRC})
