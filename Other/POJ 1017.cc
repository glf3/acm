/*经典装箱问题*/
/*装体积为3的箱子时需考虑特殊情况*/
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
using namespace std;


const int maxn = 10030;
const int INF = 0x3f3f3f3f;

int box[5] = {0, 5, 3, 1}; //余数分别为0,1,2,3时可以装2*2SIZE的箱子的个数 

int n1, n2, n3, n4, n5, n6;

int read_case()
{
	scanf("%d %d %d %d %d %d", &n1, &n2, &n3, &n4, &n5, &n6);
	if(n1+n2+n3+n4+n5+n6 == 0) return 0;
	return 1;
}

void solve()
{
	int ans = 0;
	ans = n4+n5+n6+(int)ceil(1.0*n3/4);
	int y = n4*5 + box[n3%4];
	if(n2 > y) ans += (int)ceil(1.0*(n2-y)/9);
	int empty = 36*ans - 36*n6 - 25*n5 - 16*n4 - 9*n3 - 4*n2;
	if(n1 > empty) ans += (int)ceil(1.0*(n1-empty)/36);
	printf("%d\n", ans);
}

int main()
{
	while(read_case())
	{
		solve();
	}
	return 0;
}
