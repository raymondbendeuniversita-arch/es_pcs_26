#include <iostream>
#include <string>

#include "CircuitReader.hpp"
#include "SolverDFS.hpp"      
#include "SolverDePina.hpp"
#include "timecounter.h"


int main(int argc, const char *argv[]) {
	
    timecounter tc; 

    if (argc < 2) {
        std::cout << "Il file non è stato passato correttamente." << std::endl;
        return 1; 
    }

    std::string nomefile = argv[1];

    CircuitReader reader;

    if (!reader.read_file(nomefile)) {
        return 1;  // se fallisce la lettura del circuito mi fermo subito 
    }

    
    std::cout << "------------------------------------------------------------------" << std::endl;

    SolverDFS soluzione_dfs;
    
    soluzione_dfs.solve(reader);  // questa funzione stampa già i risultati internamente
    

    std::cout << "------------------------------------------------------------------" << std::endl;

    SolverDePina soluzione_depina;
    
    soluzione_depina.solve(reader);  // anche questa stampa già i risultati internamente
    
	


    return 0;
}