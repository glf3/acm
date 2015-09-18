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
		edges.push_back((Edge) { from, to, dist} );
		m = edges.size();
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

