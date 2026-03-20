#include <iostream>
#include <cmath>

using namespace std;

//CONSEGNA: sia definito un array di double di lunghezza N e lo si riempia con valori a piacere.
//Se ne calcoli minimo, massimo, media e deviazione standard e so stampino i risultati

int main(){
	
	static const int N=10;
	double arr[N]={6.0,2.0,3.0,4.0,5.0,15.0,30.0,8.0,9.0,10.0};
	
	double min=arr[0];
	double max=arr[0];
	
	double media;
	double somma=0.0;
	
	
	
	for(int i=0; i<N; i++){ // ciclo for per scorrere su tutti gli elementid el vettore
		
		if(arr[i]<min){ //guardo il minimo all'interno del vettore
		
			min=arr[i];
		
		}
		
		if(arr[i]>max){ // guardo il massimo all'interno del vettore
			
			max=arr[i];
		}
		
		somma=somma+arr[i];
	}
	
	
	media=somma/N; // calcolo della media 
	
	//QUA CALCOLO DEVIAZIONE STANDARD
	double somme_scarti=0.0;
	double devstd=0.0;
		
	for(int i=0; i<N; i++){
		somme_scarti=somme_scarti+((arr[i]-media)*(arr[i]-media));
	}
	
	devstd=sqrt(somme_scarti/N);
	
	
	cout<<"il minimo è: "<<min<<endl;
	cout<<"il massimo è: "<<max<<endl;
	cout<<"La media è: "<<media<<endl;
	cout<<"La deviaizone standard è: "<<devstd<<endl;
	
 
	
	return 0;
	
}

