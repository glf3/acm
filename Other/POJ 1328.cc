/*以岛为圆心做半径为d的圆，
与x轴有两个交点，然后根据交点
从小到大排序，然后维护最小值即可。*/
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
const double PI = acos(-1.0);

struct Point
{
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) { }
	bool operator < (const Point& a) const
	{
		if(y != a.y) return y < a.y;
		return x < a.x;
	}
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }

Vector operator - (Point A, Point B) { return Vector(A.x-B.x, A.y-B.y); }

Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }

Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }

int dcmp(double x)
{
	if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

bool operator == (const Point& a, const Point &b)
{
	return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }

double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
double Area2(Point A, Point B, Point C) { return fabs(Cross(B-A, C-A)) / 2; }

const int maxn = 1010;

double sqr(double x) { return x*x; }

double Dist(Point A, Point B)
{
	return sqrt(sqr(A.x-B.x) + sqr(A.y-B.y));
}

int n;
double d;

Point A[maxn];
Point P[maxn];

int read_case()
{
	scanf("%d%lf", &n, &d);
	if(!n) return 0;
	for(int i = 0; i < n; i++) scanf("%lf%lf", &A[i].x, &A[i].y);
	return 1;
}

void solve()
{
	for(int i = 0; i < n; i++)
	{
		if(A[i].y > d) { printf("-1\n"); return ; }
		double t = sqrt(sqr(d) - sqr(A[i].y));
		P[i].x = A[i].x-t, P[i].y = A[i].x+t;
	}
	sort(P, P+n);
	double right = P[0].y;
	int ans = 1;
	for(int i = 1; i < n; i++)
	{
		if(P[i].x > right)
		{
			ans++;
			right = P[i].y;
		}
	}
	printf("%d\n", ans);
}

int main()
{
	int times = 0;
	while(read_case())
	{
		printf("Case %d: ", ++times);
		solve();
	}
	return 0;
}
