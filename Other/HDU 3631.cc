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

const int maxn = 330;
const int INF = 0x3f3f3f3f;

bool mark[maxn];
int d[maxn][maxn];

int n, m, q;

void init()
{
	memset(mark, 0, sizeof(mark));
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
		d[i][j] = (i == j)? 0:INF;
}

int read_case()
{
	scanf("%d%d%d", &n, &m, &q);
	if(!n) return 0;
	init();
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if(d[u][v] > w) d[u][v] = w;
	}
	return 1;
}

void Floyd(int k)
{
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
	d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

void solve()
{
	while(q--)
	{
		int op;
		scanf("%d", &op);
		if(op == 0)
		{
			int o;
			scanf("%d", &o);
			if(mark[o]) { printf("ERROR! At point %d\n", o); continue; }
			mark[o] = true;
			Floyd(o);
		}
		else
		{
			int u, v;
			scanf("%d%d", &u, &v);
			if(!mark[u] || !mark[v]) { printf("ERROR! At path %d to %d\n", u, v); continue; }
			int ans = d[u][v];
			if(ans == INF) printf("No such path\n");
			else printf("%d\n", ans);
		}
	}
}

int main()
{
	int times = 0;
	while(read_case())
	{
		if(times) printf("\n");
		printf("Case %d:\n", ++times);
		solve();
	}
	return 0;
}
