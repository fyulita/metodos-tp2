#pragma once
#include "types.h"


class PCA {
    public:
        PCA(unsigned int n_components);
        void fit(const Matrix& X);
        MatrixXd transform(const Matrix& X);
        Matrix covariance(Matrix A);
    private:
        unsigned int alpha;
        Matrix T;
        Vector mean_vector(const Matrix& A);
};
