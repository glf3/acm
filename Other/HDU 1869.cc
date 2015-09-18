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
#include <map>
using namespace std;

const int maxn = 220;
const int INF = 0x3f3f3f3f;

int d[maxn][maxn];

int n, m;

void Floyd()
{
	for(int k = 0; k < n; k++)
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

void init()
{
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
		d[i][j] = (i == j)? 0:INF;
}

void read_case()
{
	init();
	while(m--)
	{
		int x, y;
		scanf("%d%d", &x, &y); d[x][y] = d[y][x] = 1;
	}
}

void solve()
{
	read_case();
	Floyd();
	for(int i = 0; i < n; i++)
	for(int j = i+1; j < n; j++) if(d[i][j] > 7){ printf("No\n"); return ;}
	printf("Yes\n");
}

int main()
{
	while(~scanf("%d%d", &n, &m))
	{
		solve();
	}
	return 0;
}
