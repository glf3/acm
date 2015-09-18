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

const int maxn = 1010;

int w[maxn][maxn];

int d[maxn];
int fa[maxn];

const int INF = 0x3f3f3f3f;

int n, m;

void init()
{
	memset(w, -INF, sizeof(w));
	for(int i = 1; i <= n; i++) fa[i] = i;
}

int find(int x)
{
	return x == fa[x]? x : find(fa[x]);
}

void Union(int x, int y)
{
	int i = find(x);
	int j = find(y);
	if(i != j) fa[i] = j;
}

int Prim(int src)
{
	int tot = 0;
	bool vis[maxn] = {0};
	for(int i = 1; i <= n; i++) d[i] = (i == src)? 0:-INF;
	for(int i = 1; i <= n; i++)
	{
		int x, m = -INF;
		for(int y = 1; y <= n; y++) if(!vis[y] && m < d[y]) m = d[x=y];
		vis[x] = 1;
		tot += m;
		for(int y = 1; y <= n; y++) d[y] = max(d[y], w[x][y]);
	}
	return tot;
}

void solve()
{
	init();
	for(int i = 0; i < m; i++)
	{
		int u, v, w1;
		scanf("%d%d%d", &u, &v, &w1);
		if(w[u][v] < w1) w[u][v] = w[v][u] = w1;
		Union(u, v);
	}
	int tot = 0;
	for(int i = 1; i <= n; i++) if(fa[i] == i) tot++;
	if(tot != 1) { printf("-1\n"); return ; }
	int ans = Prim(1);
	printf("%d\n", ans);
}

int main()
{
	while(~scanf("%d%d", &n, &m))
	{
		solve();
	}
	return 0;
}
