#ifndef __MATRIX__
#define __MATRIX__
class   Matrix;
 
/// @brief 
class Matrix
{
  /// @brief 
  public:
    int rowSize;
    int colSize;
    double *data;
    /// @brief 
    Matrix();
    /// @brief 
    /// @param m 
    /// @param n 
    Matrix(int m,int n);
    void init(int m,int n);
    double getData(int i, int j);
    void setData(int i, int j, double x);

    void matrixMalloc();
    void matrixCopy(const Matrix a);
    int getRowSize();
    int getColSize();
    void printAll();
    void printRow(int m);
    void printCol(int n);
};
#endif