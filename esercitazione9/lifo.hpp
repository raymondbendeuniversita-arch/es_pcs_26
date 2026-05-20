#pragma once




template<typename T>


/*
Si implementino quindi
due classi “contenitore”1 aventi entrambe i seguenti metodi:
• costruttore di default,
• metodo put() per inserire un elemento nel contenitore,
• metodo get() per rimuovere un elemento dal contenitore,
• metodo empty() per determinare se il contenitore `e vuoto


LIFO (Last In First Out, stack)
*/



class lifo{  //classe lifo per visita in profondità
private:
	std::stack<T> l;  //contenitore stack

public:
	//nmetodo epr inseirire l'elelemnto
	void put(const T& elemento){
		l.push(elemento);
	}
	//metodo per rimuovere e restituire l'elemento in cima
	T get(){
		T a= l.top();
		l.pop();
		return a;
	}
	//verifico contenitore vuoto
	bool empty() const{
		return l.empty();
	}

};
