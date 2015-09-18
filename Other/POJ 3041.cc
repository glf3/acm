#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib> 
using namespace std;

#define MAXN 510
#define MAXM 10010

int G[MAXN][MAXN];

int xlink[MAXN]; //��ʾ������õ����ƥ������Xiƥ���Y���㣬ylinkͬ��
int ylink[MAXN];
bool vis[MAXN]; //DFS�м�¼�������״̬��0��ʾδ���ʹ���1��ʾ���ʹ� 

int nx, ny; //X��Y���϶���ĸ��� 

inline void init()
{
	memset(G, 0, sizeof(G));
	memset(xlink, -1, sizeof(xlink));
	memset(ylink, -1, sizeof(ylink)); //��ʼ��Ϊ-1 
}

bool ED(int u)
{
	      //����Ŀ������±� 
	for(int v = 1; v <= ny; v++) if(G[u][v]) 
	{
		if(!vis[v]) //v��u�ڽӣ��Ҵ���û�з��ʹ��� 
		{
			vis[v] = 1; //����v
			if(ylink[v] == -1 || ED(ylink[v])) 
			{ //���vû��ƥ�䣬����v�Ѿ�ƥ���ˣ������Դ�ylink[v]�����ҵ�һ������·
			//ע�����ǰһ�������������Ͳ���ݹ顣 
				xlink[u] = v; //��vƥ���u 
				ylink[v] = u; //��uƥ���v 
				return true; //�ҵ�������· 
			} 
		}
	}
	return false; //�����ڴ�u��ʼ������· 
}

int MaxMatch()
{
	int ans = 0;
	for(int i = 1; i <= nx; i++)
	{
		if(xlink[i] == -1) //��ÿ��δ�ǵ��������Ѱ������·
		{
			memset(vis, 0, sizeof(vis));
			ans += ED(i);
		}
	}
	return ans;
}

int n, m;

void solve()
{
	init();
	nx = ny = n;
	for(int i = 0; i < m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		G[u][v] = 1;
	}
	int ans = MaxMatch();
	printf("%d\n", ans);
}

int main()
{
	while(~scanf("%d%d", &n, &m))
	{
		solve();
	}
	return 0;
}
