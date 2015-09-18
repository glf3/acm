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
#include <sstream>
#include <set>
using namespace std;

const int maxn = 110*110;

int q[maxn];
int front, rear;

int n, p;
int t;

int calculate()
{
	int ans = 0;
	for(;;)
	{
		int max_ = 0;
		for(int i = front; i < rear; i++)
		{
			max_ = max(max_, q[i]);
		}
		if(q[front] < max_)
		{
			if(front == p) p = rear;
			q[rear++] = q[front];
			front++;
		}
		else if(q[front] == max_)
		{
			if(front == p)
				return ++ans;
			front++;
			ans++;
		}
	}
}

int main()
{
	int T;
	for(scanf("%d", &T); T > 0; T--)
	{
		front = 1, rear = 1;
		scanf("%d%d", &n, &p); p++;
		int x;
		for(int i = 0; i < n; i++)
		{
			scanf("%d", &x);
			q[rear++] = x;
		}
		if(n == 1) { printf("1\n"); continue ; }
		int ans = calculate();
		printf("%d\n", ans);
	}
	return 0;
}
