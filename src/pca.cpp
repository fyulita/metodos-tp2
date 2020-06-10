#include <iostream>
#include <fstream>
#include "pca.h"
#include "eigen.h"


// Convierte los datos del csv "input" a una matriz.
Matrix create_matrix(const std::string& input) {
    Matrix X;
    std::ifstream fileInput;
    fileInput.open(input);
    std::string row;
    int row_n = -1;
    int column_n;
    int max_column_n = 0;

    while(std::getline(fileInput, row)) {
        std::stringstream lineStream(row);
        std::string cell;
        if (row_n >= 0) {
            X.conservativeResize(row_n + 1, max_column_n);

            column_n = 0;

            while(std::getline(lineStream,cell,',')) {
                if (column_n >= 0) {
                    X(row_n, column_n) = std::stoi(cell);
                }
                column_n++;
            }
        } else {
            while(std::getline(lineStream,cell,',')) {
                max_column_n++;
            }
        }
        row_n++;
    }

    return X;
}

// Devuelve un vector con el promedio de cada columna de A.
Vector mean_vector(Matrix A) {
    int n = A.rows();
    Vector v(n);
    v.fill((double)1 / (double)n);

    return A.transpose() * v;
}

// Calcula la matriz de covarianza.
Matrix covariance(Matrix A) {
    int n = A.rows();
    Vector means = mean_vector(A);
    Vector aux;
    for (int i = 0; i < n; i++) {
        aux = A.row(i);
        A.row(i) = (aux - means) / sqrt(n - 1);
    }

    return A.transpose() * A;
}

// Devuelve una matrix con los vectores tc en sus filas.
Matrix pca(const std::string& input, unsigned int alpha) {
    Matrix X = create_matrix(input);
    std::cout << "Calculando covarianza..." << std::endl;
    Matrix C = covariance(X);

    std::pair<Vector, Matrix> eigens = get_first_eigenvalues(C, alpha);
    Vector eigenvalues = std::get<0>(eigens);
    Matrix eigenvectors = std::get<1>(eigens);

    Matrix TC = X * eigenvectors;

    return TC;
}

PCA::PCA(unsigned int n_components) {
    alpha = n_components;
}

void PCA::fit(Matrix X) {
}

Matrix PCA::transform(Matrix X) {
    std::cout << "Calculando covarianza..." << std::endl;
    Matrix C = covariance(X);

    std::pair<Vector, Matrix> eigens = get_first_eigenvalues(C, alpha);
    Vector eigenvalues = std::get<0>(eigens);
    Matrix eigenvectors = std::get<1>(eigens);

    Matrix TC = X * eigenvectors;

    return TC;
}
