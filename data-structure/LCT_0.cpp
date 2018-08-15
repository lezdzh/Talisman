#include <cstdio>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

typedef long long ll;

ll max(ll a, ll b)  {
	return a > b ? a : b;
}
ll min(ll a, ll b)  {
	return a < b ? a : b;
}
ll ABS(ll x)  {
	return x > 0 ? x : -x;
}

const int maxn = 1e5 + 5;
const int mod = 51061;
int n, q, cnt, top;
int pa[maxn], tail[maxn], st[maxn];
struct node {int ch[2], pa; ll s, w, sw, m, p; bool f;} a[maxn];
struct edge {int v, next;} e[maxn << 1];

void ins(int u, int v)  {
	e[++cnt] = (edge){v, tail[u]}; tail[u] = cnt;
}

void dfs(int u)
{
	a[u].sw = a[u].s = a[u].w = 1; a[u].m = -1;
	for(int i = tail[u]; i; i = e[i].next)
		if(e[i].v != pa[u])
		{
			pa[e[i].v] = u;
			dfs(e[i].v);
		}
}

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

int main()
{
	int u, v, x, y, c;
	char opt;
	scanf("%d%d", &n, &q);
	for(int i = 1; i < n; i++)
	{
		scanf("%d%d", &u, &v);
		ins(u, v); ins(v, u);
	}
	dfs(1);
	while(q--)
	{
		scanf("\n%c%d%d", &opt, &u, &v);
		switch(opt) {
		case '+': scanf("%d", &c); get(u, v); add(v, c); break;
		case '-': scanf("%d%d", &x, &y); cut(u, v); join(x, y); break;
		case '*': scanf("%d", &c); get(u, v); mult(v, c); break;
		case '/': get(u, v); printf("%lld\n", a[v].sw);
		}
	}
	return 0;
}
