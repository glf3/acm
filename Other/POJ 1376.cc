/*搜索*/
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

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

struct node
{
	int x, y;
	int d;
	int step;
};

int n, m;

int bx, by, ex, ey;

const int maxn = 51;

int maze[maxn][maxn];
int vis[maxn][maxn][4];

int check(int x, int y)
{
	if(x >= 1 && x <= n-1 && y >= 1 && y <= m-1 && maze[x][y] != 1) return 1;
	return 0;
}

void init()
{
	memset(maze, 0, sizeof(maze));
	memset(vis, 0, sizeof(vis));
}

int read_case()
{
	init();
	scanf("%d%d", &n, &m);
	if(!n) return 0;
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m; j++)
	{
		scanf("%d", &maze[i][j]);
		if(maze[i][j] == 1) //四个角不能走 
		{
			maze[i][j-1] = 1;
			maze[i-1][j] = 1;
			maze[i-1][j-1] = 1;
		}
	}
	scanf("%d%d%d%d%", &bx, &by, &ex, &ey);
	return 1;
}

int bfs(int bx, int by, int d)
{
	queue<node> Q;
	node cur, next;
	cur.x = bx, cur.y = by, cur.d = d, cur.step = 0;
	Q.push(cur);
	vis[bx][by][d] = 1;
	while(!Q.empty())
	{
		cur = Q.front(); Q.pop();
		if(cur.x == ex && cur.y == ey) return cur.step;
		int x = cur.x, y = cur.y, d = cur.d;
		for(int i = 1; i <= 3; i++)
		{
			int newx = x + dx[d]*i, newy = y + dy[d]*i;
			if(!check(newx, newy)) break; //必须break,是continue的话，可能就穿越了障碍。 
			if(!vis[newx][newy][d])
			{
				next = cur;
				next.x = newx, next.y = newy, next.step++;
				Q.push(next);
				vis[newx][newy][d] = 1;
			}
		}
		int d1 = (d+3)%4;
		if(check(x, y) && !vis[x][y][d1])
		{
			next = cur;
			next.d = d1, next.step++;
			Q.push(next);
			vis[x][y][d1] = 1;
		}
		int d2 = (d+1)%4;
		if(check(x, y) && !vis[x][y][d2])
		{
			next = cur;
			next.d = d2, next.step++;
			Q.push(next);
			vis[x][y][d2] = 1;
		}
	}
	return -1;
}

int found(char *s)
{
	if(s[0] == 'n') return 0;
	else if(s[0] == 'w') return 1;
	else if(s[0] == 's') return 2;
	else return 3;
}

void solve()
{
	char s[20];
	scanf("%s", s);
	int d = found(s);
	int ans = bfs(bx, by, d);
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
