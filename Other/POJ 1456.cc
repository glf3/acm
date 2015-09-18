/*求解损失最小，总值减去最小即可*/
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <map>
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

bool vis[maxn];

int n, s;

void init()
{
	s = 0;
	memset(vis, 0, sizeof(vis));
}

void read_case()
{
	init();
	for(int i = 0; i < n; i++)
	{
		scanf("%d%d", &A[i].val, &A[i].deadline);
		s += A[i].val;
	}
	sort(A, A+n);
}

void solve()
{
	read_case();
	int ans = 0;
	for(int i = 0; i < n; i++)
	{
		int flag = 0;
		for(int j = A[i].deadline; j >= 1; j--) if(!vis[j])
		{
			vis[j] = flag = 1;
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
