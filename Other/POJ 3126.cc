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

const int maxn = 10010;

int vis[maxn] = {0};
int prime[maxn] = {0};

struct node
{
	int num;
	int step;
};

void init()
{
	for(int i = 2; i < maxn; i++) if(!vis[i])
	{
		prime[i] = 1;
		for(int j = i*i; j < maxn; j += i) vis[j] = 1;
	}
	return ;
}

queue<node> Q;

int n, m;

void read_case()
{
	scanf("%d%d", &n, &m);
}

int bfs()
{
	while(!Q.empty()) Q.pop();
	memset(vis, 0, sizeof(vis));
	node cur;
	cur.num = n, cur.step = 0;
	Q.push(cur);
	vis[n] = 1;
	while(!Q.empty())
	{
		cur = Q.front(); Q.pop();
		if(cur.num == m) return cur.step;
		for(int i = 1; i <= 9; i++)
		{
			node next;
			int n2 = cur.num/10*10+i;
			if(prime[n2] && !vis[n2])
			{
				next.num = n2;
				next.step = cur.step+1;
				vis[n2] = 1;
				Q.push(next);
			}
		}
		for(int i = 0; i <= 9; i++)
		{
			node next;
			int n2 = cur.num/100*100+cur.num%10+i*10;
			if(prime[n2] && !vis[n2])
			{
				next.num = n2;
				next.step = cur.step+1;
				vis[n2] = 1;
				Q.push(next);
			}
		}
		for(int i = 0; i <= 9; i++)
		{
			node next;
			int n2 = cur.num/1000*1000+cur.num%100+i*100;
			if(prime[n2] && !vis[n2])
			{
				next.num = n2;
				next.step = cur.step+1;
				vis[n2] = 1;
				Q.push(next);
			}
		}
		for(int i = 1; i <= 9; i++)
		{
			node next;
			int n2 = cur.num%1000+i*1000;
			if(prime[n2] && !vis[n2])
			{
				next.num = n2;
				next.step = cur.step+1;
				vis[n2] = 1;
				Q.push(next);
			}
		}
	}
	return -1;
}

void solve()
{
	read_case();
	int ans = bfs();
	printf("%d\n", ans);
}

int main()
{
	init();
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
