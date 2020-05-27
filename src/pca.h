#pragma once
#include "types.h"

class PCA {
public:
    PCA(unsigned int n_components);

    void fit(Matrix X);

    Eigen::MatrixXd transform(SparseMatrix X);
private:
	unsigned int alpha;
};

Matrix create_matrix(bool train, const std::string& input, int images, int size);
Vector mean_vector(Matrix A);
Matrix covariance(Matrix A);
Vector tc(const Vector& x, Matrix eigenvectors, unsigned int alpha=10);
Matrix pca(bool train, const std::string& input, int images, int size, unsigned int alpha=10);
