#include <iostream>
#include <fstream>
#include "pca.h"
#include "eigen.h"


Matrix create_matrix(bool train, const std::string& input, int images, int size) {
    Matrix X(images, size);
    std::ifstream fileInput;
    fileInput.open(input);
    std::string row;
    int row_n = -1;
    int column_n;

    while(std::getline(fileInput, row)) {
        if (row_n >= 0) {
            std::stringstream lineStream(row);
            std::string cell;

            if (train) {
                column_n = -1;
            } else {
                column_n = 0;
            }

            while(std::getline(lineStream,cell,',')) {
                if (column_n >= 0) {
                    X(row_n, column_n) = std::stoi(cell);
                }
                column_n++;
            }
        }
        row_n++;
    }

    return X;
}

Vector mean_vector(Matrix A) {
    int n = A.cols();
    Vector v(n);
    v.fill((double)1 / (double)n);

    return A * v;
}

Matrix covariance(Matrix A) {
    int rows = A.rows();
    int columns = A.cols();
    Vector means = mean_vector(A);
    double mean;

    for (int i = 0; i < rows; i++) {
        mean = means(i);
        for (int j = 0; j < columns; j++) {
            A(i, j) = (A(i, j) - mean) / sqrt(columns - 1);
        }
    }

    return A.transpose() * A;
}

Vector tc(const Vector& x, Matrix eigenvectors, unsigned int alpha) {
    unsigned int rows = eigenvectors.rows();
    unsigned int columns = eigenvectors.cols();
    Vector eigenvector(rows);

    if (columns < alpha) {
        alpha = columns;
    }

    Vector ans(alpha);

    for (unsigned int i = 0; i < alpha; i++) {
        eigenvector = eigenvectors.block(0, i, rows, 1);
        ans(i) = eigenvector.dot(x);
    }

    return ans;
}

Matrix pca(bool train, const std::string& input, int images, int size, unsigned int alpha) {
    Matrix X = create_matrix(train, input, images, size);
    Matrix C = covariance(X);

    std::pair<Vector, Matrix> eigens = get_first_eigenvalues(C, C.cols());
    Vector eigenvalues = std::get<0>(eigens);
    Matrix eigenvectors = std::get<1>(eigens);

    X = X * eigenvectors;

    Matrix TC(C.cols(), alpha);

    for (int i = 0; i < C.cols(); i++) {
        TC.row(i) = tc(X.row(i), eigenvectors, alpha);
    }

    return TC;
}

PCA::PCA(unsigned int n_components) {
    alpha = n_components;
}

void PCA::fit(Matrix X) {

}


MatrixXd PCA::transform(SparseMatrix X) {
    Matrix den = Matrix(X);
    std::pair<Vector, Matrix> values = get_first_eigenvalues(covariance(den), alpha);

    Matrix eigen = values.second;
    MatrixXd res(den.rows(), alpha);

    for(int i = 0; i < den.rows(); i++) {
        Vector row = den.row(i).head(alpha);
        res.row(i) = tc(row, eigen);
    }
    return res;
}
