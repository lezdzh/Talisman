//cut[i]: i是否为割点
//bridge[i]: e[i]是否为桥
void dfs(int u, int pa)
{
	d[u] = l[u] = ++timer;
	st.push(u); vst[u] = 1;
	int child = 0;
	for(int i = tail[u]; i; i = e[i].next)
		if(!d[e[i].v])
		{
			child++;
			dfs(e[i].v, u);
			l[u] = min(l[u], l[e[i].v]);
			if(l[e[i].v] >= d[u])
            {
                cut[u] = 1;
                if(l[e[i].v] > d[u])
                    bridge[i] = 1;
            }
		}
		else if(vst[e[i].v]) l[u] = min(l[u], d[e[i].v]);
	if(!pa && child < 2) cut[u] = 0;
	if(l[u] == d[u])
	{
		int v; scc++;
		while(true)
		{
			v = st.top(); st.pop();
			id[v] = scc; vst[v] = 0; size[scc]++;
			if(u == v) break;
		}
	}
}
