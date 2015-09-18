#include <iostream>  
#include <cstdlib>  
#include <cstring>  
#include <cstdio>  
#include <string>  
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <stack>
#include <sstream>
#include <cctype>
#include <bitset>
#include <cmath>
#include <queue>
using namespace std;

const int maxn = 5010;
const int maxm = 1100*1100*2;
const int INF = 0x3f3f3f3f;

int n, m;
int val[maxn][maxn];
int a[maxn];

vector<int> b[maxn];

struct Edge
{
	int u, v, w;
	int next;
}edge[maxm];

int cnt;
int first[maxn*110];
int d[maxn*110];
int N;

void read_graph(int u, int v, int w)
{
	edge[cnt].v = v, edge[cnt].w = w;
	edge[cnt].next = first[u], first[u] = cnt++;
}

void init()
{
	cnt = 0;
	N = 0;
	memset(first, -1, sizeof(first));
	for(int i = 0; i < n; i++) b[i].clear();
}

void spfa(int s, int t)
{
	bool inq[maxn] = {0};
	queue<int> Q;
	
	Q.push(s);
	for(int i = 1; i <= N+3; i++) d[i] = (i == s)? 0:-INF;
	while(!Q.empty())
	{
		int x = Q.front(); Q.pop();
		inq[x] = 0;
		for(int e = first[x]; e != -1; e = edge[e].next)
		{
			int v = edge[e].v, w = edge[e].w;
			if(d[v] < d[x]+w)
			{
				d[v] = d[x]+w;
				if(!inq[v])
				{
					inq[v] = 1;
					Q.push(v);
				}
			}
		}
	}
}

void build()
{
	for(int i = 0; i < n-1; i++)
	{
		if(a[i] != -1 && a[i+1] != -1)
		{
			int x = b[i][1], y = b[i+1][1];
			read_graph(x, y, val[a[i]][a[i+1]]);
		}
		if(a[i] != -1 && a[i+1] == -1)
		{
			int x = b[i][1], y;
			for(int j = 1; j <= m; j++)
			{
				y = b[i+1][j];
				read_graph(x, y, val[a[i]][j]);
			}
		}
		if(a[i] == -1 && a[i+1] != -1)
		{
			int x, y = b[i+1][1];
			for(int j = 1; j <= m; j++)
			{
				x = b[i][j];
				read_graph(x, y, val[j][a[i+1]]);
			}
		}
		if(a[i] == -1 && a[i+1] == -1)
		{
			for(int j = 1; j <= m; j++)
			for(int k = 1; k <= m; k++)
				read_graph(b[i][j], b[i+1][k], val[j][k]);
		}
	}
	
	for(int i = 1; i < b[0].size(); i++)
		read_graph(N+1, b[0][i], 0);
	for(int i = 1; i < b[n-1].size(); i++)
		read_graph(b[n-1][i], N+2, 0);
}

int main()
{
	int T;
	for(scanf("%d", &T); T > 0; T--)
	{
		init();
		scanf("%d%d", &n, &m);
		
		for(int i = 1; i <= m; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d", &val[i][j]);
		
		for(int i = 0; i < n; i++) b[i].push_back(-1);
		
		for(int i = 0; i < n; i++)
		{
			scanf("%d", &a[i]);
			if(a[i] == -1)
			{
				for(int j = 1; j <= m; j++)
				{
					b[i].push_back(++N);
				}
			}
			else b[i].push_back(++N);
		}
		build();
		
		int s = N+1, t = N+2;
		spfa(s, t);
		printf("%d\n", d[t]);
	}
	return 0;
}
