const double eps = 1e-8;
const double PI = acos(-1.0);

int sign(double x) {
	return (x < -eps) ? -1 : (x > eps);
}
double sqr(double x) {
	return x * x;
}

struct point {
	double x, y;
	point(double x = 0, double y = 0) : x(x), y(y) {}
	point operator + (const point &rhs) const {
		return point(x + rhs.x, y + rhs.y);
	}
	point operator - (const point &rhs) const {
		return point(x - rhs.x, y - rhs.y);
	}
	point operator * (const double &k) const {
		return point(x * k, y * k);
	}
	point operator / (const double &k) const {
		return point(x / k, y / k);
	}
	double len2() {
		return x * x + y * y;
	}
	double len() {
		return sqrt(len2());
	}
	point rotate(const double &ang) { // 逆时针旋转 ang 弧度
		return point(cos(ang) * x - sin(ang) * y, cos(ang) * y + sin(ang) * x);
	}
	point turn90() { // 逆时针旋转 90 度
		return point(-y, x);	
	}
	double ang() {
		return atan2(y, x);
	}
	point operator < (const point &rhs) {
		return (x < rhs.x || x == rhs.x && y < rhs.y);
	}
};
double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}
double det(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}

struct line {
	point a, b;
	line(point a, point b) : a(a), b(b) {}
};
bool onSeg(const point &p, const line &l) { // 点在线段上 包含端点 
	return sign(det(p - l.a, l.b - l.a)) == 0 && sign(dot(p - l.a, p - l.b)) <= 0;
}
double disToLine(const point &p, const line &l) { // 点到直线距离 
	return fabs(det(p - l.a, l.b - l.a) / (l.b - l.a).len());
}
double disToSeg(const point &p, const line &l) { // 点到线段距离
	return sign(dot(p - l.a, l.b - l.a)) * sign(dot(p - l.b, l.a - l.b)) != 1 ?
	disToLine(l, p) : min((p - l.a).len(), (p - l.b).len());
}
point projection(const point &p, const line &l) { // 点到直线投影 
	return l.a + (l.b - l.a) * (dot(p - l.a, l.b - l.a) / (l.b - l.a).len2());
}
point symmetry(const point &a, const point &b) { // 点a关于点b的对称点 
	return b + b - a;
}
point reflection(const point &p, const line &l) { // 点关于直线的对称点 
	return symmetry(p, projection(p, l));
}
bool isLL(const line &l1, const line &l2, point &p) { // 直线求交 
	long long s1 = det(l2.b - l2.a, l1.a - l2.a);
	long long s2 = -det(l2.b - l2.a, l1.b - l2.a);
	if(!sign(s1 + s2)) return false;
	p = (l1.a * s2 + l1.b * s1) / (s1 + s2);
	return true;
}
bool p_in_tri(const point &p, const point &a, const point &b, const point &c) { //点在三角形内(包含边界) 
	return sign(abs(det(a - p, b - p)) + abs(det(b - p, c - p)) 
		+ abs(det(c - p, a - p)) - abs(det(b - a, c - a))) == 0;
}
bool Check(const point &p, const point &d, const point &a, const point &b) {
	return sign(det(d, a - p)) * sign(det(b - p, d)) >= 0;
}
bool isll(const point &p, const point &q, const point &a, const point &b) { // 跨立实验 
	return Check(p, q - p, a, b) && Check(a, b - a, p, q);
}


