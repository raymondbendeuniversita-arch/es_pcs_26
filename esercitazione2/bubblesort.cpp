#include <iostream>
using namespace std;

/*
//CONSEGNA: costruzione algoritmo di ordinamento Bubblesort

1.
Si scorra tutto l’array da ordinare, confrontando gli elementi adiacenti. Se l’elemento in
posizione i-esima `e pi`u grande dell’elemento in posizione (i + 1)-esima, si scambino i due
elementi

2. Se nel passo precedente sono stati effettuati uno o pi`u scambi, ritornare al punto 1. Se invece
non `e stato effettuato nessuno scambio l’algoritmo termina
*/


int main(){
	
	static const int N=10;
	
	double arr[N]={6.0,2.0,3.0,-4.0,5.0,15.0,30.0,8.0,9.0,10.0};
	
	//OUTPUT VETTORE INIZIALE
	
		for(int i=0; i<N; i++){
		
		cout<<arr[i]<<" ";
		
	}
	
	//ALGORITMO DI ORDINAMENTO
	for(int i=0; i<N; i++){ //primo ciclo for mi serve per scorrere N volte lungo il vettore
		for(int j=0; j<N-1; j++){ // questo secondo ciclo for mi serve per fare gli scambi opportuni
			
			if(arr[j]>arr[j+1]){ //condiizone per controlalre quale dei due è il più grande 
				double vecchio_valore=arr[j]; //varibile che mi serve a memorizzare il vecchio valore per non perderlo
				arr[j]=arr[j+1];
				arr[j+1]=vecchio_valore; //faccio gli scambi
			}
				
		}
	}
	
	cout<<"\n";
	
	//OUTPUT VETTORE ORDINATO
	for(int i=0; i<N; i++){
		
		cout<<arr[i]<<" ";
	}
	
	return 0;
}
