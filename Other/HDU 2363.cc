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

const int maxn = 1010;
const int maxm = 1010*1010;

const int INF = 0x3f3f3f3f;

struct Edge
{
	int v, w, cap;
	int next;
}edge[maxm];

int first[maxn], d[maxn];

int n, m;
int cnt;

void read_graph(int u, int v, int w)
{
	edge[cnt].v = v, edge[cnt].w = w;
	edge[cnt].next = first[u], first[u] = cnt++;
}

int cap[maxn], limit;

int spfa(int s, int t, int L, int R)
{
	queue<int> q;
	bool inq[maxn] = {0};
	for(int i = 1; i <= n; i++) d[i] = (i == s)? 0:INF;
	q.push(s);
	while(!q.empty())
	{
		int x = q.front(); q.pop();
		inq[x] = 0;
		if(cap[x] < L || cap[x] > R) continue;
		for(int e = first[x]; e != -1; e = edge[e].next)
		{
			int v = edge[e].v, w = edge[e].w;
			if(cap[v] < L || cap[v] > R) continue;
			if(d[v] > d[x] + w)
			{
				d[v] = d[x] + w;
				if(!inq[v])
				{
					inq[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return d[t] != INF;
}

void init()
{
	cnt = 0;
	memset(first, -1, sizeof(first));
}

struct node
{
	int x, y;
	bool operator < (const node &a) const
	{
		return (y-x) < (a.y-a.x);
	}
}A[110*110];

void read_case()
{
	init();
	scanf("%d%d", &n, &m);
	
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &cap[i]);
	}
	
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		read_graph(u, v, w);
		read_graph(v, u, w);
	}
}

void solve()
{
	read_case();
	int c = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = i+1; j <= n; j++)
		{
			A[c].x = min(cap[i], cap[j]);
			A[c++].y = max(cap[i], cap[j]);
		}
	}
	sort(A, A+c);
	int i;
	for(i = 0; i < c; i++) //在差允许的范围内才有点连边，然后最短路即是答案。
	{
		if(spfa(1, n, A[i].x, A[i].y)) break;
	}
	printf("%d %d\n", A[i].y-A[i].x, d[n]);
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
