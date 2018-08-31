void dfs(int u)
{
	size[u] = 1;
	for(int i = 1; pa[u][i - 1] && i <= 17; i++)
		pa[u][i] = pa[pa[u][i - 1]][i - 1];
	for(int i = tail[u]; i; i = e[i].next)
		if(e[i].v != pa[u][0])
		{
			pa[e[i].v][0] = u;
			dep[e[i].v] = dep[u] + 1;
			dfs(e[i].v);
			size[u] += size[e[i].v];
			if(size[e[i].v] > size[son[u]])
				son[u] = e[i].v;
		}
}

void dfs1(int u, int anc)
{
	top[u] = anc;
	in[u] = ++timer;
	if(son[u]) dfs1(son[u], anc);
	for(int i = tail[u]; i; i = e[i].next)
		if(e[i].v != pa[u][0] && e[i].v != son[u])
			dfs1(e[i].v, e[i].v);
	out[u] = timer;
}

int lca(int u, int v)
{
	if(dep[u] > dep[v]) swap(u, v);
	for(int x = dep[v] - dep[u], i = 0; x; x >>= 1, i++)
		if(x & 1) v = pa[v][i];
	if(u == v) return u;
	for(int i = 17; i >= 0; i--)
		if(pa[u][i] != pa[v][i])
			u = pa[u][i], v = pa[v][i];
	return pa[u][0];
}

int get(int u, int v)
{
	int res = 0;
	while(top[u] != top[v])
	{
		if(dep[top[u]] > dep[top[v]]) swap(u, v);
		res += query(1, 1, n, in[top[v]], in[v]);
		v = pa[top[v]][0];
	}
	if(dep[u] > dep[v]) swap(u, v);
	res += query(1, 1, n, in[u], in[v]);
	return res;
}
