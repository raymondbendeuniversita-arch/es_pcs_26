#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iomanip> //mi serve per setw() per gestire meglio l'impaginazione



#include "sorts.hpp"
#include "timecounter.h"
#include "randfiller.h"


/*si utilizzi il codice fornito in timecounter.h e timecounter.cpp
per misurare il tempo di esecuzione degli algoritmi implementati. Si misuri in particolare il tempo
impiegato su vettori di lunghezze {4, 8, 16, . . . , 8192} riempiti in modo casuale. Si confronti tali
tempi con i tempi della funzione di ordinamento std::sort()*/



int main(void){
	
	randfiller rf; 
	timecounter tc;
	
	
	//creo una tabella per i tempi con comando setw(), set width che imposta la alrgehzza
	std::cout<<"\n";
	std::cout << "TEMPO ALGORITMI"<<"\n";
	std::cout<<"\n";
	
    std::cout << std::left << std::setw(25) << "Dimensione vettore" ;
    std::cout << std::setw(20) << "Bubblesort"; 
    std::cout << std::setw(20) << "Insertionsort"; 
    std::cout << std::setw(20) << "Selectionsort"; 
    std::cout << std::setw(20) << "std::sort" << "\n";
	for(int i=0; i<=100; i++){
		std::cout<<"-";

	}
	std::cout<<"\n";
	
	//creazione vettori di lunghezze {4,8,16,....,8192}
	for (int i=4; i <= 8192; i*=2){
		
		//creo vettore con valori casuali da -10000 a 10000
		std::vector<int> v(i);
		v.resize(i);  // dimensione i-esima
        rf.fill(v, -10000, 10000); 
		
		 
        std::cout<< std::setw(25) << i; //qua indico la lunghezza del vettore

        //TEMPO bubblesort
        std::vector<int> v_bubble = v; // copio vettore originale per algortimo bubble 
        tc.tic();
        bubblesort(v_bubble);
        std::cout<< std::setw(20) << tc.toc();
		

        //TEMPO insertionsort
        std::vector<int> v_insertion = v; // copio vettore originale per algortimo insertion
        tc.tic();
        insertionsort(v_insertion);
        std::cout<< std::setw(20) << tc.toc();

        //TEMPO selectionsort
        std::vector<int> v_selection = v; // copio vettore originale per algortimo selection
        tc.tic();
        selectionsort(v_selection);
        std::cout << std::setw(20) << tc.toc();

        //TEMPO std::sort
        std::vector<int> v_s = v; // copio vettore originale per comando std::sort
        tc.tic();
        std::sort(v_s.begin(), v_s.end()); 
        std::cout << std::setw(20) << tc.toc() << "\n";	
}

	

    return 0;
	
	
	
}