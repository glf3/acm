/*树上DFS*/
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
using namespace std;

const int maxn = 1010;

vector<int> gr[maxn], nodes[maxn];

int n, s, k, fa[maxn];

bool vis[maxn];

void dfs(int u, int f, int d)
{
	fa[u] = f;
	int nc = gr[u].size();
	if(nc == 1 && d > k) nodes[d].push_back(u); //深度大于K的叶子节点
	for(int i = 0; i < nc; i++)
	{
		int v = gr[u][i];
		if(v != f) dfs(v, u, d+1);
	}
}

void dfs2(int u, int f, int d)
{
	vis[u] = 1;
	int nc = gr[u].size();
	for(int i = 0; i < nc; i++)
	{
		int v = gr[u][i];
		if(v != f && d < k) dfs2(v, u, d+1);
	}
}

int solve()
{
	int ans = 0;
	memset(vis, 0, sizeof(vis));
	for(int d = n-1; d > k; d--)
	{
		for(int i = 0; i < nodes[d].size(); i++)
		{
			int u = nodes[d][i];
			if(vis[u]) continue;
			int v = u;
			for(int j = 0; j < k; j++) v = fa[v];
			dfs2(v, -1, 0);
			ans++;
		}
	}
	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d%d", &n, &s, &k);
		for(int i = 1; i <= n; i++) gr[i].clear(), nodes[i].clear();
		for(int i = 0; i < n-1; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			gr[a].push_back(b);
			gr[b].push_back(a);
		}
		dfs(s, -1, 0);
		int ans = solve();
		printf("%d\n", ans);
	}
	system("pause");
	return 0;
}
