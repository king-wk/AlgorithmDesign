/**
 * Filename�����ڽ����
 * Author���ľ��� 1811507
 * Date��2020.4.17
 * Description�� ���÷����㷨
 *               �ֽ⣺�����еĵ㰴��x���ꡢy�����С��������
 *                     �����±�ֽ⣬ʹ�㼯��Ϊ��������
 *                     �ݹ�Ѱ���������ϵ������ԣ�ȡ������Сֵd
 *               �ϲ������м���x����mid����һ��[mid-d,mid+d]�����򣬻�ȡ���������еĵ�
 *                     ������Щ�㣬���Ƿ���ھ���С��d�ĵ��
 */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
/* һ����Ե������� */
const double INF = 1e20;
/* ���� */
const int N = 30001;
/* �� */
struct Point {
	double	x;
	double	y;
}
point[N];
/* ʵ������ĵ��� */
int n;
/* ���ڼ�¼λ������[mid-d,mid+d]�ĵ� */
int tmpt[N];
/**
 * ����x���ꡢy�����˳��Ƚ�������Ĵ�С
 */
bool cmpxy(const Point &a, const Point &b) {
	if ( a.x != b.x ) {
		return(a.x < b.x);
	}
	return(a.y < b.y);
}
/**
 * ����y����Ƚ�������Ĵ�С
 */
bool cmpy(const int &a, const int &b) {
	return(point[a].y < point[b].y);
}
/**
 * ��������doubleֵ�е���Сֵ
 */
double min(double a, double b) {
	return(a < b ? a : b);
}
/**
 * �������λ�õĵ�ľ����ƽ��
 */
double dis(int i, int j) {
	double	dis_x = point[i].x - point[j].x;
	double	dis_y = point[i].y - point[j].y;
	return(dis_x * dis_x + dis_y * dis_y);
}
/**
 * ���ؼ����е���С�����Եľ���
 * left�����ϵ���߽��λ�ã�right�����ϵ��ұ߽�λ��
 * ʹ�÷����㷨
 */
double Closest_Pair(int left, int right) {
	/* ��С����d */
	double d = INF;
	/* ���ֻ��һ���㣬ֱ�ӷ�����С����d */
	if (left == right) {
		return(d);
	}
	/* ���ֻ�������㣬ֱ�ӷ���������ľ��� */
	if (left + 1 == right) {
		return(dis(left, right));
	}
	/* �����м���λ��mid������mid�����Ϸֳ������� */
	int mid = (left + right) / 2;
	/* ������߼��ϵ���С�����Եľ��� */
	double d1 = Closest_Pair(left, mid);
	/* �����ұ߼��ϵ���С�����Եľ��� */
	double d2 = Closest_Pair(mid + 1, right);
	/* ȡ������С�������Сֵ */
	d = min(d1, d2);
	int i, j, k = 0;
	/* ��ȡ����[mid-d,mid+d]�����е� */
	for (i = left; i <= right; i++) {
		if (fabs(point[mid].x - point[i].x) <= d) {
			tmpt[k++] = i;
		}
	}
	/* �������еĵ㰴��y�������� */
	sort(tmpt, tmpt + k, cmpy);
	/* ������������еĵ㣬�ҵ���С���� */
	for (i = 0; i < k; i++) {
		/*
		 * ���i����j���y����ľ������d����ôi����j��֮��ĵ�y�������һ��Ҳ����d
		 * �������y����������d����ô������ľ���һ������d��������ǰ��������
		 */
		for (j = i + 1; j < k && point[tmpt[j]].y - point[tmpt[i]].y < d; j++) {
			double d3 = dis(tmpt[i], tmpt[j]);
			if ( d > d3 ) {
				/*
				 * ������������֮��ľ���С��d
				 * ��ô�õ��µ���С����
				 */
				d = d3;
			}
		}
	}
	return(d);
}
int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> point[i].x >> point[i].y;
	}
	/* ���ݵ㼯��x���ꡢy���꽫�㼯���� */
	sort(point, point + n, cmpxy);
	/* ������ڽ���Ծ����ƽ������С�������λ */
	cout << fixed << setprecision(2) << Closest_Pair(0, n - 1);
	return(0);
}

