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
int up[maxn];

int find(int x)
{
	if(fa[x] == x) return x;
	int p = fa[x];
	fa[x] = find(fa[x]);
	up[x] += up[p];
	return fa[x];
}

void Union(int x, int y)
{
	int fx = find(x), fy = find(y);
	if(fx == fy) return ;
	fa[fy] = fx;
	up[fy] = rank[fx];
	rank[fx] += rank[fy];
}

int n;

void init()
{
	for(int i = 0; i <= n; i++) fa[i] = i, rank[i] = 1, up[i] = 0;
}

void read_case()
{
	scanf("%d", &n);
}

void solve()
{
	read_case();
	init();
	int m = n;
	while(m--)
	{
		char op[5];
		int x, y;
		scanf("%s", op);
		if(op[0] == 'M')
		{
			scanf("%d%d", &x, &y);
			Union(x, y);
		}
		else
		{
			scanf("%d", &x);
			int ans = rank[find(x)] - up[x] - 1;
			printf("%d\n", ans);
		}
	}
}

int main()
{
	solve();
	system("pause");
	return 0;
}
