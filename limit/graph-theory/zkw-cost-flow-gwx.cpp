//稠密图、二分图中较快，稀疏图中不如SPFA
int flow, cost, price;
int dfs(int u, int f)
{
	if(u == t){ flow += f; cost += price * f; return f;}
	vst[u] = 1;
	int used = 0;
	for(int i = tail[u]; i; i = e[i].next)
		if(!vst[e[i].v] && e[i].c > 0 && e[i].w == 0)
		{
			int w = dfs(e[i].v, min(e[i].c, f - used));
			e[i].c -= w; e[i ^ 1].c += w; used += w;
			if(used == f) return f;
		}
	return used;
}
bool modlabel()
{
	int d = inf;
	for(int u = s; u <= t; u++)
		if(vst[u])
			for(int i = tail[u]; i; i = e[i].next)
				if(e[i].c > 0 && !vst[e[i].v]) d = min(d, e[i].w);
	if(d == inf) return 0;
	for(int u = s; u <= t; u++)
		if(vst[u])
			for(int i = tail[u]; i; i = e[i].next)
				e[i].w -= d, e[i ^ 1].w += d;
	price += d;
	return 1;
}
void zkw()
{
	do
		do memset(vst, 0, sizeof(vst));
		while(dfs(s, inf) > 0);
	while(modlabel());
}
