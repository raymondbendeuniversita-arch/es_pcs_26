#pragma once

#include <iostream>
#include <algorithm>   // per max e min
#include <vector>
#include <set>
#include <map>


// implemento una classe unidirected_edge che rappresenta un arco di un grafo:
class unidirected_edge {
	int nodo_a, nodo_b;

public: 
    //  costruttore che permette di specificare i due nodi connessi dall’arco:
    unidirected_edge(int u, int v){
	   // il vertice di partenza deve essere sempre minore di quello di arrivo:
	   nodo_a = std::min(u, v);
	   nodo_b = std::max(u, v);
	}
	
	// scrivo due metodi, from() e to(), che restituiscono i due nodi: 
	int from() const { return nodo_a; }
	int to() const { return nodo_b; }
	
	// implemento un operator< per unidirected_edge, affinchè gli archi possano essere ordinabili. 
	// Restituisce True o False se l'operazione < è rispettata o meno:
    bool operator<(const unidirected_edge& other) const {
		if (nodo_a != other.nodo_a) {   // confronto i primi due nodi degli archi
			return nodo_a < other.nodo_a;
		}
		return nodo_b < other.nodo_b;   // se i primi due nodi sono uguali, vado a vedere i secondi 
	}	
	
	// implemento operator== per unidirected_edge (restiruisce sempre un booleano):
	bool operator==(const unidirected_edge& other) const {
		return nodo_a == other.nodo_a && nodo_b == other.nodo_b;  // tutti i nodi devono essere uguali
	}
	
	// implemento operator<< per la stampa di un oggetto della classe unidirected_edge. 
	// Utilizzo una funzione friend così può leggere nodo_a e nodo_b che sarebbero privati e non pubblici:
	friend std::ostream& operator<<(std::ostream& os, const unidirected_edge& edge) {   
		os << "(" << edge.nodo_a << ")--(" << edge.nodo_b << ")";
		return os;
	}
};




// implemento una classe unidirected_graph e utilizzo i metodi set, map e vector forniti dalla libreria standard:
class unidirected_graph {
	std::map<int, std::set<int>> vicini;  // mappa dei nodi vicini
	std::vector<unidirected_edge> edges;  // lista di tutti gli archi per mantenere il corretto ordine
	
public: 
    unidirected_graph() = default;  // costruttore di default
	unidirected_graph(const unidirected_graph& other) = default;   // costruttore di copia
	
	// implemento un metodo neighbours() che, dato un nodo, restituisce i suoi vicini. 
	// Quindi deve prendere in ingresso il nodo di cui voglio cercare i vicini e deve restituire un set con tutti i vicini: 
	std::set<int> neighbours(int nodo) const {
		if (vicini.count(nodo)) {   // il metodo count() restituisce 1 se il nodo è presente nella nostra mappa, 0 altrimenti
			return vicini.at(nodo);   // se il nodo esiste, restituiamo la lista dei suoi vicini salvata nella mappa
		}
		return {};  // se il nodo non è salvato nella mappa o non ha vicini, restituisco un set vuoto
	}
	
	
	// implemento un metodo add_edges() che permetta di aggiungere un arco al grafo:
	void add_edges(int u, int v) {
        unidirected_edge new_edge(u, v);   // definisco un nuovo arco
        
        // uso std::find per i vector
        if (std::find(edges.begin(), edges.end(), new_edge) == edges.end()) {   // lo aggiungo solo se non è già presente 
		                                                                        // (se find restituisce escattamente la fine del vettore, vuol dire che non è presente)
            edges.push_back(new_edge);   // aggiorno la lista degli archi che mi servirà poi per all_edges()
            vicini[u].insert(v);
            vicini[v].insert(u);
        }
    }
	
	
	// implemento il metodo all_edges() che restituisce il vettore con tutti gli archi: 
	std::vector<unidirected_edge> all_edges() const {
		return edges;
	}
	
	
	// analogamente, implemento un metodo all_nodes() che restituisce un set contenete tutti i nodi del grafo:
	std::set<int> all_nodes() const {
		std::set<int> nodes;  // inizializzo un set di nodi
		
		for (const auto& element : vicini) {  // ogni elemento element della mappa è compostgo da una chiave (nodo) e un valore (l'insieme dei suioi vicini)
			nodes.insert(element.first);   // prendo la chiave dell'elemento (il nodo) e lo inserisco nel set
		}
		
		return nodes;
	}
	
	
	// implemento un metodo edge_number() che, dato un arco, restituisce la sua numerazione all'interno del grafo
	// (cioè deve restituire l'indice di un arco): 
	int edge_number(const unidirected_edge& edge) const {
		for (size_t i = 0; i < edges.size(); i++) {
            if (edges[i] == edge) {
				return i;
			}
        }
		
        return -1;  // se l'arco non è presente nell lista degli archi e non posso restituire l'indice, restituisco un valore che mi indica "arco non trobvato"
	}
	
	
	// implemento un metodo edge_at() che, dato un numero d'arco, restituisce il corrispondente oggetto arco all'interno del grafo
	// (cioè devo restituire l'arco corrispondente ad un certo indice):
	unidirected_edge edge_at(size_t indice) const {
        if (indice >= 0 && indice < edges.size()) {
            return edges[indice];
        }
		
		std::cerr << "Errore: indice non valido." << "\n";
		return unidirected_edge(-1, -1);  // se c'è un errore sull'indice, restituisco un arco finto
    }
	
	
	// infine, implemento un operatore operator-(), che permette di calcolare la differenza tra due grafi: dati G e G′,
    // la differenza G−G′ è data dagli archi presenti in G e non presenti in G′.
	unidirected_graph operator-(const unidirected_graph& other) const {
        unidirected_graph risultato;  // inizializzo un grafo nuovo che conterrà il risultato, cioè la differenza
		auto other_edges = other.all_edges();  // faccio una lista di tutti gli archi dedl secondo grafo (other) chiamando il metodo di prima
		
        for (const auto& edge : edges) {  // itero sugli archi del grafo attuale
		
			// cerco se l'arco di questo grafo esiste nell'altro (stesso ragionamento che ho usato per add_edges()):
            if (std::find(other_edges.begin(), other_edges.end(), edge) == other_edges.end()) {
                risultato.add_edges(edge.from(), edge.to());
            }
        }
        return risultato;
    }

};