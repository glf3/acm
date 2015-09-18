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

const int maxn = 16;
int a[maxn];
int b[maxn];

int n;

int check(int a[])
{
	for(int i = 0; i < n; i++)
		if(a[i] != 0) return 0;
	return 1;
}

void work(int a[], int b[])
{
	memcpy(a, b, sizeof(b));
	
	for(int i = 0; i < n-1; i++)
		b[i] = abs(a[i]-a[i+1]);
	b[n-1] = abs(a[n-1]-a[0]);
}

int main()
{
	int T;
	for(scanf("%d", &T); T > 0; T--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		if(check(a)) { printf("ZERO\n"); continue ;}
		int flag = 0;
		for(int i = 1; i <= 1000; i++)
		{
			work(a, b);
			if(check(b)) { flag = 1; break; }
			memcpy(a, b, sizeof(b));
		}
		printf("%s\n", flag? "ZERO":"LOOP");
	}
	return 0;
}
