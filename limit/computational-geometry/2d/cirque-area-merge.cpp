//n^2*logn 
struct point {
	point rotate(const double &ang) {return point(cos(ang) * x - sin(ang) * y, cos(ang) * y + sin(ang) * x);}
	double ang() {return atan2(y, x);}
};
struct Circle {
	point o; double r;
	int tp; // 正圆为1 反向圆为-1 
	Circle (point o = point(0, 0), double r = 0, int tp = 0) : o(o), r(r), tp(tp) {}
};
struct Event {
	point p; double ang; int delta;
	Event (point p = point(0, 0), double ang = 0, double delta = 0) : p(p), ang(ang), delta(delta) {}
};
bool operator < (const Event &a, const Event &b) {return a.ang < b.ang;}
void addEvent(const Circle &a, const Circle &b, vector<Event> &evt, int &cnt) {
	double d2 = (a.o - b.o).len2(),
		dRatio = ((a.r - b.r) * (a.r + b.r) / d2 + 1) / 2,
		pRatio = sqrt(-(d2 - sqr(a.r - b.r)) * (d2 - sqr(a.r + b.r))) / d2 / 2;
	point d = b.o - a.o, p = d.rotate(PI / 2),
		q0 = a.o + d * dRatio + p * pRatio,
		q1 = a.o + d * dRatio - p * pRatio;
	double ang0 = (q0 - a.o).ang(),
		ang1 = (q1 - a.o).ang();
	evt.push_back(Event(q1, ang1, b.tp));
	evt.push_back(Event(q0, ang0, -b.tp));
	cnt += (ang1 > ang0) * b.tp;
}
bool issame(const Circle &a, const Circle &b) {return sign((a.o - b.o).len()) == 0 && sign(a.r - b.r) == 0;}
bool overlap(const Circle &a, const Circle &b) {return sign(a.r - b.r - (a.o - b.o).len()) >= 0;}
bool intersect(const Circle &a, const Circle &b) {return sign((a.o - b.o).len() - a.r - b.r) < 0;}
int C;
Circle c[N];
double area[N];
void solve() { // area[1]..area[C]
	memset(area, 0, sizeof(double) * (C + 1));
	for (int i = 0; i < C; ++i) {
		int cnt = (c[i].tp > 0);
		vector<Event> evt;
		for (int j = 0; j < i; ++j) if (issame(c[i], c[j])) cnt += c[j].tp;
		for (int j = 0; j < C; ++j)
			if (j != i && !issame(c[i], c[j]) && overlap(c[j], c[i])) cnt += c[j].tp;
		for (int j = 0; j < C; ++j)
			if (j != i && !overlap(c[j], c[i]) && !overlap(c[i], c[j]) && intersect(c[i], c[j]))
				addEvent(c[i], c[j], evt, cnt);
		if (evt.size() == 0) area[cnt] += c[i].tp * PI * c[i].r * c[i].r;
		else {
			sort(evt.begin(), evt.end());
			evt.push_back(evt.front());
			for (int j = 0; j + 1 < (int)evt.size(); ++j) {
				cnt += evt[j].delta;
				area[cnt] += c[i].tp * det(evt[j].p, evt[j + 1].p) / 2;
				double ang = evt[j + 1].ang - evt[j].ang;
				if (ang < 0) ang += PI * 2;
				area[cnt] += c[i].tp * (ang * c[i].r * c[i].r / 2 - sin(ang) * c[i].r * c[i].r / 2);
			}
		}
	}
}

