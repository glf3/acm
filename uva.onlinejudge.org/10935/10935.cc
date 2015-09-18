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
using namespace std;

int main()
{
	int n;
	while(~scanf("%d", &n) && n)
	{
		vector<int> ans;
		deque<int> dq;
		int x;
		if(n == 1)
		{
			if(n == 1)
			{
				printf("Discarded cards:\n");
				printf("Remaining card: %d\n", 1);
			}
			continue ;
		}
		for(int i = 1; i <= n; i++)
			dq.push_back(i);
		while(dq.size() != 2)
		{
			x = dq.front(); dq.pop_front();
			ans.push_back(x);
			x = dq.front(); dq.pop_front();
			dq.push_back(x);
		}
		x = dq.front(); dq.pop_front();
		ans.push_back(x);
		int remain = dq.front();
		printf("Discarded cards: %d", ans[0]);
		for(int i = 1; i < ans.size(); i++)
			printf(", %d", ans[i]);
		printf("\nRemaining card: %d\n", remain);
	}
	return 0;
}
