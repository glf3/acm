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

const int maxn = 30;
const int INF = 0x3f3f3f3f;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int maze[maxn][maxn];

int n, m;
int bx, by, ex, ey;

void init()
{
	memset(maze, 0x3f, sizeof(maze));
}

int read_case()
{
	init();
	scanf("%d%d", &m, &n);
	if(!m) return 0;
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m; j++)
	{
		scanf("%d", &maze[i][j]);
		if(maze[i][j] == 2) bx = i, by = j;
		if(maze[i][j] == 3) ex = i, ey = j;
	}
	maze[bx][by] = 0;
	return 1;
}

int check(int x, int y)
{
	if(x >= 1 && x <= n && y >= 1 && y <= m) return 1;
	return 0;
}

void dfs(int x, int y, int step, int &ans)
{
	if(step > 10) return ;
	if(x == ex && y == ey)
	{
		if(ans > step) ans = step;
	}
	for(int i = 0; i < 4; i++)
	{
		int xx = x + dx[i];
		int yy = y + dy[i];
		if(!check(xx, yy)) continue;
		if(maze[xx][yy] == 1) continue;
		for(;;)
		{
			xx += dx[i];
			yy += dy[i];
			if(!check(xx, yy)) break;
			if(maze[xx][yy] == 1 || maze[xx][yy] == 3) break;
		}
		if(check(xx, yy))
		{
			maze[xx][yy] = 0;
			dfs(xx-dx[i], yy-dy[i], step+1, ans);
			maze[xx][yy] = 1;
		}
	}
}

void solve()
{
	int flag = 0;
	int ans = INF;
	dfs(bx, by, 0, ans);
	if(ans > 10) { printf("-1\n"); return ; }
	printf("%d\n", ans);
}

int main()
{
	while(read_case())
	{
		solve();
	}
	return 0;
}
