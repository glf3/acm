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

int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int day[8] = {7, 1, 2, 3, 4, 5, 6};

int n, m;

int read_case()
{
	scanf("%d%d", &n, &m);
	if(n > month[m]) return 0;
	return 1;
}

void solve()
{
	if(!read_case()) printf("Impossible\n");
	int days = 0;
	for(int i = 0; i < m; i++)
	{
		days += month[i];
	}
	days += n;
	printf("%d\n", day[days%7]);
}

int main()
{
	solve();
	return 0;
}
