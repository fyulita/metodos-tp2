#include <iostream>
#include <fstream>
#include "pca.h"
#include "knn.h"

using namespace std;

// Convierte los datos del csv "input" a una matriz.
Matrix create_matrix(const std::string& input) {
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

// Guarda una matriz en un archivo csv.
void save_vector(const Vector &A, const string &output) {
    ofstream Output;
    Output.open(output);
    for (int i = 0; i < A.rows(); i++) {
        Output << A(i) << "\n";
    }
    Output.close();
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
            Matrix train_set = create_matrix(train_set_file);
            Matrix y = train_set.col(0);
            Matrix X = train_set.block(0, 1, train_set.rows(), train_set.cols() - 1);
            Matrix test_set = create_matrix(test_set_file);

            unsigned int k = 100;
            KNNClassifier knn = KNNClassifier(k);
            knn.fit(X, y);
            Vector prediction = knn.predict(test_set);
            save_vector(prediction, classif);

            return 0;
        } else if (method == 1) { // PCA + kNN
            Matrix train_set_matrix = create_matrix(train_set_file);
            Matrix y = train_set_matrix.col(0);
            Matrix X_matrix = train_set_matrix.block(0, 1, train_set_matrix.rows(), train_set_matrix.cols() - 1);
            Matrix test_set_matrix = create_matrix(test_set_file);

            unsigned int alpha = 300;
            PCA X = PCA(alpha);
            PCA test_set = PCA(alpha);
            Matrix X_trans = X.transform(X_matrix);
            Matrix test_set_trans = test_set.transform(test_set_matrix);

            unsigned int k = 100;
            KNNClassifier knn = KNNClassifier(k);
            knn.fit(X_trans, y);
            Vector prediction = knn.predict(test_set_trans);
            save_vector(prediction, classif);

            return 0;
        }
    }
}
