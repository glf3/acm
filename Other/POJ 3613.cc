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

const int maxn = 110;
const int INF = 0x3f3f3f3f;

map<int, int> Map;

typedef struct Matrix
{
	int m[maxn][maxn];
	void init() { memset(m, INF, sizeof(m)); }
}Ma;

int k, n, m, s, e;

void init()
{
	n = 0;
	Map.clear();
}

Ma Floyd(Ma A, Ma B)
{
	Ma C;
	C.init();
	for(int k = 1; k <= n; k++)
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				if(C.m[i][j] > A.m[i][k] + B.m[k][j])
					C.m[i][j] = A.m[i][k] + B.m[k][j];
			}
		}
	}
	return C;
}

Ma power(Ma A, int k)
{
	if(k == 0) return A;
	Ma ans = A;
	while(k)
	{
		if(k & 1)
		{
			ans = Floyd(ans, A);
		}
		A = Floyd(A, A);
		k /= 2;
	}
	return ans;
}

Ma A;

void read_case()
{
	init();
	A.init();
	for(int i = 0; i < m; i++)
	{
		int x, y, w;
		scanf("%d%d%d", &w, &x, &y);
		if(!Map[x]) Map[x] = ++n;
		if(!Map[y]) Map[y] = ++n;
		int u = Map[x], v = Map[y];
		if(w < A.m[u][v])
		{
			A.m[u][v] = A.m[v][u] = w;
		}
	}
}

void solve()
{
	read_case();
	Ma ans;
	ans = power(A, k-1);
	printf("%d\n", ans.m[Map[s]][Map[e]]);
}

int main()
{
	while(~scanf("%d%d%d%d", &k, &m, &s, &e))
	{
		solve();
	}
	return 0;
}
