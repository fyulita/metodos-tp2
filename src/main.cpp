#include <iostream>
#include <fstream>
#include "pca.h"

using namespace std;

// train.csv: 42000 images of 784 pixels (28x28). First column is the label.
// test.csv: 28000 images of 784 pixels (28x28).
// smalltest.csv: 1 image of 784 pixels (28x28).


int main(int argc, char** argv){
    if (argc != 6) {
        printf("Parametros Invalidos!\n");
        return 1;
    } else {
        string function = argv[1];
        if (function == "pca") {
            bool train = atoi(argv[2]) == 1;
            string input = argv[3];
            input = "../data/" + input;
            unsigned int alpha = atoi(argv[4]);
            string output = argv[5];
            output = "../data/" + output;

            Matrix ans = pca(train, input, alpha);

            const static Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n");
            ofstream file(output.c_str());
            file << ans.format(CSVFormat);

            return 0;
        }
    }
}
