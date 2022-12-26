#include "core.h"

//高斯消元核心段
void guass(const Matrix c,Matrix &x) {
  int m = c.rowSize;
  int n = c.colSize;
  Matrix a;
  a.init(m,n);
  x.init(1,(a.colSize - 1));
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

void fileRead(Matrix &matrix,string fileName=".\\data.txt"){
  int m = 0;
  int n = 0;
  int i = 0;
  ifstream inFile;
  inFile.open(fileName, ios::in);
  if (!inFile)  //文件不存在
  {
    cout <<fileName<<" doesn't exist" << endl;
    exit(1);
  } 
  string line;
  getline(inFile,line);
  vector<string>  pp = split(line," ");
  m=stringToDouble(pp[0]);
  n=stringToDouble(pp[1]);
  matrix.init(m,n);
  while (getline(inFile,line))
  {
    vector<string>  row =  split(line," ");
    for ( int j = 0; j < row.size(); j++ )
    { 
	    matrix.setData(i,j , stringToDouble(row[j])); 
    }
    i++;
  }
  inFile.close();
}

void fileWrite( Matrix &matrix,string fileName=".\\result.txt"){
 int m = matrix.rowSize;
 int n = matrix.colSize;
 ofstream outFile;
 outFile.open(fileName, std::ios::out);

  for (int i=0; i<m; i++)
  {
    for(int j=0; j < n; j++)
    {
        outFile << std::to_string(matrix.getData(i,j)) << " ";
    }
    outFile << "\n";
  }
  outFile.close();
}

void keyboard(Matrix &matrix){
  int m,n;
  string line;
  cout<<"请输入增广矩阵的行数：\n"<<endl;
  cin>>m;
  cin.ignore(std::numeric_limits< streamsize >::max(), '\n');
  cout<<"请输入增广矩阵的列数：\n"<<endl;
  cin>>n;
  cin.ignore(std::numeric_limits< streamsize >::max(), '\n');
  matrix.init(m,n);
  cout<<"请输入整个增广矩阵：\n"<<endl;
  for (int i = 0; i < m; i++)
  {
    getline(cin,line);
    vector<string>  row =  split(line," ");
    for ( int j = 0; j < n; j++ )
    { 
	    matrix.setData(i,j,stringToDouble(row[j])); 
    }
  }
}