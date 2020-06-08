#include <algorithm>
//#include <chrono>
#include <iostream>
#include "knn.h"
#include <numeric>      
#include <algorithm>    

using namespace std;


KNNClassifier::KNNClassifier(unsigned int n_neighbors)
{
	k = n_neighbors;
}

void KNNClassifier::fit(Matrix X, Matrix y){
	this->X = X;
	this->Y = y;
}


double KNNClassifier::predictAux(Vector vec){

	Matrix sub = Matrix(X.rows(), X.cols());
    for(int i = 0; i < sub.rows(); i++){
        sub.row(i) = vec;
    }


	Matrix aux = Matrix(X.rows(), X.cols());
    aux = X - sub;

    //termino de hacer distancia euclideana
    Vector dis = Vector(X.rows());
    for(int i = 0; i < X.rows(); i++){
        dis(i) = aux.row(i).squaredNorm();
    }

    //ordeno digitos por distancia
    vector<int> ind(dis.size());
   	iota(ind.begin(), ind.end(), 0);
	sort(ind.begin(), ind.end(),[&dis](size_t i1, size_t i2) {return dis(i1) < dis(i2);});
  
    ind.resize(k);  //me quedo solo con los mas cercanos


    //lleno el vector res con los tags pertinentes a los k cercanos
    Vector res = Vector(k);
	for(unsigned int i = 0; i < k; i++){
        res(i) = Y(0,ind[i]);
    }

    //contamos la cantidad de apariciones de cada tag entre los k cercanos
    Vector coun(res.size());
    for(int i = 0; i<coun.size(); i++){
    	//coun(i) = count(res.begin(),res.end(),res(i));
    	coun(i) = 0;
    	for (int j = 0; j < res.size(); j++) {
    	    if (res(i) == res(j)) {
    	        coun(i)++;
    	    }
    	}
 	}

    // aca no se podria hacer un sortIndex()? y usar el primero
    double max = -1;
 	int index = -1;
    for(int i = 0; i < coun.count(); i++){
    	if(coun(i) > max){
       		max = coun(i);
       		index = i;
     	}
   }
   return res(index);
}


Vector KNNClassifier::predict(Matrix X){
    auto ret = Vector(X.rows());

    for (unsigned k = 0; k < X.rows(); ++k) {
        ret(k) = predictAux(X.row(k));
    }

    return ret;
}
