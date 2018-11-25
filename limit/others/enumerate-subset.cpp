for (int x = 1; x <= n; x++)
	for (int y  = x & (x - 1); y; (--y) &= x) {
		//y is a subset of x
	}
