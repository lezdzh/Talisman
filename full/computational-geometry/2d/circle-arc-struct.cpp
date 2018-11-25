struct circle {
	point o;
	double r;
	circle(point o, double r) : o(o), r(r) {}
};
struct arcs { // 点l顺时针到点r 
	point o, l, r;
	arcs() {}
	arcs(point o, point l, point r) : o(o), l(l), r(r) {}
};
bool isCL(circle a, line l, point &p1, point &p2) { // 圆与直线的交点 
	double x = dot(l.a - a.o, l.b - l.a);
	double y = (l.b - l.a).len2();
	double d = x * x - y * ((l.a - a.o).len2() - a.r * a.r);
	if(sign(d) < 0) return false;
	d = max(d, 0.0);
	point p = l.a - ((l.b - l.a) * (x / y)), delta = (l.b - l.a) * (sqrt(d) / y);
	p1 = p + delta, p2 = p - delta;
	return true;
}
double ang(const point &d1, const point &d2) { // 向量d1顺时针转到向量d2的角度 
	if (sign(det(d1, d2)) == 0)
		return (sign(dot(d1, d2)) > 0) ? 0 : pi;
	if (sign(det(d1, d2)) < 0)
		return acos(dot(d1, d2) / d1.len() / d2.len());
	else return 2 * pi - acos(dot(d1, d2) / d1.len() / d2.len());
}
bool onArcs(const point &p, const arcs &a) { // 点在圆弧上 
	return sign(ang(a.l - a.o, a.r - a.o) - ang(a.l - a.o, p - a.o)) > 0;
}

/*struct circle {
	point o;
	double r;
	circle(point o, double r) : o(o), r(r) {}
};

struct arcs {
	//l -> r clockwise
	point o, l, r; 
	arcs() {}
	arcs(point o, point l, point r) : o(o), l(l), r(r) {}
};

//Circle intersect with Line
bool isCL(circle a, line l, point &p1, point &p2) {
	double x = dot(l.a - a.o, l.b - l.a);
	double y = (l.b - l.a).len2();
	double d = x * x - y * ((l.a - a.o).len2() - a.r * a.r);
	if(sign(d) < 0) return false;
	d = max(d, 0.0);
	point p = l.a - ((l.b - l.a) * (x / y)), delta = (l.b - l.a) * (sqrt(d) / y);
	p1 = p + delta, p2 = p - delta;
	return true;
}

//use acos !precision

//angle (d1, d2) clockwise
double ang(const point &d1, const point &d2) {
	if (sign(det(d1, d2)) == 0)
		return (sign(dot(d1, d2)) > 0) ? 0 : pi;
	if (sign(det(d1, d2)) < 0)
		return acos(dot(d1, d2) / d1.len() / d2.len());
	else return 2 * pi - acos(dot(d1, d2) / d1.len() / d2.len());
}
//
bool onArcs(const point &p, const arcs &a) {
	return sign(ang(a.l - a.o, a.r - a.o) - ang(a.l - a.o, p - a.o)) > 0;
}*/
