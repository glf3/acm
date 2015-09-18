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

const int maxn = 550;
const int maxm = 550*550;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int u, v, w;
	int next;
}edge[maxm];

int cnt;
int first[maxn], d[maxn];
int fa[maxn];

void read_graph(int u, int v, int w)
{
	edge[cnt].v = v, edge[cnt].w = w;
	edge[cnt].next = first[u], first[u] = cnt++;
}

bool inq[maxn];

struct node
{
	int x, y, w;
}A[maxn], B[maxn];

int spfa(int src, int n)
{
	queue<int> q;
	memset(inq, 0, sizeof(inq));
	int cnt[maxn] = {0};
	for(int i = 0; i <= n; i++) d[i] = (i == src)? 0 : INF;
	q.push(src);
	while(!q.empty())
	{
		int x = q.front(); q.pop();
		inq[x] = 0;
		for(int e = first[x]; e != -1; e = edge[e].next)
		{
			int v = edge[e].v, w = edge[e].w;
			if(d[v] > d[x] + w)
			{
				fa[v] = x;
				d[v] = d[x] + w;
				if(!inq[v])
				{
					inq[v] = 1;
					q.push(v);
					if(++cnt[v] > n) return v;
				}
			}
		}
	}
	return -1;
}

int s, e;
int n, m;
int G[maxn][maxn];
int ans[maxn][maxn];
int sum[maxn];

void init()
{
	cnt = 0;
	memset(first, -1, sizeof(first));
	memset(sum, 0, sizeof(sum));
}

void read_case()
{
	init();
	for(int i = 0; i < n; i++) scanf("%d%d%d", &A[i].x, &A[i].y, &A[i].w);
	for(int i = 0; i < m; i++) scanf("%d%d%d", &B[i].x, &B[i].y, &B[i].w);
	s = n+m;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			G[i][j] = abs(A[i].x-B[j].x)+abs(A[i].y-B[j].y)+1;
			read_graph(i, j+n, G[i][j]);
		}
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			scanf("%d", &ans[i][j]);
			if(ans[i][j])
			{
				read_graph(j+n, i, -G[i][j]);
				sum[j] += ans[i][j];
			}
		}
	}
	for(int i = 0; i < m; i++)
	{
		if(sum[i] < B[i].w) read_graph(i+n, s, 0);
		if(sum[i] > 0) read_graph(s, i+n, 0);
	}
}

void solve()
{
	read_case();
	int u = spfa(s, s+1);
	if(u == -1) printf("OPTIMAL\n");
	else
	{
		printf("SUBOPTIMAL\n");
		memset(inq, 0, sizeof(inq));
		int v = u;
		while(!inq[v])
		{
			inq[v] = 1;
			v = fa[v];
		}
		u = v;
		do
		{
			int from = fa[v], to = v;
			if(from < n && to >= n && to < s) ans[from][to-n]++;
			if(to < n && from >= n && from < s) ans[to][from-n]--;
			v = fa[v];
		}while(v != u);
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				printf(j != m-1? "%d " : "%d\n", ans[i][j]);
			}
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	solve();
	system("pause");
	return 0;
}
