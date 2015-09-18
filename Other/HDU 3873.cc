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

typedef long long LL;

const int maxn = 3010;
const int maxm = 70010;

const LL INF = 999999999;

struct Edge
{
	int v, w, cap;
	int next;
}edge[maxm];

int first[maxn], in[maxn];

LL les[maxn];
LL d[maxn];

vector<int> node[maxn];

int n, m;
int cnt;

void init()
{
	cnt = 0;
	memset(first, -1, sizeof(first));
	memset(les, 0, sizeof(les));
	for(int i = 1; i <= n; i++) node[i].clear();
}

void read_graph(int u, int v, int w)
{
	edge[cnt].v = v, edge[cnt].w = w;
	edge[cnt].next = first[u], first[u] = cnt++;
}

typedef pair<LL, int> pii;

LL Dijkstra(int s, int t)
{
	priority_queue<pii, vector<pii>, greater<pii> > Q;
	for(int i = 1; i <= n; i++) d[i] = (i == s)? 0:INF;
	Q.push(make_pair(d[s], s));
	while(!Q.empty())
	{
		pii u = Q.top(); Q.pop();
		int x = u.second;
		if(u.first != d[x]) continue;
		
		for(int j = 0; j < node[x].size(); j++) //保护节点被摧毁
		{
			int cur = node[x][j];
			in[cur]--;
			les[cur] = max(les[cur], d[x]);
			if(d[cur] != INF && in[cur] == 0)
			{
				d[cur] = max(d[cur], les[cur]);
				Q.push(make_pair(d[cur], cur));
			}
		}
		for(int e = first[x]; e != -1; e = edge[e].next)
		{
			int v = edge[e].v, w = edge[e].w;
			if(d[v] > d[x] + w)
			{
				d[v] = max(d[x]+w, les[v]);
				if(in[v] == 0)
				{
					Q.push(make_pair(d[v], v));
				}
			}
		}
	}
	return d[t];
}

void read_case()
{
	scanf("%d%d", &n, &m);
	init();
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		read_graph(u, v, w);
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &in[i]);
		for(int j = 1; j <= in[i]; j++)
		{
			int k;
			scanf("%d", &k);
			node[k].push_back(i);
		}
	}
}

void solve()
{
	read_case();
	LL ans = Dijkstra(1, n);
	printf("%I64d\n", ans);
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
