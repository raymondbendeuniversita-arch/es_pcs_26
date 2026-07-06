#pragma once 

#include <iostream>
#include "Eigen/Eigen"
#include <cmath>

Eigen::VectorXd gradiente_coniugato(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, const Eigen::VectorXd& x0, double tol, int max_iter) {
	Eigen::VectorXd x = x0;
	Eigen::VectorXd res = b - A * x;
	Eigen::VectorXd p = res;
	
	int k = 0;  // inizializzo le iterazioni
	
	while (res.norm()>tol && k<max_iter) {    // condizioni di arresto sulla norma del residuo e il numero massimo di iterazioni che vogliamo 
		Eigen::VectorXd Ap = A * p;   // il prodotto matrice vettore è costoso: lo calcolo solo una volta all'inizio dell'itezione
	
		double alpha = p.dot(res) / p.dot(Ap);    // p.dot(res) = p.transpose() * res
			
		x = x + alpha * p;   // aggiorno soluzione
		res = b - A * x;     // aggiorno residuo
			
		double beta = p.dot(A * res) / p.dot(Ap);
			
		p = res - beta * p;   // aggiorno p
		k++;   // iterazione
	}
	
	std::cout << "Numero iterazioni eseguite: "<< k << "\n";
	std::cout << "Residuo finale: " << res.norm() << "\n";
	
	return x;   // ritorno la soluzione
}