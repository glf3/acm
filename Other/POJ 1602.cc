/*用并查集来确定当前deadline之前
有最近的可用时间*/
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

int flag;

void init()
{
    for(int i = 0; i < maxn; i++) fa[i] = i;
}

int read_case()
{
	init();
	int x, y;
	flag = 1;
	scanf("%d%d", &x, &y);
	if(x == -1) return 0;
	Union(x, y);
	while(scanf("%d%d", &x, &y) && (x || y))
	{
		scanf("%d%d", &x, &y);
		if(find(y) != y) flag = 0;
	}
	return 1;
}

void solve()
{
	printf(f? "is a tree.\n" : "is not a tree.\n");
}

int main()
{
	int times = 0;
	while(read_case())
	{
		printf("Case %d ", ++times);
		solve();
	}
	return 0;
}
