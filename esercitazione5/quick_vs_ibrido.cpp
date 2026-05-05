#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iomanip> //mi serve per setw() per gestire meglio l'impaginazione



#include "sorts.hpp"
#include "quicksort_ibrido.hpp"
#include "timecounter.h"
#include "randfiller.h"

const int n_vettori=100000;


int main(void){
	
	randfiller rf; 
	timecounter tc;


	//Qua faccio il confrotno tra i 2 
	std::cout<<"\n";
	std::cout <<"QUICKSORT vs QUICK IBRIDO -- Media su 100000 campioni"<<"\n";
	std::cout<<"\n";
	
    std::cout << std::left << std::setw(15) << "Dim" ;
    std::cout << std::setw(20) << "Quicksort"; 
    std::cout << std::setw(20) << "Quicksort ibrido"<< "\n";
	for(int i=0; i<=60; i++){
		std::cout<<"-";

	}
	std::cout<<"\n";
	
	
	for (int i=2; i <=100; i+=2){
		
		
        std::cout<< std::left<<std::setw(15) << i; //qua indico la lunghezza del vettore
		
		
		//prealloco i 100000 vettori casuali
		std::vector<std::vector<int>> preallocamento(n_vettori, std::vector<int>(i));
		
		
        for (int j = 0; j <n_vettori; j++) {
            rf.fill(preallocamento[j], -10000, 10000);
        }
		// QUICKSORT
        std::vector<std::vector<int>> pr_quick2 = preallocamento; //faccio la copia dei vettori
        tc.tic();
        for (int j = 0; j < n_vettori; j++) {
            quicksort(pr_quick2[j], 0, i - 1);
        }
        double tempo_quick2 = tc.toc() / n_vettori;

        //QUICK IBRIDO
        std::vector<std::vector<int>> pr_ibrido = preallocamento; //faccio la copia dei vettori
        tc.tic();
        for (int j = 0; j < n_vettori; j++) {
            quick_ibrido(pr_ibrido[j], 0, i - 1);
        }
        double tempo_ibrido = tc.toc() / n_vettori;
		
		
		std::cout << std::setw(20) << tempo_quick2;
        std::cout << std::setw(20) << tempo_ibrido << "\n";
			
		
	}
	
	
	    return 0;
	
	
	
}