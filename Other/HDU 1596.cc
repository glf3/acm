#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

const int SIZE = 1010;
const int INF = -110;

double w[SIZE][SIZE];
double d[SIZE];
int v[SIZE];
int n;

void Dijkstra(int s, int e)  //start, end;
{
    int i, j;
    memset(v, 0, sizeof(v));
    for(i = 1; i <= n; i++) d[i] = w[s][i];
    v[s] = 1;
    d[s] = 1;
    for(i = 1; i <= n; i++)
    {
        int x;
        double m = INF;
        for(int y = 1; y <= n; y++) if(!v[y] && d[y] > m) m = d[x=y];          //d[y] > m;
        if(x == e || m == INF) break;
        v[x] = 1;
        for(int y = 1; y <= n; y++) if(!v[y]) d[y] >?= d[x]*w[x][y];          //d[x]*w[x][y];
    }
    if(d[e]) printf("%.3lf\n", d[e]);
    else printf("What a pity!\n");
}  //Dijkstra


int main()
{
    int i, j;
    while(~scanf("%d", &n))
    {
        for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= n; j++)
            {
                scanf("%lf", &w[i][j]);
            }
        }
        int T;
        for(scanf("%d", &T); T > 0; T--)
        {
            int s, e;
            scanf("%d%d", &s, &e);
            Dijkstra(s, e);
        }
    }
    return 0;
}
