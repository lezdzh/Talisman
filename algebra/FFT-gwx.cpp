#include <complex>

int n, m;
int rev[maxn];  //maxn > 2 ^ k

struct C
{
	double r, i;
	friend C operator + (const C &a, const C &b){
		return (C){a.r + b.r, a.i + b.i};
	}
	friend C operator - (const C &a, const C &b){
		return (C){a.r - b.r, a.i - b.i};
	}
	friend C operator * (const C &a, const C &b){
		return (C){a.r*b.r - a.i*b.i, a.r*b.i + a.i*b.r};
	}
	C operator / (const double x){
		return (C){r / x, i / x};
	}
} a[maxn], b[maxn];

void fft(C *a, int f)
{
	for(int i = 0; i < m; i++)
		if(i < r[i])
			swap(a[i], a[r[i]]);
	for(int l = 2; l <= m; l <<= 1)
	{
		int h = l >> 1;
		C ur = (C){cos(pi / h), f * sin(pi / h)};
		for(int i = 0; i < m; i += l)
		{
			C w = (C){1, 0};
			for(int k = 0; k < h; k++, w = w * ur)
			{
				C x = a[i + k], y = a[i + k + h] * w;
				a[i + k] = x + y; a[i + k + h] = x - y;
			}
		}
	}
	if(f == -1)
		for(int i = 0; i < m; i++)
			a[i] = a[i] / m;
}

void multi(C *a, C *b)
{
    fft(a, 1); fft(b, 1);
	for(int i = 0; i < m; i++)
		a[i] *= b[i];
	fft(a, -1);
}

void init()
{
    for(m = 1; m <= 2 * n; m <<= 1);
	for(int i = 0, j = 0; i < m; i++)
	{
		rev[i] = j;
		for(int x = m >> 1; (j ^= x) < x; x >>= 1);
	}
}
