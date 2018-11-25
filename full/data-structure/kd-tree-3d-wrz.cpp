// 这里写的是询问三维空间中的一个长方体内有没有点
int D;
struct point 
{
	int d[3];
	bool operator < (const point &that) const {return d[D] < that.d[D];}
}p[N];
struct node
{
	int d[2][3]; // 0 min 1 max
}t[N<<2];
void pushup(int x)
{
	for(int i = 0; i < 3; i++)
	{
		t[x].d[0][i] = min(t[x<<1].d[0][i], t[x<<1|1].d[0][i]);
		t[x].d[1][i] = max(t[x<<1].d[1][i], t[x<<1|1].d[1][i]);
	}
}
void build(int x, int l, int r, int d)
{
	if(l == r) 
	{
		for(int i = 0; i < 3; i++)
			t[x].d[0][i] = t[x].d[1][i] = p[l].d[i];
		return;
	}
	D = d; int mid = (l+r) >> 1;
	nth_element(p+l, p+mid, p+r+1);
	(++d) %= 3;
	build(x<<1, l, mid, d);
	build(x<<1|1, mid+1, r, d);
	pushup(x);
}
int d[2][3];
bool query(int x, int l, int r)
{
	int in = 1, out = 0;
	for(int i = 0; i < 3; i++) 
	{
		if(!(d[0][i] <= t[x].d[0][i] && t[x].d[1][i] <= d[1][i])) in = 0; // 包含
		if(d[1][i] < t[x].d[0][i] || t[x].d[1][i] < d[0][i]) out = 1; // 不交
	}
	if(in) return true; if(out) return false;
	int mid = (l+r) >> 1;
	return query(x<<1, l, mid) || query(x<<1|1, mid+1, r);
}