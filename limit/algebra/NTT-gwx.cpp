const int G;
int n, m, inm;
int rev[maxn], a[maxn], b[maxn];    //maxn > 2 ^ k

ll power(ll b, int k)
{
	ll res = 1;
	for(; k; k >>= 1, b = b * b % mod)
		if(k & 1)
			res = res * b % mod;
	return res;
}

void ntt(ll*a, int f)
{
	for(int i = 0; i < m; i++)
		if(rev[i] < i)
            swap(a[i], a[rev[i]]);
	for(int l = 2, h = 1; l <= m; h = l, l <<= 1)
	{
		int ur;
		if(f == 1)
            ur = power(G, (mod - 1) / l);
		else
            ur = power(G, mod - 1 - (mod - 1) / l);
		for(int i = 0; i < m; i += l)
		{
			ll w = 1;
			for(int k = i; k < i + h; k++, w = w * ur % mod)
			{
				int x = a[k], y = a[k + h] * w % mod;
				a[k] = (x + y) % mod;
				a[k + h] = (x - y + mod) % mod;
			}
		}
	}
	if(f == -1)
		for(int i = 0; i < m; i++)
			a[i] = a[i] * inm % mod;
}

void multi()
{
	ntt(a, 1); ntt(b, 1);
	for(int i = 0; i < m; i++)
		a[i] = a[i] * b[i] % mod;
	ntt(a, -1);
}

void init()
{
	for(m = 1; m <= 2 * n; m <<= 1) ;
	for(int i = 1; i < m; i++)
	{
		rev[i] = rev[i - 1];
		for(int j = m >> 1; (rev[i] ^= j) < j; j >>= 1) ;
	}
}
