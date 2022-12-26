#include "core.h"

//高斯消元核心段
void guass(const Matrix c,Matrix &x) {
  int m = c.rowSize;
  int n = c.colSize;
  Matrix a;
  a.init(m,n);
  a.matrixCopy(c);
  a.printAll();
  for (int j = 0; j < n - 1; j++) { //从第一列到第n-1列
    for (int i = j + 1; i < m; i++) {   //从第j+1行到第m行
      if ( a.getData(j,i) == 0) continue;
      double t = - a.getData(i,j) / a.getData(j,j);
      for (int k = j; k < n; k++) a.setData(i,k,a.getData(i,k) + a.getData(j,k) * t);
    }
  }
  cout<<"----------已化为阶梯型矩阵----------"<<endl;
  //判断是否有解
  for (int i = 0; i < m; i++) {
    int flag = 0;
    for (int j = 0; j < n - 1; j++) {
      if (a.getData(i,j) != 0) flag = 1;
    }
    if (flag == 1 && a.getData(i,n-1) == 0) {
      cout<<"方程组无解"<<endl;
      return;
    }
  }
  //判断是否有无穷多解
  if (m < n - 1) {
    cout<<"方程组有无穷多组解\n"<<endl;
    return;
  }
  else for (int i = 0; i < m; i++) {
    if (a.getData(i,i) == 0) {
      cout<<"方程组有无穷多组解\n"<<endl;
      return;
    }
  }
  //求解方程
  cout<<"方程组有唯一解：\n"<<endl;
  for (int i = m - 1; i >= 0; i--) {
    x.setData(0,i ,a.getData(i,n-1));
    for (int j = i + 1; j < n - 1; j++) x.setData(0,i,x.getData(0,i) - a.getData(i,j) * a.getData(1,j));
     x.setData(0,i,x.getData(0,i) /a.getData(i,i));
  }
  x.printAll();
  /*
  for (int i = 0; i < n - 1; i++) 
  {
    cout<< "x[" << i << "]=" << x[i] <<endl;
  }
  */
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
