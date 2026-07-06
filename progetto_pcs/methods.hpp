#pragma once

#include <queue>  // per std::queue
#include <stack>  // per std::stack


// implemento la classe per la politica FIFO (first in first out):
template <typename T>
class fifo {
	std::queue<T> q;
public: 
    // costruttore di default:
	fifo() = default;
	  
	// metodo put() per inserire un elemento nel contenitore: 
	void put(const T& element) {
		q.push(element); 
	}
	
	// metodo get() per rimuovere un elemento dal contenitore:
    T get() {
		T element = q.front();  
		q.pop();
		return element;
	}

	// metodo empty() per determinare se il contenitore è vuoto: 
	bool empty() const {
		return q.empty();
	}
};


// implemento la classe per la politica LIFO (last in first out):
template <typename T>
class lifo {
	std::stack<T> s;
public: 
    // costruttore di default: 
	lifo() = default;
	
	// metodo put() per inserire un elemento nel contenitore: 
	void put(const T& element) {
		s.push(element);
	}
	
	// metodo get per rimuovere un elemento dal contenitore: 
	T get() {
		T element = s.top();
		s.pop();
		return element;
	}
	
	// metodo empty() per determinare se il contenitore è vuoto: 
	bool empty() const {
		return s.empty();
	}
};