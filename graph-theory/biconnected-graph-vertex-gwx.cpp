//cut[i]: i是否为割点
//bridge[i]: e[i]是否为桥
void dfs(int u, int pa)
{
	d[u] = l[u] = ++timer;
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
		else if(e[i].v != pa) l[u] = min(l[u], d[e[i].v]);
	if(!pa && child < 2) cut[u] = 0;
}
