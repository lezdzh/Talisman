void tarjan(int u)
{
	d[u] = l[u] = ++timer;
	vst[u] = 1; st.push(u);
	for(int i = tail[u]; i; i = a[i].next)
		if(!d[a[i].v]) tarjan(a[i].v), l[u] = min(l[u], l[a[i].v]);
		else if(vst[a[i].v]) l[u] = min(l[u], d[a[i].v]);
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
