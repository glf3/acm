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
#include <sstream>
#include <set>
using namespace std;

const int maxn = 100000 + 100;
int fa[maxn];

int find(int x)
{
	return x == fa[x]? x : fa[x] = find(fa[x]);
}

struct Edge
{
	int x, y, z;
	Edge(int x=0, int y=0, int z=0):x(x), y(y), z(z) {}
	bool operator < (const Edge &a) const
	{
		return z < a.z;
	}
}edge[maxn];

int cmp(Edge a, Edge b)
{
	return a.z > b.z;
}

int n, m;

int Kruskal(int flag)
{
	int ans = 0;
	if(flag) sort(edge, edge+m); //最小生成树 
	else sort(edge, edge+m, cmp); //最大生成树
	
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 0; i < m; i++)
	{
		int x = edge[i].x, y = edge[i].y, z = edge[i].z;
		
		x = find(x), y = find(y);
		if(x != y)
		{
			ans += z;
			fa[x] = y;
		}
	}
	return ans;
}

int f[51];

set<int> S;

void init()
{
	f[0] = 1, f[1] = 1;
	S.insert(1);
	for(int i = 2; i < 45; i++)
		 { f[i] = f[i-1]+f[i-2]; S.insert(f[i]); }
}

int ok(int x, int y)
{
	for(int i = x; i <= y; i++)
		if(S.count(i)) return 1;
	return 0;
}

void Union(int x, int y)
{
	x = find(x), y = find(y);
	fa[x] = y;
}

int main()
{
	init();
	int T, kase = 0;
	for(scanf("%d", &T); T > 0; T--)
	{
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) fa[i] = i;
		
		for(int i = 0; i < m; i++)
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			Union(x, y);
			edge[i] = Edge(x, y, z);
		}
		
		printf("Case #%d: ", ++kase);
		if(n == 1) { printf("No\n"); continue ; }
		
		int count = 0;
		for(int i = 1; i <= n; i++) if(fa[i] == i) count++;
		if(count != 1) { printf("No\n"); continue ; }
		int x = Kruskal(1);
		int y = Kruskal(0);
		if(ok(x, y)) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
