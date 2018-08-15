__inline int dcmp(const double &x) {return fabs(x) < eps ? 0 : (x > 0 ? 1 : -1);}
int getQuad(const Point &a) {
	if (dcmp(a.x) > 0 && dcmp(a.y) >= 0) return 1;
	if (dcmp(a.x) <= 0 && dcmp(a.y) > 0) return 2;
	if (dcmp(a.x) < 0 && dcmp(a.y) <= 0) return 3;
	if (dcmp(a.x) >= 0 && dcmp(a.y) < 0) return 4;
	return 0;
}
//base基准点
bool cmp(const int &iA, const int &iB) {
	Point a = p[iA] - base, b = p[iB] - base;
	int aQ = getQuad(a), bQ = getQuad(b);
	if (aQ < bQ) return true;
	if (aQ > bQ) return false;
	double d = det(a, b);
	if (dcmp(d) > 0) return true;
	if (dcmp(d) < 0) return false;
	return sqrdist(a) < sqrdist(b);
}
