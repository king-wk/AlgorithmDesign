/**
 * Filename：G-S算法
 * Author：文静静 1811507
 * Date：2020.3.8
 * Description：初始化所有的男人和女人都是自由的，如果存在有男人m的list里还没有和他约过会的女性
 *              那么这个男人m找到他list里还没有和他约过会并且排名最高的女人w，和这个女人w开始约会，他们的约会状态变成1
 *              如果这个女人w现在没有对象，那么m求婚成功成为w的对象，寻找下一个还没有对象的男性
 *              如果这个女人w现在有一个对象m2，如果m在w的排名里相比m2靠前，那么m求婚成功成为w的对象，而m2变为自由
 *              如果m在w的排名里相比m2靠后，那么m肯定求婚失败，仍为自由，继续寻找约会对象。
 *              最后输出所有男性的对象
 */

#include <iostream>

using namespace std;

/**
 * 输入为男人index，以及女人的数量number，和男人与女人的约会记录
 * 如果如果男人index的list里每一个女人的约会记录都是1，那么表示他要么求婚成功了，要么约过会但是求婚失败了
 * 如果有女人的约会记录为0，说明男人还没有跟她约过会
 * 输出男人index的list里是否还有单身女性
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
 * 判断所有的男人是否都已经有了对象
 * 遍历所有男人，如果男人的状态为0，说明他还没有对象，如果状态为1，说明他已经有了对象
 * 如果扫描到有男人还没有对象，用index记录这个男人
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
	/* 男人的状态记录，如果manstate[i]为1表示男人i有对象，如果为0表示男人i没有对象 */
	int *manstate = new int[number];
	/* 女人的状态记录，如果womanstate[i]为1表示女人i有对象，如果为0表示女人i没有对象 */
	int *womanstate = new int[number];
	/* 男人与女人的约会状态记录，如果man_woman[i][j]为1表示男人i与女人j已经约会过了 */
	int **man_woman;
	/* 女人目前的约会对象记录 */
	int *woman_manpair = new int[number];
	/* 女人列表次序里的男人，比如woman_man_rank[i][1]=j表示女人i列表里排第一的为男人j */
	int **woman_man_rank;
	woman_man_rank = new int *[number];
	/* woman[i][j]=1，说明男人j在女人i的列表里排第一，即woman_man_rank[i][1]=j */
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
	/* 从第一个男人开始 */
	int index = 0;
	/* 如果还存在一个自由的男人并且还没有向所有女人求婚，而且这个男人的list里还有单身女性 */
	while ((!man_have_pair(number, manstate, index)) && man_have_date(number, index, man_woman))
	{
		int m = index;
		int w;
		for (i = 0; i < number; i++)
		{
			/* 找到这个单身男性里排名最高且还没有约会过的女性 */
			if (man_woman[m][man[m][i]] == 0)
			{
				w = man[m][i];
				break;
			}
		}
		/* 这个男人和女人开始约会 */
		man_woman[m][w] = 1;
		/* 如果这个女性是自由的，那么他求婚成功，成为这个女人的对象 */
		if (womanstate[w] == 0)
		{
			woman_manpair[w] = m;
			womanstate[w] = 1;
			manstate[m] = 1;
		}else  {
			/* 
			 * 如果这个女性不是自由的
			 * 令m2为这个女性当前的对象 
			 */
			int m2 = woman_manpair[w];
			/*
			 * 如果m在w的排名里比m2靠前，那么m求婚成功
			 * m的对象变成m，m2变成自由状态
			 */
			if (woman_man_rank[w][m2] > woman_man_rank[w][m])
			{
				woman_manpair[w] = m;
				manstate[m2] = 0;
				manstate[m] = 1;
			}
			/*
			 * m在w的排名在m2的后面
			 * 那么他求婚失败，仍为自由
			 */
		}
	}
	/* 记录男人最后的对象 */
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
	 * number表示man和woman的数量
	 * man[][]数组记录man的优先列表
	 * woman[][]数组记录woman的优先列表
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
	/* end_manpair记录男人1~n的匹配对象 */
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
