#include "core.h"
using namespace std;

int main() {
  Matrix B,x;
  cout<<"请选择要计算的任务:"<<endl;
  cout<<"1、手动输入增广矩阵"<<endl
  <<"2、文件读如增广矩阵"<<endl;
  int expression;
  cin>>expression;
  switch (expression) {
    case 1 :
       keyboard(B);
       break; 
    case 2 :
       fileRead(B,".\\data.txt");
       break;
    default : 
      exit(0);
}
inverse(B,x);

//x.printAll();
  //guass(B,x);
  //x.printAll();
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