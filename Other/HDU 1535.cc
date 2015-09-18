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

struct Edge
{
	int from, to, dist;
};

struct Node
{
	int d, u;
	bool operator < (const Node &rhs) const
	{
		return d > rhs.d;
	}
};

const int maxn = 10010;
const int INF = 0x3f3f3f3f;

typedef long long LL;

struct Dijkstra
{
	int n, m;
	vector<Edge> edges;
	vector<int> G[maxn];
	int d[maxn];
	int p[maxn];
	
	void init(int n)
	{
		this->n = n;
		for(int i = 0; i < n; i++) G[i].clear();
		edges.clear();
	}
	
	void AddEdge(int from, int to, int dist)
	{
		edges.push_back((Edge) {from, to, dist});
		int m = edges.size();
		G[from].push_back(m-1);
	}
	
	void dijkstra(int s)
	{
		priority_queue<Node> Q;
		for(int i = 0; i < n; i++) d[i] = (i == s)? 0:INF;
		Q.push((Node) {0, s});
		while(!Q.empty())
		{
			Node x = Q.top(); Q.pop();
			int u = x.u;
			if(x.d != d[u]) continue;
			for(int i = 0; i < G[u].size(); i++)
			{
				Edge&e = edges[G[u][i]];
				if(d[e.to] > d[u] + e.dist)
				{
					d[e.to] = d[u] + e.dist;
					p[e.to] = G[u][i];
					Q.push((Node) {d[e.to], e.to});
				}
			}
		}
	}
};

Dijkstra solver1, solver2;

int n, m;

int from[maxn], to[maxn], dist[maxn];

void read_case()
{
	scanf("%d%d", &n, &m);
	solver1.init(n), solver2.init(n);
	for(int i = 0; i < m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w); u--; v--;
		solver1.AddEdge(u, v, w);
		solver2.AddEdge(v, u, w);
	}
}

void solve()
{
	read_case();
	solver1.dijkstra(0);
	solver2.dijkstra(0);
	LL ans = 0;
	for(int i = 0; i < n; i++)
	{
		ans += (LL)(solver1.d[i] + solver2.d[i]);
	}
	printf("%lld\n", ans);
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
