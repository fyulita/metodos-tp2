#include <algorithm>
#include <iostream>
#include "eigen.h"


std::pair<double, Vector> power_iteration(const Matrix& X, unsigned num_iter, double epsilon) {
    int n = X.cols();
    Vector eigenvector = Vector::Zero(n);
    Vector eigenvector_new = Vector::Random(n);

    unsigned int i = 0;
    while (i < num_iter && !(eigenvector_new - eigenvector).isZero(epsilon)) {
        eigenvector = eigenvector_new;
        eigenvector_new = X * eigenvector_new;
        eigenvector_new = eigenvector_new / eigenvector_new.norm();

        i++;
    }

    double eigenvalue = eigenvector.transpose().dot(X * eigenvector) / eigenvector.norm();

    return std::make_pair(eigenvalue, eigenvector);
}

std::pair<Vector, Matrix> get_first_eigenvalues(const Matrix& X, unsigned num, unsigned num_iter, double epsilon) {
    if (num > X.rows()) {
        num = X.rows();
    }

    Matrix A = X;
    Vector eigenvalues = Vector::Zero(num);
    Matrix eigenvectors(A.rows(), num);
    double eigenvalue = 100;
    Vector eigenvector;

    unsigned int i = 0;
    while (i < num && eigenvalue > epsilon) {
        std::pair<double, Vector> eigens = power_iteration(A, num_iter, epsilon);
        eigenvalue = std::get<0>(eigens);
        eigenvector = std::get<1>(eigens);

        std::cout << "Calculando autovalores... (" << i + 1 << "/" << num << ")" << std::endl;

        eigenvalues(i) = eigenvalue;
        eigenvectors.col(i) = eigenvector;
        A = A - eigenvalue * eigenvector * eigenvector.transpose();

        i++;
    }

    return std::make_pair(eigenvalues, eigenvectors);
}
