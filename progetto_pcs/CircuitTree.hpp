#pragma once
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "graph.hpp"
#include "methods.hpp"

//trova il cammino unico nell'albero per unire i due estremi di un arco e chiudere la maglia.
class CircuitTree {
public:
    // ricerca del cammino nell'albero BFS tra node_start e node_end:
    bool path_in_tree(const unidirected_graph& tree, int start, int end, std::vector<int>& path) {
        std::map<int, int> parent;   // serve a memorizzare il genitore di ciascun nodo
        std::set<int> visited;
        fifo<int> q;   // politica FIFO implementata in methods.hpp per trovare il cammino minimo sull'albero
        
        q.put(start);  
        visited.insert(start);
        parent[start] = -1;   // il nodo di partenza chiaramente non ha un genitore. Dato che i nodi sono interi positivi, questo serve a dire che start è esattamente il primo di tutti
        
		
		// visita BFS: cerchiamo la strada che collega il nodo iniziale start al nodo finale end per chiudere la maglika del circuito
        bool found = false;
        while (!q.empty()) {
            int u = q.get();   // estraiamo il noldo in cima alla coda
            if (u == end) {
                found = true;   // il nodo estratto è esattamente ikl nodo finale della maglia chde cercavamo e posso benissimo uscire dal ciclo
                break;
            }
            for (int v : tree.neighbours(u)) {   // non abbiamo ancora trovato il nostro nodo end, quindi cerchiamo tra i vicini di u
                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    parent[v] = u;
                    q.put(v);
                }
            }
        }
        
        if (!found) return false;   // questa riga viene eseguita solo se il ciclo while finisce perchè la coda si è svutata e non è stato trovato n essun nodo di fine 
		                            // in realtà è stato aggiunto solo in maniera preventiva perchè in un circuito chiuso ben formato non dovremmo avere problemi di questo tipo
		
        
        // cammino a ritroso per ricostruire la sequenza ordinata dei nodi dall'inizio alla fine:
        int current = end; 
        while (current != -1) {
            path.push_back(current);  // prendiamo il nodo corrente e lo inseriamo in coda al vettore path 
            current = parent[current];   // aggiorno il nodo corrente: praticamente nella successiva iterazione verrà aggiunto al vettore del percorso esattamente il padre
        }
        std::reverse(path.begin(), path.end());   // ora che ho il percorso da end a start lo giro al contrario con la funzione reverse della librerfia algorithm
        return true;
    }
};