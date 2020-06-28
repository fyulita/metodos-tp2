#pragma once
#include "types.h"


class PCA {
    public:
        PCA(unsigned int n_components);
        void fit(Matrix A);
        Matrix transform(Matrix X);

    private:
        unsigned int alpha;
        Vector mean_vector(Matrix A);
        Matrix covariance(Matrix A);
};
