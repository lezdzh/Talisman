//sa[i]：排第i的串的开头位置  rank[i]:开头位置为i的串的排名
//maxn = 2 ^ k

void trans(int*s1, int*s2, int*r1, int*r2)
{
	for(int i = 1; i <= n; i++)
		v[r1[s1[i]]] = i;
	for(int i = n; i >= 1; i--)
		if(s1[i] > k)
			s2[v[r1[s1[i] - k]]--] = s1[i] - k;
	for(int i = n - k + 1; i <= n; i++)
		s2[v[r1[i]]--] = i;
	for(int i = 1; i <= n; i++)
		r2[s2[i]] = r2[s2[i - 1]] + (r1[s2[i]] != r1[s2[i - 1]] || r1[s2[i] + k] != r1[s2[i - 1] + k]);
}

int lcp(int s, int t)
{
	s = rank[p][s], t = rank[p][t];
	if(s > t) swap(s, t);
	s++;
	int k = Log[t - s + 1];
	return min(f[s][k], f[t + 1 - (1 << k)][k]);
}

void work()
{
	for(int k = 0; k <= maxk; k++)
		for(int i = 1 << k; i < (1 << k + 1) && i <= n; i++)
			Log[i] = k;
	int p = 0, q = 1;
	for(int i = 1; i <= n; i++)
		v[a[i]]++;
	for(int i = 1; i <= S; i++)  //S:alphabet_size
		v[i] += v[i - 1];
	for(int i = 1; i <= n; i++)
		sa[p][v[a[i]]--] = i;
	for(int i = 1; i <= n; i++)
		rank[p][sa[p][i]] = rank[p][sa[p][i - 1]] + (a[sa[p][i]] != a[sa[p][i - 1]]);
	k = 1;
	while(k < n)
	{
		trans(sa[p], sa[q], rank[p], rank[q]);
		p ^= 1, q ^= 1;
		k <<= 1;
	}
	for(int i = 1; i <= n; i++)
	{
		h[i] = max(h[i - 1] - 1, 0);
		int j = sa[p][rank[p][i] - 1];
		while(a[i + h[i]] == a[j + h[i]])
			h[i]++;
	}
	for(int i = 2; i <= n; i++)
		f[i][0] = h[i];
	for(int k = 1; k <= maxk; i++)
		for(int i = 2; i + (1 << k) - 1 <= n; i++)
			f[i][k] = min(f[i][k - 1], f[i + (1 << k - 1)][k - 1]);
}
