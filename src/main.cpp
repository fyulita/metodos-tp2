#include <iostream>
#include "pca.h"
#include "eigen.h"

// train.csv: 42000 images of 784 pixels (28x28). First column is the label.
// test.csv: 28000 images of 784 pixels (28x28).
// smalltest.csv: 1 image of 784 pixels (28x28).


int main(int argc, char** argv){
    std::string file = "../data/smalltest.csv";

    Matrix X = create_matrix(false, file, 1, 784);

    //std::cout << "X:\n" << X << std::endl;

    Matrix C = covariance(X);

    //std::cout << "C:\n" << C << std::endl;

    std::pair<Vector, Matrix> eigens = get_first_eigenvalues(C, C.rows(), 100);
    Vector eigenvalues = std::get<0>(eigens);
    Matrix eigenvectors = std::get<1>(eigens);

    //std::cout << "Lambda:\n" << eigenvalues << std::endl;
    //std::cout << "V:\n" << eigenvectors << std::endl;

    Matrix X_hat = X * eigenvectors;
    Matrix C_hat = X_hat.transpose() * X_hat;

    std::cout << "C_hat:\n" << C_hat << std::endl;

    Vector ans = tc(X_hat.row(0), eigenvectors);

    std::cout << "tc:\n" << ans << std::endl;

    return 0;
}
