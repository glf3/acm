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
const int kind = 3;

int fa[maxn];
int rank[maxn];

int find(int x)
{
	if(fa[x] == x) return x;
	int p = fa[x];
	fa[x] = find(fa[x]);
	rank[x] = (rank[x]+rank[p])%3;
	return fa[x];
}

void Union(int x, int y, int d)
{
	int fx = find(x), fy = find(y);
	fa[fx] = fy;
	rank[fx] = (rank[y]-rank[x]+kind+d)%kind;
}

int n, m;

void init()
{
	for(int i = 0; i <= n; i++) fa[i] = i, rank[i] = 0;
}

void solve()
{
	init();
	int ans = 0;
	while(m--)
	{
		int d, x, y;
		scanf("%d%d%d", &d, &x, &y);
		if(x > n || y > n || (d == 2 && x == y)) { ans++; continue; }
		int fx = find(x), fy = find(y);
		if(fx == fy)
		{
			if((rank[x]-rank[y]+kind)%kind != d-1) ans++;
		}
		else Union(x, y, d-1);
	}
	printf("%d\n", ans);
}

int main()
{
	scanf("%d%d", &n, &m);
	solve();
	system("pause");
	return 0;
}
