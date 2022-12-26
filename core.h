#ifndef __CORE__
#define __CORE__
   #include <bits/stdc++.h>
   #include <stdio.h>
   #include <iostream>
   #include <iomanip>
   #include <cmath>
   #include <string>
   #include <algorithm>
   #include <fstream>
   #include <sstream>
   #include "matrix.h"
   using namespace std;

   //高斯消元核心段
   void guass(const Matrix c,Matrix &x);

   //字符串分割函数
   vector<string> split(const string &str, const string &delim);
    
   //string转double函数
   double stringToDouble(const string &str);

   //文件读
   void fileRead(Matrix &matrix,string fileName=".\\data.txt");

   //文件写
   void fileRead(Matrix &matrix,string fileName);

   //键盘输入接口
   void keyboard(Matrix &matrix);

#endif