#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib> 
using namespace std;

#define MAXN 510
#define MAXM 10010

int G[MAXN][MAXN];

int xlink[MAXN]; //表示最终求得的最大匹配中与Xi匹配的Y顶点，ylink同理。
int ylink[MAXN];
bool vis[MAXN]; //DFS中记录顶点访问状态，0表示未访问过，1表示访问过 

int nx, ny; //X、Y集合顶点的个数 

inline void init()
{
	memset(G, 0, sizeof(G));
	memset(xlink, -1, sizeof(xlink));
	memset(ylink, -1, sizeof(ylink)); //初始化为-1 
}

bool ED(int u)
{
	      //看题目具体的下标 
	for(int v = 1; v <= ny; v++) if(G[u][v]) 
	{
		if(!vis[v]) //v与u邻接，且从来没有访问过。 
		{
			vis[v] = 1; //访问v
			if(ylink[v] == -1 || ED(ylink[v])) 
			{ //如果v没有匹配，或者v已经匹配了，但可以从ylink[v]出发找到一条增广路
			//注意如果前一个条件成立，就不会递归。 
				xlink[u] = v; //把v匹配给u 
				ylink[v] = u; //把u匹配给v 
				return true; //找到可增广路 
			} 
		}
	}
	return false; //不存在从u开始的增广路 
}

int MaxMatch()
{
	int ans = 0;
	for(int i = 1; i <= nx; i++)
	{
		if(xlink[i] == -1) //从每个未盖点出发进行寻找增广路
		{
			memset(vis, 0, sizeof(vis));
			ans += ED(i);
		}
	}
	return ans;
}

int n, m;

void solve()
{
	init();
	nx = ny = n;
	for(int i = 0; i < m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		G[u][v] = 1;
	}
	int ans = MaxMatch();
	printf("%d\n", ans);
}

int main()
{
	while(~scanf("%d%d", &n, &m))
	{
		solve();
	}
	return 0;
}
