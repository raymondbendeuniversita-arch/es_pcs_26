#pragma once

#include <vector>
#include <algorithm> 

//IMPLEMENTAZIONE 3 ALGORTIMI DI ORDINAMENTO (bubblesort, insertion sort e selection sort)

//tempi e grafici su matlab

template<typename T>
bool is_sorted(const std::vector<T>& A){

	int N=A.size();
	if(N<=1){   //qua gestisco caso lunghezza 0 o 1 del vettore che sono per definzione gia ordinati 
		return true;
	}
	
	for(int i=0; i<N-1; i++){
		if(A[i]>A[i+1]){
			return false;
		}
	}
	return true;
	
	
	
}




template<typename T>
void bubblesort(std::vector<T>& A){
	int N=A.size();
	
	for(int i=0; i<N-1; i++){ 
		for(int j=N-1; j>=i+1; j--){ 
			
			if(A[j]<A[j-1]){ //condiizone per controlalre quale dei due è il più grande 
				T temp=A[j]; //varibile che mi serve a memorizzare il vecchio valore per non perderlo
				A[j]=A[j-1];
				A[j-1]=temp; //faccio gli scambi
			}
				
		}
	}
	
}


template<typename T>
void insertionsort(std::vector<T>& A){
	int N=A.size();
	
	for(int i=1;i<N;i++){
		T value=A[i];
		int j=i-1;
		while(j>=0 && A[j]>value){
			T temp=A[j+1];
			A[j+1]=A[j];
			A[j]=temp;
			
			j=j-1;
		}
		A[j+1]=value;
		
	}
}


template<typename T>
void selectionsort(std::vector<T>& A){
	int N=A.size();
	for(int i=0; i <N-1; i++){
		int indice_minimo=i;
		for(int j=i+1; j<N; j++){
			if(A[j]<A[indice_minimo]){
				indice_minimo=j;
			
			}
			
		}
		
		if(indice_minimo!=i){
			T temp=A[i];
			A[i]=A[indice_minimo];
			A[indice_minimo]=temp;
		}
	}
	
}







