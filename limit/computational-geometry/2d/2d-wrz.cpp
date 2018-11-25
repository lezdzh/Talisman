// c++11

#include<bits/stdc++.h>
using namespace std;

const double inf = 1e9;
const double eps = 1e-9;
const double pi = acos(-1.0);

/*精度误差下的各种运算*/
bool le(double x, double y){return x < y - eps;} // x严格小于y
bool leq(double x, double y){return x < y + eps;} // x小于等于y
bool equ(double x, double y){return fabs(x - y) < eps;} // x等于y
double mysqrt(double x) {return x < eps ? 0 : sqrt(x);} // 开根号
double sqr(double x) {return x * x;} // 平方

struct point // 点或向量
{
	double x, y;
	double operator * (point that){return x*that.x + y*that.y;}
	double operator ^ (point that){return x*that.y - y*that.x;}
	point operator * (double t){return (point){x*t, y*t};}
	point operator / (double t){return (point){x/t, y/t};}
	point operator + (point that) {return (point){x + that.x, y + that.y};}
	point operator - (point that) {return (point){x - that.x, y - that.y};}
	double len(){return mysqrt(x*x+y*y);} // 到原点距离/向量长度
	point reset_len(double t) // 改变向量长度为t，t为正则方向不变，t为负则方向相反
	{
		double p = len();
		return (point){x*t/p, y*t/p};
	}
	point rot90() {return (point){-y, x};} // 逆时针旋转90度
	point rotate(double angle) // 使向量逆时针旋转angle弧度
	{
		double c = cos(angle), s = sin(angle);
		return (point){c * x  - s * y, s * x + c * y};
	}
};

struct line // 参数方程表示，p为线上一点，v为方向向量
{
	point p, v; // p为线上一点，v为方向向量

	double angle; // 半平面交用，用atan2计算，此时v的左侧为表示的半平面。注意有的函数声明一个新的line时没有初始化这个值！
	bool operator < (const line &that) const {return angle < that.angle;} // 半平面交用，按与x轴夹角排序
};

struct circle
{
	point c; double r;
};


double distance(point a, point b) // a，b两点距离
{
	return mysqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
 
circle make_circle(point a, point b) // 以a，b两点为直径作圆
{
	double d = distance(a, b);
	return (circle){(a+b)/2, d/2};
}
 
double point_to_line(point a, line b) // 点a到直线b距离
{
	return fabs((b.v ^ (a - b.p)) / b.v.len());
}
 
point project_to_line(point a, line b) // 点a到直线b的垂足/投影
{
	return b.v.reset_len((a - b.p) * b.v / b.v.len()) + b.p;
}
 
vector<point> circle_inter(circle a, circle b) // 圆a和圆b的交点，需保证两圆不重合，圆的半径必须大于0
{
	double d = distance(a.c, b.c); 
	vector<point> ret;
	if(le(a.r + b.r, d) || le(a.r + d, b.r) || le(b.r + d, a.r)) return vector<point>(); // 相离或内含
	point r = (b.c - a.c).reset_len(1);
	double x = ((sqr(a.r) - sqr(b.r)) / d + d) / 2;
	double h = mysqrt(sqr(a.r) - sqr(x));
	if(equ(h, 0)) return vector<point>({a.c + r * x}); // 内切或外切
	else return vector<point>({a.c + r*x + r.rot90()*h, a.c + r*x - r.rot90()*h}); // 相交两点
}
 
vector<point> line_circle_inter(line a, circle b) // 直线a和圆b的交点
{
	double d = point_to_line(b.c, a);
	if(le(b.r, d)) return vector<point>(); // 不交
	double x = mysqrt(sqr(b.r) - sqr(d));
	point p = project_to_line(b.c, a);
	if(equ(x, 0)) return vector<point> ({p}); // 相切
	else return vector<point> ({p + a.v.reset_len(x), p - a.v.reset_len(x)}); // 相交两点
}
 
point line_inter(line a, line b) // 直线a和直线b的交点，需保证两直线不平行
{
	double s1 = a.v ^ (b.p - a.p);
	double s2 = a.v ^ (b.p + b.v - a.p);
	return (b.p * s2 - (b.p + b.v) * s1) / (s2 - s1);
}
 
vector<point> tangent(point p, circle a) // 过点p的圆a的切线的切点，圆的半径必须大于0
{
	circle c = make_circle(p, a.c);
	return circle_inter(a, c);
}
 
vector<line> intangent(circle a, circle b) // 圆a和圆b的内公切线
{
	point p = (b.c * a.r + a.c * b.r) / (a.r + b.r);
	vector<point> va = tangent(p, a), vb = tangent(p, b);
	vector<line> ret;
	if(va.size() == 2 && vb.size() == 2)
	{
		ret.push_back((line){va[0], vb[0] - va[0]});
		ret.push_back((line){va[1], vb[1] - va[1]});
	}
	else if(va.size() == 1 && vb.size() == 1)
	{
		ret.push_back((line){p, (a.c - b.c).rot90()});
	}
	return ret;
}

// 判断半平面交是否有解，若有解需保证半平面交必须有界，可以通过外加四个大半平面解决
// lcnt为半平面数量，l为需要做的所有半平面的数组，p为存交点的临时数组，h为时刻更新的合法的半平面数组，下标均从1开始
bool HP(int lcnt, line *l, line *h, point *p) 
{
	sort(l+1, l+1+lcnt);
	int head = 1, tail = 1; 
	h[1] = l[1];
	for(int i = 2; i <= lcnt; i++)
	{
		line cur = l[i];
		for(; head < tail && le(cur.v ^ (p[tail-1]-cur.p), 0); tail--); // 先删队尾再删队头，顺序不能换
		for(; head < tail && le(cur.v ^ (p[head]-cur.p), 0); head++);
		h[++tail] = cur;
		if(equ(h[tail].v ^ h[tail-1].v, 0)) // 平行
		{
			if(le(h[tail].v * h[tail-1].v, 0)) return false; // 方向相反的平行直线，显然已经不可能围出有界半平面了
			tail--;
			if(le(h[tail+1].v ^ (h[tail].p - h[tail+1].p), 0)) h[tail] = h[tail+1];
		}
		if(head < tail) p[tail-1] = line_inter(h[tail-1], h[tail]); 
	}
	for(; head < tail && le(h[head].v ^ (p[tail-1]-h[head].p), 0); tail--);
	return tail - head > 1;
}

double calc(double X){return 0;} // 计算给定X坐标上的覆盖的长度，配合辛普森积分使用
// 自适应辛普森积分，参数分别为(左端点x坐标，中点x坐标，右端点x坐标，左端点答案，中点答案，右端点答案)
// 改变计算深度应调整eps
double simpson(double l, double mid, double r, double fl, double fm, double fr) 
{
	double lmid = (l+mid)/2, rmid = (r+mid)/2, flm = calc(lmid), frm = calc(rmid);
	double ans = (r-l) * (fl + 4*fm + fr), ansl = (mid-l) * (fl + 4*flm + fm), ansr = (r-mid) * (fm + 4*frm + fr);
	if(fabs(ansl + ansr - ans) < eps) return ans / 6;
	else return simpson(l,lmid,mid,fl,flm,fm) + simpson(mid,rmid,r,fm,frm,fr);
}


int main(){}