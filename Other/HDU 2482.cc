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

const int maxn = 5050;
const int maxm = 1010*1010;

const int INF = 0x3f3f3f3f;

const int place[8]={5120, 2560, 1280, 640, 320, 160, 80, 40};  

struct Edge
{
	int v, w, cap;
	int next;
}edge[maxm];

int first[maxn], d[maxn];

int n, m;
int cnt;

void read_graph(int u, int v, int w)
{
	edge[cnt].v = v, edge[cnt].w = w;
	edge[cnt].next = first[u], first[u] = cnt++;
}

int spfa(int s, int t)
{
	queue<int> q;
	bool inq[maxn] = {0};
	for(int i = 0; i <= m+1; i++) d[i] = (i == s)? 0:INF;
	q.push(s);
	while(!q.empty())
	{
		int x = q.front(); q.pop();
		inq[x] = 0;
		for(int e = first[x]; e != -1; e = edge[e].next)
		{
			int v = edge[e].v, w = edge[e].w;
			if(d[v] > d[x] + w)
			{
				d[v] = d[x] + w;
				if(!inq[v])
				{
					inq[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return d[t];
}

struct node
{
	int x, y;
	char s[30];
}A[maxn];

vector<node> bus_line[maxn];

void trans(char *p, int  &x, int &y)
{
	x *= 4, y *= 4;
	for(int i = 0; i < 8; i++)
	{
		if(p[i] == '1') y += place[i];
		else if(p[i] == '2') x += place[i];
		else if(p[i] == '3') x += place[i], y += place[i];
	}
}

int find(char *s)
{
	for(int i = 0; i < n; i++)
	{
		if(!strcmp(s, A[i].s)) return i;
	}
}

int find_bus(vector<node> A, vector<node> B)
{
	for(int i = 0; i < A.size(); i++)
	for(int j = 0; j < B.size(); j++) if(!strcmp(A[i].s, B[j].s)) return 1;
	return 0;
}

double sqr(double x) { return x*x; }

double Dist(int x1, int y1, int x2, int y2)
{
	return sqrt(sqr(x1-x2) + sqr(y1-y2));
}

char s[30], e[30];

int bx, by, ex, ey;

void init()
{
	cnt = 0;
	memset(first, -1, sizeof(first));
	memset(A, 0, sizeof(A));
}

void read_case()
{
	init();
	scanf("%s%d%d", s, &bx, &by);
	scanf("%s%d%d", e, &ex, &ey);
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		scanf("%s%d%d", A[i].s, &A[i].x, &A[i].y);
	}
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) bus_line[i].clear();
	for(int i = 1; i <= m; i++)
	{
		char ch[30];
		int q;
		scanf("%d", &q);
		while(q--)
		{
			scanf("%s", ch);
			int id = find(ch);
			bus_line[i].push_back(A[id]);
		}
	}
}

const double eps = 1e-8;

int dcmp(double x)
{
	if(fabs(x) < eps) return 0; else return x < 0? -1 : 1;
}

void solve()
{
	read_case();
	trans(s, bx, by);
	trans(e, ex, ey);
	if(dcmp(Dist(bx, by, ex, ey)-2000.0) <= 0) { printf("walk there\n");  return ;}
	int s = 0, t = m+1;
	bool flag1 = 0, flag2 = 0;
	for(int i = 1; i <= m; i++)
	{
		for(int j = 0; j < bus_line[i].size(); j++)
		{
			double k1 = Dist(bx, by, bus_line[i][j].x, bus_line[i][j].y);
			double k2 = Dist(ex, ey, bus_line[i][j].x, bus_line[i][j].y);
			if(dcmp(k1 -1000.0) <= 0)
			{
				flag1 = true;
				read_graph(s, i, 1);
			}
			if(dcmp(k2-1000.0) <= 0)
			{
				flag2 = true;
				read_graph(i, t, 0);
			}
		}
	}
	
	if(!flag1 || !flag2) { printf("take a taxi\n"); return ; }
	
	for(int i = 1; i <= m; i++)
	{
		for(int j = i+1; j <= m; j++)
		{
			if(find_bus(bus_line[i], bus_line[j]))
			{
				read_graph(i, j, 1);
				read_graph(j, i, 1);
			}
		}
	}
	spfa(s, t);
	if(d[t] != INF) printf("%d\n", d[t]);
	else printf("take a taxi\n");
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
