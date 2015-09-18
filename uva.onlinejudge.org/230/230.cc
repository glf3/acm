/*
题意：模拟一个图书馆管理系统。首先输入若干图书的标题和作者，然后是若干指令：
BORROW指令表示借书，RETURN指令表示还书，
SHELVE表示把所有已归还但还未上架的图书与在书架中的书比较大小，
排序后依次插入书架并输出图书标题和插入位置。
图书排序的方法是先按作者从小到大排序，然后再按标题从小到大排序。
在处理第一条指令前，你应当将所有图书按照这种方式排序。

对于每一个书名，用map映射作者为后面插入排序用，然后自定义set<Node>中Node的排序方法。
一个存书架中的书单，另外一个存还书的书单，每当遇到一个SHELVE，将还书书单清空即可。
刚开始以为只要将还书的书单排序，而不需要与在书架中的书单比较大小错了几次。
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <sstream>
using namespace std;

typedef map<string, string> Map;

struct Node
{
	string title, name;
	
	Node() {}
	Node(string title, string name):title(title), name(name) {}
	bool operator < (const Node &rhs) const
	{
		if(name != rhs.name) return name < rhs.name;
		else return title < rhs.title;
	}
};

typedef set<Node> Set;

Map R;
Set list, S;
Set::iterator it, it1;

void setDel(string title)
{
	for(it = list.begin(); it != list.end(); it++)
		if(it->title == title)
			 { list.erase(it); break; }
}

Set::iterator find(string title)
{
	for(it = list.begin(); it != list.end(); it++)
		if(it->title == title)
			return (--it);
}

int main()
{
	list.clear(); R.clear(); S.clear();
	string s, title, name;
	int p, q;
	while(getline(cin, s))
	{
		if(s == "END") break;
		p = s.find('"', 1); q = s.find('y', p+1);
		title = s.substr(0, p+1); name = s.substr(q+2);
		list.insert(Node(title, name));
		R[title] = name;
	}
	
	string t, s2;
	while(getline(cin, s))
	{
		if(s == "END") break;
		if(s[0] == 'B')
		{
			p = s.find(' ');
			t = s.substr(0, p); s2 = s.substr(p+1);
			setDel(s2);
		}
		else if(s[0] == 'R')
		{
			p = s.find(' ');
			t = s.substr(0, p); s2 = s.substr(p+1);
			S.insert(Node(s2, R[s2]));
		}
		else if(s[0] == 'S')
		{
			for(Set::iterator it = S.begin(); it != S.end(); it++)
			{
				title = it->title;
				list.insert(Node(title, R[title]));
				if(list.begin()->title == title)
				{
					cout << "Put " << title << " first" << endl;
				}
				else
				{
					it1 = find(title);
					cout << "Put " << title << " after " << it1->title << endl;
				}
			}
			cout << "END" << endl;
			S.clear();
		}
	}
	return 0;
}
