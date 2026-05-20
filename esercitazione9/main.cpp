#include <iostream>
#include <concepts>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>
#include <set>
#include <map>
#include <vector>

#include "fifo.hpp"
#include "lifo.hpp"
#include "algoritmi_visite.hpp"



int main(){
	unidirected_graph<int> G;
    // Grafo G
    G.add_edges(1, 2);
    G.add_edges(1, 3);
    G.add_edges(1, 4);
    G.add_edges(1, 6);
    G.add_edges(2, 4);
    G.add_edges(2, 5);
    G.add_edges(2, 7);
    G.add_edges(3, 6);
    G.add_edges(4, 6);
    G.add_edges(4, 7);
    G.add_edges(5, 7);
    G.add_edges(6, 7);
    G.add_edges(6, 8);
    G.add_edges(7, 9);
    G.add_edges(8, 9);
	
    std::cout << "Grafo G" << std::endl;
    for (const auto& edge : G.all_edges()) {
        std::cout << edge << " ";
    }
    std::cout << "\n"<< std::endl;
	
    //TEST BFS 
    fifo<int> q;
    unidirected_graph<int> bfs_albero = graph_visit(G, 1, q);

    std::cout << "Albero di visita BFS" << std::endl;
    for (const auto& edge : bfs_albero.all_edges()) {
        std::cout << edge << " ";
    }
    std::cout << "\n"<< std::endl;

    //TEST DFS
    lifo<int> s;
    unidirected_graph<int> dfs_albero = graph_visit(G, 1, s);

    std::cout << "Albero di visita DFS" << std::endl;
    for (const auto& edge : dfs_albero.all_edges()) {
        std::cout << edge << " ";
    }
    std::cout << "\n"<< std::endl;
	
	//TEST DFS RICORSIVA
	unidirected_graph<int> dfs_albero_ricorsivo = recursive_dfs(G, 1);

    std::cout << "Albero di visita DFS RICORSIVO" << std::endl;
    for (const auto& edge : dfs_albero_ricorsivo.all_edges()) {
        std::cout << edge << " ";
    }
    std::cout << "\n";
	

	return 0;
}



