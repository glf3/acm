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

const double eps = 1e-8;
const double PI = acos(-1.0);

struct Point
{
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) { }
	bool operator < (const Point& a) const
	{
		if(a.x != x) return x < a.x;
		return y < a.y;
	}
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }

Vector operator - (Point A, Point B) { return Vector(A.x-B.x, A.y-B.y); }

Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }

Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }

int dcmp(double x)
{
	if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

bool operator == (const Point& a, const Point &b)
{
	return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }

double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
double Area2(Point A, Point B, Point C) { return fabs(Cross(B-A, C-A)) / 2; }

Point GetLineIntersection(Point P, Vector v, Point Q, Vector w)
{
	Vector u = P-Q;
	double t = Cross(w, u) / Cross(v, w);
	return P+v*t;
}

bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2)
{
	double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1);
	double c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
	return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

double PointDistanceToLine(Point P, Point A, Point B)
{
	Vector v1 = B-A, v2 = P-A;
	return Cross(v1, v2);
}

double PointDistanceToSegment(Point P, Point A, Point B)
{
	if(A == B) return Length(P-A);
	Vector v1 = B-A, v2 = P-A, v3 = P-B;
	if(dcmp(Dot(v1, v2) < 0)) return Length(v2);
	else if(dcmp(Dot(v1, v3) > 0)) return Length(v3);
	else return fabs(Cross(v1, v2)) / Length(v1);
}

double sqr(double x) { return x*x; }

double Dist(Point A, Point B)
{
	return sqrt(sqr(A.x-B.x) + sqr(A.y-B.y));
}

Point read_point()
{
	Point A;
	scanf("%lf%lf", &A.x, &A.y);
	return A;
}

const int maxn = 1010;

Point P[maxn], Q[maxn];

Vector v1[maxn];

bool IsIntersection(Point P, Point Q, Point A, Point B)
{
	Vector v1 = B-A, v2 = P-A;
	Vector v3 = B-A, v4 = Q-A;
	//printf("%lf\n", Cross(v1, v2) - Cross(v3, v4));
	return Cross(v1, v2) * Cross(v3, v4);
}

int n;

int equal(Point A, Point B)
{
	if(dcmp(A.x-B.x) == 0 && dcmp(A.y-B.y) == 0) return 1;
	return 0;
}

void read_case()
{
	scanf("%d", &n);
	for(int i = 0; i < 2*n; i += 2)
	{
		P[i] = read_point();
		P[i+1] = read_point();
	}
}

int check()
{
	int flag = 0;
	for(int i = 0; i < 2*n; i++)
	{
		for(int j = i+1; j < 2*n; j++)
		{
			if(!equal(P[i], P[j]))
			{
				flag = 1;
				for(int k = 0; k < 2*n; k+=2)
				{
					if(IsIntersection(P[k], P[k+1], P[i], P[j]) > eps)
					{
						flag = 0;
						break;
					}
				}
				if(flag) return 1;
			}
		}
	}
	if(!flag) return 0;
	return 1;	
}

void solve()
{
	read_case();
	if(check()) printf("Yes!\n");
	else printf("No!\n");
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
