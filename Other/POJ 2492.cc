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

const int maxn = 100010;

int fa[maxn];
int rank[maxn];

int find(int x)
{
	if(fa[x] == x) return x;
	int p = fa[x];
	fa[x] = find(fa[x]);
	rank[x] = rank[x]^rank[p];
	return fa[x];
}

void Union(int x, int y, int d)
{
	int fx = find(x), fy = find(y);
	fa[fx] = fy;
	rank[fx] = d^(rank[x]^rank[y]);
}

int n, m;

void init()
{
	for(int i = 0; i <= n; i++) fa[i] = i, rank[i] = 0;
}

void read_case()
{
	scanf("%d%d", &n, &m);
	init();
}

void solve()
{
	read_case();
	int flag = 0;
	while(m--)
	{
		char op[3];
		int x, y;
		scanf("%d%d", &x, &y);
		int fx = find(x), fy = find(y);
		if(fx == fy)
		{
			if(rank[x] ^ rank[y] != 1) flag = 1;
		}
		else Union(x, y, 1);
	}
	if(flag) printf("Suspicious bugs found!\n");
	else printf("No suspicious bugs found!\n");
	printf("\n");
}

int main()
{
	int T, times = 0;
	scanf("%d", &T);
	while(T--)
	{
		printf("Scenario #%d:\n", ++times);
		solve();
	}
	return 0;
}
