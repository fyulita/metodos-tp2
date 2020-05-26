#pragma once
#include "types.h"

class PCA {
public:
    PCA(unsigned int n_components);

    void fit(Matrix X);

    Eigen::MatrixXd transform(SparseMatrix X);
private:
};

Matrix create_matrix(std::string input, int images, int size=783);
Vector mean_vector(Matrix A);
Matrix covariance(Matrix A);
