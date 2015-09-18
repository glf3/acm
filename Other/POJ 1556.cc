/*线段判交+最短路*/
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
 
struct Line
{
    Point P;
    Vector v;
    double ang;
    Line() {}
    Line(Point P, Vector v) : P(P), v(v) { ang = atan2(v.y, v.x); }
    bool operator < (const Line& L) const
    {
        return ang < L.ang;
    }
};
 
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
 
Vector Rotate(Vector A, double rad)
{
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad) + A.y*cos(rad));
}
 
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
 
bool OnSegment(Point p, Point a1, Point a2)
{
    return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}
 
/*double PolygonArea(Point* p, int n)
{
    double area = 0;
    for(int i = 1; i < n-1; i++)
        area += Cross(p[i]-p[0], p[i+1]-p[0]);
    return area/2;
}*/

double PolygonArea(vector<Point> p)
{
	int n = p.size();
    double area = 0;
    for(int i = 1; i < n-1; i++)
        area += Cross(p[i]-p[0], p[i+1]-p[0]);
    return area/2;
}

double PointDistanceToLine(Point P, Point A, Point B)
{
    Vector v1 = B-A, v2 = P-A;
    return fabs(Cross(v1, v2)) / Length(v1);
}
 
double PointDistanceToSegment(Point P, Point A, Point B)
{
    if(A == B) return Length(P-A);
    Vector v1 = B-A, v2 = P-A, v3 = P-B;
    if(dcmp(Dot(v1, v2) < 0)) return Length(v2);
    else if(dcmp(Dot(v1, v3) > 0)) return Length(v3);
    else return fabs(Cross(v1, v2)) / Length(v1);
}
 
