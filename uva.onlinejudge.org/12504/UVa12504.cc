#include <iostream>  
#include <cstdlib>  
#include <cstring>  
#include <cstdio>  
#include <string>  
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <stack>
#include <sstream>
#include <cctype>
#include <bitset>
using namespace std;

const int maxn = 110;
typedef map<string, string> Map;
Map R1, R2;
char s1[maxn], s2[maxn];
char t1[maxn], t2[maxn];
int n1, n2;

void print()
{
	vector<string> v1, v2;
	char *p1 = strtok(t1, ",");
	while(p1 != NULL)
	{
		v1.push_back(p1);
		p1 = strtok(NULL, ",");
	}
	char *p2 = strtok(t2, ",");
	while(p2 != NULL)
	{
		v2.push_back(p2);
		p2 = strtok(NULL, ",");
	}
	
	string s, t;
	for(int i = 0; i < v1.size(); i++)
	{
		int p = v1[i].find(':');
		s = v1[i].substr(0, p);
		t = v1[i].substr(p+1);
		if(!R1.count(s)) R1[s] = t;
	}
	for(int i = 0; i < v2.size(); i++)
	{
		int p = v2[i].find(':');
		s = v2[i].substr(0, p);
		t = v2[i].substr(p+1);
		if(!R2.count(s)) R2[s] = t;
	}
	vector<string> add, del, change;
	for(Map::iterator it = R1.begin(); it != R1.end(); it++)
	{
		s = it->first, t = it->second;
		if(!R2.count(s))
		{
			del.push_back(s);
		}
		else if(R2.count(s))
		{
			if(t != R2[s])
				change.push_back(s);
		}
	}
	
	for(Map::iterator it = R2.begin(); it != R2.end(); it++)
	{
		s = it->first, t = it->second;
		if(!R1.count(s))
		{
			add.push_back(s);
		}
	}
	
	if(add.size() || del.size() || change.size())
	{
		if(add.size() != 0)
		{
			cout << "+" << add[0];
			for(int i = 1; i < add.size(); i++)
				cout << "," << add[i];
			cout << endl;	
		}
		if(del.size() != 0)
		{
			cout << "-" << del[0];
			for(int i = 1; i < del.size(); i++)
				cout << "," << del[i];
			cout << endl;	
		}
		if(change.size() != 0)
		{
			cout << "*" << change[0];
			for(int i = 1; i < change.size(); i++)
				cout << "," << change[i];
			cout << endl;	
		}
	}
	else printf("No changes\n");
	printf("\n");
}

int main()
{
	int T;
	for(scanf("%d", &T); T > 0; T--)
	{
		R1.clear(); R2.clear();
		n1 = n2 = 0;
		scanf("%s%s", s1, s2);
		for(int i = 1; i < strlen(s1)-1; i++)
			t1[n1++] = s1[i];
		t1[n1] = '\0';
		for(int i = 1; i < strlen(s2)-1; i++)
			t2[n2++] = s2[i];
		t2[n2] = '\0';
		print();
	}
	return 0;
}
