#pragma once




template<typename T>

/*
Si implementino quindi
due classi “contenitore”1 aventi entrambe i seguenti metodi:
• costruttore di default,
• metodo put() per inserire un elemento nel contenitore,
• metodo get() per rimuovere un elemento dal contenitore,
• metodo empty() per determinare se il contenitore `e vuoto


FIFO (First In First Out,coda) 
*/


class fifo{  //classe fifo per viista in ampieza
private:
	std::queue<T> q;  //contenitore coda
public:
	//nmetodo epr inseirire l'elelemnto
	void put(const T& elemento){
		q.push(elemento);  
	}
	//metodo per rimuovere e restituire l'elemento in testa 
	T get(){
		T a= q.front();
		q.pop();
		return a;
	}
	//verifico contenitore vuoto
	bool empty() const{
		return q.empty();
	}

};
