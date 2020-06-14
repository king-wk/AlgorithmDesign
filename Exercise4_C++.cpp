/**
 * Filename���ַ����Ƚ�����
 * Author���ľ��� 1811507
 * Date��2020.4.28
 * Description���Ƚ������ַ����ַ���A[1...i],B[1...j]֮��ľ���
 *              �ո���ո�ľ���Ϊ0���ո����ַ��ľ���Ϊk���ַ����ַ�֮�����Ϊ����ASCII��֮��ľ���ֵ
 *              1.A�ַ�����i��Ϊ�ո�B�ַ�����j�����ַ�����val(i,j)=val(i-1,j)+k;
 *              2.A�ַ�����i��Ϊ�ַ���B�ַ�����j���ǿո���val(i,j)=val(i,j-1)+k;
 *              3.A�ַ�����i��Ϊ�ַ���B�ַ�����j�����ַ�����val(i,j)=val(i-1,j-1)+dist(a,b);
 *              val(i,j)=min{val(i-1,j)+k,val(i,j-1)+k,val(i-1,j-1)+dist(a,b)}
 */

#include <iostream>
#include <string>

using namespace std;

/* �����ַ��� */
string A;
string B;
/* �ַ���ո�֮��ľ��� */
int k;
/* ��¼�����ַ������������ */
int val[4000][4000];


/**
 * ����Ϊ�����ַ�a,b
 * ���Ϊ�����ַ���ASCII���ľ���ֵ
 */
int dist(char a, char b)
{
	return(abs(a - b));
}

/**
 * �����������н�С��ֵ
 */
int min(int a, int b)
{
	return a>b?b:a;
}

/**
 * ���������ַ���A,B
 * �����ַ���A��B����С��չ����
 */
int compare()
{
	int	len1 = A.length();
	int	len2 = B.length();
	
	/*
	 * ���ݹ�ʽval(i,j)=min{val(i-1,j)+k,val(i,j-1)+k,val(i-1,j-1)+dist(a,b)}�Ե����ϵ���
	 */
	for (int i = 0; i <= len1; i++)
	{
		for (int j = 0; j <= len2; j++)
		{	
			/*
			 * �ַ���A��B����Ч�±�Ϊ1~len1��1~len2
			 * ��i��jΪ0ʱ��ʾ�ַ���A��BΪ�մ�
			 * ���ַ���BΪ�մ�����ôval(i,0)=i*k
			 * ���ַ���BΪ�մ�����ôval(0,j)=j*k
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

