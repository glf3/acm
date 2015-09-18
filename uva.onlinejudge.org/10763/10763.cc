#include <iostream>  
#include <cstdlib>  
#include <cstring>  
#include <cstdio>  
#include <string>  
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

typedef pair<int, int> PII;

map<PII, int> a;
map<PII, int>::iterator it;

#define readint(T) scanf("%d", &T)
const int maxn = 500000 + 100;
int n;

void print()
{
	for(it = a.begin(); it != a.end(); it++)
	{
		int x = it->first.first, y = it->first.second, sz = it->second;
		if(a[make_pair(y, x)] != sz) { printf("NO\n"); return ;}
	}
	printf("YES\n");
}

int main()
{
	for(;;)
	{
		readint(n); if(!n) break;
		
		a.clear();
		for(int i = 0; i < n; i++)
		{
			int x, y; readint(x), readint(y);
			PII p = make_pair(x, y);
			if(!a.count(p)) a[p] = 0;
			a[p]++;
		}
		print();
	}
	return 0;
}
