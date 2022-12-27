#include "core.h"
using namespace std;
void sect(Matrix A,Matrix B,Matrix x);
void guass_api(Matrix A, Matrix B,Matrix x){
    cout<<"请选择输入方式:"<<endl;
    cout<<"1、手动输入增广矩阵"<<endl
        <<"2、文件读入增广矩阵"<<endl
        <<"0、退出程序" << endl;
    int expression;
    cin>>expression;
    switch (expression) {
        case 1 :
        keyboard(B);
        break; 
        case 2 :
        fileRead(B,".\\data.txt");
        break;
      case 0 :
       exit(0);
       break;
        default : 
        exit(0);
    }
   guass(B,x);
   x.printAll();
  sect(A,B,x);
}
void LU_api(Matrix A,Matrix B,Matrix x){
    cout<<"请选择输入方式:"<<endl;
    cout<<"1、手动输入矩阵"<<endl
        <<"2、文件读入矩阵"<<endl
        <<"0、退出程序" << endl;
    int expression;
    cin>>expression;
    switch (expression) {
        case 1 :
        keyboard(B);
        break; 
        case 2 :
        fileRead(B,".\\data.txt");
        break;
      case 0 :
       exit(0);
       break;
        default : 
        exit(0);
    }
    inverse(B, x);
    cout<<"逆矩阵为:"<<endl;
    x.printAll();
    sect(A,B,x);
}


void ma_api(Matrix A,Matrix B,Matrix x){
    cout<<"请选择输入方式:"<<endl;
    cout<<"1、手动输入矩阵"<<endl
        <<"2、文件读入矩阵"<<endl
        <<"0、退出程序" << endl;
    int expression;
    cin>>expression;
    switch (expression) {
        case 1 :
        cout<<"输入矩阵A"<<endl;
        keyboard(A);
        cout<<"输入矩阵B"<<endl;
        keyboard(A);
        break; 
        case 2 :
        cout<<"正在读入矩阵A"<<endl;
        fileRead(A,".\\data.txt");
        cout<<"正在读入矩阵A"<<endl;
        fileRead(B,".\\data2.txt");
        cout<<"读取完毕"<<endl;
        break;
      case 0 :
       exit(0);
       break;
        default : 
        exit(0);
    }
    multiply(A,B,x);
    cout<<"矩阵乘为:"<<endl;
    x.printAll();
    sect(A,B,x);
}

void mu(Matrix A,Matrix B,Matrix x){
  cout<<"请选择要计算的任务(输入编号):"<<endl;
  cout<<"1、高斯消元计算线性方程组"<<endl
      <<"2、LU分解计算矩阵的逆"<<endl
      <<"3、计算矩阵乘"<<endl
       <<"0、退出程序" << endl;
  int expression;
  cin>>expression;
  switch (expression) {
    case 1 :
       guass_api(A,B,x);
       break; 
    case 2 :
       LU_api(A,B,x);
       break;
    case 3 :
       ma_api(A,B,x);
       break;
    case 0 :
       exit(0);
       break;
    default : 
      exit(0);
  }
}

void sect(Matrix A,Matrix B,Matrix x){
  cout<<"请选择下列操作:"<<endl;
  cout<<"1、保存结果"<<endl
      <<"2、返回主目录"<<endl
      <<"0、退出程序" << endl;
  int expression;
  cin>>expression;
  switch (expression) {
    case 1 :
       fileWrite(x,".\\result.txt");
       cout<<"1、保存结果"<<endl;
       sect(A,B,x);
       break; 
    case 2 :
       mu(A,B,x);
       break;
    case 0 :
       exit(0);
       break;
    default : 
      exit(0);
  }
}

int main() {
  Matrix A,B,x;
  mu(A,B,x);
  return 0;
}