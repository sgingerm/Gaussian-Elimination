#include "core.h"
using namespace std;

int main() {
  int m,n;
  string line;
  Matrix B,x;
  cout<<"请输入增广矩阵的行数：\n"<<endl;
  cin>>m;
  cin.ignore(std::numeric_limits< streamsize >::max(), '\n');
  cout<<"请输入增广矩阵的列数：\n"<<endl;
  cin>>n;
  cin.ignore(std::numeric_limits< streamsize >::max(), '\n');
  B.init(m,n);
  cout<<"请输入整个增广矩阵：\n"<<endl;
  for (int i = 0; i < m; i++)
  {
    getline(cin,line);
    vector<string>  row =  split(line," ");
    for ( int j = 0; j < n; j++ )
    { 
	    B.setData(i,j,stringToDouble(row[j])); 
    }
  }
  x.init(1,(B.colSize - 1));
  guass(B,x);

  //work();
  /*
  fileRead(matrix,1,1);
  for(int i = 0;i<3;i++){
    for(int j = 0; j < 3; j++){
      cout << matrix[i][j] << " ";
    }
    cout<<endl;
  }
  */
  return 0;
}