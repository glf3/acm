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

const double R = 6875.0;
const double PI = acos(-1.0);
const double eps = 1e-8;

struct Point
{
	double x, y, z;
	Point(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {};
};

double torad(double rad)
{
	return rad/180 * PI;
}

Point A, B;

void get_coord(double R, double lat, double lng, Point &P) //lat 纬度, lng 经度 
{
	lat = torad(lat);
	lng = torad(lng);
	P.x = R*cos(lat)*cos(lng);
	P.y = R*cos(lat)*sin(lng);
	P.z = R*sin(lat);
}

double lat, lng;

double Dist3D(Point A, Point B)
{
	return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y) + (A.z-B.z) * (A.z-B.z));
}

double GetDistance(double d)
{
	return 2*asin(d/(2*R))*R;
}

const int maxn = 100;

char s[50][maxn];

int n;

int check(char *s)
{
	int len = strlen(s);
	for(int i = 0; i < len; i++) if(s[i] == 'S' || s[i] == 'W') return 1;
	return 0;
}

void read_case()
{
	n = 1;
	char str[maxn];
	for(;;)
	{
		gets(s[n]);
		if(!strcmp(s[n], "===")) break;
		n++;
	}
	double a, b, c;
	sscanf(s[4], "%lf^%lf'%lf''", &a, &b, &c);
	lat = a*1.0 + b*1.0/60.0 + c*1.0/3600.0;
	if(check(s[4])) lat = -lat;
	sscanf(s[5], "%s %lf^%lf'%lf''", str, &a, &b, &c);
	lng = a + b*1.0/60.0 + c*1.0/3600.0;
	if(check(s[5])) lng = -lng;
	get_coord(R, lat, lng, A);
	sscanf(s[7], "%lf^%lf'%lf''", &a, &b, &c);
	lat = a + b/60 + c/3600;
	if(check(s[7])) lat = -lat;
	sscanf(s[8], "%s %lf^%lf'%lf''", str, &a, &b, &c);
	lng = a + b/60 + c/3600;
	if(check(s[8])) lng = -lng;
	get_coord(R, lat, lng, B);
}

int dcmp(double x)
{
	if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

void solve()
{
	read_case();
	double d = Dist3D(A, B);
	double ans = GetDistance(d) / 2;
	printf("The distance to the iceberg: %.2lf miles.\n", ans);
	if(dcmp(floor(ans*100+0.5) - 10000) < 0) printf("DANGER!\n"); //精确到小数点后3位。
	//精度很坑爹的。 
}

int main()
{
	//freopen("titanic8.in","r",stdin);
	//freopen("me_titanic8.out","w",stdout);
	solve();
	system("pause");
	return 0;
}

/*
in:
	
Message #488.
Received at 18:15:23.
Current ship's coordinates are
40^09'18" NL
and 1^00'01" WL.
An iceberg was noticed at
40^50'11" NL
and 1^00'00" EL.
===

out:
	
The distance to the iceberg: 100.00 miles.

in:
	
Message #488.
Received at 18:15:23.
Current ship's coordinates are
40^09'19" NL
and 1^00'01" WL.
An iceberg was noticed at
40^50'12" NL
and 1^00'00" EL.
===

out:
	
The distance to the iceberg: 99.99 miles.
DANGER!

*/
