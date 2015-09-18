/*基于优先队列的BFS*/
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

const int maxn = 1010;
const int maxm = 10010*2;
const int maxd = 110;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int v, w;
	int next;
}edge[maxm];

int first[maxn];
int A[maxn];
bool vis[maxn][maxd];
int d[maxn][maxd];

struct node
{
	int pos, cost;
	int flue;
	bool operator < (const node &a) const
	{
		return cost > a.cost;
	}
};

priority_queue<node> Q;

int n, m;
int cnt;

void init()
{
	cnt = 0;
	memset(first, -1, sizeof(first));
}

void read_graph(int u, int v, int w)
{
	edge[cnt].v = v, edge[cnt].w = w;
	edge[cnt].next = first[u], first[u] = cnt++;
}

void read_case()
{
	init();
	for(int i = 0; i < n; i++) scanf("%d", &A[i]);
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		read_graph(u, v, w), read_graph(v, u, w);
	}
}

int bfs(int src, int end, int V)
{
	while(!Q.empty()) Q.pop();
	memset(vis, 0, sizeof(vis));
	memset(d, INF, sizeof(d));
	node cur, next;
	if(src == end) return 0;
	cur.pos = src, cur.cost = 0, cur.flue = 0;
	Q.push(cur);
	d[src][0] = 0;
	while(!Q.empty())
	{
		cur = Q.top(); Q.pop();
		if(cur.pos == end) return cur.cost;
		int pos = cur.pos, cost = cur.cost, flue = cur.flue;
		vis[pos][flue] = true;
		if(flue+1 <= V && !vis[pos][flue+1] && d[pos][flue+1] > d[pos][flue] + A[pos]) //加一单位油 
		{
			next = cur;
			d[pos][flue+1] = d[pos][flue] + A[pos];
			next.pos = pos;
			next.cost = d[pos][flue+1]; 
			next.flue = flue+1;
			Q.push(next);
		}
		for(int e = first[pos]; e != -1; e = edge[e].next) //走到相邻节点 
		{
			int v = edge[e].v;
			int newflue = flue-edge[e].w;
			if(newflue >= 0 && !vis[v][newflue] && cost < d[v][newflue])
			{
				next = cur;
				d[v][newflue] = cost;
				next.pos = v;
				next.cost = d[v][newflue];
				next.flue = newflue;
				Q.push(next);
			}
		}
	}
	return -1;
}

void solve()
{
	read_case();
	int q;
	scanf("%d", &q);
	int src, end, V;
	while(q--)
	{
		scanf("%d%d%d", &V, &src, &end);
		int ans = bfs(src, end, V);
		if(ans == -1) printf("impossible\n");
		else printf("%d\n", ans);
	}
}

int main()
{
	while(~scanf("%d%d", &n, &m))
	{
		solve();
	}
	return 0;
}
