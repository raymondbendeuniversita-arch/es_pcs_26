#pragma once



#include <vector>
#include <algorithm> 

#include "sorts.hpp"

const int SOGLIA=24;



template<typename T>
void insertion_sottovettore(std::vector<T>& A, int primo, int ultimo){ //ora devo lavorare con un sottovettore delimitato quinid da primo e ultimo
	
	for(int i=primo+1;i<=ultimo;i++){
		T value=A[i];
		int j=i-1;
		while(j>=primo && A[j]>value){
			T temp=A[j+1];
			A[j+1]=A[j];
			A[j]=temp;
			
			j=j-1;
		}
		A[j+1]=value;
		
	}
}





//Algortimo quicksort ibrido che usa l'isnertion
template<typename T>
void quick_ibrido(std::vector<T>& A, int sinistra, int destra){
	if(sinistra<destra){
		if ((destra - sinistra) <= SOGLIA) {
            insertion_sottovettore(A, sinistra, destra);
        }
		else {
		int pivot=partition(A, sinistra, destra);
		quick_ibrido(A,sinistra,pivot-1);
		quick_ibrido(A,pivot+1,destra);	
		}	
	}
}
















