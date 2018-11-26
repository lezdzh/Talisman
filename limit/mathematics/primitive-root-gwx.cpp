bool check_force(int g, int p)
{
	int cnt = 0, prod = g;
	for(int i = 1; i <= p - 1; ++i, prod = prod * g % p)
		if(prod == 1) if(++cnt > 1) return 0;
	return 1;
}
//d[]: prime divisor of (p - 1)
bool check_fast(int g, int p)
{
	for(int i = 1; i <= m; ++i)
		if(power(g, (p - 1) / d[i], p) == 1) return 0;
	return 1;
}
int primitive_root(int p)
{
	for(int i = 2; i < p; ++i) if(check(i, p)) return i;
}