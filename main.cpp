#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
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
    cout<< i << "x[" << i << "]=" << x[i] <<endl;
  }
}

//字符串分割函数
vector<string> split(const string &str, const string &delim) {
// str要分隔字符串，delim分割字段
  vector<string> res;
  if (str.empty()) return res;
  
  char *strs = new char[str.length() + 1];
  strcpy(strs, str.c_str());

  char *d = new char[delim.length() + 1];
  strcpy(d, delim.c_str());

  char *p = strtok(strs, d);
  while (p) {
    string s = p; 
    res.emplace_back(s); 
    p = strtok(nullptr, d);
  }
  delete[] strs;
  delete[] d;
  return res;
}

double stringToDouble(const string &str){
  istringstream iss(str);
  double num;
  iss >> num;
  return num;
}


void fileRead(double (&matrix)[3][3],int m,int n,string fileName=".\\data.txt"){
  int i = 0;
  ifstream inFile;
  inFile.open(fileName, ios::in);
  if (!inFile)  //文件不存在
  {
    cout <<fileName<<" doesn't exist" << endl;
    exit(1);
  } 
  string line;
  while (getline(inFile,line))
  {
    vector<string>  row =  split(line," ");
    for ( int j = 0; j < row.size(); j++ )
    { 
	    matrix[i][j] = stringToDouble(row[j]); 
      cout<<matrix[i][j]<<" ";
    }
    cout<<endl;
    i++;
  }
  cout<<"================"<<endl;
  inFile.close();
}


int main() {
  double a[3][3];
  fileRead(a,1,1);
  for(int i = 0;i<3;i++){
    for(int j = 0; j < 3; j++){
      cout << a[i][j] << " ";
    }
    cout<<endl;
  }
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

