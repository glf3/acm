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
const int maxn = 110;
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
int fa[maxn];

int value[maxn];

void read_graph(LL u, LL v, LL w)
{
    edge[cnt].v = v, edge[cnt].w = w;
    edge[cnt].next = first[u], first[u] = cnt++;
}

void spfa(int s)
{
    queue<int> q;
    bool inq[maxn] = {0};
    for(int i = 1; i <= n+1; i++) d[i] = (i == s)?0:-INF;
    q.push(s);
    while(!q.empty())
    {
        int x = q.front(); q.pop();
        inq[x] = 0;
        for(int e = first[x]; e != -1; e = edge[e].next)
        {
            int v = edge[e].v;
            if(d[v] < d[x] + value[v])
            {
                d[v] = d[x] + value[v];
                fa[v] = x;
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
    memset(fa, -1, sizeof(fa));
}

void read_case()
{
	init();
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &value[i]);
	value[n+1] = 0;
	scanf("%d", &m);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		read_graph(u, v, 0);
	}
}

void print_path(int u)
{
	if(fa[u] == -1) { printf("%d", u); return ;}
	print_path(fa[u]);
	if(u != n+1) printf("->%d", u);
}

void solve()
{
	read_case();
	spfa(1);
	printf("points : %d\n", d[n+1]);
	printf("circuit : ");
	print_path(n+1);
	printf("->1\n");
}

int main()
{
	int T, times = 0;
	scanf("%d", &T);
	while(T--)
	{
		if(times) printf("\n");
		printf("CASE %d#\n", ++times);
		solve();
	}
	return 0;
}
