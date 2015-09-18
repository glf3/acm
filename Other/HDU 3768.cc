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

const int maxn = 100010;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int v, w;
	int next;
}edge[maxn*2];

int first[maxn], d[12][maxn];

int n, m;
int cnt;

void read_graph(int u, int v, int w)
{
	edge[cnt].v = v, edge[cnt].w = w;
	edge[cnt].next = first[u], first[u] = cnt++;
}

void spfa(int s, int id)
{
	queue<int> q;
	bool inq[maxn] = {0};
	for(int i = 0; i <= n; i++) d[id][i] = (i == s)? 0:INF;
	q.push(s);
	while(!q.empty())
	{
		int x = q.front(); q.pop();
		inq[x] = 0;
		for(int e = first[x]; e != -1; e = edge[e].next)
		{
			int v = edge[e].v, w = edge[e].w;
			if(d[id][v] > d[id][x] + w)
			{
				d[id][v] = d[id][x] + w;
				if(!inq[v])
				{
					inq[v] = 1;
					q.push(v);
				}
			}
		}
	}
}

int S;

void init()
{
	cnt = 0;
	memset(first, -1, sizeof(first));
}

int st[12], x[12];

void read_case()
{
	init();
	scanf("%d%d", &n, &m);
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		read_graph(u, v, w);
		read_graph(v, u, w);
	}
	scanf("%d", &S);
	for(int i = 1; i <= S; i++) scanf("%d", &st[i]);
	st[0] = 0;
}

void solve()
{
	read_case();
	for(int i = 0; i <= S; i++) spfa(st[i], i);
	for(int i = 1; i <= S; i++) x[i] = i;
	
	int A[12];
	int ans = INF, Min;
	do
	{
		Min = 0;
		for(int i = 1; i <= S; i++) A[i] = x[i];
		A[0] = 0, A[S+1] = 0;
		for(int i = 0; i < S+1; i++)
		{
			Min += d[A[i]][st[A[i+1]]];
		}
		ans = min(ans, Min);
	}while(next_permutation(x+1, x+S+1));
	printf("%d\n", ans);
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
