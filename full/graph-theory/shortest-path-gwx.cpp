void spfa()
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
	    if(d[a[i].v] > d[u] + a[i].c)
	    {
		d[a[i].v] = d[u] + a[i].c;
		if(!vst[a[i].v])
		{
		    vst[a[i].v] = 1;
		    q.push(a[i].v);
		}
	    }
    }
}

void dijkstra()
{
    memset(d, 127, sizeof(d));
    d[s] = 0;
    for(int i = 1; i <= n; i++)
    {
	int dis = inf, u;
	for(int j = 1; j <= n; j++)
	    if(!vst[j] && d[j] < dis)
	    {
		dis = d[j];
		pos = j;
	    }
	vst[pos] = 1;
	for(int i = tail[u]; i; i = a[i].next)
	    if(!vst[a[i].v])
		d[a[i].v] = min(d[a[i].v], d[u] + a[i].c);
    }
}

void floyd()
{
    for(int i = 1; i <= n; i++)
	for(int j = 1; j <= n; j++)
	    if(i != j)
		for(int k = 1; k <= n; k++)
		    if(i != k && j != k)
			d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
