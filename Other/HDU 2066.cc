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
		edges.push_back((Edge) { from, to, dist});
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
int A[maxn], B[maxn];

int T, S, D;

int n;

inline void read_case()
{
	solver.init(maxn);
	while(T--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w); u--, v--;
		solver.AddEdge(u, v, w);
		solver.AddEdge(v, u, w);
	}
	for(int i = 0; i < S; i++) scanf("%d", &A[i]), A[i]--;
	for(int i = 0; i < D; i++) scanf("%d", &B[i]), B[i]--;
}

inline void solve()
{
	read_case();
	int ans = INF;
	for(int i = 0; i < S; i++)
	{
		solver.dijkstra(A[i]);
		for(int j = 0; j < D; j++)
		{
			ans = min(ans, solver.d[B[j]]);
		}
	}
	printf("%d\n", ans);
}

int main()
{
	while(~scanf("%d%d%d", &T, &S, &D))
	{
		solve();
	}
	return 0;
}
