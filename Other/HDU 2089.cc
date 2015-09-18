/*选择先结束的即可*/
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

const int maxn = 110;

struct node
{
	int x, y;
	bool operator < (const node &a) const
	{
		if(y != a.y) return y < a.y;
		return x < a.x;
	}
}A[maxn];

int n;

int read_case()
{
	scanf("%d", &n);
	if(!n) return 0;
	for(int i = 0; i < n; i++) scanf("%d%d", &A[i].x, &A[i].y);
	sort(A, A+n);
	return 1;
}

void solve()
{
	int ans = 1;
	int left = A[0].x, right = A[0].y;
	for(int i = 1; i < n; i++)
	{
		if(A[i].x >= right)
		{
			ans++;
			right = A[i].y;
		}
	}
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
