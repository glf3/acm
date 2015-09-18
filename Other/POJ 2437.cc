/*将左区间值从小到大排序，
然后向右找当前覆盖区间
的最大值即可。*/
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


const int maxn = 10030;
const int INF = 0x3f3f3f3f;

typedef __int64 LL;

int n;
LL L;

struct node
{
	LL x, y;
	bool operator < (const node &a) const
	{
		return x < a.x;
	}
}A[maxn];

void read_case()
{
	for(int i = 0; i < n; i++) scanf("%I64d%I64d", &A[i].x, &A[i].y);
	sort(A, A+n);
}

void solve()
{
	read_case();
	int i, pos = 0;
	int ans = 0;
	LL right = -INF;
	for(i = 0; i < n; )
	{
		right = max(right, A[i].x);
		int c = (int)ceil(1.0*(A[i].y-right)/L);
		right += L*c;
		ans += c;
		while(i < n && A[i].y <= right) i++;
	}
	printf("%d\n", ans);
}

int main()
{
	while(~scanf("%d%d", &n, &L))
	{
		solve();
	}
	return 0;
}
