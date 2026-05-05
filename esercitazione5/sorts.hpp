#pragma once

#include <vector>
#include <algorithm> 



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

//Algoritmo merge 
template<typename T>
void merge(std::vector<T>& A, int sinistra, int centro, int destra) {
    
    int n1 = centro - sinistra + 1;
    int n2 = destra - centro;

    //creo i vettori vettori L ed R
    std::vector<T>L(n1);
    std::vector<T>R(n2);

    for (int i = 0; i<n1; i++) {
        L[i] = A[sinistra+i];
    }
    for (int j = 0; j<n2; j++) {
        R[j] = A[centro+j+ 1];
    }


    int i = 0; 
    int j = 0; 
	

    for (int k = sinistra; k<=destra; k++) {
        if (i < n1 && (j >= n2 ||L[i]<=R[j])) {
            A[k] = L[i];
            i++;
        } 
		else{
            A[k] = R[j];
            j++;
        }
    }
}

//Algortimo mergesort
template<typename T>
void mergesort(std::vector<T>& A, int sinistra, int destra){
	if(sinistra<destra){
		int centro=(sinistra+destra)/2;
		mergesort(A,sinistra,centro);
		mergesort(A,centro+1,destra);
		merge(A,sinistra,centro,destra);
	}
}



//Algortimo partition
template<typename T>
int partition(std::vector<T>& A, int sinistra, int destra){
	T x=A[destra];
	int i=sinistra-1;
	for(int j=sinistra; j<=destra-1;j++){
		if(A[j]<=x){
			i++;
			std::swap(A[i], A[j]);
		}	
	}
	std::swap(A[i + 1], A[destra]);
	return i+1;

}



//Algortimo quicksort
template<typename T>
void quicksort(std::vector<T>& A, int sinistra, int destra){
	if(sinistra<destra){
		int pivot=partition(A, sinistra, destra);
		quicksort(A,sinistra,pivot-1);
		quicksort(A,pivot+1,destra);	
	}
	
	
	
}
















