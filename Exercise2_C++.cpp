/**
 * Filename：输出无向连通图最小生成树权重之和
 * Author：文静静 1811507
 * Date：2020.3.23
 * Description：prim算法：将第一个点放入集合V中，然后选取一条权值最小的边(a,b)，其中a在集合V中，b不在
 *                        将b结点加入V中，重复操作，直到V中有了图G的所有结点。
 *                                                用lowcost[i]记录V中的点到点i（i不位于V中）的最小权值，通过比较所有不属于V中的点它们与V中点的最小权值，获取最小边(a,b)
 */
#include <iostream>

using namespace std;

/* 两个点的最大权值 */
const int INF = 10000000;


/**
 * 输入为图G的邻接矩阵，结点数n，边数m
 * 输出为prim算法所得最小生成树的权重之和
 */
int prim(int **G, int n, int m)
{
	/* 记录集合V中点到该点的最小距离 */
	int *lowcost = new int[n];
	/* 记录已被选中的点 */
	int *V = new int[n];
	/* 初始化，所有的点都不在V中，所以V中点到所有点的距离为最大权值 */
	for (int i = 0; i < n; i++)
	{
		lowcost[i] = INF;
		V[i] = 0;
	}
	/*
	 * num记录V中结点数，当V中结点数为n时已经包含了G中所有结点
	 * sum记录最小生成树的权重之和
	 * v记录V中最新加入的结点
	 */
	int num = 1, sum = 0, v = 0;
	/* 将第一个点加入集合V */
	V[0] = 1;
	while (num < n)
	{
		/*
		 * mincost记录V中的点到V外的点的最小权值
		 * minvertex记录到V中的点权值最小的点
		 */
		int mincost = INF;
		int minvertex = 0;
		for (int i = 1; i < n; i++)
		{
			/* 寻找不属于集合V中的结点 */
			if (V[i] != 1)
			{
				/*
				 * 获取最新加入集合V的点v到V外每一点的权值
				 * 更新V外每一点到集合V中的点的最小权值
				 */
				int temp = G[v][i];
				if (temp < lowcost[i] && temp != 0)
				{
					lowcost[i] = temp;
				}
				/* 记录V外点集合V中的点的最小权值和这个点 */
				if (lowcost[i] < mincost)
				{
					mincost	= lowcost[i];
					minvertex = i;
				}
			}
		}
		/*
		 * 将到V中点权值最小的点加入V中，并将权值累加进sum中
		 * V中的结点数加一
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
	/* 图G的有效范围为0~n，所以输入时下标减一 */
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
