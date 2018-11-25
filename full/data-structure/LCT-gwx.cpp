int pa[maxn], st[maxn];
struct node
{
	int ch[2], pa;
	ll s, w, sw;	//s: size of subtree; w: value; sw: sum of value
	ll m, p;	//tags of addition and multiplication
	bool f;	//tag of flip
} a[maxn];

void flip(int u)
{
	if(!u) return;
	swap(a[u].ch[0], a[u].ch[1]);
	a[u].f ^= 1;
}

void add(int u, int c)
{
	if(!u) return;
	(a[u].p += c) %= mod;
	(a[u].w += c) %= mod;
	(a[u].sw += a[u].s * c % mod) % mod;
}

void mult(int u, int c)
{
	if(!u) return;
	if(a[u].m == -1) a[u].m = c;
	else (a[u].m *= c) %= mod;
	(a[u].p *= c) %= mod;
	(a[u].w *= c) %= mod;
	(a[u].sw *= c) %= mod;
}

void pushdown(int u)
{
	if(!u) return;
	int l = a[u].ch[0], r = a[u].ch[1];
	if(a[u].m != -1)
	{
		mult(l, a[u].m); mult(r, a[u].m);
		a[u].m = -1;
	}
	if(a[u].p)
	{
		add(l, a[u].p); add(r, a[u].p);
		a[u].p = 0;
	}
	if(a[u].f)
	{
		flip(l); flip(r);
		a[u].f ^= 1;
	}
}

void maintain(int u)
{
	pushdown(u);
	int l = a[u].ch[0], r = a[u].ch[1];
	a[u].s = a[l].s + a[r].s + 1;
	a[u].sw = (a[l].sw + a[r].sw + a[u].w) % mod;
}

void rotate(int u)
{
	int x = a[u].pa, y = a[x].pa, d = (a[x].ch[1] == u);
	if(!y) pa[u] = pa[x], pa[x] = 0;
	else a[y].ch[a[y].ch[1] == x] = u;
	a[x].ch[d] = a[u].ch[d ^ 1], a[a[u].ch[d ^ 1]].pa = x;
	a[u].ch[d ^ 1] = x; a[x].pa = u; a[u].pa = y;
	maintain(x); maintain(u);
}

void splay(int u)
{
	int t = u;
	while(a[t].pa) st[++top] = t, t = a[t].pa;
	pushdown(t);
	while(top) pushdown(st[top]), top--;
	while(a[u].pa)
	{
		int x = a[u].pa, y = a[x].pa;
		if(!y)  {rotate(u); return;}
		if(a[x].ch[1] == u ^ a[y].ch[1] == x) rotate(u);
		else rotate(x);
		rotate(u);
	}
}

void access(int u)
{
	splay(u);
	if(a[u].ch[1])
		a[a[u].ch[1]].pa = 0, pa[a[u].ch[1]] = u, a[u].ch[1] = 0, maintain(u);
	while(pa[u])
	{
		int v = pa[u];
		splay(v);
		if(a[v].ch[1])
			a[a[v].ch[1]].pa = 0, pa[a[v].ch[1]] = v, a[v].ch[1] = 0;
		a[v].ch[1] = u; a[u].pa = v; pa[u] = 0;
		maintain(v); splay(u);
	}
}

void sroot(int u)
{
	access(u); flip(u);
}

void get(int u, int v)
{
	sroot(u); access(v);
}

void cut(int u, int v)
{
	get(u, v); a[v].ch[0] = a[u].pa = 0;
	maintain(v);
}

void join(int u, int v)
{
	access(u); sroot(v);
	a[u].ch[1] = v; a[v].pa = u;
	maintain(u);
}
