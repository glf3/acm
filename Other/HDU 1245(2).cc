#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

const int maxn = 110;
const double eps = 1e-6;
const double INF = 1e60;

struct node
{
	double x, y;
}A[maxn];

int dcmp(double x) { if(fabs(x) < eps) return 0; else return x < 0? -1 : 1; }

double sqr(double x) { return x*x; }

double Dist1(node a) { return fabs(sqrt(sqr(a.x) + sqr(a.y)) - 7.50) ; } //到点的距离
double Dist2(node a, node b) { return sqrt(sqr(a.x-b.x) + sqr(a.y-b.y)) ; } //同类点之间的距离 
double Dist3(node a) { return dcmp(fabs(50-fabs(a.x)) - fabs(50-fabs(a.y))) > 0 ? fabs(50-fabs(a.y)) : fabs(50-fabs(a.x)); }
 //到终点的距离
  
int n, D;

double d[maxn][maxn];
double cost[maxn];
int step[maxn];

void read_case()
{
	for(int i = 1; i <= n; i++) scanf("%lf%lf", &A[i].x, &A[i].y);
}

void build()
{
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= n; j++) d[i][j] = Dist2(A[i], A[j]);
	
	for(int i = 1; i <= n; i++)
	{
		d[0][i] = Dist1(A[i]);
		d[i][0] = d[n+1][i] = 0;
		d[i][n+1] = Dist3(A[i]);
	}
	d[0][n+1] = INF;
}

void bfs(int s, int t)
{
	int cur, next;
	queue<int> q;
	for(int i = 0; i <= n+1; i++) cost[i] = (i == s)? 0:INF;
	step[0] = 0;
	q.push(s);
	while(!q.empty())
	{
		cur = q.front(); q.pop();
		for(next = 1; next <= n+1; next++)
		{
			if(dcmp(d[cur][next] - D) <= 0 && 
			  (dcmp(cost[cur] + d[cur][next] - cost[next]) < 0 || 
			  (dcmp(cost[cur] + d[cur][next] - cost[next]) <= 0 && dcmp(step[cur]+1 < step[next]) < 0)))
			  { //能使得距离减少或者在距离相等的情况下使得步数减少则入队 
					cost[next] = cost[cur] + d[cur][next];
					step[next] = step[cur]+1;
					q.push(next);
			  }
		}
	}
}

void solve()
{
	read_case();
	if(dcmp(D-42.50) >= 0) { printf("42.5 1\n"); return ; } //一步跳出去 
	build();
	bfs(0, n+1);
	if(dcmp(cost[n+1] - INF) < 0) printf("%.2lf %d\n", cost[n+1], step[n+1]);
	else printf("can't be saved\n");
}

int main()
{
	while(~scanf("%d%d", &n, &D))
	{
		solve();
	}
	return 0;
}
