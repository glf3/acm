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

const int maxn = 50010;

int rank[maxn];
int fa[maxn];

int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void Union(int x, int y)
{
	x = find(x), y = find(y);
	if(x == y) return ;
	if(rank[x] > rank[y])
	{
		fa[y] = x;
		rank[x] += rank[y];
	}
	else
	{
		fa[x] = y;
		rank[y] += rank[x];
	}
}

int n, m;

void init()
{
	for(int i = 1; i <= n ;i++) fa[i] = i, rank[i] = 1;
}

int read_case()
{
	scanf("%d%d", &n, &m);
	if(!n) return 0;
	init();
	while(m--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		Union(x, y);
	}
	return 1;
}

void solve()
{
	int ans = 0;
	for(int i = 1; i <= n; i++) if(fa[i] == i) ans++;
	printf("%d\n", ans);
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
