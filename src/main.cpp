#include <iostream>
#include "pca.h"

// train.csv: 42000 images of 784 pixels (28x28). First column is the label.
// test.csv: 28000 images of 784 pixels (28x28).
// smalltest.csv: 1 image of 784 pixels (28x28).


int main(int argc, char** argv){
    std::string file = "../data/test.csv";
    Matrix ans = pca(false, file, 10);
    std::cout << ans << std::endl;

    return 0;
}
