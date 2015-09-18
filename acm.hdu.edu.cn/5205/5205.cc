/*
HDU 5205：你是孙悟空，给定一个迷宫，起点、终点。迷宫中有M把钥匙，编号分别为1-9，每次只能向相邻的四个点走，每次花费1时间，
如果有蛇'S'，花费2时间，杀死之后不再花费时间，只有按照顺序取完所有的钥匙你才有可能救走唐僧，求最小的时间。

影响当前节点状态的当前坐标、花费时间、所取得钥匙以及杀死的蛇，所以开个Node节点把上述的状态存下来。
因为当前状态只与三种状态有关，坐标、钥匙，会有很多无意义的重复状态。所以标记数组开三维的。
由于杀蛇的额外时间会导致BFS步数改变，所以用优先队列。用二进制模拟取得的钥匙，刚开始用二进制存杀死的蛇，
WA了一次发现爆int了，于是用vector存下杀死的蛇，最后走到终点并且取得所有钥匙即可。
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <set>
using namespace std;
 
const int maxn = 110;
const int INF = 0x3f3f3f3f;
 
char map[maxn][maxn];
 
bool vis[maxn][maxn][1<<10];
bool hash[maxn*maxn];
 
int n, m, K;
int bx, by, ex, ey;
 
struct Node
{
    int x, y, step;
    int status;
     
    vector<int> Snake;
    bool operator <(const Node &rhs) const
    {
        return step > rhs.step;
    }
};
 
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
 
int check(int x, int y)
{
    if(x >= 0 && x < n && y >= 0 && y < m && map[x][y] != '#')
        return 1;
    return 0;
}
 
int ok(int x, int status)
{
    for(int i = x-2; i >= 0; i--)
    {
        int tmp = status;
        if((tmp & (1<<i)) == 0) return 0;
    }
    return 1;
}
 
int idx(int x, int y, Node rhs)
{
    int tmp = x*m+y;
     
    int size = rhs.Snake.size();
    for(int i = 0; i < size; i++)
        if(rhs.Snake[i] == tmp) return 1;
    return 0;
}
 
int bfs()
{
    priority_queue<Node> Q;
     
    Node cur, next;
     
    cur.x = bx, cur.y = by, cur.status = 0, cur.step = 0;
    Q.push(cur);
     
    vis[bx][by][cur.status] = 1;
 
    while(!Q.empty())
    {
        cur = Q.top(); Q.pop();
         
        int x = cur.x, y = cur.y, step = cur.step;
        if(cur.x == ex && cur.y == ey && cur.status == ((1<<K)-1))
            return step;
         
        for(int i = 0; i < 4; i++)
        {
            next = cur;
            int newx = x+dx[i], newy = y+dy[i];
             
            int status = cur.status;
            if(!check(newx, newy) || vis[newx][newy][status]) continue ;
             
            if(isdigit(map[newx][newy]))
            {
                int tmp = map[newx][newy]-'0';
                 
                if(ok(tmp, status))
                {
                    next.x = newx, next.y = newy, next.step++;
                    status |= (1<<(tmp-1));
                    next.status = status;
                    Q.push(next);
                    vis[newx][newy][next.status] = 1;
                }
                else
                {
                    next.x = newx, next.y = newy, next.step++;
                    next.status = status;
                    Q.push(next);
                    vis[newx][newy][status] = 1;
                }
            }
            else
            {
                next.x = newx, next.y = newy; next.status = status;
                if(map[newx][newy] == 'S')
                {
                    if(hash[newx*m+newy] && idx(newx, newy, next))
                        next.step++;
                    else { next.step += 2; next.Snake.push_back(newx*m+newy); }
                }
                else next.step++;
                Q.push(next);
                vis[newx][newy][status] = 1;
            }
        }
    }
    return -1;
}
 
void init()
{
    memset(hash, 0, sizeof(hash));
    memset(vis, 0, sizeof(vis));
}
 
int main()
{
    while(~scanf("%d%d", &n, &K) && (n+K))
    {
        init();
        m = n;
         
        for(int i = 0; i < n; i++)
            scanf("%s", map[i]);
             
        for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(map[i][j] == 'K') bx = i, by = j;
            else if(map[i][j] == 'T') ex = i, ey = j;
            else if(map[i][j] == 'S') hash[i*m+j] = 1;
         
        int ans = bfs();
         
        if(ans != -1)
            printf("%d\n", ans);
        else printf("impossible\n");
    }
    return 0;
}
