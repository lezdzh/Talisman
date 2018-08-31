int min_represent(char *s, int len) // 当s不是字符串时应该将char改成int等，len是s的长度，下标从0开始到n-1结束
{
	int i = 0, j = 1;
	for(; i < len && j < len; )
	{
		int k = 0;
		for(; s[(i+k)%len] == s[(j+k)%len] && k < len; k++);
		if(k == len) break;
		if(s[(i+k)%len] > s[(j+k)%len])
		{
			i += k+1;
			if(i <= j) i = j + 1;
		}
		else 
		{
			j += k+1;
			if(j <= i) j = i + 1;
		}
	}
	return i < j ? i : j;
}