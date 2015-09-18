/*
HDU 5203：给定一段区间，初始颜色为2，你可以将一整段区间涂成某一种颜色，询问一段区间上的颜色数。
线段树操作。由于颜色最多只有30种，我们可以利用一个int来处理所有的颜色，向下用&运算，向上用|运算来合并所有颜色即可。
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;
 
const int maxn = 1000100;
 
#define lc o<<1
#define rc o<<1|1
 
struct SegmentTree
{
    int color[maxn<<2];
    int setv[maxn<<2];
     
    int n;
     
    void init(int n)
    {
        this->n = n;
    }
     
    void pushup(int o)
    {
        color[o] = color[lc] | color[rc];
    }
     
    void build(int o, int L, int R)
    {
        color[o] = (1<<1); setv[o] = 2;
        if(L == R) return ;
        int M = L+(R-L)/2;
        build(lc, L, M);
        build(rc, M+1, R);
        pushup(o);
    }
     
    void pushdown(int o, int L, int R)
    {
        if(setv[o])
        {
            color[lc] = (1<<(setv[o]-1));
            color[rc] = (1<<(setv[o]-1));
             
            setv[lc] = setv[rc] = setv[o];
            setv[o] = 0;
        }
    }
     
    void update(int o, int L, int R, int y1, int y2, int v)
    {
        if(y1 <= L && y2 >= R)
        {
            color[o] = (1<<(v-1));
            setv[o] = v;
            return ;
        }
         
        int M = L+(R-L)/2;
        pushdown(o, L, R);
         
        if(y1 <= M) update(lc, L, M, y1, y2, v);
        if(y2 > M) update(rc, M+1, R, y1, y2, v);
        pushup(o);
    }
     
    int query(int o, int L, int R, int y1, int y2)
    {
        if(y1 <= L && y2 >= R) return color[o];
         
        int M = L+(R-L)/2;
        pushdown(o, L, R);
         
        int ans = 0;
        if(y1 <= M) ans |= query(lc, L, M, y1 ,y2);
        if(y2 > M) ans |= query(rc, M+1, R, y1, y2);
        return ans;
    }
     
    void print(int o, int L, int R)
    {
        printf("%d ", color[o]);
        if(L == R) return ;
         
        int M = L+(R-L)/2;
        print(lc, L, M); print(rc, M+1, R);
    }
};
 
////////////////
 
void readint(int &x)
{
    char c = getchar();
    while(!isdigit(c)) c = getchar();
     
    x = 0;
    while(isdigit(c))
    {
        x = x*10+c-'0';
        c = getchar();
    }
}
 
void writeint(int x)
{
    if(x > 9) writeint(x/10);
    printf("%d", x%10);
}
 
SegmentTree g;
int n, m, c;
 
int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        if(n == 0 && m == 0) break;
        g.init(n+10);
        g.build(1, 1, n);
        while(m--)
        {
            char cmd[10]; int x, y, z;
            scanf("%s", cmd);
            if(cmd[0] == 'P')
            {
                readint(x), readint(y), readint(z);
                if(x > y)
                    swap(x, y);
                g.update(1, 1, n, x, y, z);
            }
            else if(cmd[0] == 'Q')
            {
                readint(x), readint(y);
                if(x > y)
                    swap(x, y);
                int tmp = g.query(1, 1, n, x, y);
                 
                int ans = 1;
                 
                while(tmp)
                {
                    if(tmp & 1 && tmp/2 != 0) writeint(ans), putchar(' ');
                    else if(tmp & 1) writeint(ans), puts("");
                    tmp >>= 1;
                    ans++;
                }
            }
        }
    }
    return 0;
}
