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

const int maxn = 110;
const int INF = 0x3f3f3f3f;

int energy[maxn];

struct BellManFord
{
	int n, m;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool inq[maxn];
	int d[maxn];
	int p[maxn];
	int cnt[maxn];
	bool vis[maxn];
	
	void init(int n)
	{
		this->n = n;
		for(int i = 0; i < n; i++) G[i].clear();
		edges.clear();
		memset(vis, 0, sizeof(vis));
	}
	
	void AddEdge(int from, int to, int dist)
	{
		edges.push_back((Edge) {from, to, dist});
		m = edges.size();
		G[from].push_back(m-1);
	}
	
	int dfs(int u, int t)
	{
		vis[u] = 1;
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = edges[G[u][i]].to; //±ß±éÀú 
			if(vis[v]) continue;
			if(v == t) return 1;
			if(dfs(v, t)) return 1;
		}
		return 0;
	}
	
	bool spfa(int s, int t)
	{
		queue<int> Q;
		memset(inq, 0, sizeof(inq));
		memset(cnt, 0, sizeof(cnt));
		for(int i = 0; i <= n; i++) d[i] = (i == s)? 0:-INF;
		d[s] = 100;
		Q.push(s);
		while(!Q.empty())
		{
			int u = Q.front(); Q.pop();
			inq[u] = false;
			for(int i = 0; i < G[u].size(); i++)
			{
				Edge&e = edges[G[u][i]];
				if(d[e.to] < d[u] + e.dist)
				{
					d[e.to] = d[u] + e.dist;
					p[e.to] = G[u][i];
					if(!inq[e.to] && d[e.to] > 0)
					{
						Q.push(e.to);
						inq[e.to] = true;
						if(++cnt[e.to] > n)
						{
							if(d[t] > 0 || dfs(e.to, t)) return 1;
							else return 0;
						}
					}
				}
			}
		}
		return d[t] > 0;
	}
};

BellManFord solver;

int n, m;

void read_case()
{
	solver.init(n);
	int from, to, dist;
	for(int i = 0; i < n; i++)
	{
		scanf("%d%d", &dist, &m);
		while(m--)
		{
			scanf("%d", &to); to--;
			solver.AddEdge(i, to, dist);
		}
	}
}

void solve()
{
	read_case();
	int s = 0, t = n-1;
	int ans = solver.spfa(s, t);
	printf(ans == 1? "winnable\n":"hopeless\n");
}

int main()
{
	while(~scanf("%d", &n) && n != -1)
	{
		solve();
	}
	return 0;
}
