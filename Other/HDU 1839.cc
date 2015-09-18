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

const long long INF = 0x3f3f3f3f;
const int maxn = 10010;
const int maxm = 110010;

typedef int LL;

struct Edge
{
    LL v;
    LL w, cap;
    LL next;
}edge[maxm];

LL cnt;

LL n, m, t;

LL first[maxn];
LL d[maxn];

void read_graph(LL u, LL v, LL cap, LL w)
{
    edge[cnt].v = v, edge[cnt].w = w, edge[cnt].cap = cap;
    edge[cnt].next = first[u], first[u] = cnt++;
}

LL limit;

bool inq[maxn];

LL spfa(LL s)
{
    queue<LL> q;
    for(LL i = 1; i <= n; i++) d[i] = (i == s)? 0:INF;
    memset(inq, 0, sizeof(inq));
    q.push(s);
    while(!q.empty())
    {
        LL x = q.front(); q.pop();
        inq[x] = 0;
        for(LL e = first[x]; e != -1; e = edge[e].next) if(edge[e].cap >= limit)
        {
            LL v = edge[e].v, w = edge[e].w;
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
    return d[n];
}

LL cap[maxm];

void init()
{
    cnt = 0;
    memset(first, -1, sizeof(first));
    memset(cap, 0, sizeof(cap));
}

void read_case()
{
    init();
    scanf("%d%d%d", &n, &m, &t);
    for(LL i = 0; i < m; i++)
    {
        LL u, v, c, w;
        scanf("%d%d%d%d", &u, &v, &c, &w);
        cap[i] = c;
        read_graph(u, v, c, w);
        read_graph(v, u, c, w);
    }
}

void solve()
{
    read_case();
    sort(cap, cap+m);
    LL x = 0, y = m-1;
    LL index;
    int ans;
    while(x <= y)
    {
        LL mid = x+(y-x)/2;
        limit = cap[mid];
        spfa(1);
        if(d[n] <= t)
        {
			x = mid+1;
			ans = cap[mid];
		}
        else y = mid-1;
    }
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
