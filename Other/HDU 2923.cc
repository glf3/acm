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

const int maxn = 150;
const int INF = 0x3f3f3f3f;

int d[maxn][maxn];

void Floyd(int n)
{
	for(int k = 1; k <= n; k++)
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
			}
		}
	}
}

int n, m, q;

map<string, int> Map;

int tot;

void init()
{
	tot = 0;
	Map.clear();
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			d[i][j] = (i == j)? 0:INF;
		}
	}
}

int S[1100];

char str[maxn];

int read_case()
{
	scanf("%d%d%d%*c", &n, &q, &m);
	if(!n && !q && !m) return 0;
	init();
	for(int i = 0; i <= q; i++)
	{
		scanf("%s", str);
		if(!Map[str]) Map[str] = ++tot;
		S[i] = Map[str];
	}
	
	char s1[maxn], s2[maxn], s3[maxn];
	
	for(int i = 0; i < m; i++)
	{
		int u, v, w;
		scanf("%s%s%s", s1, s2, s3);
		if(!Map[s1]) Map[s1] = ++tot;
		if(!Map[s3]) Map[s3] = ++tot;
		u = Map[s1], v = Map[s3];
		sscanf(s2+2, "%d", &w);
		if(s2[0] == '<' && w < d[v][u]) d[v][u] = w;
		if(s2[strlen(s2)-1] == '>' && w < d[u][v]) d[u][v] = w;	
	}
	return 1;
}

void solve()
{
	Floyd(n);
	int ans = 0;
	for(int i = 1; i <= q; i++) ans += (d[1][S[i]]+d[S[i]][1]);
	printf("%d\n", ans);
}

int main()
{
	int times = 0;
	while(read_case())
	{
		printf("%d. ", ++times);
		solve();
	}
	return 0;
}
