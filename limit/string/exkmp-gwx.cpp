void get_next()
{
	int a = 0, p = 0;
	nxt[0] = m;
	for(int i = 1; i < m; i++)
	{
		if(i >= p || i + nxt[i - a] >= p)
		{
			if(i >= p) 	p = i;
			while(p < m && t[p] == t[p - i]) p++;
			nxt[i] = p - i;
			a = i;
		}
		else nxt[i] = nxt[i - a];
	}
}

void exkmp()
{
	int a = 0, p = 0;
	get_next();
	for(int i = 0; i < n; i++)
	{
		if(i >= p || i + nxt[i - a] >= p) // i >= p 的作用：举个典型例子，s 和 t 无一字符相同
		{
			if(i >= p) p = i;
			while(p < n && p - i < m && s[p] == t[p - i]) p++;
			ext[i] = p - i;
			a = i;
		}
		else ext[i] = nxt[i - a];
	}
}
