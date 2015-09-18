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

typedef long long LL;

LL n;

struct node
{
	string ans;
	node() {ans = ""; }
};

int read_case()
{
	scanf("%lld", &n);
	if(!n) return 0;
	return 1;
}

LL Mod(string s, int n)
{
	int len = s.length();
	int ans = 0;
	for(int i = 0; i < len; i++)
	{
		ans = (ans*10+s[i]-'0')%n;
	}
	return ans;
}

bool vis[220];

node bfs()
{
	queue<node> Q;
	node cur, next;
	cur.ans = "1";
	memset(vis, 0, sizeof(vis));
	Q.push(cur);
	LL m;
	for(;;)
	{
		cur = Q.front(); Q.pop();
		if(Mod(cur.ans, n) == 0) return cur;
		next = cur;
		next.ans = cur.ans + "1";
		m = Mod(next.ans, n);
		if(!vis[m])
		{
			Q.push(next);
			vis[m] = 1;
		}
		next = cur;
		next.ans = cur.ans + "0";
	    m = Mod(next.ans, n);
		if(!vis[m])
		{
			Q.push(next);
			vis[m] = 1;
		}
	}
}

void solve()
{
	node ans = bfs();
	cout<<ans.ans<<endl;
}

int main()
{
	while(read_case())
	{
		solve();
	}
	return 0;
}
