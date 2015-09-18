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

char Haab[30][30] = {"pop", "no", "zip", "zotz", "tzec", "xul",
					 "yoxkin", "mol", "chen", "yax", "zac", 
					 "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"};

char T[30][30] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk",
				  "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", 
				  "canac", "ahau"};

int found(char *s)
{
	for(int i = 0; i < 30; i++) if(!strcmp(Haab[i], s)) return i;
	return -1;
}

void solve()
{
	int day, year;
	char month[30];
	scanf("%d. %s %d", &day, month, &year);
	int days = 0;
	days += year*365;
	int m = found(month);
	days += m*20;
	days += day;
	printf("%d %s %d\n", days%13+1, T[days%20], (int)(days/260));
}

int main()
{
	int T;
	scanf("%d", &T);
	printf("%d\n", T);
	while(T--)
	{
		solve();
	}
	return 0;
}
