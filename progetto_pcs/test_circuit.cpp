#include <iostream>
#include <vector>
#include <string>

#include "CircuitReader.hpp"
#include "SolverDFS.hpp"
#include "SolverDePina.hpp"

int main() {
    CircuitReader reader;

 
    std::cout << "1. ESECUZIONE TEST SPAZIATURE ---\n";
    if (!reader.read_file("../netlist_spazi.txt")) {
        std::cerr << "Lettura netlist_spazi.txt fallita.\n";
        return EXIT_FAILURE;
    }
    
    SolverDFS solver_dfs_spazi;
    solver_dfs_spazi.solve(reader);
    std::cout << "Test Spaziature Completato.\n\n";


   
    std::cout << "2. ESECUZIONE TEST NO GENERATORI ---\n";
    if (!reader.read_file("../netlist_no_volt.txt")) {
        std::cerr << "Lettura netlist_no_volt.txt fallita.\n";
        return EXIT_FAILURE;
    }
    SolverDFS solver_dfs_novolt;
    solver_dfs_novolt.solve(reader); 
    std::cout << "Test No Generatori Completato.\n\n";


    
    std::cout << "3. ESECUZIONE TEST NO RESISTENZE ---\n";
    if (!reader.read_file("../netlist_no_res.txt")) {
        std::cerr << "Lettura netlist_no_res.txt fallita.\n";
        return EXIT_FAILURE;
    }
    SolverDFS solver_dfs_nores;
    solver_dfs_nores.solve(reader); 
    std::cout << "Test No Resistenze Completato.\n\n";


    
    std::cout << "4. ESECUZIONE TEST CIRCUITO SCOLLEGATO ---\n";
    if (!reader.read_file("../netlist_scollegata.txt")) {
        std::cerr << "Lettura netlist_scollegata.txt fallita.\n";
        return EXIT_FAILURE;
    }
    SolverDePina solver_depina;
    solver_depina.solve(reader); 
    std::cout << "Test Circuito Scollegato Completato.\n\n";

   
    return EXIT_SUCCESS;
}