/*条件是两两不同，暴力枚举即可。*/
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

typedef __int64 LL;

LL A[maxn];

int n;

void read_case()
{
	for(int i = 0; i < n; i++) scanf("%I64d", &A[i]);
	sort(A, A+n);
}

void solve()
{
	read_case();
	LL ans = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = i+1; j < n; j++)
		{
			ans += A[j]-A[i];
		}
	}
	printf("%I64d\n", ans*2);
}

int main()
{
	while(~scanf("%d", &n))
	{
		solve();
	}
	return 0;
}
