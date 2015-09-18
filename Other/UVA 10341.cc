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

#define F(x) (p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u)

const double eps = 1e-14;

int main()
{
	int p, r, q, s, t, u;
	while(~scanf("%d%d%d%d%d%d", &p, &q, &r, &s, &t, &u))
	{
		double f0 = F(0), f1 = F(1);
		if(f1 > eps || f0 < -eps) printf("No solution\n");
		else
		{
			double m;
			double x = 0, y = 1;
			while(y-x > eps)
			{
				m = x + (y-x)/2;
				if(F(m) < 0) y = m; else x = m;
			}
			printf("%.4lf\n", m);
		}
	}
	return 0;
}
