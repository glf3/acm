/*
http://hi.baidu.com/aekdycoin/item/216100f4b861accb531c26ae
*/
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

struct Sqr
{
	int left, right;
	int len;
};

typedef Sqr s;

const int maxn = 60;

s S[maxn];

int n;

int read_case()
{
	scanf("%d", &n);
	if(!n) return 0;
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &S[i].len);
		S[i].left = 0;
		for(int j = 0; j < i; j++)
		{
			S[i].left = max(S[i].left, S[j].right - abs(S[i].len-S[j].len));
		}
		S[i].right = S[i].left + S[i].len*2;
	}
	return 1;
}

void solve()
{
	for(int i = 1; i < n; i++)
	{
		for(int j = 0; j < i ; j++)
		{
			if(S[i].left < S[i].right)
			{
				if(S[i].len > S[j].len && S[i].left < S[j].right)
					S[j].right = S[i].left;
				else if(S[i].len < S[j].len && S[i].left < S[j].right)
					S[i].left = S[j].right;
			}
		}
	}
	for(int i = 0; i < n; i++) if(S[i].left < S[i].right)
		printf("%d ", i+1);
	printf("\n");
}

int main()
{
	while(read_case())
	{
		solve();
	}
	return 0;
}
