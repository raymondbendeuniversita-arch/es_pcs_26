#pragma once


#include "fifo.hpp"
#include "lifo.hpp"
#include "unidirected_graph.hpp"

/*
Si implementi una singola funzione template graph visit() che:
• Prende in input due parametri, il grafo da visitare ed il nodo sorgente
• Prende un parametro template che specifica il tipo del contenitore da usare per effettuare la
visita
• Restituisce un oggetto di tipo grafo contenente l’albero risultante dalla visita
La funzione, in base al contenitore passato come parametro, deve effettuare una visita in ampiezza
oppure una visita in profondit`
*/


//FUNZIONE DI VISITA GRAFO
template <typename I, typename contenitore>
unidirected_graph<I> graph_visit(const unidirected_graph<I>& G, const I& s /*sorgente quello da cui parto*/, contenitore& c) {
    
    unidirected_graph<I> albero;
    std::set<I> visitati;
    c.put(s); //inserisco nodo sorgente inziale nel contenitore che può essere lo stack o la coda
    visitati.insert(s);
    
    while (!c.empty()) {// continuo finchè ci sono nodi
        I u = c.get();
        std::set<I>nodi_vicini = G.neighbours(u); //recupero i nodi vicini
        
        for (const auto& v : nodi_vicini) {
            if (visitati.count(v) == 0) {
                visitati.insert(v);
                c.put(v);
                albero.add_edges(u, v); //aggiungo arco 
            }
        }
    }
    
    return albero;
}



/*
Si implementi una funzione recursive dfs() che
• Prende in input due parametri, il grafo da visitare ed il nodo sorgente
• Restituisce un oggetto di tipo grafo contenente l’albero risultante dalla visita
e che usa la versione ricorsiva della DFS per visitare il grafo
*/



//Esegue l'esplorazione
template <typename I>
void visita_ricorsiva(const unidirected_graph<I>& G, const I& u, std::set<I>& visitati, unidirected_graph<I>& albero) {

	visitati.insert(u);
    for (const auto& v : G.neighbours(u)) { //ciclo sui nodi vicini
        if (visitati.count(v) == 0) {
            albero.add_edges(u, v); //arco
            visita_ricorsiva(G, v, visitati, albero);
        }
    }
}
//FUNZIONE RICORSIVA
template <typename I>
unidirected_graph<I> recursive_dfs(const unidirected_graph<I>& G, const I& s) {
    unidirected_graph<I> albero_visita; //creo il grafo
    std::set<I> visitati; //creo set per nodi viistati
    
    visita_ricorsiva(G, s, visitati, albero_visita); //prima chiaamta 
    
    return albero_visita;
}

/*
Si implementi l’algoritmo di Dijkstra utilizzando la struttura dati grafo dell’esercitazione precedente.
*/

