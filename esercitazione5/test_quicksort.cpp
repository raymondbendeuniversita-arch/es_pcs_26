#include <iostream>
#include <vector>


#include "sorts.hpp"
#include "randfiller.h"

/*Si ricordano le richieste dell’esercitazione precedente rispetto ai test:
• Testare gli algoritmi di ordinamento su 100 vettori di dimensioni scelte a caso
• Per ognuna delle dimensioni si testi gli algoritmi su vettori riempiti in modo casuale e che
includano numeri sia negativi sia positivi.
• Si crei un vettore di std::string e lo si riempia con una decina di stringhe scelte a piacere,
si verifichi quindi che gli algoritmi ordinano correttamente anche le stringhe.*/



//  QUICKSORT
int main(){
	
	randfiller rf; 
	
	
	
	//creazione 100 vettori di dimensioni scelte a caso
	for(int i=0; i<100;i++){
		//Dimensioni casuali, uso un vettore di lunghezza 1 che lo riempio con un numero da 0 a 1000
		//e poi prendo posizone [0] del vettore
		std::vector<int> vettore_dimensione;
		vettore_dimensione.resize(1);
		rf.fill(vettore_dimensione, 0, 1000);
		
		
		//vettore di interi
		std::vector<int> vi;
		vi.resize(vettore_dimensione[0]);  // dimensioni casuali
		rf.fill(vi, -10000, 10000); 
		quicksort(vi, 0, (int)vi.size() - 1);
		if(is_sorted(vi)==false){
			return EXIT_FAILURE;
		}
		
		
		//vettore di float
		std::vector<float> vf;
		vf.resize(vettore_dimensione[0]);
		rf.fill(vf, -10000.0f, 10000.0f);
		quicksort(vf,0, (int)vf.size() - 1);
		if(is_sorted(vf)==false){
			return EXIT_FAILURE;
		}
		
		
		
		//vettore di double
		std::vector<double> vd;
		vd.resize(vettore_dimensione[0]);
		rf.fill(vd, -10000.0, 10000.0);
		quicksort(vd,0, (int)vd.size() - 1);
		if(is_sorted(vd)==false){
			return EXIT_FAILURE;
		}
	
		}

	//vettore di stringhe
	std::vector <std::string> vs={"mela","abate","abaco","zanzara","sole","pera","banana","cane", "gatto","123 ","1 23"};
	quicksort(vs,0, (int)vs.size() - 1);
	if(is_sorted(vs)==false){
		return EXIT_FAILURE;
	}	
	
	
	return EXIT_SUCCESS;
	
	
}