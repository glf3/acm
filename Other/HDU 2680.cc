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

const int maxn = 1010;
const int INF = 0x3f3f3f3f;

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

Dijkstra solver;

int S[maxn];

int n, m, s;
int q;

void read_case()
{
	s--;
	solver.init(n);
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w); u--; v--;
		solver.AddEdge(v, u, w);
	}
	scanf("%d", &q);
	for(int i = 0; i < q; i++) scanf("%d", &S[i]), S[i]--;
}

void solve()
{
	read_case();
	solver.dijkstra(s);
	int ans = INF;
	for(int i = 0; i < q; i++) ans = min(ans, solver.d[S[i]]);
	if(ans == INF) printf("-1\n");
	else printf("%d\n", ans);
}

int main()
{
	while(~scanf("%d%d%d", &n, &m, &s))
	{
		solve();
	}
	return 0;
}
