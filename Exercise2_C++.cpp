/**
 * Filename�����������ͨͼ��С������Ȩ��֮��
 * Author���ľ��� 1811507
 * Date��2020.3.23
 * Description��prim�㷨������һ������뼯��V�У�Ȼ��ѡȡһ��Ȩֵ��С�ı�(a,b)������a�ڼ���V�У�b����
 *                        ��b������V�У��ظ�������ֱ��V������ͼG�����н�㡣
 *                                                ��lowcost[i]��¼V�еĵ㵽��i��i��λ��V�У�����СȨֵ��ͨ���Ƚ����в�����V�еĵ�������V�е����СȨֵ����ȡ��С��(a,b)
 */
#include <iostream>

using namespace std;

/* ����������Ȩֵ */
const int INF = 10000000;


/**
 * ����ΪͼG���ڽӾ��󣬽����n������m
 * ���Ϊprim�㷨������С��������Ȩ��֮��
 */
int prim(int **G, int n, int m)
{
	/* ��¼����V�е㵽�õ����С���� */
	int *lowcost = new int[n];
	/* ��¼�ѱ�ѡ�еĵ� */
	int *V = new int[n];
	/* ��ʼ�������еĵ㶼����V�У�����V�е㵽���е�ľ���Ϊ���Ȩֵ */
	for (int i = 0; i < n; i++)
	{
		lowcost[i] = INF;
		V[i] = 0;
	}
	/*
	 * num��¼V�н��������V�н����Ϊnʱ�Ѿ�������G�����н��
	 * sum��¼��С��������Ȩ��֮��
	 * v��¼V�����¼���Ľ��
	 */
	int num = 1, sum = 0, v = 0;
	/* ����һ������뼯��V */
	V[0] = 1;
	while (num < n)
	{
		/*
		 * mincost��¼V�еĵ㵽V��ĵ����СȨֵ
		 * minvertex��¼��V�еĵ�Ȩֵ��С�ĵ�
		 */
		int mincost = INF;
		int minvertex = 0;
		for (int i = 1; i < n; i++)
		{
			/* Ѱ�Ҳ����ڼ���V�еĽ�� */
			if (V[i] != 1)
			{
				/*
				 * ��ȡ���¼��뼯��V�ĵ�v��V��ÿһ���Ȩֵ
				 * ����V��ÿһ�㵽����V�еĵ����СȨֵ
				 */
				int temp = G[v][i];
				if (temp < lowcost[i] && temp != 0)
				{
					lowcost[i] = temp;
				}
				/* ��¼V��㼯��V�еĵ����СȨֵ������� */
				if (lowcost[i] < mincost)
				{
					mincost	= lowcost[i];
					minvertex = i;
				}
			}
		}
		/*
		 * ����V�е�Ȩֵ��С�ĵ����V�У�����Ȩֵ�ۼӽ�sum��
		 * V�еĽ������һ
		 */
		V[minvertex]= 1;
		v = minvertex;
		sum += mincost;
		num++;
	}
	return(sum);
}


int main()
{
	int n, m;
	cin >> n >> m;
	int **G;
	G = new int *[n];
	for (int i = 0; i < n; i++)
	{
		G[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			G[i][j] = 0;
		}
	}
	/* ͼG����Ч��ΧΪ0~n����������ʱ�±��һ */
	for (int k = 0; k < m; k++)
	{
		int i, j, r;
		cin >> i >> j >> r;
		G[i - 1][j - 1] = r;
		G[j - 1][i - 1] = r;
	}
	cout << prim(G, n, m);
	return(0);
}
