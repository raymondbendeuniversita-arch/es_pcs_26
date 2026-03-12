#include <fstream>
#include <iostream>
using namespace std;

//CONSEGNA: il programma deve stampare il nome della citt`a e la media delle quattro
//temperature misurate nella citt`a stessa

int main(int argc, const char *argv[]){
	
	if(argc<2){
		cout<<"Non è stato passato il file" << endl; //da terminale non ho passato alcun file, argc conta anche il nome del programma 
		return 1;
	}
	
	
	string filename= argv[1];
	ifstream ifs(filename);
	if (ifs.is_open()){ //verifico la corretta apertura del file 
		cout<<"File aperto correttamente"<<endl;
		string citta;
			double t1;
			double t2;
			double t3;
			double t4;
			double media=0.0;
		while(ifs>>citta>>t1>>t2>>t3>>t4){
			
			
			media=(t1+t2+t3+t4)/4.0;
			cout<< citta << " " << media <<"\n";
			
			
		}
		
		

	}
	else{ // questo è il caso in cui non è stato posisbile aprire il file 
		cout<<"File non aperto correttamente"<<endl; 	
	}
	
	
	
	
	return 0;
}
