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

const int maxn = 110;
const int INF = 0x3f3f3f3f;

int d[maxn][maxn];
int path[maxn][maxn];
int tax[maxn];

int n, m;

void print_path(int u, int v)
{
	int first = 1;
	printf("%d", u+1);
	while(u != v)
	{
		printf("-->%d", path[u][v]+1);
		u = path[u][v];
	}
}

void Floyd()
{
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++) path[i][j] = j;
	
	for(int k = 0; k < n; k++)
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
		{
			if(d[i][j] > d[i][k] + d[k][j] + tax[k]) //ÏÈÏûºÄ£¬ÔÚ×ÖµäÐò 
			{
				d[i][j] = d[i][k] + d[k][j] + tax[k];
				path[i][j] = k;
			}
			if(d[i][j] == d[i][k] + d[k][j] + tax[k] && path[i][j] > path[i][k])
			{
				path[i][j] = path[i][k];
			}
		}
}

void init()
{
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
	{
		d[i][j] = (i == j)? 0:INF;
	}
}

int read_case()
{
	init();
	scanf("%d", &n);
	if(!n) return 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			scanf("%d", &d[i][j]);
			if(d[i][j] == -1) d[i][j] = INF;
		}
	}
	for(int i = 0; i < n; i++) scanf("%d", &tax[i]);
	return 1;
}

void solve()
{
	Floyd();
	int u, v;
	while(scanf("%d%d", &u, &v) && u != -1 && v != -1)
	{
		u--; v--;
		printf("From %d to %d :\n", u+1, v+1);
		printf("Path: ");
		print_path(u, v);
		printf("\n");
		printf("Total cost : %d\n\n", d[u][v]);
	}
}

int main()
{
	while(read_case())
	{
		solve();
	}
	return 0;
}
