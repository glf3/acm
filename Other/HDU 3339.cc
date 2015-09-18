/*×î¶ÌÂ·+0/1±³°ü*/
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
const int maxm = 20010;

struct Edge
{
    int v, next, w;
}edge[maxm];

int n, m;
int cnt;

int first[maxn], d[maxn];

void read_graph(int u, int v, int w)
{
    edge[cnt].v = v, edge[cnt].w = w;
    edge[cnt].next = first[u], first[u] = cnt++;
}

void spfa(int s)
{
    queue<int> q;
    bool inq[maxn] = {0};
    for(int i = 0; i <= n; i++) d[i] = (i == s)? 0:INF;
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

int power[maxn];

int sum;
int f[maxm];

void init()
{
    cnt = 0;
    sum = 0;
    memset(first, -1, sizeof(first));
    memset(f, 0, sizeof(f));
}

void read_case()
{
	init();
	scanf("%d%d", &n, &m);
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		read_graph(u, v, w);
		read_graph(v, u, w);
	}
	for(int i = 1; i <= n; i++) scanf("%d", &power[i]), sum += power[i];
}

void solve()
{
	read_case();
	spfa(0);
	int V = 0;
	int flag = 1;
	for(int i = 1; i <= n; i++)
	{
		V += d[i];
		if(V >= INF) flag = 0;
	}
	if(!flag) { printf("impossible\n"); return ; }
	for(int i = 1; i <= n; i++)
	{
		for(int v = V; v >= d[i]; v--)
		{
			f[v] = max(f[v], f[v-d[i]]+power[i]);
		}
	}
	for(int v = 1; v <= V; v++) if(f[v] >= (sum/2)+1) { printf("%d\n", v); return ;}
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
