struct Point
{
	double x, y;
	int id;
	Point operator - (const Point &a) const {
		return (Point){x - a.x, y - a.y, id};
	}
} b[maxn], c[maxn];
struct node
{
	Point p;
	int ch[2];
} a[maxn];
struct rev
{
	int id;
	double dis;
	bool operator < (const rev &a) const{
		int tmp = sign(dis - a.dis);
		if(tmp)
			return tmp < 0;
		return id < a.id;
	}
};
typedef pr priority_queue <rev>;
pr p0;
int build(int l, int r, int f)
{
	if(l > r)
		return 0;
	int x = (l + r) >> 1;
	if(f == 0)
		nth_element(a + l, a + x, a + r + 1, cmp0);	//按x排序
	else
		nth_element(a + l, a + x, a + r + 1, Cmp1); //按y排序
	a[x].ch[0] = build(l, x - 1, f ^ 1);
	a[x].ch[1] = build(x + 1, r, f ^ 1);
	return x;
}
void update(pr &a, rev x)
{
	if(a.size() < K)
		a.push(x);
	else if(x < a.top())
	{
		a.pop();
		a.push(x);
	}
}
pr merge(pr a, pr b)
{
	int s1 = a.size(), s2 = b.size();
	if(s1 < s2)
	{
		while(!a.empty())
		{
			update(b, a.top());
			a.pop();
		}
		return b;
	}
	else
	{
		while(!b.empty())
		{
			update(a, b.top());
			b.pop();
		}
		return a;
	}
}
pr query(int u, Point x, int f)
{
	if(!u)
		return p0;//empty priority_queue
	int d = (dis(a[a[u].ch[0]].p, x) > dis(a[a[u].ch[1]].p, x));
	double dx;
	pr res = query(a[u].ch[d], x, f ^ 1);
	update(res, (rev){a[u].p.id, dis(a[u].p, x)});
	if(f == 0)
		dx = abs(x.x - a[u].p.x);
	else
		dx = abs(x.y - a[u].p.y);
	if(dx > res.top().dis)
		return res;
	res = merge(res, query(a[u].ch[d ^ 1], x, f ^ 1));
	return res;
}
pr solve(Point p)	//离p最近的K个点
{
	int root = build(1, tot, 0);
	return query(root, p, 0);
}
