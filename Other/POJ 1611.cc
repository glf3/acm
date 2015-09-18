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

const int maxn = 30010;

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
	for(int i = 0; i < n ;i++) fa[i] = i, rank[i] = 1;
}

int read_case()
{
	scanf("%d%d", &n, &m);
	if(!n) return 0;
	init();
	while(m--)
	{
		int t;
		scanf("%d", &t);
		int x, y;
		scanf("%d", &x);
		for(int i = 1; i < t; i++)
		{
			scanf("%d", &y);
			Union(x, y);
		}
	}
	return 1;
}

void solve()
{
	int ans = rank[find(0)];
	printf("%d\n", ans);
}

int main()
{
	while(read_case())
	{
		solve();
	}
	return 0;
}
