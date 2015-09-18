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

const int maxn = 20;
const int INF = 0x3f3f3f3f;

typedef long long LL;

LL minv[maxn], maxv[maxn];

LL cmp(LL a, LL b)
{
	return a > b;
}

LL n1, n2, n;

void init()
{
	for(LL i = 0; i < 15; i++) maxv[i] = 0;
	for(LL i = 0; i < 15; i++) minv[i] = INF;
}

LL read_case()
{
	scanf("%lld%lld%lld", &n1, &n2, &n);
	if(n1 == 0 && n2 == 0 && n == 0) return 0;
	return 1;
}

void solve()
{
	init();
	LL ans = 0;
	for(LL i = 0; i < n; i++)
	{
		LL t;
		scanf("%lld", &t), ans += t;
		sort(maxv, maxv+n1);
		if(t > maxv[0]) maxv[0] = t;
		sort(minv, minv+n2, cmp);
		if(t < minv[0]) minv[0] = t;
	}
	for(LL i = 0; i < n1; i++) ans -= maxv[i];
	for(LL i = 0; i < n2; i++) ans -= minv[i];
	printf("%.6lf\n", 1.0*ans/(n-n1-n2));
}

int main()
{
	while(read_case())
	{
		solve();
	}
	return 0;
}
