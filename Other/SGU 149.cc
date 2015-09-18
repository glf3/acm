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

const int maxn = 10010;

struct Edge
{
	int v, w;
	int next;
}edge[maxn*4];

int n, cnt;

int first[maxn];
int fa[maxn];
int best[maxn];
int d[maxn][3];
int falen[maxn];

void init()
{
	cnt = 0;
	memset(first, -1, sizeof(first));
	memset(best, 0, sizeof(best));
}

void read_graph(int u, int v)
{
	edge[cnt].v = v;
	edge[cnt].next = first[u], first[u] = cnt++;
}

void dfs1(int u)
{
	d[u][0] = 0;
	for(int e = first[u]; e != -1; e = edge[e].next)
	{
		int v = edge[e].v;
		int w = falen[v];
		dfs1(v);
		if(d[u][0] < d[v][0] + w)
		{
			d[u][0] = d[v][0] + w;
			best[u] = v;
		}
	}
	d[u][1] = 0;
	for(int e = first[u]; e != -1; e = edge[e].next)
	{
		int v = edge[e].v;
		int w = falen[v];
		if(best[u] == v) continue;
		d[u][1] = max(d[u][1], d[v][0]+w);
	}
}

void dfs2(int u)
{
	d[u][2] = 0;
	if(u == best[fa[u]]) d[u][2] = max(d[u][2], d[fa[u]][1]);
	else d[u][2] = max(d[u][2], d[fa[u]][0]);
	d[u][2] = max(d[u][2], d[fa[u]][2]);
	d[u][2] += falen[u];
	for(int e = first[u]; e != -1; e = edge[e].next)
	{
		int v = edge[e].v;
		dfs2(v);
	}
}

void read_case()
{
	init();
	scanf("%d", &n);
	for(int u = 2; u <= n; u++)
	{
		int v, w;
		scanf("%d%d", &v, &w);
		read_graph(v, u);
		fa[u] = v;
		falen[u] = w;
	}
	d[0][0] = d[0][1] = d[0][2] = 0;
	fa[1] = falen[1] = 0;
}

void solve()
{
	read_case();
	dfs1(1), dfs2(1);
	for(int i = 1; i <= n; i++)
	{
		printf("%d\n", max(d[i][0], d[i][2]));
	}
}

int main()
{
	solve();
	return 0;
}
