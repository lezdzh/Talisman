void gauss()
{
	for(int i = 1; i <= n; i++)
	{
		for(int j = i; j <= n; j++)
			if(fabs(a[j][i]) > eps)
			{
				for(int k = 1; k <= n + 1; k++)
					swap(a[i][k], a[j][k]);
				break;
			}
		for(int j = i + 1; j <= n; j++)
		{
			double t = a[j][i] / a[i][i];
			for(int k = 1; k <= n + 1; k++)
				a[j][k] -= t * a[i][k];
		}
	}
}
