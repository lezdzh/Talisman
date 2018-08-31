int power(ll b, int k, int p)
{
	ll res = 1;
	for(; k; k >>= 1, b = b * b % p)
		if(k & 1)
			res = res * b % p;
	return res;
}

bool check(int x, int p)
{
	int cnt = 0;
	for(int i = 1; i <= p - 1; i++)
		if(power(x, i, p) == 1)
			if(++cnt > 1)
				return 0;
	return cnt == 1;
}

int primitive_root(int p)
{
	for(int i = 2; i < p; i++)
		if(check(i, p))
			return i;
}
