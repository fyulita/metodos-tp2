#include <iostream>
#include "pca.h"
#include "eigen.h"
#include "knn.h"

// train.csv: 42000 images of 784 pixels (28x28). First column is the label.
// test.csv: 28000 images of 784 pixels (28x28).
// smalltest.csv: 1 image of 784 pixels (28x28).


int main(int argc, char** argv){
    /*
    Matrix A(3, 3);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 3;
    A(1, 0) = 4;
    A(1, 1) = 5;
    A(1, 2) = 6;
    A(2, 0) = 7;
    A(2, 1) = 8;
    A(2, 2) = 9;
    std::cout << "A:\n" << A << std::endl;

    Matrix B(2, 2);
    B = A.block(1, 1, 2, 2);
    std::cout << "B:\n" << B << std::endl;

    Vector v(3);
    v = A.row(0);
    std::cout << "v:\n" << v << std::endl;

    Vector w(2);
    w = A.block(0, 0, 2, 3).col(0);
    std::cout << "w:\n" << w << std::endl;

    Matrix C(3, 3);
    C(0, 0) = 0;
    C(0, 1) = 1;
    C(1, 0) = 1;
    C(1, 1) = -1;
    std::cout << "C:\n" << C << std::endl;

    Vector u = Vector::Ones(3);
    Vector aux;
    for (int i = 0; i < A.rows(); i++) {
        aux = A.row(i);
        A.row(i) = aux - i * u;
    }
    std::cout << "A:\n" << A << std::endl;
    */

    std::string file = "../data/test.csv";

    Matrix X = create_matrix(false, file, 28000, 784);

    std::cout << "Calculated Matrix." << std::endl;
    //std::cout << "X:\n" << X << std::endl;

    Matrix C = covariance(X);

    std::cout << "Calculated Covariance." << std::endl;
    //std::cout << "C:\n" << C << std::endl;

    std::pair<Vector, Matrix> eigens = get_first_eigenvalues(C, 300);
    Vector eigenvalues = std::get<0>(eigens);
    Matrix eigenvectors = std::get<1>(eigens);

    //std::cout << "Lambda:\n" << eigenvalues << std::endl;
    //std::cout << "V:\n" << eigenvectors << std::endl;

    Matrix X_hat = X * eigenvectors;
    Matrix C_hat = X_hat.transpose() * X_hat;

    //std::cout << "C_hat:\n" << C_hat << std::endl;

    Vector ans = tc(X_hat.row(0), eigenvectors);

    std::cout << "tc:\n" << ans << std::endl;

    return 0;

}
