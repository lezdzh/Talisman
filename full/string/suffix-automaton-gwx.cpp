int root = 1, cnt = 1, last = 1;
int pa[maxn], l[maxn], ch[maxn][maxs];

void add(int c) //c : 0 ~ alpha_size
{
	int np = ++cnt, p = last; last = cnt;
	l[np] = x; r[np] = 1;
	while(p && !ch[p][c])
		ch[p][c] = np, p = pa[p];
	if(!p)
	{
		pa[np] = root;
		return;
	}
	int q = ch[p][c];
	if(l[q] == l[p] + 1)
		pa[np] = q;
	else
	{
		int nq = ++cnt;
		l[nq] = l[p] + 1;
		pa[nq] = pa[q];
		pa[q] = pa[np] = nq;
		memcpy(ch[nq], ch[q], sizeof(ch[q]));
		while(p && ch[p][c] == q)
			ch[p][c] = nq, p = pa[p];
	}
}

void get_right()
{
	for(int i = 1; i <= n; i++) add(i);
	for(int i = 1; i <= cnt; i++) v[l[i]]++;
	for(int i = 1; i <= n; i++) v[i] += v[i - 1];
	for(int i = cnt; i; i--) t[v[l[i]]--] = i;
	for(int i = cnt; i; i--) if(pa[t[i]]) r[pa[t[i]]] += r[t[i]];
	r[1] = 0;
}
