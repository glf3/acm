/*问题转换为单源最短路
注意数据范围*/
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

typedef unsigned long long LL;

const int maxn = 50010;
const int maxm = 50010;
const LL INF = (LL)1<<64-1;

struct Edge
{
	int v, w;
	int next;
}edge[4*maxm];

int first[maxn];
LL d[maxn];
LL weight[maxn];

int n, m;
int cnt;

int src, end;

void init()
{
	cnt = 0;
	memset(first, -1, sizeof(first));
	memset(d, 0, sizeof(d));
}

void read_graph(int u, int v, int w)
{
	edge[cnt].v = v, edge[cnt].w = w;
	edge[cnt].next = first[u], first[u] = cnt++;
}

void read_case()
{
	init();
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%llu", &weight[i]);
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		read_graph(u, v, w), read_graph(v, u, w);
	}
}

void spfa(int src)
{
	queue<int> q;
	bool inq[maxn] = {0};
	for(int i = 1; i <= n; i++) d[i] = (i == src)? 0:INF;
	q.push(src);
	while(!q.empty())
	{
		int x = q.front(); q.pop();
		inq[x] = 0;
		for(int e = first[x]; e != -1; e = edge[e].next)
		{
			int v = edge[e].v, w = edge[e].w;
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
}

void solve()
{
	read_case();
	spfa(1);
	LL ans = 0;
	for(int i = 1; i <= n; i++)
	{
		if(d[i] == INF) { printf("No Answer\n");  return ; }
		ans += LL(d[i] * weight[i]); 
	}
	printf("%llu\n", ans);
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
