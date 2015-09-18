/*实际上求最少输多少局*/
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

int n, m;

const int maxn = 1010;

int A[maxn], B[maxn];

bool vis[maxn];

void init()
{
	memset(vis, 0, sizeof(vis));
}

int read_case()
{
	init();
	scanf("%d%d", &m, &n);
	if(!n) return 0;
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &A[i]);
		vis[A[i]] = 1;
	}
	sort(A, A+n);
	return 1;
}

void solve()
{
	int ans = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = A[i]; j <= n*m; j++) //最大的数一定为N*M 
		{
			if(!vis[j]) //存在没被标记的说明牌中一定有一个数比A[i]大。 
			{
				vis[j] = 1;
				ans++;
				break;
			}
		}
	}
	printf("%d\n", n-ans);
}

int main()
{
	int times = 0;
	while(read_case())
	{
		printf("Case %d: ", ++times);
		solve();
	}
	return 0;
}
