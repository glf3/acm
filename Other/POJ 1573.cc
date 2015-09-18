/*Ä£Äâ*/
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

const int maxn = 20;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, 1, -1};

char maze[maxn][maxn];

int vis[maxn][maxn];

int n, m, s;

void init()
{
	memset(vis, 0, sizeof(vis));
}

int read_case()
{
	init();
	scanf("%d%d%d%*c", &n, &m, &s);
	if(!n) return 0;
	for(int i = 1; i <= n; i++) scanf("%s", maze[i]+1);
	return 1;
}

int check(int x, int y)
{
	if(x >= 1 && x <= n && y >= 1 && y <= m) return 1;
	return 0;
}

void solve()
{
	int tot = 1;
	char d = maze[1][s];
	int x = 1, y = s;
	int flag = 0;
	int ans1 = 0, ans2 = 0;
	for(;;)
	{
		if(!check(x, y)) { ans2 = tot-1; break; }
		if(vis[x][y] != 0) { flag = 1; ans1 = vis[x][y]-1; ans2 = tot-vis[x][y]; break; }
		vis[x][y] = tot++;
		switch(d)
		{
			case 'N': x += dx[0], y += dy[0];break;
			case 'S': x += dx[1], y += dy[1];break;
			case 'E': x += dx[2], y += dy[2];break;
			case 'W': x += dx[3], y += dy[3];break;
		}
		d = maze[x][y];
	}
	if(!flag) printf("%d step(s) to exit\n", ans2);
	else printf("%d step(s) before a loop of %d step(s)\n", ans1, ans2);
}

int main()
{
	while(read_case())
	{
		solve();
	}
	return 0;
}
