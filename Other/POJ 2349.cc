#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 1100
#define INF 0X3F3F3F3F

int n, k, m;

struct node
{
    double x, y;
}a[MAXN*MAXN];

struct Edge
{
    int u, v;
    double w;
}edge[MAXN*MAXN];

int p[MAXN], tot;

int cmp(const Edge a, const Edge b)
{
    return a.w < b.w;
}

double w[MAXN][MAXN], d[MAXN];

void init()
{
    tot = 0;
}

double dist(const node a, const node b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int find(int x)
{ 
    return x == p[x]? x : p[x] = find(p[x]);
}

void Kruskal()
{
    double ans = 0;
    int count = 0;
    for(int i = 0; i <= n; i++) p[i] = i;
    sort(edge, edge+tot, cmp);
    for(int i = 0; i < tot; i++)
    {
        int x = find(edge[i].u), y = find(edge[i].v);
        if(x != y)
        {
            ans = edge[i].w;
            p[x] = y;
            count++;
        }
        if(count == n-m)
        {
            printf("%.2lf\n", ans);
            return ;
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        init();
        scanf("%d%d", &m, &n);
        for(int i = 1; i <= n; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++) if(i != j)
            {
                edge[tot].u = i, edge[tot].v = j;
                edge[tot].w = dist(a[i], a[j]);
                tot++;
            }
        }
        Kruskal();
    }
    return 0;
}
