#include <iostream>
#include "pca.h"
#include "eigen.h"
#include "pca.h"

int main(int argc, char** argv){
    std::string test = "../data/smalltest01.csv";

    Matrix X = create_matrix(test, 3, 4);
    Vector mean = mean_vector(X);
    Matrix C = covariance(X);

    std::cout << "X:\n" << X << std::endl;
    std::cout << "mean:\n" << mean << std::endl;
    std::cout << "C:\n" << C << std::endl;

    Matrix A(2, 2);
    A(0, 0) = 0;
    A(0, 1) = 1;
    A(1, 0) = -2;
    A(1, 1) = -3;

    std::pair<Vector, Matrix> eigens = get_first_eigenvalues(A, 2);
    Vector eigenvalues = std::get<0>(eigens);
    Matrix eigenvectors = std::get<1>(eigens);

    std::cout << "A:\n" << A << std::endl;
    std::cout << "Lambda:\n" << eigenvalues << std::endl;
    std::cout << "V:\n" << eigenvectors << std::endl;

    return 0;
}
