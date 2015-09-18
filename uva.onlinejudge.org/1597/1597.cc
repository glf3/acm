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
const int maxm = 1500 + 10;

typedef pair<int, string> PII;
typedef map<PII, bitset<maxm> > Map;
Map R;

string article[maxn][maxm];
int size[maxn];

inline void transform(string &s)
{
	for(int i = 0; i < s.length(); i++)
		if(isalpha(s[i]))
			s[i] = tolower(s[i]);
		else
			s[i] = ' ';
}

int n;

inline void read()
{
	string s, t;
	scanf("%d%*c", &n);
	for(int i = 0; i < n; i++)
	{
		int b = 0;
		while(getline(cin, s) && s != "**********")
		{
			article[i][b] = s;
			transform(s);
			stringstream ss(s);
			while(ss >> t)
			{
				PII pii = make_pair(i, t);
				if(!R.count(pii)) R[pii] = bitset<maxm>();
				R[pii].set(b);
			}
			b++;
		}
		size[i] = b;
	}
}

inline int search1(const string s)
{
	string ans = "";
	int ok = 0, find = 0;
	for(int i = 0; i < n; i++)
	{
		PII pii = make_pair(i, s);
		if(R.count(pii))
		{
			ok = find = 1;
			bitset<maxm> b = R[pii];
			for(int j = 0; j < b.size(); j++) if(b.test(j))
				ans += article[i][j] + "\n";
		}
		if(ok) { ans += "----------\n"; ok = 0; }
	}
	if(!find) return 0;
	ans = ans.substr(0, ans.length()-11);
	cout << ans;
	return 1;
}

inline int search2(const string s)
{
	bool vis[maxn] = {0};
	string ans = "";
	int find = 0;
	for(int i = 0; i < n; i++)
	{
		PII pii = make_pair(i, s);
		if(!R.count(pii))
		{
			find = 1;
			for(int j = 0; j < size[i]; j++)
				ans += article[i][j] + "\n";
			ans += "----------\n";
		}
	}
	if(!find) return 0;
	ans = ans.substr(0, ans.length()-11);
	cout << ans;
	return 1;
}

inline int search3(const string s, const string t)
{
	string ans = "";
	int ok = 0, find = 0;
	for(int i = 0; i < n; i++)
	{
		PII pii1 = make_pair(i, s), pii2 = make_pair(i, t);
		bitset<maxm> b;
		if(R.count(pii1) && R.count(pii2))
		{
			ok = find = 1;
			b = R[pii1] | R[pii2];
			for(int j = 0; j < b.size(); j++) if(b.test(j))
				ans += article[i][j] + "\n";
		}
		if(ok) { ans += "----------\n"; ok = 0; }
	}
	if(!find) return 0;
	ans = ans.substr(0, ans.length()-11);
	cout << ans;
	return 1;
}

inline int search4(const string s, const string t)
{
	string ans = "";
	int ok = 0, find = 0;
	for(int i = 0; i < n; i++)
	{
		PII pii1 = make_pair(i, s), pii2 = make_pair(i, t);
		bitset<maxm> b;
		//if(R.count(pii1) || R.count(pii2)) //犯了同样的错误，应该先判断是否存在，如果直接R[pii2]，相当于插入但没赋值。
		if(R.count(pii1))
		{
			ok = find = 1;
			b = b | R[pii1];
		}
		if(R.count(pii2))
		{
			ok = find = 1;
			b = b | R[pii2];
		}
		for(int j = 0; j < b.size(); j++) if(b.test(j))
			ans += article[i][j] + "\n";
		
		if(ok) { ans += "----------\n"; ok = 0; }
	}
	if(!find) return 0;
	ans = ans.substr(0, ans.length()-11);
	cout << ans;
	return 1;
}

inline void print()
{
	string s, t[3];
	int q; scanf("%d%*c", &q);
	
	while(q--)
	{
		getline(cin, s);
		stringstream ss(s);
		int b = 0, find = 0;
		while(ss >> t[b]) b++;
		if(b == 1)
		{
			find = search1(t[0]);
		}
		else if(b == 2)
		{
			find = search2(t[1]);
		}
		else if(b == 3)
		{
			if(t[1] == "AND")
			{
				find = search3(t[0], t[2]);
			}
			else if(t[1] == "OR")
			{
				find = search4(t[0], t[2]);
			}
		}
		if(!find) cout << "Sorry, I found nothing." << endl;
		cout << "==========" << endl;
	}
}

int main()
{
	read();
	print();
	return 0;
}
