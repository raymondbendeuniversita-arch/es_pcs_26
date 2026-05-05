#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iomanip> //mi serve per setw() per gestire meglio l'impaginazione



#include "sorts.hpp"
#include "timecounter.h"
#include "randfiller.h"

const int n_vettori=100000;


/*Si estenda quanto fatto per la precedente esercitazione 4 con gli algoritmi Mergesort e Quicksort
Una volta implementati gli algoritmi, si aggiungano i test unitari che, chiamando la funzione is_sorted()
 precedentemente scritta, verifichino l’effettivo funzionamento dell’algoritmo.*/
 
 
 
 /*Si confrontino i tempi di Bubblesort, Selectionsort ed Insertionsort con i tempi di Quicksort
e di Mergesort su vettori piccoli (indicativamente, dimensioni inferiori a 100) e si determini se
esiste una dimensione al disotto della quale gli algoritmi quadratici sono pi`u veloci degli algoritmi
logaritmici

Si confrontino infine i tempi delle proprie implementazioni con i tempi misurati per std::sort()
 
 */



int main(void){
	
	randfiller rf; 
	timecounter tc;
	
	
	//creo una tabella per i tempi con comando setw(), set width che imposta la alrgehzza
	std::cout<<"\n";
	std::cout <<"TEMPO ALGORITMI -- Media su 100000 campioni"<<"\n";
	std::cout<<"\n";
	
    std::cout << std::left << std::setw(15) << "Dim" ;
    std::cout << std::setw(15) << "Bubble"; 
    std::cout << std::setw(15) << "Insertion"; 
    std::cout << std::setw(15) << "Selection"; 
	std::cout << std::setw(15) << "Merge";
	std::cout << std::setw(15) << "Quick";
    std::cout << std::setw(15) << "std::sort" << "\n";
	for(int i=0; i<=100; i++){
		std::cout<<"-";

	}
	std::cout<<"\n";
	
	//ciclo per dimensioni, da 2 a 100.
	for (int i=2; i <=100; i+=2){
		
		
        std::cout<< std::left<<std::setw(15) << i; //qua indico la lunghezza del vettore
		
		
		//prealloco i 100000 vettori casuali
		std::vector<std::vector<int>> preallocamento(n_vettori, std::vector<int>(i));
		
		
        for (int j = 0; j <n_vettori; j++) {
            rf.fill(preallocamento[j], -10000, 10000);
        }
		// BUBBLESORT
        std::vector<std::vector<int>> pr_bubble = preallocamento; //faccio la copia dei vettori
        tc.tic();
        for (int j = 0; j < n_vettori; j++) {
            bubblesort(pr_bubble[j]);
        }
        double tempo_bubble = tc.toc() / n_vettori;

        //INSERTIONSORT
        std::vector<std::vector<int>> pr_insertion = preallocamento; //faccio la copia dei vettori
        tc.tic();
        for (int j = 0; j < n_vettori; j++) {
            insertionsort(pr_insertion[j]);
        }
        double tempo_insertion = tc.toc() / n_vettori;

        //SELECTIONSORT
        std::vector<std::vector<int>> pr_selection = preallocamento; //faccio la copia dei vettori
        tc.tic();
        for (int j = 0; j < n_vettori; j++) {
            selectionsort(pr_selection[j]);
        }
        double tempo_selection = tc.toc() / n_vettori;

        //MERGESORT
        std::vector<std::vector<int>> pr_merge = preallocamento; //faccio la copia dei vettori
        tc.tic();
        for (int j = 0; j < n_vettori; j++) {
            mergesort(pr_merge[j], 0, i - 1);
        }
        double tempo_merge = tc.toc() / n_vettori;

        //QUICKSORT
        std::vector<std::vector<int>> pr_quick = preallocamento; //faccio la copia dei vettori
        tc.tic();
        for (int j = 0; j < n_vettori; j++) {
            quicksort(pr_quick[j], 0, i - 1);
        }
        double tempo_quick = tc.toc() / n_vettori;

        //STD::SORT
        std::vector<std::vector<int>> pr_std = preallocamento; //faccio la copia dei vettori
        tc.tic();
        for (int j = 0; j < n_vettori; j++) {
            std::sort(pr_std[j].begin(), pr_std[j].end());
        }
        double tempo_std = tc.toc() / n_vettori;

        //stampo i tempi
        std::cout << std::setw(15) << tempo_bubble;
        std::cout << std::setw(15) << tempo_insertion;
        std::cout << std::setw(15) << tempo_selection;
        std::cout << std::setw(15) << tempo_merge;
        std::cout << std::setw(15) << tempo_quick;
        std::cout << std::setw(15) << tempo_std << "\n";
	}
	


    return 0;
	
	
	
}