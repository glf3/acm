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

const int maxn = 1010;
const int maxm = 10010;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int v, w;
	int next;
}edge[maxm];

int first[maxn];
int d[maxn][2];
bool vis[maxn][2];
int R[maxn][2];

int n, m;
int cnt;

int src, end;

void init()
{
	cnt = 0;
	memset(first, -1, sizeof(first));
	memset(d, 0, sizeof(d));
	memset(vis, 0, sizeof(vis));
	memset(R, 0, sizeof(R));
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
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		read_graph(u, v, w);
	}
	scanf("%d%d", &src, &end);
}

int Dijkstra(int src)
{
	for(int i = 1; i <= n; i++)
	{
		d[i][0] = d[i][1] = INF;
	}
	d[src][0] = 0;
	R[src][0] = 1;
	for(int i = 1; i < 2*n; i++)
	{
		int x, m = INF;
		int flag;
		for(int y = 1; y <= n; y++)
		{
			if(!vis[y][0] && m > d[y][0]) m = d[x=y][0], flag = 0;
			else if(!vis[y][1] && m > d[y][1]) m = d[x=y][1], flag = 1;
		}
		vis[x][flag] = 1;
		for(int e = first[x]; e != -1; e = edge[e].next)
		{
			int v = edge[e].v, w = edge[e].w;
			if(d[v][0] > m + w)
			{
				d[v][1] = d[v][0];
				R[v][1] = R[v][0];
				d[v][0] = m + w;
				R[v][0] = R[x][flag];
			}
			else if(d[v][0] == m + w)
			{
				R[v][0] += R[x][flag];
			}
			else if(d[v][1] > m + w)
			{
				d[v][1] = m + w;
				R[v][1] = R[x][flag];
			}
			else if(d[v][1] == m + w)
			{
				R[v][1] += R[x][flag];
			}
		}
	}
	if(d[end][0]+1 == d[end][1]) return R[end][0] + R[end][1];
	return R[end][0];
}

void solve()
{
	read_case();
	int ans = Dijkstra(src);
	printf("%d\n", ans);
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
