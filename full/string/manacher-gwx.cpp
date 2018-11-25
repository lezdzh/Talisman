//maxn = 2 * n
void manacher(int n)
{
	int p = 0, r = 0;
	for(int i = 1; i <= n; i++)
	{
		if(i <= r) len[i] = min(len[2 * p - i], r - i + 1);
		else len[i] = 1;
		while(b[i + len[i]] == b[i - len[i]]) len[i]++;
		if(i + len[i] - 1 >= r)
			r = i + len[i] - 1, p = i;
	}
}

int main()
{
	scanf("%d\n%s", &n, a + 1);
	b[++tot] = '@'; b[++tot] = '#';
	for(int i = 1; i < n; i++)
		b[++tot] = a[i], b[++tot] = '#';
	b[++tot] = a[n];
	b[++tot] = '#'; b[++tot] = '$';
	manacher(tot);
}
