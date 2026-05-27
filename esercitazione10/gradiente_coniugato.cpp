#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>

double condA(const Eigen::MatrixXd& A)
{
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
  Eigen::VectorXd singularValuesA = svd.singularValues();
  return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}



int main() 
{
  const int n=10;  //dimensione
  const double tol = 1.0e-15; //tolleranza

  Eigen::MatrixXd B = Eigen::MatrixXd::Random(n,n);// creazione matrice B dimensione nxn di valori casuali

  if (abs(B.determinant()) < tol)
    return -1;
  Eigen::MatrixXd A = B.transpose() * B;  //matrice simmetrica definita positiva 
  Eigen::VectorXd x_true = Eigen::VectorXd::Ones(n); //vettore soluzione esatta

  Eigen::VectorXd b = A * x_true; //vettore termine noto



  //vettori iniziali
  Eigen::VectorXd x = Eigen::VectorXd::Zero(n);  //vettore iniziale di zeri
  Eigen::VectorXd res = b - A * x; //vettore residuo
  double res_norm_0 = res.norm(); //norma residuo
  Eigen::VectorXd p = res; //vettore discesa

  const unsigned int it_max = 10000;  //iterazioni massime
  unsigned int it = 0;
  const double res_tol = 1.0e-12;

  std::cout.precision(2);
  std::cout<< std::scientific<< "Matrix Cond: "<< condA(A)<< std::endl;  //condizionamneto matrice

  //Metodo gradiente coniugato
  while (it < it_max && res.norm() > res_tol * res_norm_0){
    const double alpha_k = ((p.transpose() * res) / (p.transpose() * A * p)).value(); //costante alphak


    x = x + alpha_k * p;
    res = b - A *x;


    const double beta_k = ((p.transpose()*A * res) / (p.transpose() * A * p)).value(); //costante betak

    p = res - beta_k*p;

    


    it++;
  }

  const auto err_rel = (x_true.norm() == 0.0) ? (x - x_true).norm() :
                                              (x - x_true).norm() / x_true.norm();

  std::cout.precision(4);
  std::cout<< std::scientific<< "it"<< "/"<< "it_max"<< std::endl;
  std::cout<< std::scientific<< it<< "/"<< it_max<< std::endl;
  std::cout<< std::scientific<< "res"<< "/"<< "res_tol"<< std::endl;
  std::cout<< std::scientific<< res.norm() / res_norm_0<< "/"<< res_tol<< std::endl;
  std::cout<< std::scientific<< "err_rel"<< std::endl;
  std::cout<< std::scientific<< err_rel<< std::endl;
  /*
  std::cout<< std::scientific<< "soluzione"<< std::endl;
  std::cout<< std::scientific<< x << std::endl;  
  */                                          




  return 0;
}
