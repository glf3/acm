/*
HDU 5204：给定一个迷宫，求最长的一条路径，该路径上任意一点都可以通过最多不超过一次的转弯到达。
BFS。一直往一个方向走，初始转弯数为-1。元素出队列转弯数+1，每次将转弯数为0或者1的入队，对所有队列中的元素，标记走过坐标的时间。
可以证明，经过0次或者1次转弯到达的地方，最小到达的时间即为出队列的时间。枚举所有'.'为起点，取最小到达时间的最大值。
*/

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
 
int n, m;
 
const int maxn = 110;
 
char map[maxn][maxn];
 
int vis[maxn][maxn];
 
struct node
{
    int x, y;
    int step, k;
};
 
const int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
 
const int dx2_[] = {0, 0, 1, -1};
const int dy2_[] = {1, -1, 0, 0};
 
int check(int x, int y)
{
    if(x >= 0 && x < n && y >= 0 && y < m && map[x][y] != '#')
        return 1;
    return 0;
}
 
int bfs(int bx, int by)
{
    memset(vis, 0, sizeof(vis));
     
    queue<node> Q;
     
    node cur, next;
    cur.x = bx, cur.y = by, cur.step = 1, cur.k = -1;
    Q.push(cur);
    vis[bx][by] = 1;
     
    while(!Q.empty())
    {
        cur = Q.front(); Q.pop();
         
        cur.k++;
        int x = cur.x, y = cur.y, k = cur.k;
        if(k == 0)
        {
            for(int i = 0; i < 8; i++)
            {
                next = cur;
                int step = cur.step;
                 
                int newx = x+dx[i], newy = y+dy[i];
             
                while(check(newx, newy) && !vis[newx][newy])
                {
                    step++;
                    if(!vis[newx][newy])
                    {
                        vis[newx][newy] = step;
                        next.x = newx, next.y = newy; next.step = step; next.k = k;
                        Q.push(next);
                    }
                    newx += dx[i], newy += dy[i];
                }
            }
        }
        else if(k == 1)
        {
            int x = cur.x, y = cur.y, k = cur.k;
            for(int i = 0; i < 4; i++)
            {
                next = cur;
                int step = cur.step;
                int newx = x+dx2_[i], newy = y+dy2_[i];
                 
                while(check(newx, newy) && !vis[newx][newy])
                {
                    step++;
                    if(!vis[newx][newy])
                    {
                        vis[newx][newy] = step;
                    }
                    newx += dx2_[i], newy += dy2_[i];
                }
            }
        }
    }
     
    int ans = 0;
    for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++) if(vis[i][j])
        ans = max(ans, vis[i][j]);
    return ans;
}
 
int main()
{
    while(~scanf("%d", &n) && n)
    {
        m = n;
        for(int i = 0; i < n; i++)
            scanf("%s", map[i]);
         
        int ans = 0;
         
        for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(map[i][j] == '.')
                ans = max(ans, bfs(i, j));
        printf("%d\n", ans);
    }
    return 0;
}
