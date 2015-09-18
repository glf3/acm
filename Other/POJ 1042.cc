/*贪心+枚举
枚举每一个城市为终点，每次找最大的即可*/
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

int n, h;

const int maxn = 110;

int f[maxn], d[maxn];
int t[maxn];
int T[maxn][maxn];
int sum[maxn];

void init()
{
	memset(sum, 0, sizeof(sum));
	memset(T, 0, sizeof(T));
}

int read_case()
{
	init();
	scanf("%d", &n);
	if(!n) return 0;
	scanf("%d", &h);
	for(int i = 0; i < n; i++) scanf("%d", &f[i]);
	for(int i = 0; i < n; i++) scanf("%d", &d[i]);
	for(int i = 0; i < n-1; i++) scanf("%d", &t[i]);
	return 1;
}

void solve()
{
	for(int i = 0; i < n; i++)
	{
		int m = h*12;
		for(int j = 0; j < i; j++) m -= t[j];
		for(int j = 0; j < m; j++)
		{
			int max = f[0]-T[i][0]*d[0];
			if(max < 0) max = 0;
			int index = 0;
			for(int k = 0; k <= i; k++)
			{
				int t = f[k]-T[i][k]*d[k];
				if(max < t)
				{
					max = t;
					index = k;
				}
			}
			T[i][index]++;
			sum[i] += max;
		}
	}
	int temp = sum[0];
	int index = 0;
	for(int i = 0; i < n; i++)
	{
		if(sum[i] > temp)
		{
			temp = sum[i];
			index = i;
		}
	}
	int first = 1;
	for(int i = 0; i < n; i++)
	{
		if(first) { printf("%d", T[index][i]*5); first = 0; }
		else printf(", %d", T[index][i]*5);
	}
	printf("\n");
	printf("Number of fish expected: %d\n\n", sum[index]);
}

int main()
{
	while(read_case())
	{
		solve();
	}
	return 0;
}
