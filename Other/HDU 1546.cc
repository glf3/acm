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

int n, m;

char str[maxn][110];
int w[maxn];

void read_case()
{
	solver.init(n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d%*c", &w[i]);
		scanf("%s", str[i]);
	}
}

void build()
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++) if(i != j)
		{
			int len = strlen(str[i]);
			int k;
			for(k = 0; k < 4; k++)
			{
				if(str[i][len-4+k] != str[j][k]) break;
			}
			if(k >= 4)
			{
				solver.AddEdge(i, j, w[i]);
			}
		}
	}
}

void solve()
{
	read_case();
	build();
	solver.dijkstra(0);
	int ans = solver.d[n-1];
	if(ans == INF) printf("-1\n");
	else printf("%d\n", ans);
}

int main()
{
	while(~scanf("%d", &n) && n)
	{
		solve();
	}
	return 0;
}
