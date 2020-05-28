#include <algorithm>
#include <iostream>
#include "eigen.h"


std::pair<double, Vector> power_iteration(const Matrix& X, unsigned num_iter, double epsilon) {
    int n = X.cols();
    Vector eigenvector = Vector::Random(n);

    for (unsigned int i = 0; i < num_iter; i++) {
        eigenvector = X * eigenvector;
        eigenvector = eigenvector / eigenvector.norm();
    }

    double eigenvalue = eigenvector.transpose().dot(X * eigenvector) / eigenvector.norm();

    return std::make_pair(eigenvalue, eigenvector);
}

std::pair<Vector, Matrix> get_first_eigenvalues(const Matrix& X, unsigned num, unsigned num_iter, double epsilon) {
    Matrix A = X;
    Vector eigenvalues(num);
    Matrix eigenvectors(A.rows(), num);
    double eigenvalue;
    Vector eigenvector;

    for (unsigned int i = 0; i < num; i++) {
        std::pair<double, Vector> eigens = power_iteration(A, num_iter);
        eigenvalue = std::get<0>(eigens);
        eigenvector = std::get<1>(eigens);

        std::cout << "Calculating eigenvalues and eigenvectors... " << i + 1 << "/" << num << ": " << eigenvalue << std::endl;

        eigenvalues(i) = eigenvalue;
        eigenvectors.col(i) = eigenvector;
        A = A - eigenvalue * eigenvector * eigenvector.transpose();
    }

    return std::make_pair(eigenvalues, eigenvectors);
}
