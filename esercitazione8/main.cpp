#include <iostream>
#include <algorithm>
#include <concepts>

#include <set>
#include <map>
#include <vector>




#include "unidirected_edge.hpp"
#include "unidirected_graph.hpp"




/*
Si implementi una struttura dati in grado di rappresentare un grafo non diretto

*/




int main(){
	
    unidirected_edge<int> e1(50, 10);
    unidirected_edge<int> e2(10, 50);
    unidirected_edge<int> e3(5, 100);

    std::cout << "--- TEST EDGES ---" << std::endl;
    std::cout << "Edge 1: (" << e1.from() << "," << e1.to() << ")" << std::endl;
    std::cout << "Edge 1 == Edge 2: " << (e1 == e2 ? "Vero" : "Falso") << std::endl;
    std::cout << "Edge 1 < Edge 3: " << (e1 < e3 ? "Vero" : "Falso") << std::endl;

    std::cout << "\n--- TEST GRAFO G (COSTRUTTORE DEFAULT) ---" << std::endl;
    unidirected_graph<int> G;
    for (int i = 0; i < 20; ++i) {
        G.add_edges(i, i + 1);
        G.add_edges(i, i + 2);
    }

    std::cout << "G - Nodi totali: " << G.all_nodes().size() << std::endl;
    std::cout << "G - Archi totali: " << G.all_edges().size() << std::endl;

    std::cout << "\n--- TEST COSTRUTTORE DI COPIA (G_copia) ---" << std::endl;
    unidirected_graph<int> G_copia(G);
    std::cout << "G_copia - Archi totali: " << G_copia.all_edges().size() << std::endl;

    std::cout << "\n--- TEST SOTTOINSIEME H E DIFFERENZA ---" << std::endl;
    unidirected_graph<int> H;
    for (int i = 0; i < 5; ++i) {
        H.add_edges(i, i + 1);
    }

    unidirected_graph<int> diff = G - H;
    std::cout << "Archi in (G - H): " << diff.all_edges().size() << std::endl;

    std::cout << "\n--- TEST POSIZIONI (EDGE_AT / EDGE_NUMBER) ---" << std::endl;
    int index = 10;
    unidirected_edge<int> target = G.edge_at(index);
    std::cout << "Arco a indice " << index << ": (" << target.from() << "," << target.to() << ")" << std::endl;
    std::cout << "Indice dell'arco (" << target.from() << "," << target.to() << "): " << G.edge_number(target) << std::endl;

    std::cout << "\n--- TEST GRAFO L (DUPLICATI E VICINI) ---" << std::endl;
    unidirected_graph<int> L;
    L.add_edges(100, 200);
    L.add_edges(200, 100);
    L.add_edges(100, 300);
    L.add_edges(100, 400);
    L.add_edges(100, 500);

    std::cout << "L - Archi (attesi 4): " << L.all_edges().size() << std::endl;
    std::cout << "Vicini di 100: ";
    for (int v : L.neighbours(100)) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
	
	
	std::cout << "\n--- TEST STAMPA COMPLETA GRAFO M ---" << std::endl;
    unidirected_graph<int> M;

    // Ciclo per aggiungere archi tra 10 nodi (da 0 a 9)
    for (int i = 0; i < 9; ++i) {
        M.add_edges(i, i + 1); // Connessione lineare
        if (i < 8) {
            M.add_edges(i, i + 2); // Connessione a salto
        }
    }

    // Stampa di tutti i nodi
    std::cout << "Elenco Nodi: { ";
    for (int n : M.all_nodes()) {
        std::cout << n << " ";
    }
    std::cout << "}" << std::endl;

    // Stampa di tutti gli archi con la loro numerazione
    std::cout << "Elenco Archi (Totali: " << M.all_edges().size() << "):" << std::endl;
    auto archi_M = M.all_edges();
    for (std::size_t i = 0; i < archi_M.size(); ++i) {
        std::cout << "  [" << i << "] (" << archi_M[i].from() << ","  << archi_M[i].to() << ")" << std::endl;
    }
	
	// Vicini del nodo 2
    std::cout << "Vicini del nodo 2: ";
    std::set<int> v2 = M.neighbours(2);
    for (int v : v2) {
        std::cout << v << " ";
    }
 
    //  Arco in posizione 15
    unidirected_edge<int> arco15 = M.edge_at(15);
    std::cout << "Arco in posizione 15: (" << arco15.from() << "," << arco15.to() << ")" << std::endl;

    // Posizione dell'arco (5,7)
    unidirected_edge<int> cerca_57(7, 5); 
    int pos57 = M.edge_number(cerca_57);
    std::cout << "Posizione dell'arco (5,7): " << pos57 << std::endl;


    return 0;
	
	
	
}