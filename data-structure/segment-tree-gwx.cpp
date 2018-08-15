//01序列，支持区间翻转、区间赋值、求最长0/1子段
struct seg
{
    int l, r, tag, flip, left[2], right[2], mid[2], s[2];
} a[4 * maxn];

void pushdown(int k)
{
	if(a[k].l < a[k].r)
	{
		if(a[k].tag >= 0)
		{
			a[k << 1].tag = a[k << 1 ^ 1].tag = a[k].tag;
			a[k << 1].flip = a[k << 1 ^ 1].flip = 0;
		}
		if(a[k].flip) a[k << 1].flip ^= 1, a[k << 1 ^ 1].flip ^= 1;
	}
	if(a[k].tag >= 0)
	{
		int x = a[k].tag; a[k].tag = -1;
		a[k].s[x] = a[k].left[x] = a[k].right[x] = a[k].mid[x] = a[k].r - a[k].l + 1;
		x ^= 1;
		a[k].s[x] = a[k].left[x] = a[k].right[x] = a[k].mid[x] = 0;
	}
	if(a[k].flip)
	{
		a[k].flip = 0;
		swap(a[k].s[0], a[k].s[1]);
		swap(a[k].left[0], a[k].left[1]);
		swap(a[k].right[0], a[k].right[1]);
		swap(a[k].mid[0], a[k].mid[1]);
	}
}

void maintain(int k)
{
	pushdown(k << 1); pushdown(k << 1 ^ 1);
	for(int i = 0; i <= 1; i++)
	{
		a[k].s[i] = a[k << 1].s[i] + a[k << 1 ^ 1].s[i];
		if(a[k << 1].left[i] == a[k << 1].r - a[k << 1].l + 1) a[k].left[i] = a[k << 1].left[i] + a[k << 1 ^ 1].left[i];
		else a[k].left[i] = a[k << 1].left[i];
		if(a[k << 1 ^ 1].right[i] == a[k << 1 ^ 1].r - a[k << 1 ^ 1].l + 1) a[k].right[i] = a[k << 1].right[i] + a[k << 1 ^ 1].right[i];
		else a[k].right[i] = a[k << 1 ^ 1].right[i];
		a[k].mid[i] = max(a[k << 1].right[i] + a[k << 1 ^ 1].left[i], max(a[k << 1].mid[i], a[k << 1 ^ 1].mid[i]));
	}
}

void build(int k, int l, int r)
{
	int mid = (l + r) >> 1;
	a[k] = (seg){l, r, -1};
	if(l == r)
	{
		int x = c[l];
		a[k].left[x] = a[k].right[x] = a[k].mid[x] = a[k].s[x] = 1;
		return;
	}
	build(k << 1, l, mid);
	build(k << 1 ^ 1, mid + 1, r);
	maintain(k);
}

void change(int k, int opt)
{
	if(opt <= 1) a[k].tag = opt, a[k].flip = 0;
	else a[k].flip ^= 1;
}

void revise(int k, int s, int t, int opt)
{
	int l = a[k].l, r = a[k].r, mid = (l + r) >> 1;
	if(l == s && r == t)  {change(k, opt); return;}
	pushdown(k);
	if(t <= mid) revise(k << 1, s, t, opt);
	else if(s > mid) revise(k << 1 ^ 1, s, t, opt);
	else revise(k << 1, s, mid, opt), revise(k << 1 ^ 1, mid + 1, t, opt);
	maintain(k);
}

int query_sum(int k, int s, int t)
{
	int l = a[k].l, r = a[k].r, mid = (l + r) >> 1, res;
	pushdown(k);
	if(l == s && r == t) return a[k].s[1];
	if(t <= mid) res = query_sum(k << 1, s, t);
	else if(s > mid) res = query_sum(k << 1 ^ 1, s, t);
	else res = query_sum(k << 1, s, mid) + query_sum(k << 1 ^ 1, mid + 1, t);
	return res;
}

int query_sec(int k, int s, int t)
{
	int l = a[k].l, r = a[k].r, mid = (l + r) >> 1, res = 0;
	pushdown(k);
	if(l == s && r == t) return a[k].mid[1];
	if(t <= mid) res = query_sec(k << 1, s, t);
	else if(s > mid) res = query_sec(k << 1 ^ 1, s, t);
	else
	{
		int tmp;
		res = max(query_sec(k << 1, s, mid), query_sec(k << 1 ^ 1, mid + 1, t));
		res = max(res, min(a[k << 1].right[1], mid - s + 1) + min(a[k << 1 ^ 1].left[1], t - mid));
	}
	return res;
}
