/*最短路；三点连通*/
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
const int maxn = 210;
const int maxm = 1000*1000;

typedef int LL;

struct Edge
{
    LL v;
    LL w;
    LL next;
}edge[maxm];

LL cnt;

LL n, m;

LL first[maxn];

int d[maxn];

void read_graph(LL u, LL v, LL w)
{
    edge[cnt].v = v, edge[cnt].w = w;
    edge[cnt].next = first[u], first[u] = cnt++;
}

void spfa(int s)
{
    queue<int> q;
    bool inq[maxn] = {0};
    for(int i = 0; i <= n; i++) d[i] = (i == s)?0:INF;
    q.push(s);
    while(!q.empty())
    {
        int x = q.front(); q.pop();
        inq[x] = 0;
        for(int e = first[x]; e != -1; e = edge[e].next)
        {
            int v = edge[e].v, w = edge[e].w;
            if(d[v] > d[x] + w)
            {
                d[v] = d[x] + w;
                if(!inq[v])
                {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

bool vis[maxn];

void init()
{
    cnt = 0;
    memset(first, -1, sizeof(first));
    memset(vis, 0, sizeof(vis));
}

int price[maxn];

void read_case()
{
	init();
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int u, v, w;
		scanf("%d%d", &v, &w); w--;
		read_graph(0, v, w);
		price[v] = w;
	}
	for(int i = 1; i <= n; i++)
	for(int j = i+1; j <= n; j++)
	if(price[i] == price[j])
	{
		read_graph(i, j, 0);
		read_graph(j, i, 0);
	}
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		read_graph(u, v, w);
	}
}

void solve()
{
	read_case();
	spfa(0);
	int ans = 0;
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= n; j++) if(i != j)
	for(int k = 1; k <= n; k++) if(i != k && j != k)
		if(d[i]+d[j] == d[k]) vis[k] = 1;
	for(int i = 1; i <= n; i++) if(vis[i]) ans++;
	for(int i = 1; i <= n; i++) printf("%d %d\n", i, d[i]);
	printf("%d\n", ans);
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
