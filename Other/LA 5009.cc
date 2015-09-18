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
#include <map>
using namespace std;

const int maxn = 10010;

int n, a[maxn], b[maxn], c[maxn];

double F(double x)
{
	double ans = a[0]*x*x+b[0]*x+c[0];
	for(int i = 0; i < n; i++)
		ans = max(ans, a[i]*x*x+b[i]*x+c[i]);
	return ans;
}

const double eps = 1e-10;

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%d%d%d", &a[i], &b[i], &c[i]);
		double x = 0, y = 1000.0;
		double m;
		while(y-x > eps)
		{
			double m1 = x+(y-x)/3;
			double m2 = y-(y-x)/3;
			if(F(m1) < F(m2)) y = m2; else x = m1;
		}
		printf("%.4lf\n", F(x));
	}
	return 0;
}
