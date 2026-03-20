#include <iostream>

int main(){
	
	double ad[4] = {0.0, 1.1, 2.2, 3.3};
	float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
	int ai[3] = {0, 1, 2};

	int x = 1;
	float y = 1.1;

	(&y)[1] = 0; // & stampa l'indirizzo in memoria 

	std::cout << x << "\n";
	
	
	
	std::cout<<"indirizzi vettore float"<<"\n";
	std::cout << &af[0] << "\n";
	std::cout << &af[1] << "\n";
	std::cout << &af[2] << "\n";
	std::cout << &af[3] << "\n";
	
	
	std::cout<<"indirizzi vettore double"<<"\n";
	std::cout << &ad[0] << "\n";
	std::cout << &ad[1] << "\n";
	std::cout << &ad[2] << "\n";
	std::cout << &ad[3] << "\n";
	
	std::cout<<"indirizzi scalari"<<"\n";
	std::cout << &y << "\n";
	std::cout << &x << "\n";
	

	return 0;
}
