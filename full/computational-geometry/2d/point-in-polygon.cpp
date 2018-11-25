bool pit_in_polygon(pit q){ // 点在多边形内
	int cnt = 0;
	for(int i = 1; i <= n; ++i){
		pit p1 = p[i];
		pit p2 = p[suc[i]];
		if(pit_on_seg(q, p1, p2)) return true;
		int k = dcmp(det(p2 - p1, q - p1));
		int d1 = dcmp(p1.y - q.y);
		int d2 = dcmp(p2.y - q.y);
		if(k > 0 && d1 <= 0 && d2 > 0) ++cnt;
		if(k < 0 && d2 <= 0 && d1 > 0) --cnt;
	}
	if(cnt != 0) return true;
	else return false;
}
bool seg_in_polygon(pit a, pit b){ // 线段在多边形内 撒点
	vec v = b - a;
	for(int t = 1; t <= 1000; ++t){
		pit c = a + v * (1.00 * (rand() % 10000) / 10000);
		if(pit_in_polygon(c)) continue;
		else return false;
	}
	return true;
}
