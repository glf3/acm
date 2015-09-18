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

struct node
{
	int deadline, val;
	bool operator < (const node &a) const
	{
		return val > a.val;
	}
}A[maxn];

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

void init()
{
	for(int i = 0; i < maxn; i++) fa[i] = i;
}

void read_case()
{
	init();
	for(int i = 0; i < n; i++) scanf("%d%d", &A[i].val, &A[i].deadline);
	sort(A, A+n);
}

void solve()
{
	read_case();
	int ans = 0;
	for(int i = 0; i < n; i++)
	{
		int x = find(A[i].deadline);
		if(x > 0)
		{
			fa[x] = x-1;
			ans += A[i].val;
		}
	}
	printf("%d\n", ans);
}

int main()
{
	while(~scanf("%d", &n))
	{
		solve();
	}
	return 0;
}
