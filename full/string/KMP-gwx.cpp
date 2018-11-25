void kmp(char a[], char b[])  //a串中找b串
{
    int j = 0;
    for(int i = 2; i <= m; i++)
    {
    	while(j && b[i] != b[j + 1]) j = p[j];
    	if(b[i] == b[j + 1])  j++;
    	p[i] = j;
    }
    j = 0;
    for(int i = 1; i <= n; i++)
    {
    	while(j && b[j + 1] != a[i]) j = p[j];
    	if(b[j + 1] == a[i]) j++;
    	if(j == m)
    	{
    	    ans[++cnt] = i;
    	    j = p[j];
    	}
    }
}
