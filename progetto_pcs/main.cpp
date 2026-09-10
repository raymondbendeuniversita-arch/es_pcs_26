#include <iostream>
#include <string>
#include "CircuitSolver.hpp"

int main(int argc, char* argv[]) {
    std::string filename = "netlist.txt";

    // permette di passare il nome del file netlist da riga di comando:
    if (argc > 1) {
        filename = argv[1];
    }
	
    CircuitSolver solver;

    // lettura della netlist:
    if (!solver.read_netlist(filename)) {
        std::cerr << "Impossibile continuare senza un file di netlist valido.\n";
        return 1;
    }

    // risoluzione tramite DFS:
    solver.solve_circuit_dfs();
	
	std::cout << "\n";

    // risoluzione tramite algoritmo di De Pina:
    solver.solve_circuit_depina();

    return 0;
}