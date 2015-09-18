#include <iostream>  
#include <cstdlib>  
#include <cstring>  
#include <cstdio>  
#include <string>  
#include <algorithm>
#include <map>
#include <vector>
#include <set>
using namespace std;

typedef pair<double, double> PII;

typedef set<PII> Set;
Set::iterator its;
Set S;

typedef map<double, vector<PII> > Map;
Map::iterator itm;
Map R;

int ok()
{
	for(itm = R.begin(); itm != R.end(); itm++)
	{
		vector<PII> b = R[itm->first];
		for(int i = 0; i < b.size(); i++)
		{
			int flag = 1;
			double x1 = b[i].first, y1 = b[i].second;
			for(int j = 0; j < b.size(); j++)
			{
				double x2 = b[j].first, y2 = b[j].second;
				double t = (x1+x2)/2;
				for(its = S.begin(); its != S.end(); its++)
				{
					double x3 = 2*t-its->first, y3 = its->second;
					if(!S.count(make_pair(x3, y3)))
					{
						flag = 0;
						break;
					}
				}
				if(flag) return 1;
			}
		}
	}
	return 0;
}

int main()
{
	int T;
	for(scanf("%d", &T); T > 0; T--)
	{
		int n; scanf("%d", &n);
		S.clear();
		R.clear();
		for(int i = 0; i < n; i++)
		{
			double x, y; scanf("%lf%lf", &x, &y);
			if(!R.count(y)) R[y] =  vector<PII>();
			R[y].push_back(make_pair(x, y));
			S.insert(make_pair(x, y));
		}
		
		if(ok()) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
