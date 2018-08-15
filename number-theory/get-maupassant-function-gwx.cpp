void init()
{
	mu[1] = 1;
	for(int i = 2; i <= lim; i++)
	{
		if(!p[i])
		{
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= cnt && i * prime[j] <= lim; j++)
		{
			p[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			else
				mu[i * prime[j]] = -mu[i];
		}
	}
}
//gwx
	for(int i = 2; i <= N; i++)
	{
		if(!phi[i])
		{
			pri[++tot]=i;
			phi[i] = i-1;
		}
		for(int j = 1; j <= tot && i * pri[j] <= N; j++)
		if(i % pri[j] == 0)
		{
			phi[i * pri[j]] = phi[i] * pri[j];
			break;
		}
		else phi[i * pri[j]] = phi[i] * (pri[j] - 1);
	}
	
//莫比乌斯反演+分块
void init()
{
	mu[1] = 1;
	for(int i = 2; i <= up; i++)
	{
		if(!p[i]) prime[++cnt] = i, mu[i] = -1;
		for(int j = 1; j <= cnt && i * prime[j] <= up; j++)
		{
			p[i * prime[j]] = 1;
			if(i % prime[j] == 0)  {mu[i * prime[j]] = 0; break;}
			else mu[i * prime[j]] = -mu[i];
		}
	}
}

void solve()
{
    for(int i = 1, j = 1; i <= n; i = j + 1)
    {
    	j = min(m / (m / i), n / (n / i));
    	ans += (ll)(mu[j] - mu[i - 1]) * d[n / i] * d[m / i];
    }
}
