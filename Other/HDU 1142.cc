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
bool vis[maxn];
int d[maxn];
int n, m;

void init()
{
	memset(vis, 0, sizeof(vis));
	memset(d, 0, sizeof(d));
}

int dp(int u, int t)
{
	int &ans = d[u];
	if(vis[u]) return ans;
	if(u == t) return 1;
	ans = 0;
	vis[u] = 1;
	for(int i = 0; i < solver.G[u].size(); i++)
	{
		int v = solver.edges[solver.G[u][i]].to;
		if(solver.d[u] > solver.d[v]) ans += dp(v, t);
	}
	return ans;
}

int main()
{
	while(~scanf("%d", &n) && n)
	{
		solver.init(n);
		scanf("%d", &m);
		while(m--)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w); u--; v--;
			solver.AddEdge(u, v, w);
			solver.AddEdge(v, u, w);
		}
		solver.dijkstra(1);
		init();
		int ans = dp(0, 1);
		printf("%d\n", ans);
	}
	return 0;
}
