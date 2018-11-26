// 用之前必须先init(); 如果所有的逆元都能预处理就是O(n)的，否则是O(nlogn)的
#define MOD 1000000007
int inv[N], invf[N], f[N];
int fpow(int a, int b)
{
	int r = 1;
	for(; b; b >>= 1)
	{
		if(b & 1) r = 1ll*r*a%MOD;
		a = 1ll*a*a%MOD;
	}
	return r;
}
int la(int x, int k) // k次，求f(x)
{
	int lim = k+2, ff = 1; 
	for(int i = 1; i <= lim; i++) ff = 1ll * ff * (x-i) % MOD;
	for(int i = 1; i <= lim; i++) f[i] = (f[i-1] + fpow(i, k)) % MOD; // 预处理 f(1),f(2),...,f(lim)，注意修改
	if(x <= lim) return f[x]; int ret = 0;
	for(int i = 1; i <= lim; i++)
	{
		(ret += 1ll * f[i] 
				* ff % MOD * (x-i < N ? inv[x-i] : fpow(x-i, MOD-2)) % MOD // 复杂度
				* invf[i-1] % MOD * invf[lim-i] % MOD * ((lim-i) % 2 ? MOD-1 : 1) % MOD
		) %= MOD;
	}
	return ret;
}
void init()
{
	inv[1] = 1;	for(int i = 2; i < N; i++) inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
	invf[0] = 1; for(int i = 1; i < N; i++) invf[i] = 1ll * invf[i-1] * inv[i] % MOD;
}