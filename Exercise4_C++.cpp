/**
 * Filename：字符串比较问题
 * Author：文静静 1811507
 * Date：2020.4.28
 * Description：比较两个字符串字符串A[1...i],B[1...j]之间的距离
 *              空格与空格的距离为0，空格与字符的距离为k，字符与字符之间距离为它们ASCII码之差的绝对值
 *              1.A字符串第i个为空格，B字符串第j个是字符，则val(i,j)=val(i-1,j)+k;
 *              2.A字符串第i个为字符，B字符串第j个是空格，则val(i,j)=val(i,j-1)+k;
 *              3.A字符串第i个为字符，B字符串第j个是字符，则val(i,j)=val(i-1,j-1)+dist(a,b);
 *              val(i,j)=min{val(i-1,j)+k,val(i,j-1)+k,val(i-1,j-1)+dist(a,b)}
 */

#include <iostream>
#include <string>

using namespace std;

/* 两个字符串 */
string A;
string B;
/* 字符与空格之间的距离 */
int k;
/* 记录两个字符串距离的数组 */
int val[4000][4000];


/**
 * 输入为两个字符a,b
 * 输出为两个字符的ASCII码差的绝对值
 */
int dist(char a, char b)
{
	return(abs(a - b));
}

/**
 * 返回两个数中较小的值
 */
int min(int a, int b)
{
	return a>b?b:a;
}

/**
 * 根据两个字符串A,B
 * 返回字符串A和B的最小扩展距离
 */
int compare()
{
	int	len1 = A.length();
	int	len2 = B.length();
	
	/*
	 * 根据公式val(i,j)=min{val(i-1,j)+k,val(i,j-1)+k,val(i-1,j-1)+dist(a,b)}自底向上迭代
	 */
	for (int i = 0; i <= len1; i++)
	{
		for (int j = 0; j <= len2; j++)
		{	
			/*
			 * 字符串A和B的有效下标为1~len1和1~len2
			 * 当i或j为0时表示字符串A或B为空串
			 * 若字符串B为空串，那么val(i,0)=i*k
			 * 若字符串B为空串，那么val(0,j)=j*k
			 */
			if (i == 0)
			{
				val[i][j] = j * k;
			}
			if (j == 0)
			{
				val[i][j] = i * k;
			}
			if (i != 0 && j != 0)
			{
				val[i][j] = min(min(val[i - 1][j] + k, val[i][j - 1] + k), val[i - 1][j - 1] + dist(A[i - 1], B[j - 1]));
			}
		}
	}
	return(val[len1][len2]);
}


int main()
{
	cin >> A >> B;
	cin >> k;
	cout << compare();
	return(0);
}

