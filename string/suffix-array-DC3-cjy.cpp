//cjy
#define mset(a) memset(a, 0, sizeof(a))

typedef long long ll;

const int maxn = 131072 + 5;

int n, m, p, q = 1, k = 1, mx, last, lim;
int sa[2][maxn], rk[2][maxn], v[maxn], f[maxn][17], Log[maxn], h[maxn], di[maxn];
char c[maxn];
ll ans1, ans2;

void clean()
{
	p = mx = ans1 = ans2 = last = 0;
	q = k = 1;
	mset(sa);
	mset(rk);
	mset(v);
	mset(h);
	memset(f, 127, sizeof(f));
}

void trans(int *s1, int *s2, int *r1, int *r2)
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
	if(!s || !t)
		return 0;
	if(s == t)
		return n - s + 1;
	s = rk[p][s], t = rk[p][t];
	if(s > t)
		swap(s, t);
	s++;
	int k = Log[t - s + 1];
	return min(f[s][k], f[t + 1 - (1 << k)][k]);
}

void init()
{
	lim = Log[n];
	for(int i = 1; i <= n; i++)
		v[c[i]]++;
	for(int i = 'a'; i <= 'z'; i++)
		v[i] += v[i - 1];
	for(int i = 1; i <= n; i++)
		sa[p][v[c[i]]--] = i;
	for(int i = 1; i <= n; i++)
		rk[p][sa[p][i]] = rk[p][sa[p][i - 1]] + (c[sa[p][i]] != c[sa[p][i - 1]]);
	while(k < n)
	{
		trans(sa[p], sa[q], rk[p], rk[q]);
		p ^= 1; q ^= 1; k <<= 1;
	}
	for(int i = 1; i <= n; i++)
	{
		if(rk[p][i] == 1)
		{
			mx = 0;
			continue;
		}
		int j = sa[p][rk[p][i] - 1];
		if(mx)
			mx--;
		while(c[i + mx] == c[j + mx])
			mx++;
		h[rk[p][i]] = mx;
	}
	for(int i = 2; i <= n; i++)
		f[i][0] = h[i];
	for(int k = 1; k <= lim; k++)
		for(int i = 2; i + (1 << k) - 1 <= n; i++)
			f[i][k] = min(f[i][k - 1], f[i + (1 << k - 1)][k - 1]);
}
