/*平均权值最小的回路*/
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

#pragma comment(linker, "/STACK:102400000,102400000")

struct Edge
{
	int from, to;
	double dist;
};

const int maxn = 1010;
const int INF = 0x3f3f3f3f;

struct BellManFord
{
	int n, m;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool inq[maxn];
	double d[maxn];
	int p[maxn];
	int cnt[maxn];
	
	void init(int n)
	{
		this->n = n;
		for(int i = 0; i < n; i++) G[i].clear();
		edges.clear();
	}
	
	void AddEdge(int from, int to, int dist)
	{
		edges.push_back((Edge) {from, to, dist});
		m = edges.size();
		G[from].push_back(m-1);
	}
	
	bool spfa()
	{
		queue<int> Q;
		memset(inq, 0, sizeof(inq));
		memset(cnt, 0, sizeof(cnt));
		for(int i = 0; i < n; i++) { d[i] = 0; inq[0] = 1; Q.push(i); }
		while(!Q.empty())
		{
			int u = Q.front(); Q.pop();
			inq[u] = false;
			for(int i = 0; i < G[u].size(); i++)
			{
				Edge&e = edges[G[u][i]];
				if(d[e.to] > d[u] + e.dist)
				{
					d[e.to] = d[u] + e.dist;
					p[e.to] = G[u][i];
					if(!inq[e.to])
					{
						Q.push(e.to);
						inq[e.to] = 1;
						if(++cnt[e.to] > n) return 1;
					}
				}
			}
		}
		return 0;
	}
};

BellManFord solver;

bool test(double x)
{
	for(int i = 0; i < solver.m; i++) solver.edges[i].dist -= x;
	bool ret = solver.spfa();
	for(int i = 0; i < solver.m; i++) solver.edges[i].dist += x;
	return ret;
}

int main()
{
	int T;
	scanf("%d", &T);
	for(int t = 1; t <= T; t++)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		solver.init(n);
		int ub = 0;
		while(m--)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w); u--, v--; ub = max(ub, w);
			solver.AddEdge(u, v, w);
		}
			printf("Case #%d: ", t);
			if(!test(ub+1)) printf("No cycle found.\n");
			else
			{
				double x = 0, y = ub;
				while(y-x > 1e-3)
				{
					double m = x+(y-x)/2;
					if(test(m)) y = m; else x = m;
				}
				printf("%.2lf\n", x);
			}
	}
	return 0;
}
