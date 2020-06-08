#pragma once
#include "types.h"


class PCA {
    public:
        PCA(unsigned int n_components);

        void fit(Matrix X);

        Eigen::MatrixXd transform(SparseMatrix X);
    private:
        unsigned int alpha;
        //Vector tc(const Vector& x, Matrix eigenvectors);
        //Matrix covariance;
};


Matrix pca(bool train, const std::string& input, unsigned int alpha=300);
