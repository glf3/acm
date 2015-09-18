/*ʵ��������������پ�*/
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
using namespace std;

int n, m;

const int maxn = 1010;

int A[maxn], B[maxn];

bool vis[maxn];

void init()
{
	memset(vis, 0, sizeof(vis));
}

int read_case()
{
	init();
	scanf("%d%d", &m, &n);
	if(!n) return 0;
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &A[i]);
		vis[A[i]] = 1;
	}
	sort(A, A+n);
	return 1;
}

void solve()
{
	int ans = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = A[i]; j <= n*m; j++) //������һ��ΪN*M 
		{
			if(!vis[j]) //����û����ǵ�˵������һ����һ������A[i]�� 
			{
				vis[j] = 1;
				ans++;
				break;
			}
		}
	}
	printf("%d\n", n-ans);
}

int main()
{
	int times = 0;
	while(read_case())
	{
		printf("Case %d: ", ++times);
		solve();
	}
	return 0;
}
