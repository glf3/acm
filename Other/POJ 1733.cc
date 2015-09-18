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

const int maxn = 22222;
int fa[maxn], rank[maxn];
int l[maxn], r[maxn], c[maxn];
int X[maxn];

int find(int x)
{
	if(fa[x] == x) return x;
	int p = fa[x];
	fa[x] = find(fa[x]);
	rank[x] ^= rank[p];
	return fa[x];
}

int Union(int x, int y, int d)
{
	int fx = find(x), fy = find(y);
	if(fx == fy) return (rank[x]^rank[y]) == d;
	fa[fx] = fy;
	rank[fx] = d^(rank[x]^rank[y]);
	return 1;
}

int BSearch(int x, int y, int v)
{
	while(x <= y)
	{
		int m = x+(y-x)/2;
		if(X[m] == v) return m;
		else if(X[m] < v) x = m+1;
		else y = m-1;
	}
	return -1;
}

int n, m;
int cnt;

void init()
{
	cnt = 0;
	for(int i = 0; i < maxn; i++) fa[i] = i, rank[i] = 0;
}

void read_case()
{
	init();
	char op[15];
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d%s", &l[i], &r[i], op);
		X[cnt++] = l[i]-1;
		X[cnt++] = r[i];
		if(op[0] == 'e') c[i] = 0;
		else c[i] = 1;
	}
	sort(X, X+cnt);
	cnt = unique(X, X+cnt)-X;
}

void solve()
{
	read_case();
	int flag = 0;
	for(int i = 1; i <= m; i++)
	{
		int L = BSearch(0, cnt-1, l[i]-1);
		int R = BSearch(0, cnt-1, r[i]);
		if(!Union(L, R, c[i]))
		{
			flag = 1;
			printf("%d\n", i-1);
			break;
		}
	}
	if(!flag) printf("%d\n", m);
}

int main()
{
	while(~scanf("%d%d", &n, &m))
	{
		solve();
	}
	return 0;
}
