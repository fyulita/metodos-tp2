#include <iostream>
#include <fstream>
#include <utility>
#include "pca.h"
#include "eigen.h"


Matrix create_matrix(std::string input, int images, int size)
{
    Matrix X(images, size);
    std::ifstream fileInput;
    fileInput.open(input);
    std::string row;
    int row_n = -1;
    while(std::getline(fileInput, row))
    {
        if (row_n >= 0)
        {
            std::stringstream lineStream(row);
            std::string cell;
            int column_n = 0;
            while(std::getline(lineStream,cell,','))
            {
                X(row_n, column_n) = std::stoi(cell);
                column_n++;
            }
        }
        row_n++;
    }

    return X;
}

Vector mean_vector(Matrix A)
{
    int n = A.cols();
    Vector v(n);
    v.fill((double)1 / (double)n);

    return A * v;
}

Matrix covariance(Matrix A)
{
    int rows = A.rows();
    int columns = A.cols();
    Vector means = mean_vector(A);

    for (int i = 0; i < rows; i++)
    {
        double mean = means(i);
        for (int j = 0; j < columns; j++)
        {
            A(i, j) = (A(i, j) - mean) / sqrt(columns - 1);
        }
    }

    return A.transpose() * A;
}

PCA::PCA(unsigned int n_components)
{
    
}

void PCA::fit(Matrix X)
{

}


MatrixXd PCA::transform(SparseMatrix X)
{
    throw std::runtime_error("Sin implementar");
}
