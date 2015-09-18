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

struct node
{
	int deadline, val;
	bool operator < (const node &a) const
	{
		return val > a.val;
	}
}A[maxn];

int s;

int n;

void read_case()
{
	s = 0;
	for(int i = 0; i < n; i++)
	{
		scanf("%d%d", &A[i].val, &A[i].deadline);
		s += A[i].val;
	}
}

bool vis[maxn];

void init()
{
	memset(vis, 0, sizeof(vis));
}

void solve()
{
	init();
	read_case();
	sort(A, A+n);
	int ans = 0;
	for(int i = 0; i < n; i++)
	{
		int flag = 0;
		for(int j = A[i].deadline; j >= 1; j--) if(!vis[j])
		{
			flag = 1;
			vis[j] = 1;
			break;
		}
		if(!flag) ans += A[i].val;
	}
	printf("%d\n", s-ans);
}

int main()
{
	while(~scanf("%d", &n))
	{
		solve();
	}
	return 0;
}
