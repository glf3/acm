#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
using namespace std;

const int maxn = 20010;
const int INF = 0x3f3f3f3f;

struct Edge
{
	bool vis;
	int v, w;
	int next;
}edge[4*maxn];

int cnt;
int n;
int tot;

int first[maxn];

void init()
{
	cnt = 0;
	tot = 0;
	memset(first, -1, sizeof(first));
}

void read_graph(int u, int v)
{
	edge[cnt].v = v, edge[cnt].w = 0, edge[cnt].vis = 0;
	edge[cnt].next = first[u], first[u] = cnt++;
}

int dfs(int x)
{
	int sum = 0;
	for(int e = first[x]; e != -1; e = edge[e].next)
	{
		if(!edge[e].vis)
		{
			edge[e].vis = edge[e^1].vis = 1;
			edge[e].w += dfs(edge[e].v);
			edge[e^1].w = (n-edge[e].w);
		}
		sum += edge[e].w;
	}
	return sum+1;
}

int ans[maxn];

void cal(int y)
{
	y = n/2;
	for(int i = 1; i <= n; i++)
	{
		int Max = -INF;
		for(int e = first[i]; e != -1; e = edge[e].next)
		{
			Max = max(Max, edge[e].w);
		}
		if(y >= Max) ans[tot++] = i;
	}
}

void read_case()
{
	init();
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		read_graph(u, v), read_graph(v, u);
	}
}

void solve()
{
	read_case();
	dfs(1);
	cal(n/2);
	if(tot == 0) { printf("NONE\n"); return ;}
	sort(ans, ans+tot);
	for(int i = 0; i < tot; i++) printf("%d\n", ans[i]);
}

int main()
{
	while(~scanf("%d", &n))
	{
		solve();
	}
	return 0;
}
