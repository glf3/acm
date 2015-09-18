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

void read_case()
{
	scanf("%lld", &n);
}

int check(LL n)
{
	LL t = n;
	t /= 10;
	int a = t%10;
	if(a == 1) return 4;
	t = n;
	if(t % 10 == 1) return 1;
	else if(t % 10 == 2) return 2;
	else if(t % 10 == 3) return 3;
	else if(t % 10 == 4) return 4;
	else return 5;
}

void solve()
{
	read_case();
	int flag = check(n);
	switch(flag)
	{
		case 1:printf("%lldst\n", n);break;
		case 2:printf("%lldnd\n", n);break;
		case 3:printf("%lldrd\n", n);break;
		case 4:printf("%lldth\n", n);break;
		default:printf("%lldth\n", n);break;
	}
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
