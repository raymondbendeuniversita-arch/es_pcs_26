#pragma once


template<typename I> requires std::integral<I>


/*
Si implementi una classe unidirected edge che rappresenta un arco in un grafo. La classe deve
avere un costruttore che permette di specificare i due nodi connessi dall’arco, inoltre devono esserci
due metodi from() e to() che restituiscono i due nodi. 
Si implementi anche :
• operator< per unidirected edge, affinch´e gli archi possano essere ordinabili
• operator== per unidirected edge
• operator<< per unidirected edge

Si faccia in modo che unidirected edge garantisca sempre che from è minore di to
*/


class unidirected_edge {
private:
	I node_from;  //questo deve essere il più piccolo
	I node_to;    // questo nodo deve essere il più grande
	
	
	//qua metto il più piccolo nel from e l'altro più garnde nel to
	void sorting_nodi(I a, I b){
		node_from=std::min(a,b);
		node_to=std::max(a,b);
	}

public:
	//costruttore che permette di specificare i due nodi connessi dall’arco
	unidirected_edge(I a, I b){
		sorting_nodi(a,b);
	}
	
	//metodi from e to
	I from() const{
		return node_from;
	}
	I to() const{
		return node_to;
	}
	
	//OPERATORI <,==
	 bool operator<(const unidirected_edge& other) const {
			 if (node_from < other.node_from){
				return true;
			}
			if (node_from > other.node_from){
				return false;
			}
			
			// node_from=other.node_from, quindi gaurdo nodi to
			if (node_to < other.node_to) {
				return true;
			}
    
			return false;
		
	 }
	 
	 bool operator==(const unidirected_edge& other) const{
		if ((node_from != other.node_from) || (node_to != other.node_to) ) {
			return false;
		}
		return true;
		
		}
};	 
// OPERATORE PER LA STAMPA <<
template<typename I>
std::ostream& 
operator<< (std::ostream& os, const unidirected_edge<I>& edge) {
	os <<"("<<edge.from()<<", "<<edge.to()<<")";
	
	
    return os; 
}





