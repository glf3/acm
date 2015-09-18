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
#include <sstream>
#include <set>
#include <map>
using namespace std;

const int maxn = 120000 + 100;
const int maxd = 100 + 100;

map<string, int> M;
typedef set<string> Set;

char s[maxn][maxd];

int main()
{
	int n = 0;
	while(~scanf("%s", s[n]))
	{
		if(!M.count(s[n])) M[s[n]] = 1;
		n++;
	}
	
	vector<string> ans;
	Set S;
	
	for(int i = 0; i < n; i++)
	{
		int len = strlen(s[i]);
		
		for(int j = 1; j < len; j++)
		{
			char s1[maxd] = {'\0'}, s2[maxd] = {'\0'};
			strncpy(s1, s[i], j);
			strncpy(s2, s[i]+j, len-j);
			
			if(M.count(s1) && M.count(s2)) S.insert(s[i]);
		}
	}
	for(Set::iterator it = S.begin(); it != S.end(); it++)
		cout << *it << endl;
	return 0;
}
