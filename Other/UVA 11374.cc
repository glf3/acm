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

const int maxn = 510;
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
		for(int i = 0; i < n; i++) d[i] = (i == s)? 0 : INF;
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
	
	void GetPaths(int s, int *dist, vector<int>* paths)
	{
		dijkstra(s);
		for(int i = 0; i < n; i++)
		{
			dist[i] = d[i];
			paths[i].clear();
			int t = i;
			paths[i].push_back(t);
			while(s != t)
			{
				paths[i].push_back(edges[p[t]].from);
				t = edges[p[t]].from;
			}
			reverse(paths[i].begin(), paths[i].end());
		}
	}
};

int n, s, e, m;

Dijkstra solver;
int d1[maxn], d2[maxn];
vector<int> paths1[maxn], paths2[maxn];

void read_case()
{
	solver.init(n);
	s--, e--;
	for(int i = 0; i < m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w); u--; v--;
		solver.AddEdge(u, v, w);
		solver.AddEdge(v, u, w);
	}
	solver.GetPaths(s, d1, paths1);
	solver.GetPaths(e, d2, paths2);
}

void solve()
{
	read_case();
	int ans = d1[e];
	vector<int> path = paths1[e];
	int midpoint = -1;
	int k;
	
	scanf("%d", &k);
	for(int i = 0; i < k; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w); u--, v--;
		for(int j = 0; j < 2; j++)
		{
			if(d1[u] + d2[v] + w < ans)
			{
				ans = d1[u] + d2[v] + w;
				path = paths1[u];
				for(int j = paths2[v].size()-1; j >= 0; j--)
				{
					path.push_back(paths2[v][j]);
				}
				midpoint = u;
			}
			swap(u, v);
		}
	}
	for(int i = 0; i < path.size()-1; i++) printf("%d ", path[i]+1);
	printf("%d\n", e+1);
	if(midpoint == -1) printf("Ticket Not Used\n"); else printf("%d\n", midpoint+1);
	printf("%d\n", ans);
}

int main()
{
	int times = 0;
	while(~scanf("%d%d%d%d", &n, &s, &e, &m))
	{
		if(times) printf("\n");
		++times;
		solve();
	}
	return 0;
}
