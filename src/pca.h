#pragma once
#include "types.h"


class PCA {
    public:
        PCA(unsigned int n_components);

        void fit(Matrix X);

        Matrix transform(Matrix X);
    private:
        unsigned int alpha;
        //Vector tc(const Vector& x, Matrix eigenvectors);
        //Matrix covariance;
};


Matrix pca(const std::string& input, unsigned int alpha=300);
