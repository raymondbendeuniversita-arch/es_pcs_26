#pragma once


#include "unidirected_edge.hpp"


template<typename I> requires std::integral<I>


/*
Si passi quindi all’implementazione di una classe unidirected graph. Essa deve prevedere:
• Un costruttore di default
• Un costruttore di copia
• Un metodo neighours() che, dato un nodo, restituisce i suoi vicini,

• Un metodo add edge() che permetta di aggiungere un arco al grafo,
• Un metodo all edges() che restituisce tutti gli archi,
• Un metodo all nodes() che restituisce tutti gli nodi,
• Un metodo edge number() che, dato un arco, ne restituisce la sua numerazione all’interno
del grafo,
• Un metodo edge at() che, dato un numero d’arco, restituisce il corrispondente oggetto arco
all’interno del grafo,
• L’operatore operator-(), che permette di calcolare la differenza tra due grafi: dati G e G′
,
la differenza G − G′ `e data dagli archi presenti in G e non presenti in G′
.

*/


class unidirected_graph {
private:


	std::vector<unidirected_edge<I>> edges;   //in questo modo memorizzo per ogni arco la sua numerazione
	std::map<I,std::set<I>> adiacente;	      //in questo modo memorizzo chiave=nodo associato all'arco per guardare poi i vicini di un nodo
	std::set<I> nodi;                         //mi serve per avere l'elenco di tutti i nodi senza duplicati							
	

public:

	//COSTRUTTORE DI DEFAULT
	unidirected_graph() {}
	
	
	//COSTRUTTORE DI COPIA, copio i 3 contneitori sopra tramite other
	unidirected_graph(const unidirected_graph& other) {
		edges = other.edges;
		adiacente = other.adiacente;
		nodi = other.nodi;
	}
	
	//METODO CHE AGGIUNGE UN ARCO AL GRAFO
	void add_edges(I a, I b){
		
		unidirected_edge<I> arco(a, b);
		
		//ora devo controlloare se è duplicato o meno all'interno di edges avendo come contneitore vector
		for(const auto& e:edges){
			
			if (e == arco) {
				return;
			}
		}
		//se questa condizone non si attiva inserisco l'arco
		edges.push_back(arco);
		
		//ora devo inserire i nodi
		
		adiacente[arco.from()].insert(arco.to());
		adiacente[arco.to()].insert(arco.from());
		
		nodi.insert(arco.from());
		nodi.insert(arco.to());
	
		
	}
	
	
	//METODO CHE RESTITUSICE I VICINI DI UN NODO
	std::set<I> neighbours(I n) const{
		
		if (adiacente.count(n) == 1) { //returns the number of elements matching specific key,
									//Returns 1 or 0 since this container does not allow duplicates.
			
			return adiacente.at(n); //at() Returns a reference to the mapped value of the element with specified key
		
		}
		
		// se nodo non esiste o non ci sono archi restitusco uns et vuoto
		return std::set<I>();
		
	}
	
	

	
	//METODO CHE RESTITUSICE TUTTI GLI ARCHI
	std::vector<unidirected_edge<I>> all_edges() const {
		return edges; 
	}
	
	
	
	//METODO CHE RESTITUSICE TUTTI I NODI
	std::set<I> all_nodes() const {
		return nodi; 
	}
	
	//METODO CHE DATO UN NUMERO RESTITUISCE RESTITUSICE L'ARCO
	unidirected_edge<I> edge_at(int n) const {
		return edges.at(n);
	}
	
	
	//METODO CHE DATO UN ARCO RESTITUSICE LA SUA NUMERAZIONE
	int edge_number(const unidirected_edge<I>& e) const {
		for(std::size_t i=0; i<edges.size();i++){
			if(edges[i]==e){
				return i;
			}
		}
		return -1; //se non è presente mi serve poi nella condzione dell'if del operator-
	}
	
	
	//OPERATORE - CHE PERMETTE DI CALCOLARE LA DIFERENZA TRAQ DUE GRAFI
	unidirected_graph operator-(const unidirected_graph& other) const{
		unidirected_graph differenza;
		for(const auto& e:edges){
			if(other.edge_number(e)==-1){
				differenza.add_edges(e.from(),e.to());
			}
		}
		return differenza;
	
	}
		
	
};