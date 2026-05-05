cmake_minimum_required(VERSION 3.20)
project(esercitazione4_ordinamento_vettori)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")



# Creo il target per l'eseguibile principale del mio progetto software
set(SRC_test_sorts timecounter.cpp measure_merge_quick.cpp)
add_executable(measure_sorts ${SRC_test_sorts})


set(SRC_test_sorts timecounter.cpp quick_vs_ibrido.cpp)
add_executable(benchmark ${SRC_test_sorts})

## Creo i target per gli eseguibili che effettueranno i test unitari
add_executable(test_mergesort test_mergesort.cpp)
add_test(NAME mergesort COMMAND test_mergesort)

add_executable(test_quicksort test_quicksort.cpp)
add_test(NAME quicksort COMMAND test_quicksort)

add_executable(test_quickibrido test_quickIbrido.cpp)
add_test(NAME quickibrido COMMAND test_quickibrido)


enable_testing()