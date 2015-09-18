#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <string.h>
using namespace std;

const int SIZE = 31;

char maze[SIZE][SIZE][SIZE];
int flag[SIZE][SIZE][SIZE];
int l, r, c;
const int dx[] = {-1,1,0,0,0,0};
const int dy[] = {0,0,-1,1,0,0};
const int dz[] = {0,0,0,0,-1,1};

int bx, by, bz;   //入口 
int ex, ey, ez;   //出口 

int check(int x, int y, int z)
{
	if(x >= 0 && y >= 0 && z >= 0 && x < l && y < r && z < c && maze[x][y][z] != '#') return 1;
		return 0;
}


struct node
{
	int x, y, z;
	int step;
};


int bfs(int bx, int by, int bz)
{
	queue<node> Q;
	node p, q;
	p.x = bx; p.y = by; p.z = bz;
	p.step = 0;
	flag[bx][by][bz] = 1;
	Q.push(p);
	while(!Q.empty())
	{
		p = Q.front();
		Q.pop();
		if(p.x == ex && p.y == ey && p.z == ez)
		{
			printf("Escaped in %d minute(s).\n", p.step);
			return 1;
		}
		for(int i = 0; i < 6; i++)
		{
			q = p;
			q.x += dx[i];
			q.y += dy[i];
			q.z += dz[i];
			if(check(q.x, q.y, q.z) && !flag[q.x][q.y][q.z])
			{
				q.step++;
				flag[q.x][q.y][q.z] = 1;
				Q.push(q);
			}
		}
	}
	return 0;
}


void init()
{
	memset(flag, 0, sizeof(flag));
	memset(maze, '#', sizeof(maze));
	ex = ey = ez = bx = by = bz = 0;
}

int main()
{
	int i, j, k;
	while(~scanf("%d%d%d", &l, &r, &c), l, r, c)
	{
		init();
		for(i = 0; i < l; i++)
		{
			for(j = 0; j < r; j++)
			{
				scanf("%s", maze[i][j]);
				for(k = 0; k < c; k++)
				{
					if(maze[i][j][k] == 'E')
					{
						ex = i;
						ey = j;
						ez = k;
					}
					if(maze[i][j][k] == 'S')
					{
						bx = i;
						by = j;
						bz = k;
					}
				}
			}
		}
		int ans = bfs(bx, by, bz);
		if(!ans) printf("Trapped!\n");
	}
	return 0;
}

