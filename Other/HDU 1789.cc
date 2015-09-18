/*按照罚分降序排序，尽量安排到deadline,
如果不行，则往前推，如果全安排，则罚分。*/
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

const int maxn = 1010;

struct node
{
	int deadline, val;
	bool operator < (const node &a) const
	{
		return val > a.val;
	}
};

node A[maxn];
bool vis[maxn];

int n;

void init()
{
	memset(vis, 0, sizeof(vis));
}

void read_case()
{
	init();
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", &A[i].deadline);
	for(int i = 0; i < n; i++) scanf("%d", &A[i].val);
	sort(A, A+n);
}

void solve()
{
	read_case();
	int ans = 0;
	for(int i = 0; i < n; i++)
	{
		int flag = 0;
		for(int j = A[i].deadline; j >= 1; j--)
		{
			if(!vis[j])
			{
				vis[j] = flag = 1;
				break;
			}
		}
		if(!flag) ans += A[i].val;
	}
	printf("%d\n", ans);
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
