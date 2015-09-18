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
#include <map>
using namespace std;

const int maxn = 100;
const int INF = 0x3f3f3f3f;

int n, m;

struct Matrix
{
	int mat[maxn][maxn];
	Matrix() { memset(mat, 0, sizeof(mat)); }
	
	void input()
	{
		for(int i = 0; i < m; i++)
		{
			for(int j = 0; j < m; j++)
			{
				scanf("%d", &mat[i][j]);
			}
		}
	}
	
	void unit()
	{
		memset(mat, 0, sizeof(mat));
		for(int i = 0; i < m; i++) mat[i][i] = 1;
	}
	
	Matrix& operator = (const Matrix &a)
	{
		memcpy(mat, a.mat, sizeof(a.mat));
		return *this;
	}
	
	friend Matrix operator * (const Matrix &a, const Matrix &b)
	{
		Matrix ans;
		for(int i = 0; i < m; i++)
		{
			for(int j = 0; j < m; j++)
			{
				for(int k = 0; k < m; k++)
				{
					ans.mat[i][j] += a.mat[i][k] * b.mat[k][j];
				}
			}
		}
		return ans;
	}
	
	friend bool operator == (const Matrix &a, const Matrix &b)
	{
		for(int i = 0; i < m; i++)
		{
			for(int j = 0; j < m; j++)
			{
				if(a.mat[i][j] != b.mat[i][j]) return 0;
			}
		}
		return 1;
	}
};

Matrix A[maxn];

int d[maxn][maxn];

void init()
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			d[i][j] = (i == j)? 0:INF;
		}
	}
}

void Floyd()
{
	for(int k = 0; k < n; k++)
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
			}
		}
	}
}

int read_case()
{
	scanf("%d%d", &n, &m);
	init();
	if(!n) return 0;
	for(int i = 0; i < n; i++) A[i].input();
	return 1;
}

void build()
{
	Matrix C;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++) if(i != j)
		{
			C = A[i]*A[j];
			for(int k = 0; k < n; k++) if(i != k && j != k)
			{
				if(C == A[k]) d[i][k] = 1;
			}
		}
	}
}

void solve()
{
	int q;
	build();
	Floyd();
	scanf("%d", &q);
	while(q--)
	{
		int u, v;
		scanf("%d%d", &u, &v); u--; v--;
		if(d[u][v] != INF) printf("%d\n", d[u][v]);
		else printf("Sorry\n");
	}
}

int main()
{
	while(read_case())
	{
		solve();
	}
	return 0;
}