int isPointInPolygon(Point p, Point *poly, int n)
{
    int wn = 0;
    for(int i = 0; i < n; i++)
    {
        const Point& p1 = poly[i], p2 = poly[(i+1)%n];
        if(p == p1 || p == p2 || OnSegment(p, p1, p2)) return -1;
        int k = dcmp(Cross(p2-p1, p-p1));
        int d1 = dcmp(p1.y - p.y);
        int d2 = dcmp(p2.y - p.y);
        if(k > 0 && d1 <= 0 && d2 > 0) wn++;
        if(k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    if(wn != 0) return 1;
    return 0;
}
 
int ConvexHull(Point *p, int n, Point *ch) //凸包
{
    sort(p, p+n);
    n = unique(p, p+n) - p; //去重
    int m = 0;
    for(int i = 0; i < n; i++)
    {
        while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2; i >= 0; i--)
    {
        while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if(n > 1) m--;
    return m;
}
 
Vector Normal(Vector A)
{
    double L = Length(A);
    return Vector (-A.y/L, A.x/L);
}

double Dist(Point p1, Point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
 
double Dist2(Point p1, Point p2)
{
    return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}
 
// 返回点集直径的平方
double RotatingCalipers(Point *P, int n) //旋转卡壳 
{
  if(n == 1) return 0;
  if(n == 2) return Dist2(P[0], P[1]);
  P[n] = P[0]; //避免取模
  double ans = 0;
  for(int u = 0, v = 1; u < n; u++)
  {
    //一条直线贴住边p[u]-p[u+1]
    for(;;)
    {
      // 当Area(p[u], p[u+1], p[v+1]) <= Area(p[u], p[u+1], p[v])时停止旋转
      // 即Cross(p[u+1]-p[u], p[v+1]-p[u]) - Cross(p[u+1]-p[u], p[v]-p[u]) <= 0
      // 根据Cross(A,B) - Cross(A,C) = Cross(A,B-C)
      // 化简得Cross(p[u+1]-p[u], p[v+1]-p[v]) <= 0
      double diff = Cross(P[u+1]-P[u], P[v+1]-P[v]);
      if(diff <= 0)
      {
        ans = max(ans, Dist2(P[u], P[v])); // u和v是对踵点
        if(diff == 0) ans = max(ans, Dist2(P[u], P[v+1])); // diff == 0时u和v+1也是对踵点
        break; //即边平行
      }
      v = (v + 1) % n;
    }
  }
  return ans;
}
 
bool OnLeft(Line L, Point p)
{
    return Cross(L.v, p-L.P) > 0;
}
 
Point GetLineIntersection2(const Line &a, const Line &b)
{
    Vector u = a.P-b.P;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.P+a.v*t;
}
 
int HalfPlaneIntersection(Line* L, int n, Point* poly)
{
    sort(L, L+n);
    int first, last;
    Point *p = new Point[n];
    Line* q = new Line[n];
    q[first=last=0] = L[0];
    for(int i = 1; i < n; i++)
    {
        while(first < last && !OnLeft(L[i], p[last-1])) last--;
        while(first < last && !OnLeft(L[i], p[first])) first++;
        q[++last] = L[i];
        if(fabs(Cross(q[last].v, q[last-1].v)) < eps)
        {
            last--;
            if(OnLeft(q[last], L[i].P)) q[last] = L[i];
        }
        if(first < last) p[last-1] = GetLineIntersection2(q[last-1], q[last]);
    }
    while(first < last && !OnLeft(q[first], p[last-1])) last--;
    if(last - first <= 1) return 0;
    p[last] = GetLineIntersection2(q[last], q[first]);
     
    int m = 0;
    for(int i = first; i <= last; i++) poly[m++] = p[i];
    return m;
}
 
vector<Point> CutPolygon(const vector<Point> &poly, Point A, Point B) //可返回单点或者线段 
{
    vector<Point> newpoly;
    int n = poly.size();
    for(int i = 0; i < n; i++)
    {
        Point C = poly[i], D = poly[(i+1)%n];
        if(dcmp(Cross(B-A, C-A)) >= 0) newpoly.push_back(C);
        if(dcmp(Cross(B-A, C-D)) != 0)
        {
            Point ip = GetLineIntersection(A, B-A, C, D-C);
            if(OnSegment(ip, C, D)) newpoly.push_back(ip);
        }
    }
    return newpoly;
}

const int maxn = 1110;
const double INF = 0x3f3f3f3f;

Line L[maxn];

Point read_point()
{
    Point A;
    scanf("%lf%lf", &A.x, &A.y);
    return A;
}

struct Edge
{
	int v;
	double w;
	int next;
}edge[4*maxn];

int cnt;
int first[maxn];
double d[maxn];

void init()
{
	cnt = 0;
	memset(first, -1, sizeof(first));
}

void read_graph(int u, int v, double w)
{
	edge[cnt].v = v, edge[cnt].w = w;
	edge[cnt].next = first[u], first[u] = cnt++;
}

double py[20][4];
double wx[20];

int psize;

int n;

Point P[maxn];

int check(Point a, Point b)
{
	if(dcmp(a.x - b.x) >= 0) return 0;
	int i = 0;
	while(wx[i] <= a.x && i < n) i++;
	while(wx[i] < b.x && i < n)
	{
		Point p1 = Point(wx[i], 0), p2 = Point(wx[i], py[i][0]);
		Point p3 = Point(wx[i], py[i][1]), p4 = Point(wx[i], py[i][2]);
		Point p5 = Point(wx[i], py[i][3]), p6 = Point(wx[i], 10);
		if(SegmentProperIntersection(a, b, p1, p2)
		|| SegmentProperIntersection(a, b, p3, p4)
		|| SegmentProperIntersection(a, b, p5, p6)) return 0;
		
		i++;
	}
	return 1;
}

double spfa(int src, int end)
{
	queue<int> q;
	bool inq[maxn] = {0};
	for(int i = 0; i < maxn; i++) d[i] = (i == src)? 0:INF;
	q.push(src);
	while(!q.empty())
	{
		int x = q.front(); q.pop();
		inq[x] = 0;
		for(int e = first[x]; e != -1; e = edge[e].next)
		{
			int v = edge[e].v;
			double w = edge[e].w;
			if(d[v] > d[x] + w)
			{
				d[v] = d[x] + w;
				if(!inq[v])
				{
					inq[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return d[end];
}

int read_case()
{
	init();
	scanf("%d", &n);
	if(n == -1) return 0;
	P[0] = Point(0, 5);
	psize = 1;
	for(int i = 0; i < n; i++)
	{
		scanf("%lf", &wx[i]);
		for(int j = 0; j < 4; j++)
		{
			scanf("%lf", &py[i][j]);
			P[psize++] = Point(wx[i], py[i][j]);
		}
	}
	P[psize++] = Point(10, 5);
	for(int i = 0; i < psize; i++)
	{
		for(int j = i+1; j < psize; j++)
		{
			if(check(P[i], P[j])) read_graph(i, j, Dist(P[i], P[j]));
		}
	}
	return 1;
}

void solve()
{
	double ans = spfa(0, psize-1);
	printf("%.2lf\n", ans);
}

int main()
{
	while(read_case())
	{
		solve();
	}
	return 0;
}
