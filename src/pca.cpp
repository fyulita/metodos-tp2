#include <iostream>
#include <utility>
#include "pca.h"
#include "eigen.h"

PCA::PCA(unsigned int n_components) {
    alpha = n_components;
}

// Devuelve un vector con el promedio de cada columna de A.
Vector PCA::mean_vector(const Matrix& A) {
    unsigned int n = A.rows();
    Vector v(n);
    v.fill((double)1 / (double)n);

    return A.transpose() * v;
}

// Calcula la matriz de covarianza.
Matrix PCA::covariance(Matrix A) {
    int n = A.rows();
    Vector means = mean_vector(A);
    Vector aux;
    for (int i = 0; i < n; i++) {
        aux = A.row(i);
        A.row(i) = (aux - means) / sqrt(n - 1);
    }

    return A.transpose() * A;
}

void PCA::fit(const Matrix& X) {
    std::cout << "Calculando covarianza..." << std::endl;
    Matrix C = covariance(X);

    std::pair<Vector, Matrix> eigens = get_first_eigenvalues(C, alpha);
    Vector eigenvalues = std::get<0>(eigens);
    Matrix eigenvectors = std::get<1>(eigens);

    this->T = eigenvectors;
}

MatrixXd PCA::transform(const Matrix& X) {
    std::cout << "Listo!" << std::endl;
    return X * T;
}
