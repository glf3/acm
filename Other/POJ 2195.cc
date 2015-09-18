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

const int maxn = 10010;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int u, v, cap, flow, cost;
	int next;
}edge[4*maxn];

int first[maxn];
int d[maxn];
int p[maxn], a[maxn];

bool inq[maxn];

int n, m;
int cnt;

const int maxd = 110;

char map[maxd][maxd];
int H[maxd][2];
int M[maxd][2];

void init()
{
	cnt = 0;
	memset(first, -1, sizeof(first));
}

void init_flow()
{
	for(int i = 0; i < cnt; i += 2)
	{
		edge[i].flow += edge[i^1].flow;
		edge[i^1].flow = 0;
	}
}

void read_graph(int u, int v, int cap, int cost)
{
	edge[cnt].u = u, edge[cnt].v = v, edge[cnt].cap = cap, edge[cnt].cost = cost;
	edge[cnt].next = first[u], first[u] = cnt++;
	
	edge[cnt].u = v, edge[cnt].v = u, edge[cnt].cap = 0, edge[cnt].cost = -cost;
	edge[cnt].next = first[v], first[v] = cnt++;
}

int spfa(int s, int t, int &flow, int &cost, int n)
{
	queue<int> q;
	bool inq[maxn] = {0};
	for(int i = 0; i <= n; i++) d[i] = (i == s)? 0:INF;
	p[s] = 0, a[s] = INF;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		inq[u] = 0;
		for(int e = first[u]; e != -1; e = edge[e].next)
		{
			int v = edge[e].v, cap = edge[e].cap, flow = edge[e].flow, cost = edge[e].cost;
			if(cap > flow && d[v] > d[u] + cost)
			{
				d[v] = d[u] + cost;
				p[v] = e;
				a[v] = min(a[u], cap-flow);
				if(!inq[v])
				{
					inq[v] = 1;
					q.push(v);
				}
			}
		}
	}
	if(d[t] == INF) return 0;
	flow += a[t];
	cost += d[t] * a[t];
	for(int u = t; u != s; u = edge[p[u]].u)
	{
		edge[p[u]].flow += a[t];
		edge[p[u]^1].flow -= a[t];
	}
	return 1;
}

int MinCost(int s, int t, int n)
{
	int flow = 0, cost = 0;
	while(spfa(s, t, flow, cost, n));
	return cost;
}

void solve()
{
	init();
	int HH = 1, MM = 1;
	for(int i = 0; i < n; i++) scanf("%s", map[i]);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			if(map[i][j] == 'H')
			{
				H[HH][0] = i;
				H[HH][1] = j;
				HH++;
			}
			if(map[i][j] == 'm')
			{
				M[MM][0] = i;
				M[MM][1] = j;
				MM++;
			}
		}
	}
	HH--, MM--;
	for(int i = 1; i <= HH; i++)
	{
		read_graph(0, i, 1, 0);
	}
	for(int j = 1; j <= MM; j++)
	{
		read_graph(HH+j, HH+MM+1, 1, 0);
	}
	for(int i = 1; i <= HH; i++)
	{
		for(int j = 1; j <= MM; j++)
		{
			int cost = abs(H[i][0]-M[j][0]) + abs(H[i][1]-M[j][1]);
			read_graph(i, HH+j, 1, cost);
		}
	}
	int s = 0, t = HH+MM+1;
	int ans = MinCost(s, t, HH+MM+2);
	printf("%d\n", ans);
	init_flow();
}

int main()
{
	while(~scanf("%d%d", &n, &m) && (n || m))
	{
		solve();
	}
	return 0;
}
