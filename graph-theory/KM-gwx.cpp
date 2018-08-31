//最大匹配
bool find(int k)
{
	if(k == 0)
		return 0;
	px[k] = 1;
	for(int i = 1; i <= m; i++)
		if(!py[i])
		{
			int t = x[k] + y[i] - a[k][i];
			if(!t)
			{
				py[i] = 1;
				if(!match[i] || find(match[i]) == 1)
				{
					match[i] = k;
					return 1;
				}
			}
			else
				slack[i] = min(slack[i], t);
		}
	return 0;
}

void revise()
{
	int d = inf;
	for(int i = 1; i <= m; i++)
		if(!py[i])
			d = min(d, slack[i]);
	for(int i = 1; i <= n; i++)
		if(px[i])
			x[i] -= d;
	for(int i = 1; i <= m; i++)
		if(py[i])
			y[i] += d;
		else
			slack[i] -= d;
}

void solve()
{
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
			slack[j] = inf;
		while(true)
		{
			memset(px, 0, sizeof(px));
			memset(py, 0, sizeof(py));
			if(find(i) == 1)
				break;
			revise();
		}
	}
	for(int i = 1; i <= m; i++)
		if(match[i])
			f[match[i]] = i;
}
