/*空树也是树，一个树只能有一个树根。*/
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

const int maxn = 10010;

int rank[maxn];
int fa[maxn];
int move[maxn];

int find(int x)
{
	if(fa[x] == x) return x;
	int p = fa[x];
	fa[x] = find(fa[x]);
	move[x] += move[p];
	return fa[x];
}

void Union(int x, int y)
{
	x = find(x);
	y = find(y);
	if(x == y) return ;
	fa[x] = y;
	rank[y] += rank[x];
	move[x]++;
}

int n, m;

void init()
{
	for(int i = 1; i <= n; i++) fa[i] = i, rank[i] = 1, move[i] = 0;
}

void read_case()
{
	scanf("%d%d", &n, &m);
	init();
}

void solve()
{
	read_case();
	while(m--)
	{
		int x, y;
		char op[5];
		scanf("%s", op);
		if(op[0] == 'T')
		{
			scanf("%d%d", &x, &y);
			Union(x, y);
		}
		else
		{
			scanf("%d", &x);
			int xx = find(x);
			printf("%d %d %d\n", xx, rank[xx], move[x]);
		}
	}
}

int main()
{
	int T, times = 0;
	scanf("%d", &T);
	while(T--)
	{
		printf("Case %d:\n", ++times);
		solve();
	}
	return 0;
}
