/*SPFA+枚举*/
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
const int maxn = 1010;
const int maxm = 1000*1000;

struct Edge
{
    int v, next, w;
}edge[maxm];

int n, m;
int cnt;

int first[maxn], d[maxn];
int fa[maxn];
int edges[maxm];

bool vis[maxm];

void read_graph(int u, int v, int w)
{
    edge[cnt].v = v, edge[cnt].w = w;
    edge[cnt].next = first[u], first[u] = cnt++;
}

void init()
{
    cnt = 0;
    memset(first, -1, sizeof(first));
    memset(vis, 0, sizeof(vis));
    memset(fa, -1, sizeof(fa));
}

int spfa(int s, int t, int flag)
{
    queue<int> q;
    bool inq[maxn] = {0};
    for(int i = 1; i <= n; i++) d[i] = (i == s)? 0:INF;
    q.push(s);
    while(!q.empty())
    {
        int x = q.front(); q.pop();
        inq[x] = 0;
        for(int e = first[x]; e != -1; e = edge[e].next)
        {
			if(vis[e]) continue;
            int v = edge[e].v, w = edge[e].w;
            if(d[v] > d[x] + w)
            {
                d[v] = d[x] + w;
                if(flag == 1)
                {
					fa[v] = x;
					edges[v] = e;
				}
                if(!inq[v])
                {
					inq[v] = 1;
					q.push(v);
				}
            }
        }
    }
    return d[t];
}

void read_case()
{
	init();
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		read_graph(u, v, w);
		read_graph(v, u, w);
	}
}

void solve()
{
	read_case();
	int ans = spfa(n, 1, 1);
	for(int i = 1; i != -1; i = fa[i])
	{
		vis[edges[i]] = 1; //标记最短路上的边 
		int Max = spfa(n, 1, 2);
		ans = max(ans, Max);
		vis[edges[i]] = 0; //标记最短路上的边 
	}
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
