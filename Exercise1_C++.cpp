/**
 * Filename��G-S�㷨
 * Author���ľ��� 1811507
 * Date��2020.3.8
 * Description����ʼ�����е����˺�Ů�˶������ɵģ��������������m��list�ﻹû�к���Լ�����Ů��
 *              ��ô�������m�ҵ���list�ﻹû�к���Լ���Ტ��������ߵ�Ů��w�������Ů��w��ʼԼ�ᣬ���ǵ�Լ��״̬���1
 *              ������Ů��w����û�ж�����ôm���ɹ���Ϊw�Ķ���Ѱ����һ����û�ж��������
 *              ������Ů��w������һ������m2�����m��w�����������m2��ǰ����ôm���ɹ���Ϊw�Ķ��󣬶�m2��Ϊ����
 *              ���m��w�����������m2������ôm�϶����ʧ�ܣ���Ϊ���ɣ�����Ѱ��Լ�����
 *              �������������ԵĶ���
 */

#include <iostream>

using namespace std;

/**
 * ����Ϊ����index���Լ�Ů�˵�����number����������Ů�˵�Լ���¼
 * ����������index��list��ÿһ��Ů�˵�Լ���¼����1����ô��ʾ��Ҫô���ɹ��ˣ�ҪôԼ���ᵫ�����ʧ����
 * �����Ů�˵�Լ���¼Ϊ0��˵�����˻�û�и���Լ����
 * �������index��list���Ƿ��е���Ů��
 */
bool man_have_date(int number, int index, int **man_woman)
{
	for (int i = 0; i < number; i++)
	{
		if (man_woman[index][i] == 0)
			return(1);
	}
	return(0);
}


/**
 * �ж����е������Ƿ��Ѿ����˶���
 * �����������ˣ�������˵�״̬Ϊ0��˵������û�ж������״̬Ϊ1��˵�����Ѿ����˶���
 * ���ɨ�赽�����˻�û�ж�����index��¼�������
 */
bool man_have_pair(int number, int *manstate, int &index)
{
	for (int i = 0; i < number; i++)
	{
		if (manstate[i] == 0)
		{
			index = i;
			return(0);
		}
	}
	return(1);
}


int *GS(int **man, int **woman, int number)
{
	/* ���˵�״̬��¼�����manstate[i]Ϊ1��ʾ����i�ж������Ϊ0��ʾ����iû�ж��� */
	int *manstate = new int[number];
	/* Ů�˵�״̬��¼�����womanstate[i]Ϊ1��ʾŮ��i�ж������Ϊ0��ʾŮ��iû�ж��� */
	int *womanstate = new int[number];
	/* ������Ů�˵�Լ��״̬��¼�����man_woman[i][j]Ϊ1��ʾ����i��Ů��j�Ѿ�Լ����� */
	int **man_woman;
	/* Ů��Ŀǰ��Լ������¼ */
	int *woman_manpair = new int[number];
	/* Ů���б����������ˣ�����woman_man_rank[i][1]=j��ʾŮ��i�б����ŵ�һ��Ϊ����j */
	int **woman_man_rank;
	woman_man_rank = new int *[number];
	/* woman[i][j]=1��˵������j��Ů��i���б����ŵ�һ����woman_man_rank[i][1]=j */
	int i = 0;
	for (i = 0; i < number; i++)
	{
		woman_man_rank[i] = new int[number];
		for (int j = 0; j < number; j++)
		{
			woman_man_rank[i][woman[i][j]] = j;
		}
	}
	man_woman = new int *[number];
	for (i = 0; i < number; i++)
	{
		man_woman[i] = new int[number];
		for (int j = 0; j < number; j++)
		{
			man_woman[i][j] = 0;
		}
		manstate[i] = 0;
		womanstate[i] = 0;
		woman_manpair[i] = 0;
	}
	/* �ӵ�һ�����˿�ʼ */
	int index = 0;
	/* ���������һ�����ɵ����˲��һ�û��������Ů����飬����������˵�list�ﻹ�е���Ů�� */
	while ((!man_have_pair(number, manstate, index)) && man_have_date(number, index, man_woman))
	{
		int m = index;
		int w;
		for (i = 0; i < number; i++)
		{
			/* �ҵ����������������������һ�û��Լ�����Ů�� */
			if (man_woman[m][man[m][i]] == 0)
			{
				w = man[m][i];
				break;
			}
		}
		/* ������˺�Ů�˿�ʼԼ�� */
		man_woman[m][w] = 1;
		/* ������Ů�������ɵģ���ô�����ɹ�����Ϊ���Ů�˵Ķ��� */
		if (womanstate[w] == 0)
		{
			woman_manpair[w] = m;
			womanstate[w] = 1;
			manstate[m] = 1;
		}else  {
			/* 
			 * ������Ů�Բ������ɵ�
			 * ��m2Ϊ���Ů�Ե�ǰ�Ķ��� 
			 */
			int m2 = woman_manpair[w];
			/*
			 * ���m��w���������m2��ǰ����ôm���ɹ�
			 * m�Ķ�����m��m2�������״̬
			 */
			if (woman_man_rank[w][m2] > woman_man_rank[w][m])
			{
				woman_manpair[w] = m;
				manstate[m2] = 0;
				manstate[m] = 1;
			}
			/*
			 * m��w��������m2�ĺ���
			 * ��ô�����ʧ�ܣ���Ϊ����
			 */
		}
	}
	/* ��¼�������Ķ��� */
	int *end_manpair = new int[number];
	for (i = 0; i < number; i++)
	{
		end_manpair[woman_manpair[i]] = i;
	}
	return(end_manpair);
}


int main()
{
	/*
	 * number��ʾman��woman������
	 * man[][]�����¼man�������б�
	 * woman[][]�����¼woman�������б�
	 */
	int number, **man, **woman;
	cin >> number;
	man = new int *[number];
	woman = new int *[number];
	int i = 0;
	for (i = 0; i < number; i++)
	{
		man[i] = new int[number];
		for (int j = 0; j < number; j++)
		{
			cin >> man[i][j];
			man[i][j]--;
		}
	}
	for (i = 0; i < number; i++)
	{
		woman[i] = new int[number];
		for (int j = 0; j < number; j++)
		{
			cin >> woman[i][j];
			woman[i][j]--;
		}
	}
	/* end_manpair��¼����1~n��ƥ����� */
	int *end_manpair = new int[number];
	end_manpair = GS(man, woman, number);
	for (i = 0; i < number; i++)
	{
		cout << end_manpair[i] + 1;
		if (i < number - 1)
		{
			cout << " ";
		}
	}
	return(0);
}
