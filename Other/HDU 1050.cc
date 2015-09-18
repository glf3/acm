/*找经过次数最大的房间*/
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

const int maxn = 210;

struct node
{
	int x, y;
}A[maxn];

int vis[maxn];

void init()
{
	memset(vis, 0, sizeof(vis));
}

void read_case()
{
	init();
	scanf("%d", &n);
}

void solve()
{
	read_case();
	for(int i = 0; i < n; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if(x > y) swap(x, y);
		if(x & 1) x = x+1;
		if(y & 1) y = y+1;
		x /= 2, y /= 2;
		for(int j = x; j <= y; j++) vis[j]++;
	}
	int ans = 0;
	for(int i = 0; i < maxn; i++) ans = max(ans, vis[i]);
	printf("%d\n", ans*10);
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
