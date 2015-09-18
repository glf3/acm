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

const int maxn = 110;
const int INF = 0x3f3f3f3f;

int G[maxn][maxn];
int d[maxn][maxn];

int n, m;

void init()
{
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			G[i][j] = d[i][j] = INF;
		}
	}
}

int Floyd()
{
	int mincircle = INF;
	for(int k = 1; k <= n; k++)
	{
		for(int i = 1; i < k; i++)
		{
			for(int j = i+1; j < k; j++) if(d[i][j] != INF && G[j][k] != INF && G[k][i] != INF) 
			{
				mincircle = min(mincircle, d[i][j] + G[j][k] + G[k][i]);
			}
		}
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++) if(d[i][k] != INF && d[k][j] != INF)
			{
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}
	return mincircle;
}

void solve()
{
	init();
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if(G[u][v] > w)
		{
			G[u][v] = G[v][u] = w;
			d[u][v] = d[v][u] = w;
		}
	}
	int ans = Floyd();
	if(ans != INF) printf("%d\n", ans);
	else if(ans >= INF) printf("It's impossible.\n");
}

int main()
{
	while(~scanf("%d%d", &n, &m))
	{
		solve();
	}
}
