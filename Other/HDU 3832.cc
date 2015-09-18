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
LL d1[maxn], d2[maxn], d3[maxn];

void read_graph(LL u, LL v, LL w)
{
    edge[cnt].v = v, edge[cnt].w = w;
    edge[cnt].next = first[u], first[u] = cnt++;
}

void spfa(int src, int *d)
{
    queue<int> q;
    bool inq[maxn] = {0};
    for(int i = 1; i <= n; i++) d[i] = (i == src)?0:INF;
    q.push(src);
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

struct Point
{
    double x, y;
    double R;
}A[maxn];

const double eps = 1e-8;

double sqr(double x) { return x*x; }
double Dist(Point a, Point b) { return sqrt(sqr(a.x-b.x) + sqr(a.y-b.y)); }

int dcmp(double x) { if(fabs(x) < eps) return 0; else return x < 0? -1 : 1; }

void read_case()
{
    init();
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%lf%lf%lf", &A[i].x, &A[i].y, &A[i].R);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++) if(i != j)
        {
            double t = Dist(A[i], A[j]);
            if(dcmp(t-A[i].R-A[j].R) <= 0) read_graph(i, j, 1), read_graph(j, i, 1);
        }
    }
}

void solve()
{
    read_case();
    spfa(1, d1); spfa(2, d2); spfa(3, d3);
    int ans = INF;
    for(int i = 1; i <= n; i++)
    {
		if(d1[i] != INF && d2[i] != INF && d3[i] != INF)
        	ans = min(ans, d1[i]+d2[i]+d3[i]);
    }
    if(ans < INF) printf("%d\n", n-ans-1);
    else printf("-1\n");
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
