#pragma once

#include "methods.hpp"   // politiche lifo e fifo
#include "graph.hpp"   // esercitazione precedente

//  implemento una singola funzione template graph_visit() che:
// • Prende in input due parametri, il grafo da visitare ed il nodo sorgente
// • Prende un parametro template che specifica il tipo del contenitore da usare per effettuare la visita
// • Restituisce un oggetto di tipo grafo contenente l’albero risultante dalla visita


template <typename Container>
unidirected_graph graph_visit(const unidirected_graph& G, int node, Container& C) {   // se C è fifo abbiambo una BFS, se C è lifo abbiamo una DFS
	
	unidirected_graph tree;   // inizializzo un oggetto di tipo grafo che conterrà l'albero risultante
	std::set<int> visited;   // creo un set di interi per salvare i nodi visitati
	
	// inizio ad inserire il nodo sorgente:
	C.put(node);
	visited.insert(node);
	
	while (!C.empty()) {
		int u = C.get();   // estraggo il prossimo nodo da esplorare
		
		// esploro i vicini di u (utilizzo le implementazioni dell'esercitazione precedente):
		for (int v : G.neighbours(u)) { 
            if (visited.find(v) == visited.end()) {    // se il nodo non è già presente nella lista dei nodi visitati, lo inserisco
                visited.insert(v);
				
                tree.add_edges(u, v);  // aggiungo un arco tra u e v per iniziare a costruisce l'albero di visita
                C.put(v);   // inserisco v nel contenitore per visitarlo successivamente
            }
        }
    }
	
	return tree;    // l'albero restituito sarà BFS o DFS a seconda del tipo di C
}