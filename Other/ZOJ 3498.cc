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

int n;

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int ans = 0;
		scanf("%d", &n);
		while(n) ans++, n /= 2;
		printf("%d\n", ans);
	}
	return 0;
}
