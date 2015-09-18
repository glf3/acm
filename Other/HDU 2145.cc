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
const int maxn = 310;
const int maxm = 5010;

typedef int LL;

struct Edge
{
    LL v;
    LL w;
    LL next;
}edge[maxm];

LL cnt;

LL n, m, k;

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
    for(int i = 1; i <= n; i++) d[i] = (i == s)?0:INF;
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

void init()
{
    cnt = 0;
    memset(first, -1, sizeof(first));
}

struct node
{
	double t;
	int id;
	int dis;
}A[maxn];

int pos[maxn], speed[maxn];

int s, t;

void read_case()
{
	init();
	for(int i = 0; i < k; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		read_graph(v, u, w);
	}
	scanf("%d", &t);
	for(int i = 1; i <= m; i++) scanf("%d", &pos[i]);
	for(int i = 1; i <= m; i++) scanf("%d", &speed[i]);
}

int cmp(const node a, const node b)
{
	if(a.t == b.t && a.dis != b.dis) return a.dis > b.dis;
	else if(a.t == b.t && a.dis == b.dis) return a.id > b.id;
	else if(a.t != b.t) return a.t < b.t;
}

void solve()
{
	read_case();
	spfa(t);
	for(int i = 1; i <= m; i++)
	{
		A[i].t = 1.0*d[pos[i]] / speed[i];
		A[i].dis = d[pos[i]];
		A[i].id = i;
	}
	sort(A+1, A+m+1, cmp);
	if(A[1].dis != INF) printf("%d\n", A[1].id);
	else printf("No one\n");
}

int main()
{
	while(~scanf("%d%d%d", &n, &m, &k))
	{
		solve();
	}
	return 0;
}
