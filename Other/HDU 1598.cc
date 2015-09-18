/*二分枚举差，然后再枚举下界*/
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
const int maxm = 1010*1010;

struct Edge
{
	int v, cap;
	int next;
}edge[maxm];

int d[maxn], first[maxn];
int cap[maxn];

int n, m;
int cnt;

void init()
{
	cnt = 0;
	memset(first, -1, sizeof(first));
}

void read_graph(int u, int v, int cap)
{
	edge[cnt].v = v, edge[cnt].cap = cap;
	edge[cnt].next = first[u], first[u] = cnt++;
}

int spfa(int s, int t, int L, int R)
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
			int v = edge[e].v, cap = edge[e].cap;
			if(cap < L || cap > R) continue;
			if(d[v] > d[x] + cap)
			{
				d[v] = d[x] + cap;
				if(!inq[v])
				{
					inq[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return d[t] != INF;
}

int limit;

void read_case()
{
	init();
	limit = 0;
	for(int i = 0; i < m; i++)
	{
		int u, v ;
		scanf("%d%d%d", &u, &v, &cap[i]);
		read_graph(u, v, cap[i]);
		read_graph(v, u, cap[i]);
		limit = max(limit, cap[i]);
	}
	sort(cap, cap+m);
}

void solve()
{
	read_case();
	int Q;
	scanf("%d", &Q);
	int flag;
	while(Q--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		int x = 0, y = limit;
		int ans = INF;
		while(x <= y)
		{
			flag = 0;
			int m = x+(y-x)/2;
			for(int i = 0; cap[i]+m <= limit; i++)
			{
				if(spfa(u, v, cap[i], cap[i]+m))
				{
					flag = 1;
					break;
				}
			}
			if(flag) { ans = m, y = m-1; }
			else x = m+1;
		}
		if(ans != INF) printf("%d\n", ans);
		else printf("-1\n"); 
	}
}

int main()
{
	while(~scanf("%d%d", &n, &m))
	{
		solve();
	}
	return 0;
}
