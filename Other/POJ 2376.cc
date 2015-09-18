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

int n, T;

const int maxn = 25010;

struct node
{
	int x, y;
	bool operator < (const node &a) const
	{
		return x < a.x;
	}
};

node A[maxn];

void read_case()
{
	for(int i = 0; i < n; i++) scanf("%d%d", &A[i].x, &A[i].y);
	sort(A, A+n);
}

void solve()
{
	read_case();
	int ans = 0;
	int left = 0, right = 0;
	int flag, pos = 0;
	for(;;)
	{
		if(left >= T) break;
		flag = 0;
		for(int i = pos; i < n; i++)
		{
			if(A[i].x <= left+1)
			{
				if(A[i].y > right)
				{
					pos = i;
					right = A[i].y;
					flag = 1;
				}
			}
		}
		if(flag) ans++, left = right;
		else break;
	}
	if(flag) printf("%d\n", ans);
	else printf("-1\n");
}

int main()
{
	while(~scanf("%d%d", &n, &T))
	{
		solve();
	}
	return 0;
}
