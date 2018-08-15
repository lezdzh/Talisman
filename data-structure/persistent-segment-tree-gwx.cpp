void build(int last, int &k, int l, int r, int x)
{
	k = ++tot;
	a[k] = a[last]; a[k].w++;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(x <= mid)
        build(a[last].l, a[k].l, l, mid, x);
	else
        build(a[last].r, a[k].r, mid + 1, r, x);
}
