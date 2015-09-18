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

const int maxn = 100010;

int A[maxn], B[maxn];

int n, S;

int readint()
{
	char c = getchar();
	while(!isdigit(c)) c = getchar();
	int x = 0;
	while(isdigit(c))
	{
		x = x*10 + c - '0';
		c = getchar();
	}
	return x;
}

void solve()
{
	scanf("%d%d", &n, &S);
	for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
	B[0] = 0;
	for(int i = 1; i <= n; i++) B[i] = B[i-1]+A[i];
	int ans = n+1;
	int i = 1;
	for(int j = 1; j <= n; j++)
	{
		if(B[i-1] > B[j]-S) continue;
		while(B[i] <= B[j]-S) i++;
		ans = min(ans, j-i+1);
	}
	printf("%d\n", ans == n+1? 0 : ans);
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
