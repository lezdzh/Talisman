ll solve()
{
	ll res = 0;
	memset(b, 0, sizeof(b));
	for(int i = 1; i <= tot; i++)
		for(int j = 60; j >= 0; j--)
			if((a[i] >> j) & 1)
			{
				if(!b[j])
				{
					b[j] = a[i];
					break;
				}
				a[i] ^= b[j];
			}
	for(int i = 60; i >= 0; i--)
		res = max(res, res ^ b[i]);
	return res;
}