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

struct Edge
{
	int from, to, dist;
};

struct Node
{
	int d, u;
	bool operator < (const Node &A) const
	{
		return d > A.d;
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
	bool vis[maxn];
	int r[maxn];
	void init(int n)
	{
		this->n = n;
		for(int i = 0; i < n; i++) G[i].clear();
		edges.clear();
		memset(vis, false, sizeof(vis));
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
		for(int i = 0; i < n; i++) d[i] = (i == s)? 0 : INF;
		Q.push((Node){0, s});
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
					Q.push((Node){d[e.to], e.to});
				}
			}
		}
	}
	
	int dp(int u, int t)
	{
		int &ans = r[u];
		if(vis[u]) return ans;
		if(u == t) return 1;
		ans = 0;
		vis[u] = true;
		for(int i = 0; i < G[u].size(); i++)
		{
			Edge&e = edges[G[u][i]];
			if(d[e.to] < d[u])
			{
				ans += dp(e.to, t);
			}
		}
		return ans;
	}
};

Dijkstra solver;

int n, m;

int read_case()
{
	scanf("%d", &n);
	if(!n) return 0;
	scanf("%d", &m);
	solver.init(n);
	for(int i = 0; i < m; i++)
	{
		int from, to, dist;
		scanf("%d%d%d", &from, &to, &dist); from--, to--;
		solver.AddEdge(from, to, dist);
		solver.AddEdge(to, from, dist);
	}
	return 1;
}

void solve()
{
	solver.dijkstra(1);
	int ans = solver.dp(0, 1);
	printf("%d\n", ans);
}

int main()
{
	while(read_case())
	{
		solve();
	}
	return 0;
}
