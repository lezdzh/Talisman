void linear_recurrence(long long n, int m, int a[], int c[], int p) {
	long long v[M] = {1 % p}, u[M << 1], msk = !!n;
	for(long long i(n); i > 1; i >>= 1) {
		msk <<= 1;
	}
	for(long long x(0); msk; msk >>= 1, x <<= 1) {
		fill_n(u, m << 1, 0);
		int b(!!(n & msk));
		x |= b;
		if(x < m) {
			u[x] = 1 % p;
		}else {
			for(int i(0); i < m; i++) {
				for(int j(0), t(i + b); j < m; j++, t++) {
					u[t] = (u[t] + v[i] * v[j]) % p;
				}
			}
			for(int i((m << 1) - 1); i >= m; i--) {
				for(int j(0), t(i - m); j < m; j++, t++) {
					u[t] = (u[t] + c[j] * u[i]) % p;
				}
			}
		}
		copy(u, u + m, v);
	}
	//a[n] = v[0] * a[0] + v[1] * a[1] + ... + v[m - 1] * a[m - 1].
	for(int i(m); i < 2 * m; i++) {
		a[i] = 0;
		for(int j(0); j < m; j++) {
			a[i] = (a[i] + (long long)c[j] * a[i + j - m]) % p;
		}
	}
	for(int j(0); j < m; j++) {
		b[j] = 0;
		for(int i(0); i < m; i++) {
			b[j] = (b[j] + v[i] * a[i + j]) % p;
		}
	}
	for(int j(0); j < m; j++) {
		a[j] = b[j];
	}
}
