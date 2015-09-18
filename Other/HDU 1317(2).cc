/*SPFA求最长路*/
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

const int INF = 0x3f3f3f3f;
const int maxn = 110;
const int maxm = 110*110;

struct Edge
{
    int v, next, w;
}edge[maxm];

int n, m;
int cnt;

int first[maxn], d[maxn];
int energy[maxn];

bool vis[maxn];

void read_graph(int u, int v, int w)
{
    edge[cnt].v = v, edge[cnt].w = w;
    edge[cnt].next = first[u], first[u] = cnt++;
}

void init()
{
    cnt = 0;
    memset(first, -1, sizeof(first));
}

int dfs(int u, int t)
{
	if(u == t) return 1;
	vis[u] = 1;
	for(int e = first[u]; e != -1; e = edge[e].next)
	{
		int v = edge[e].v;
		if(vis[v]) continue;
		if(dfs(v, t)) return 1;
	}
	return 0;
}

void spfa(int s, int t) //最长路 
{
    queue<int> q;
    bool inq[maxn] = {0};
    int cnt[maxn] = {0};
    for(int i = 1; i <= n; i++) d[i] = (i == s)? 0:-INF;
    d[1] = 100;
    inq[1] = 1;
    q.push(1);
    while(!q.empty())
    {
        int x = q.front(); q.pop();
        inq[x] = 0;
        for(int e = first[x]; e != -1; e = edge[e].next)
        {
            int v = edge[e].v, w = edge[e].w;
            if(d[v] < d[x] + w)
            {
                d[v] = d[x] + w;
                if(!inq[v] && d[v] > 0) //约束条件 
                {
                    inq[v] = 1;
                    q.push(v);
                    if(++cnt[v] > n) //存在正环 
                    {
						memset(vis, 0, sizeof(vis));
						if(d[n] > 0 || dfs(v, n)) { printf("winnable\n"); return; }
						else { printf("hopeless\n"); return ;}
					}
                }
            }
        }
    }
    if(d[t] > 0) printf("winnable\n");
    else printf("hopeless\n");
}

void read_case()
{
	init();
	int u, v, w;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &energy[i], &m);
		while(m--)
		{
			scanf("%d", &v);
			read_graph(i, v, energy[i]);
		}
	}
}

void solve()
{
	read_case();
	int s = 1, t = n;
	spfa(s, t);
}

int main()
{
	while(~scanf("%d", &n) && n != -1)
	{
		solve();
	}
	return 0;
}
