#include "core.h"

const double epsilon=1e-12;

//矩阵A*矩阵B=矩阵C
void multiply(const Matrix &A,const  Matrix &B,Matrix &C)
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
void inverse(const Matrix &A,const Matrix &inv_A)
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
				U.setData(i,j,0.0);
			}
			else if(i<j)
			{
				L.getData(i,j,0.0);
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
			inv_U.setData(k,i,-s/U.getData(k,k));//迭代计算，按列倒序依次得到每一个值，
			if (abs(inv_U.getData(k,i))<epsilon)
			{
				inv_U.getData(k,i,0.0);
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
					inv_L[k][i]=0.0;
				}
			}
		}
	}
	inv_A=multiply(inv_U,inv_L);
	return inv_A;
}