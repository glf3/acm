#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct Point
{
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) { }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }

Vector operator - (Point A, Point B) { return Vector(A.x-B.x, A.y-B.y); }

Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }

Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }

bool operator < (const Point &a, const Point &b)
{
	if(a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

const double eps = 1e-8;

int dcmp(double x)
{
	if(fabs(x) < eps) return 0; return x < 0 ? -1 : 1;
}

bool operator == (const Point &a, const Point &b)
{
	return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }

double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
double Area2(Point A, Point B, Point C) { return Cross(B-A, C-A); }

Vector Rotate(Vector A, double rad)
{
	return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}

Point GetIntersection(Point P, Vector v, Point Q, Vector w)
{
	Vector u = P-Q;
	double t = Cross(w, u) / Cross(v, w);
	return P+v*t;
}

Point A, B, C, D, E, F;

Point read_point()
{
	Point A;
	scanf("%lf%lf", &A.x, &A.y);
	return A;
}

Point getD(Point A, Point B, Point C)
{
	Vector v1 = B-A, v2 = C-A;
	double a1 = Angle(v1, v2);
	if(Cross(C-A, B-A) > 0) a1 = -a1; 
	v1 = Rotate(v1, a1/2);
	
	Vector v3 = B-C;
	return GetIntersection(A, v1, B, v3);
}

void solve()
{
	A = read_point();
	B = read_point();
	C = read_point();
	Point P = getD(A, B, C);
	printf("%.2f %.2f\n", P.x, P.y);
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
