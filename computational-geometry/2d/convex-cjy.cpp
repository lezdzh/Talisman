struct point {
	point operator < (const point &rhs) {
		return (x < rhs.x || x == rhs.x && y < rhs.y);
	}
};
point O;
bool cmp(const point &p1, const point &p2) {
	int x = sign(det(p1 - O, p2 - O));
	return (x > 0 || x == 0 && sign((p1 - O).len2() - (p2 - O).len2()) < 0);
}
int Graham(point p[], int n) { //点数n->t (1-base) 
	O = p[1];
	for (int i = 2; i <= n; i++)
		if (p[i].y < O.y || p[i].y == O.y && p[i].x < O.x) O = p[i];
	sort(p + 1, p + n + 1, cmp);
	int t = 2;
	for (int i = 3; i <= n; i++) {
		while (t > 2 && sign(det(p[t - 1] - p[t], p[i] - p[t])) >= 0) t--;
		p[++t] = p[i];
	}
	return t;
}

