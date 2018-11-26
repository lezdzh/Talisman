ll multi(ll x, ll y, ll M) {
	ll res = 0;
	for(; y; y >>= 1, x = (x + x) % M)
		if(y & 1) res = (res + x) % M;
	return res;
}
ll power(ll x, ll y, ll p)
{
	ll res = 1;
	for(; y; y >>= 1, x = multi(x, x, p))
		if(y & 1) res = multi(res, x, p);
	return res;
}
int primetest(ll n, int base)
{
	ll n2 = n - 1, res;
	int s = 0;
	while(!(n2 & 1)) n2 >>= 1, s++;
	res = power(base, n2, n);
	if(res == 1 || res == n - 1) return 1;
	s--;
	while(s >= 0)
	{
		res = multi(res, res, n);
		if(res == n - 1) return 1;
		s--;
	}
	return 0;	// n is not a strong pseudo prime
}
int isprime(ll n)
{
	static ll testNum[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	static ll lim[] = {4, 0, 1373653ll, 25326001ll, 25000000000ll, 2152302898747ll, 3474749660383ll, 341550071728321ll, 0, 0, 0, 0};
	if(n < 2 || n == 3215031751ll) return 0;
	for(int i = 0; i < 12; i++)
	{
		if(n < lim[i]) return 1;
		if(!primetest(n, testNum[i])) return 0;
	}
	return 1;
}
ll pollard(ll n)
{
	ll i, x, y, p;
	if(isprime(n)) return n;
	if(!(n & 1)) return 2;
	for(i = 1; i < 20; i++)
	{
		x = i, y = func(x, n), p = gcd(y - x, n);
		while(p == 1)
		{
			x = func(x, n);
			y = func(func(y, n), n);
			p = gcd((y - x + n) % n, n) % n;
		}
		if(p == 0 || p == n) continue;
		return p;
	}
}
