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

const int maxn = 70;

typedef long long LL;

int n;

char s[maxn];
LL t;

char ans[maxn];

void read_case()
{
	scanf("%d %s %lld", &n, s, &t);
}

void solve()
{
	read_case();
	LL x = t;
	if(t < 0)
	{
		x = -x;
		for(int i = 0; i < n; i++)
			if(s[i] == 'p') s[i] = 'n';
			else s[i] = 'p';
	}
	for(int i = n-1; i >= 0; i--)
	{
		if(x & 1)
		{
			ans[i] = '1';
			if(s[i] == 'p') x = x-1;
			else x = x+1;
			x = x >> 1;
		}
		else ans[i] = '0', x = x >> 1;
	}
	ans[n] = '\0';
	if(x != 0) printf("Impossible\n");
	else printf("%s\n", ans);
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
