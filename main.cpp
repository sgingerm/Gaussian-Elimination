#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
double a[21][21], x[21];
int m, n;

void print() {
  cout<<""<<endl;
  cout<<"----------"<<endl;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++){
      cout<< fixed << setprecision(4) <<a[i][j]<<"  ";
    }
    cout<<""<<endl;
  }
}
void work() {
  print();
  for (int j = 1; j <= n - 1; j++) { //从第一列到第n-1列
    for (int i = j + 1; i <= m; i++) {   //从第j+1行到第m行
      if (a[j][i] == 0) continue;
      double t = - a[i][j] / a[j][j];
      for (int k = j; k <= n; k++) a[i][k] += a[j][k] * t;
    }
    print();
  }
  cout<<"----------已化为阶梯型矩阵----------"<<endl;
  //判断是否有解
  for (int i = 1; i <= m; i++) {
    int flag = 0;
    for (int j = 1; j <= n - 1; j++) {
      if (a[i][j] != 0) flag = 1;
    }
    if (flag == 1 && a[i][n] == 0) {
      cout<<"方程组无解"<<endl;
      return;
    }
  }
  //判断是否有无穷多解
  if (m < n - 1) {
    cout<<"方程组有无穷多组解\n"<<endl;
    return;
  }
  else for (int i = 1; i <= m; i++) {
    if (a[i][i] == 0) {
      cout<<"方程组有无穷多组解\n"<<endl;
      return;
    }
  }
  //求解方程
  cout<<"方程组有唯一解：\n"<<endl;
  for (int i = m; i >= 1; i--) {
    x[i] = a[i][n];
    for (int j = i + 1; j <= n - 1; j++) x[i] -= a[i][j] * x[j];
    x[i] /= a[i][i];
  }
  for (int i = 1; i <= n - 1; i++) 
  {
    cout<< i << "x[" <<i<<"]="<<x[i]<<endl;
  }
}


void fileRead(int m,int n,string fileName=".\\data.txt"){

  ifstream inFile;
  inFile.open(fileName, ios::in);
  if (!inFile)  //条件成立，则说明文件打开成功
    cout <<fileName<<" doesn't exist" << endl;
    
  string line;
    while (getline(inFile,line))
    {
        cout <<line<<endl;//空格是为了避免数据都连在一块儿
    }
}


int main() {
  fileRead(1,1);
  /*
  cout<<"请输入增广矩阵的行数：\n"<<endl;
  cin>>m;
  cout<<"请输入增广矩阵的列数：\n"<<endl;
  cin>>n;
  cout<<"请输入整个增广矩阵：\n"<<endl;
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
      cin>>a[i][j];
  work();
  */
  return 0;
}

