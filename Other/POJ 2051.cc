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

struct Argus
{
	int Period, time;
	int num;
	bool operator < (const Argus &a) const //从小到大 
	{
		if(time != a.time) return time > a.time;
		return num > a.num;
	}
};

priority_queue<Argus> Q;

int k;

void read_case()
{
	char str[20];
	int num = 0;
	while(scanf("%s", str) && strcmp(str, "#"))
	{
		int num, Period;
		scanf("%d%d", &num, &Period);
		Argus A;
		A.num = num, A.Period = Period, A.time = Period;
		Q.push(A);
	}
	scanf("%d", &k);
}

void solve()
{
	read_case();
	for(int i = 0; i < k; i++)
	{
		Argus A = Q.top(); Q.pop();
		printf("%d\n", A.num);
		A.time += A.Period;
		Q.push(A);
	}
}

int main()
{
	solve();
	return 0;
}
