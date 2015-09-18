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
#include <map>
using namespace std;

const double eps = 1e-6;
const int maxn = 110;
const double INF = 0x3f3f3f3f;

struct Point
{
	double x, y;
	Point(double x=0, double y=0): x(x), y(y) {};
};

int dcmp(double x)
{
	if(fabs(x) < eps) return 0; else return x < 0? -1 : 1; 
}

double sqr(double x)
{
	return x*x;
}

double dist1(Point a) //源点 
{
	return fabs(sqrt(sqr(a.x) + sqr(a.y))-7.5);
}

double dist2(Point a, Point b) //同类 
{
	return sqrt(sqr(a.x-b.x) + sqr(a.y-b.y));
}

double dist3(Point a) //终点 
{
	double d1 = fabs(50-fabs(a.x)), d2 = fabs(50-fabs(a.y));
	if(dcmp(d1-d2) > 0) return d2; else return d1;
}

int n;
double D;

Point read_point()
{
	Point A;
	scanf("%lf%lf", &A.x, &A.y);
	return A;
}

Point P[maxn];
double d[maxn][maxn];

void read_case()
{
	P[0] = Point(0, 0);
	for(int i = 1; i <= n; i++) P[i] = read_point();
	for(int i = 1; i <= n; i++)
	{
		d[i][i] = 0;
		for(int j = i+1; j <= n; j++)
		{
			d[i][j] = d[j][i] = dist2(P[i], P[j]);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		d[0][i] = dist1(P[i]);
		d[i][0] = d[n+1][i] = 0.0;
		d[i][n+1] = dist3(P[i]);
	}
	d[0][n+1] = INF;
}

double cost[maxn];
int step[maxn];

void bfs(int s)
{
	queue<int> Q;
	int cur, next;
	for(int i = 0; i <= n+1; i++) cost[i] = (i == s)? 0:INF;
	step[s] = 0;
	Q.push(s);
	while(!Q.empty())
	{
		cur = Q.front(); Q.pop();
		for(int next = 1; next <= n+1; next++)
		{
			if(dcmp(d[cur][next]-D) <= 0 && ((dcmp(d[cur][next]+cost[cur]-cost[next]) < 0) || 
			  (dcmp(d[cur][next]+cost[cur]-cost[next]) <= 0 && step[cur]+1 < step[next])))
			{
				cost[next] = d[cur][next] + cost[cur];
				step[next] = step[cur]+1;
				Q.push(next);
			}
		}
	}
}

void solve()
{
	read_case();
	if(dcmp(D-42.5) > 0) { printf("42.5 1\n"); return ; }
	bfs(0);
	if(dcmp(cost[n+1]-INF) >= 0) printf("can't be saved\n");
	else printf("%.2lf %d\n", cost[n+1], step[n+1]);
}

int main()
{
	while(~scanf("%d%lf", &n, &D))
	{
		solve();
	}
	return 0;
}
