/*HDU 1051*/
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
using namespace std;

int n;

const int maxn = 5010;
const int INF = 0x3f3f3f3f;

struct node
{
	int x, y;
	bool operator < (const node &a) const
	{
		if(x != a.x) return x < a.x;
		return y < a.y;
	}
}A[maxn];

bool vis[maxn];

void init()
{
	memset(vis, 0, sizeof(vis));
}

void read_case()
{
	init();
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d%d", &A[i].x, &A[i].y);
	sort(A, A+n);
}

int check()
{
	for(int i = 0; i < n; i++) if(!vis[i]) return 0;
	return 1;
}

void solve()
{
	read_case();
	int left, right;
	int tot = 1;
	for(;;)
	{
		left = 0, right = 0;
		for(int i = 0; i < n; i++) if(!vis[i])
		{
			if(A[i].x >= left && A[i].y >= right)
			{
				left = A[i].x, right = A[i].y;
				vis[i] = tot;
			}
		}
		if(check()) break;
		tot++;
	}
	printf("%d\n", tot);
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
