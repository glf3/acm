/*最短路+二分判断限制条件*/
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
const int maxn = 10010;
const int maxm = 50010;

typedef int LL;

struct Edge
{
    LL v;
    LL w, cap;
    LL next;
}edge[maxm];

LL cnt;

LL n, m;

LL first[maxn];
LL d[maxn];

void read_graph(LL u, LL v, LL cap, LL w)
{
    edge[cnt].v = v, edge[cnt].w = w, edge[cnt].cap = cap;
    edge[cnt].next = first[u], first[u] = cnt++;
}

int s, t;
int limit;

int spfa(int src, int mid)
{
    queue<int> q;
    bool inq[maxn] = {0};
    for(int i = 1; i <= n; i++) d[i] = (i == src)?0:INF;
    q.push(src);
    while(!q.empty())
    {
        int x = q.front(); q.pop();
        inq[x] = 0;
        for(int e = first[x]; e != -1; e = edge[e].next) if(edge[e].cap >= mid)
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
    if(d[t] == INF) return 0;
        return 1;
}

int times;

void init()
{
    cnt = 0;
    memset(first, -1, sizeof(first));
}

int read_case()
{
	init();
	scanf("%d%d", &n, &m);
	if(!n && !m) return 0;
	for(int i = 0; i < m; i++)
	{
		int u, v, c, w;
		scanf("%d%d%d%d", &u, &v, &c, &w);
		if(c == -1) c = INF;
		read_graph(u, v, c, w);
		read_graph(v, u, c, w);
	}
	return 1;
}

void solve()
{
	scanf("%d%d%d", &s, &t, &limit);
	int x = 0, y = limit;
	int ans = INF, h;
	
	while(x <= y)
	{
		int mid = x+(y-x)/2;
		if(spfa(s, mid))
		{
			x = mid+1;
			h = mid;
			ans = d[t];
		}
		else y = mid-1;
	}
	if(times) printf("\n");
	printf("Case %d:\n", ++times);
	if(ans != INF)
	{
		printf("maximum height = %d\n", h);
		printf("length of shortest route = %d\n", ans);
	}
	else printf("cannot reach destination\n");
}

int main()
{
	times = 0;
	while(read_case())
	{
		solve();
	}
	return 0;
}
