/*田忌赛马，贪心证明*/
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

const int maxn = 1010;

int A[maxn], B[maxn];

int n;

int read_case()
{
	scanf("%d", &n);
	if(!n) return 0;
	for(int i = 0; i < n; i++) scanf("%d", &A[i]);
	for(int i = 0; i < n; i++) scanf("%d", &B[i]);
	sort(A, A+n), sort(B, B+n);
	return 1;
}

void solve()
{
	int firstA, firstB, lastA, lastB;
	firstA = firstB = 0, lastA = lastB = n-1;
	int ans = 0;
	for(int i = 0; i < n; i++)
	{
		if(A[firstA] > B[firstB])
		{
			firstA++;
			firstB++;
			ans++;
		}
		else if(A[firstA] < B[firstB])
		{
			firstA++;
			lastB--;
			ans--;
		}
		else if(A[firstA] == B[firstB])
		{
			if(A[lastA] > B[lastB])
			{
				lastA--;
				lastB--;
				ans++;
			}
			else
			{
				if(A[firstA] < B[lastB])
				{
					firstA++;
					lastB--;
					ans--;
				}
			}
		}
	}
	printf("%d\n", ans*200);
}

int main()
{
	int T;
	while(read_case())
	{
		solve();
	}
	return 0;
}
