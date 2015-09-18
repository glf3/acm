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
using namespace std;

typedef pair<char, int> PII;
map<char, int> E;

typedef map<PII, int> Map;
Map R;

int alldigit(string s)
{
	for(int i = 0; i < s.length(); i++)
		if(!isdigit(s[i])) return 0;
	return 1;
}

int main()
{
	R.clear(); E.clear();
	stack<string> st1, st2;
	string s, t;
	int size, b;
	
	int ans = 0, flag = 0, count = 0;
	int exit = 0;
	while(cin >> s)
	{
		if(s == ".")
		{
			if(exit) break;
			else
			{
				if(flag) printf("%d\n", ans);
				else printf("0\n");
				exit = 1;
				R.clear();
				E.clear();
				count = 0;
				flag = 0;
				continue ;
			}
		}
		exit = 0;
		if(flag) continue ;
		++count;
		int p = s.find('=');
		if(p == string::npos)
		{
			int p1 = s.find('['), p2 = s.find(']');
			t = s.substr(p1+1, p2-p1-1);
			stringstream ss(t);
			ss >> size;
			b = s[p1-1];
			if(!E[b]) E[b] = size;
		}
		else
		{
			t = s.substr(0, p);
			s = s.substr(p+1);
			//cout << t << " " << s << endl;
			//system("pause");
			char x = 0; int y = 0;
			string a, b;
			int q = 0;
			if(!alldigit(s)) //先算右值，再算左值，如果右值不合法直接跳出，而左值则没有关系。
			{
				for(int i = 0; i < s.length(); i++)
				{
					if(s[i] != '[' && s[i] != ']')
					{
						string tmp = "";
						tmp += s[i];
						while(i+1 < s.length() && isdigit(s[i+1]))
						{
							i++;
							tmp += s[i];
						}
						st2.push(tmp);
					}
					else if(s[i] == ']')
					{
						a = st2.top(); st2.pop();
						b = st2.top(); st2.pop();
						char t1 = b[0]; int t2;
						stringstream ss(a);
						ss >> t2;
						PII pii = make_pair(t1, t2);
						//printf("%c %d %d\n", t1, t2, R.count(pii));
						if(E[t1] <= t2)
						{
							ans = count;
							flag = 1;
							break;
						}
						else if(!R.count(pii))
						{
							ans = count;
							flag = 1;
							break;
						}
						else
						{
							/*printf("%yes\n");
							printf("x:%c y:%d q:%d\n", x, y, q);*/
							stringstream ss;
							ss << R[pii];
							string tmp;
							ss >> tmp;
							st2.push(tmp);
						}
					}
				}
				if(!flag)
				{
					q = 0;
					string p = st2.top();
					for(int i = 0; i < p.length(); i++)
						q = q*10+p[i]-'0';
				}
			}
			else //算右值 
			{
				q = 0;
				for(int i = 0; i < s.length(); i++)
					q = q*10+s[i]-'0';
			}
			if(flag) continue ;
			int can = 0;
			for(int i = 0; i < t.length(); i++)
			{
				if(t[i] != '[' && t[i] != ']')
				{
					string tmp = "";
					tmp += t[i];
					while(i+1 < t.length() && isdigit(t[i+1]))
					{
						i++;
						tmp += t[i];
					}
					st1.push(tmp);
				}
				else if(t[i] == ']')
				{
					if(st1.size() != 2) can = 1;
					a = st1.top(); st1.pop();
					b = st1.top(); st1.pop();
					char t1 = b[0]; int t2;
					stringstream ss(a);
					ss >> t2;
					PII pii = make_pair(t1, t2);
					if(E[t1] <= t2)
					{
						ans = count;
						flag = 1;
						break;
					}
					else if(!R.count(pii) && can == 1) //保证所有嵌套下标都处理完 
					{
						ans = count;
						flag = 1;
						break;
					}
					else
					{
						stringstream ss;
						ss << R[pii];
						string tmp;
						ss >> tmp;
						st1.push(tmp);
						x = t1, y = t2;
					}
					can = 0;
				}
			}
			
			if(!flag)
			{
				R[make_pair(x, y)] = q;
				//printf("x:%c y:%d q:%d\n", x, y, q);
			}
			while(!st1.empty()) st1.pop();
			while(!st2.empty()) st2.pop();
		}
	}
	return 0;
}
