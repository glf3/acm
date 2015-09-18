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

struct node
{
	int x, y;
	bool vis;
}A[maxn];

int find(int x)
{
	return fa[x] == x? x : fa[x] = find(fa[x]);
}

void Union(int x, int y)
{
	x = find(x), y = find(y);
	if(x == y) return ;
	if(rank[x] > rank[y])
	{
		rank[x] += rank[y];
		fa[y] = x;
	}
	else
	{
		fa[x] = y;
		if(rank[x] == rank[y]) rank[x]++;
	}
}

int n, m;

int cut[maxn];
int ans[maxn];

void init()
{
	for(int i = 0; i <= n; i++) fa[i] = i, rank[i] = 1;
}

void solve()
{
	init();
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &A[i].x, &A[i].y);
		A[i].vis = 1;
	}
	int q;
	scanf("%d", &q);
	for(int i = 1; i <= q; i++)
	{
		scanf("%d", &cut[i]);
		A[cut[i]].vis = 0;
	}
	int link = 0;
	for(int i = 1; i <= m; i++) if(A[i].vis)
	{
		int x = A[i].x, y = A[i].y;
		if(find(x) != find(y))
		{
			link++;
			Union(x, y);
		}
	}
	for(int i = q; i >= 1; i--)
	{
		ans[i] = n-link;
		int x = A[cut[i]].x, y = A[cut[i]].y;
		if(find(x) != find(y))
		{
			link++;
			Union(x, y);
		}
	}
	int first = 1;
	for(int i = 1; i <= q; i++)
	{
		if(first) { printf("%d", ans[i]); first = 0; }
		else printf(" %d", ans[i]);
	}
	printf("\n");
}

int main()
{
	scanf("%d%d", &n, &m);
	solve();
	return 0;
}
