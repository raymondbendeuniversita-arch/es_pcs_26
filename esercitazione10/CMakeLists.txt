cmake_minimum_required(VERSION 3.20)

project(esercitazione10_gradiente_coniugato) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

find_package(Eigen3 REQUIRED)

add_executable(output gradiente_coniugato.cpp)

target_link_libraries(output Eigen3::Eigen)