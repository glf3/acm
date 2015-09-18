/*有点难度的贪心
需要清晰的思路*/
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

const int maxn = 1010;

const double INF = 0x3f3f3f3f;

struct node
{
	double val;
	int w, num;
	int fa;
}A[maxn];

int root, n;

int read_case()
{
	scanf("%d%d", &n, &root);
	if(!n && !root) return 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &A[i].w);
		A[i].val = 1.0*A[i].w;
		A[i].num = 1;
	}
	for(int i = 1; i <= n-1; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		A[v].fa = u;
	}
	return 1;
}

void solve()
{
	int ans = 0;
	for(int t = 1; t <= n-1; t++)
	{
		int pos;
		double max = 0;
		for(int i = 1; i <= n; i++)
		{
			if(i == root) continue;
			if(A[i].val > max)
			{
				max = A[i].val;
				pos = i;
			}
		}
		int fa = A[pos].fa;
		while(A[fa].num == 0) fa = A[fa].fa;
		ans += A[pos].w * A[fa].num;
		A[fa].num += A[pos].num;
		A[fa].w += A[pos].w;
		A[fa].val = 1.0*A[fa].w / A[fa].num;
		A[pos].val = A[pos].num = 0;
	}
	ans += A[root].w;
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
