//初始化程序
#include <stdio.h>
double a[21][21], x[21];
int m, n;

void print() {
  printf("\n------->\n");
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) printf("%.2lf ", a[i][j]);
    printf("\n");
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
  printf("\n----------已化为阶梯型矩阵----------\n\n");
  //判断是否有解
  for (int i = 1; i <= m; i++) {
    int flag = 0;
    for (int j = 1; j <= n - 1; j++) {
      if (a[i][j] != 0) flag = 1;
    }
    if (flag == 1 && a[i][n] == 0) {
      printf("方程组无解\n");
      return;
    }
  }
  //判断是否有无穷多解
  if (m < n - 1) {
    printf("方程组有无穷多组解\n");
    return;
  }
  else for (int i = 1; i <= m; i++) {
    if (a[i][i] == 0) {
      printf("方程组有无穷多组解\n");
      return;
    }
  }
  //求解方程
  printf("方程组有唯一解：\n");
  for (int i = m; i >= 1; i--) {
    x[i] = a[i][n];
    for (int j = i + 1; j <= n - 1; j++) x[i] -= a[i][j] * x[j];
    x[i] /= a[i][i];
  }
  for (int i = 1; i <= n - 1; i++) printf("x%d = %.2lf\n", i, x[i]);
}


int main() {
  printf("请输入增广矩阵的行数和列数：\n");
  scanf("%d%d", &m, &n);
  printf("请输入整个增广矩阵：\n");
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
      scanf("%lf", &a[i][j]);
  work();
  return 0;
}