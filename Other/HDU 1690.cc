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

typedef __int64 LL;

LL L1, L2, L3, L4, C1, C2, C3, C4;

LL Get(LL d)
{
	if(d < 0) d = -d;
	LL t = d;
	if(t == 0) return 0;
	else if(t <= L1) return C1;
	else if(t <= L2) return C2;
	else if(t <= L3) return C3;
	else if(t <= L4) return C4;
	else return -1;
}

const int maxn = 110;

int n, m;

LL d[maxn][maxn];

void Floyd()
{
	for(int k = 0; k < n; k++)
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) if(d[i][k] != -1 && d[k][j] != -1)
			if(d[i][j] > d[i][k] + d[k][j] || d[i][j] == -1)
			{
				d[i][j] = d[i][k] + d[k][j];
			}
}

void init()
{
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
		d[i][j] = (i == j)? 0:-1;
}

LL X[maxn];

void read_case()
{
	init();
	scanf("%I64d %I64d %I64d %I64d %I64d %I64d %I64d %I64d", &L1, &L2, &L3, &L4, &C1, &C2, &C3, &C4);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++)
	{
		scanf("%I64d", &X[i]);
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			d[i][j] = Get(X[i]-X[j]);
		}
	}
}

void solve()
{
	read_case();
	Floyd();
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v); u--; v--;
		if(d[u][v] != -1) printf("The minimum cost between station %d and station %d is %I64d.\n", u+1, v+1, d[u][v]);
		else printf("Station %d and station %d are not attainable.\n", u+1, v+1);
	}
}

int main()
{
	int T, times = 0;
	scanf("%d", &T);
	while(T--)
	{
		printf("Case %d:\n", ++times);
		solve();
	}
	return 0;
}
