#include "core.h"
const double epsilon=1e-12;
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

void fileWrite( Matrix &matrix,string fileName){
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
  cout<<"请输入矩阵的行数：\n"<<endl;
  cin>>m;
  cin.ignore(std::numeric_limits< streamsize >::max(), '\n');
  cout<<"请输入矩阵的列数：\n"<<endl;
  cin>>n;
  cin.ignore(std::numeric_limits< streamsize >::max(), '\n');
  matrix.init(m,n);
  cout<<"请输入整个矩阵：\n"<<endl;
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


//矩阵A*矩阵B=矩阵C
void multiply(Matrix &A,Matrix &B,Matrix &C)
{
	int A_h=A.rowSize;
	int A_l=A.colSize;
	int B_h=B.rowSize;
	int B_l=B.colSize;
	if(A_l !=B_h)
	{
		cout<<"两矩阵维数无法相乘"<<endl;
		exit(0);
	}
	C.init(A_h,B_l);
	for (int i = 0; i < A_h; i++)
	{
		for (int j = 0; j < B_l; j++)
		{
            C.setData(i,j,0);
			for (int k = 0; k < A_l; k++)
			{
                C.setData(i,j,C.getData(i,j)+A.getData(i,k)*B.getData(k,j));
			}
			if (abs(C.getData(i,j))<epsilon)
			{
				C.setData(i,j,0.0);
			}
			//cout<<C[i][j]<<"\t";
		}
		//cout<<endl;
	}
}

//输入矩阵A,输出矩阵A的逆矩阵inv_A
void inverse(Matrix &A, Matrix &inv_A)
{
     
	if (A.rowSize != A.colSize)
	{
		cout<<"输入矩阵维数不合法"<<endl;
		exit(0);
	}
	int n=A.rowSize;
	Matrix L,U,inv_L,inv_U;
    inv_A.init(n,n);
    L.init(n,n);
    U.init(n,n);
    inv_L.init(n,n);
    inv_U.init(n,n);
    
//LU分解
	//L矩阵对角元素为1
	for (int i = 0; i < n; i++)
	{
		L.setData(i,i,1);   
	}
    
	//U矩阵第一行
	for (int i = 0; i < n; i++)
	{
		U.setData(0,i,A.getData(0,i));  
	}
	//L矩阵第一列
    
	for (int i = 1; i < n; i++)
	{
		L.setData(i,0,1.0*A.getData(i,0)/A.getData(0,0));  
	}
    
	//计算LU上下三角
	for (int i = 1; i < n; i++)
	{
		//计算U（i行j列）
		for (int j = i; j < n; j++)
		{
			double tem = 0;
			for (int k = 0; k < i; k++)
			{
				tem = tem +  L.getData(i,k) * U.getData(k,j);
			}
			U.setData(i,j,A.getData(i,j) - tem);
			if (abs(U.getData(i,j))<epsilon)
			{
				U.setData(i,j,0.0);
			}
		}
		//计算L（j行i列）
		for (int j = i ; j < n; j++)
		{
			double tem = 0;
			for (int k = 0; k < i; k++)
			{
				tem = tem + L.getData(j,k) * U.getData(k,i);
			}
			L.setData(j,i,1.0*(A.getData(j,i) - tem) / U.getData(i,i));
			if (abs(L.getData(i,j))<epsilon)
			{
				L.setData(i,j,0.0);
			}
		}
 
	}
	//L U剩余位置设为0
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i>j)
			{
				U.setData(i,j,0);
                inv_U.setData(i,j,0);
			}
			else if(i<j)
			{
				L.setData(i,j,0);
                inv_U.setData(i,j,0);
			}
		}
	}
	//LU求逆
	//求矩阵U的逆 
	for (int i=0;i<n;i++) 
	{
		inv_U.setData(i,i,1/U.getData(i,i));// U对角元素的值，直接取倒数
		for (int k=i-1;k>=0;k--)
		{
			double s=0;
			for (int j=k+1;j<=i;j++)
			{
				s=s+U.getData(k,j)*inv_U.getData(j,i);
			}
			inv_U.setData(k,i,-s/U.getData(k,k));//迭代计算，按列倒序依次得到每一个值

			if (abs(inv_U.getData(k,i))<epsilon)
			{
                
				inv_U.setData(k,i,0.0);
			}
		}
	}
	//求矩阵L的逆
	for (int i=0;i<n;i++)  
	{
		inv_L.setData(i,i,1); //L对角元素的值，直接取倒数，这里为1
		for (int k=i+1;k<n;k++)
		{
			for (int j=i;j<=k-1;j++)
			{
				inv_L.setData(k,i,inv_L.getData(k,i)-L.getData(k,j)*inv_L.getData(j,i)); 
				if (abs(inv_L.getData(k,i))<epsilon)
				{
					inv_L.setData(k,i,0.0);
				}
			}
		}
	}
    multiply(inv_U,inv_L,inv_A);
}