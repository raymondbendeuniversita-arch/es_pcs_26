cmake_minimum_required(VERSION 3.20)

project(progetto_pcs) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

find_package(Eigen3 REQUIRED)

add_executable(output main.cpp timecounter.cpp)

target_link_libraries(output Eigen3::Eigen)

add_executable(test_circuit test_circuit.cpp)
target_link_libraries(test_circuit Eigen3::Eigen)

add_test(NAME validazione_circuiti COMMAND test_circuit)

enable_testing()