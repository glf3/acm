/*
Source:Andrew Stankevich's Contest (16) Problem C
Title:Domino in Casino
Url:http://acdream.info/contest?cid=1165#problem-C

给定一个nxm图，让你用K个1x2的多米洛骨牌去覆盖图，所获得价值为被覆盖的点上权值之积，保证一定能放置所有的骨牌，求最大值。
以下标(i+j)来奇偶建图，对于相邻的点建容量为1，费用为两两之积的边。建立源点、汇点分别与偶数、奇数点相连，建立超级源点与先前源点建容量为2，
费用为0的边，跑费用流即可。
*/
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
  
const int maxn = 1600*2;
const int maxm = 1600*4;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int from, to, cap, flow, cost;
	Edge(int from, int to, int cap, int flow, int cost): from(from), to(to), cap(cap), flow(flow), cost(cost) {}
};

struct MCMF
{
	int n, m, s, t;
	vector<Edge> edges;
	vector<int> G[maxn];
	int inq[maxn];
	int d[maxn];
	int p[maxn];
	int a[maxn];
	
	void init(int n)
	{
		this->n = n;
		for(int i = 0; i <= n; i++) G[i].clear();
		edges.clear();
	}
	
	void AddEdge(int from, int to, int cap, int cost)
	{
		edges.push_back(Edge (from, to, cap, 0, cost));
		edges.push_back(Edge (to, from, 0, 0, -cost));
		m = edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	
	bool spfa(int s, int t, int &flow, int &cost)
	{
		for(int i = 0; i <= n; i++) d[i] = INF;
		memset(inq, 0, sizeof(inq));
		d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;
		
		queue<int> Q;
		Q.push(s);
		while(!Q.empty())
		{
			int u = Q.front(); Q.pop();
			inq[u] = 0;
			for(int i = 0; i < G[u].size(); i++)
			{
				Edge &e = edges[G[u][i]];
				if(e.cap > e.flow && d[e.to] > d[u]+e.cost)
				{
					d[e.to] = d[u]+e.cost;
					p[e.to] = G[u][i];
					a[e.to] = min(a[u], e.cap-e.flow);
					if(!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
				}
			}
		}
		if(d[t] == INF) return 0;
		flow += a[t];
		cost += d[t]*a[t];
		int u = t;
		while(u != s)
		{
			edges[p[u]].flow += a[t];
			edges[p[u]^1].flow -= a[t];
			u = edges[p[u]].from;
		}
		return 1;
	}
	
	int Mincost(int s, int t)
	{
		int flow = 0, cost = 0;
		while(spfa(s, t, flow, cost));
		return cost;
	}
};

//////////////////////////////

MCMF g;

int cost[20][110];

struct Point
{
	int x, y;
	Point(int x=0, int y=0):x(x), y(y) {}
	int ok(Point a)
	{
		if(x == a.x && (a.y == y+1 || a.y == y-1)) return 1;
		if(y == a.y && (a.x == x+1 || a.x == x-1)) return 1;
		return 0;
	}
}P1[maxn], P2[maxn];

int main()
{
	int n, m, k;
	while(~scanf("%d%d%d", &n, &m, &k))
	{
		for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++) scanf("%d", &cost[i][j]);
		
		int p1 = 0, p2 = 0;
		for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
		{
			if((i+j) & 1) P1[p1++] = Point(i, j);
			else P2[p2++] = Point(i, j);
		}
		g.init(p1+p2+10);
		
		for(int i = 0; i < p1; i++)
		for(int j = 0; j < p2; j++)
		{
			int x1 = P1[i].x, y1 = P1[i].y;
			int x2 = P2[j].x, y2 = P2[j].y;
			int Cost = -cost[x1][y1]*cost[x2][y2];
			if(P1[i].ok(P2[j]))
			{
				g.AddEdge(i, j+p1, 1, Cost);
			}
		}
		int s = p1+p2, t = p1+p2+1;
		for(int i = 0; i < p1; i++)
			g.AddEdge(s, i, 1, 0);
		for(int i = 0; i < p2; i++)
			g.AddEdge(i+p1, t, 1, 0);
		
		int s2 = p1+p2+2;
		g.AddEdge(s2, s, k, 0);
		
		int ans = g.Mincost(s2, t);
		printf("%d\n", -ans);
	}
	return 0;
}
