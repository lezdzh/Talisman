void mcf()
{
	while(true)
	{
		queue <int> q;
		memset(d, 127, sizeof(d));
		d[s] = 0;
		vst[s] = 1;
		q.push(s);
		while(!q.empty())
		{
			int u = q.front();
			q.pop();
			vst[u] = 0;
			for(int i = tail[u]; i; i = a[i].next)
				if(a[i].c > 0 && d[a[i].v] > d[u] + a[i].s)
				{
					d[a[i].v] = d[u] + a[i].s;
					pre[a[i].v] = u;
					pe[a[i].v] = i;
					if(!vst[a[i].v])
					{
						vst[a[i].v] = 1;
						q.push(a[i].v);
					}
				}
		}
		if(d[t] > inf)
			break;
		int f = inf;
		for(int i = t; i != 1; i = pre[i])
			f = min(f, a[pe[i]].c);
		flow += f;
		for(int i = t; i != 1; i = pre[i])
		{
			cost += f * a[pe[i]].s;
			a[pe[i]].c -= f;
			a[pe[i] ^ 1].c += f;
		}
	}
}

bool bfs()
{
	queue <int> q;
	memset(d, -1, sizeof(d));
	d[s] = 0;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = tail[u]; i; i = a[i].next)
			if(d[a[i].v] == -1 && a[i].c > 0)
			{
				d[a[i].v] = d[u] + 1;
				q.push(a[i].v);
			}
	}
	return d[t] != -1;
}

int dfs(int u, int flow)
{
	int used = 0;
	if(u == t)
		return flow;
	for(int &i = cur[u]; i; i = a[i].next)
		if(d[a[i].v] == d[u] + 1 && a[i].c > 0)
		{
			int w = dfs(a[i].v, min(a[i].c, flow - used));
			a[i].c -= w;
			a[i ^ 1].c += w;
			used += w;
			if(used == flow)
				return flow;
		}
	if(!used)
		d[u] = -1;
	return used;
}

int dinic()
{
	int res = 0;
	while(bfs())
	{
		memcpy(cur, tail, sizeof(tail));
		res += dfs(s, inf);
	}
	return res;
}
