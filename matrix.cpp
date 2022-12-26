#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include "matrix.h"
using namespace std;

Matrix::Matrix(){
    rowSize=0;
    colSize=0;
    data=NULL;
}

Matrix::Matrix(int m,int n){
    rowSize=m;
    colSize=n;
    matrixMalloc();
}


void Matrix::init(int m,int n){
   rowSize=m;
   colSize=n;
   matrixMalloc();
}

void Matrix::matrixMalloc(){
    data = (double *)malloc(rowSize*colSize*sizeof(double));
    if(NULL == data)
    {
        printf("malloc failed");
        return;
    }
}

void Matrix::matrixCopy(const Matrix a){
    memcpy(data,a.data,sizeof(double)*rowSize*colSize);
}

int  Matrix::getRowSize(){
    return rowSize;
}

int  Matrix::getColSize(){
    return colSize;
}

double  Matrix::getData(int i, int j){
    return *(data + i * colSize + j);
}

void  Matrix::setData(int i, int j, double x){

    *(data + i * colSize + j) = x; 
}

void Matrix::printAll(){
    cout<<"=============="<<endl;
    for(int i = 0;i < rowSize; i++){
        for(int j = 0; j < colSize; j++){
            cout<< fixed << setprecision(4) <<getData(i,j)<<" ";
        }
        cout<<endl;
    }
    cout<<"=============="<<endl;
}
void Matrix::printRow(int m){
     printf(" ");
}
void Matrix::printCol(int n){
     printf(" ");
}