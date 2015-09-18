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

int n;

bool vis[maxn];

void init()
{
    for(int i = 0; i < maxn; i++) fa[i] = i, rank[i] = 1;
    memset(vis, 0, sizeof(vis));
}

int flag;

int flag2;

int times;

int read_case()
{
	init();
	int x, y;
	flag = 1;
	flag2 = 1;
	scanf("%d%d", &x, &y);
	if(x == -1) return 0;
	if(x == 0 && y == 0) { flag2 = 0; printf("Case %d is a tree.\n", ++times); return 1; }
	vis[x] = vis[y] = 1;
	if(x == y) flag = 0;
	else Union(x, y);
	while(scanf("%d%d", &x, &y) && (x || y))
	{
		vis[x] = vis[y] = 1;
		if(find(x) == find(y)) flag = 0;
		Union(x, y);
	}
	return 1;
}

void solve()
{
	int tot = 0;
	for(int i = 1; i < maxn; i++) if(vis[i] && fa[i] == i) tot++;
	if(tot != 1) flag = 0;
	if(flag2)
	{
		if(flag) printf("is a tree.\n");
		else printf("is not a tree.\n");
	}
}

int main()
{
	times = 0;
	while(read_case())
	{
		if(flag2) printf("Case %d ", ++times);
		solve();
	}
	return 0;
}
