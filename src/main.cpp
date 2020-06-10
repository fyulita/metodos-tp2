#include <iostream>
#include <fstream>
#include "pca.h"
#include "knn.h"

using namespace std;

// Convierte los datos del csv "input" a una matriz.
Matrix parse(const std::string& input) {
    Matrix X;
    std::ifstream fileInput;
    fileInput.open(input);
    std::string row;
    int row_n = -1;
    int column_n;
    int max_column_n = 0;

    while(std::getline(fileInput, row)) {
        std::stringstream lineStream(row);
        std::string cell;
        if (row_n >= 0) {
            X.conservativeResize(row_n + 1, max_column_n);

            column_n = 0;

            while(std::getline(lineStream,cell,',')) {
                if (column_n >= 0) {
                    X(row_n, column_n) = std::stoi(cell);
                }
                column_n++;
            }
        } else {
            while(std::getline(lineStream,cell,',')) {
                max_column_n++;
            }
        }
        row_n++;
    }

    return X;
}

int main(int argc, char** argv){
    if (argc != 9) {
        printf("Parametros Invalidos!\n");
        return 1;
    } else {
        int method = atoi(argv[2]);
        string train_set_file = argv[4];
        string test_set_file = argv[6];
        string classif = argv[8];

        if (method == 0) { // kNN
            unsigned int k = 100;
            KNNClassifier knn = KNNClassifier(k);

            Matrix train_set = parse(train_set_file);
            Matrix y = train_set.col(0);
            Matrix X = train_set.block(0, 1, train_set.rows(), train_set.cols() - 1);

            Matrix test_set = parse(test_set_file);

            knn.fit(X, y);
            Vector prediction = knn.predict(test_set);
        }

        /*
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
        */
    }
}
