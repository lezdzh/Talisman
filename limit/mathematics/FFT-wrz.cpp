typedef complex<double> comp;
int len;
comp w[N<<1], a[N<<1], b[N<<1], c[N<<1]; // 数组记得至少开两倍
void init()
{
	double pi = acos(-1.0);
	for(int i = 0; i < len; i++) w[i] = (comp){cos(2*pi*i/len), sin(2*pi*i/len)};
}
void FFT(comp *a, comp *w)
{
	for(int i = 0, j = 0; i < len; i++)
	{
		if(i<j) swap(a[i], a[j]);
		for(int l = len>>1; (j^=l)<l; l >>= 1);
	}
	for(int i = 2; i <= len; i <<= 1)
	{
		int m = i >> 1;
		for(int j = 0; j < len; j += i)
		{
			for(int k = 0; k < m; k++)
			{
				comp tmp = w[len/i*k] * a[j+k+m];
				a[j+k+m] = a[j+k] - tmp;
				a[j+k] = a[j+k] + tmp;
			}
		}
	}
}
void mul(comp *a, comp *b, comp *c, int l) // 多项式乘法，c = a * b ，c的长度为l
{
	for(len = 1; len <= l; len <<= 1);
	init(); FFT(a, w); FFT(b, w);
	for(int i = 0; i < len; i++) c[i] = a[i] * b[i];
	reverse(c+1, c+len); FFT(c, w);
	for(int i = 0; i < len; i++) c[i].r /= len; // 转化为int等时应加0.5，如int(c[i].r+0.5)
}