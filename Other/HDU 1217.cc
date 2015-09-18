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

double d[maxn][maxn];

void Floyd(int n)
{
	for(int k = 1; k <= n; k++)
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				d[i][j] = max(d[i][j], d[i][k]*d[k][j]);
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
			d[i][j] = (i == j)? 1 : 0;
		}
	}
}

char str[maxn];

int read_case()
{
	scanf("%d", &n);
	if(!n) return 0;
	init();
	for(int i = 0; i < n; i++)
	{
		scanf("%s", str);
		if(!Map[str]) Map[str] = ++tot;
	}
	scanf("%d", &m);
	
	char s1[maxn], s2[maxn];
	double w;
	
	for(int i = 0; i < m; i++)
	{
		scanf("%s%lf%s", s1, &w, s2);
		int u = Map[s1], v = Map[s2];
		d[u][v] = w;
	}
	return 1;
}

void solve()
{
	Floyd(n);
	for(int i = 1; i <= n; i++) if(d[i][i] > 1) { printf("Yes\n"); return ;}
	printf("No\n");
}

int main()
{
	int times = 0;
	while(read_case())
	{
		printf("Case %d: ", ++times);
		solve();
	}
	return 0;
}
