struct BigNum {
	int sign, len;
	int a[100];
	BigNum() {
		memset(a, 0, sizeof(a));
	}
	BigNum f() const {
		BigNum res;
		res.sign = sign * -1;
		res.len = len;
		for (int i = 1; i <= len; i++)
			res.a[i] = a[i];
		return res; 
	}
	bool operator > (const BigNum &rhs) const {
		if (sign > rhs.sign) return true;
		if (sign < rhs.sign) return false;
		if (sign == 0) return false;
		if (sign > 0) {
			if (len > rhs.len) return true;
			if (len < rhs.len) return false;
			for (int i = len; i >= 1; i--) {
				if (a[i] > rhs.a[i]) return true;
				if (a[i] < rhs.a[i]) return false;
			}
			return false;
		} else {
			if (len > rhs.len) return false;
			if (len < rhs.len) return true;
			for (int i = len; i >= 1; i--) {
				if (a[i] > rhs.a[i]) return false;
				if (a[i] < rhs.a[i]) return true;
			}
			return false;
		}
	}
	BigNum operator + (const BigNum &rhs) const {
		if (sign == 0) return rhs;
		if (rhs.sign == 0) return *this;
		if (sign * rhs.sign < 0) {
			if (sign < 0) return rhs - this->f();
			else return *this - rhs.f();
		}
		BigNum res;
		if (sign * rhs.sign > 0) res.sign = sign;
		res.len = max(len, rhs.len);
		for (int i = 1; i <= res.len; i++) {
			res.a[i] += a[i] + rhs.a[i];
			if (res.a[i] >= 10) {
				res.a[i + 1]++;
				res.a[i] -= 10;
			}
		}
		if (res.a[res.len + 1]) res.len++;
		return res;
	}
	BigNum operator - (const BigNum &rhs) const {
		if (rhs.sign == 0) return *this;
		if (sign == 0) return rhs.f();
		if (sign < 0 && rhs.sign < 0) return rhs.f() - this->f();
		if (sign < 0) return (this->f() + rhs).f();
		if (rhs.sign < 0) return *this + rhs.f();
		if (*this > rhs) {
			BigNum res;
			res.sign = 1;
			res.len = len;
			for (int i = 1; i <= len; i++)
				res.a[i] = a[i];
			for (int i = 1; i <= len; i++) {
				res.a[i] -= rhs.a[i];
				if (res.a[i] < 0) {
					res.a[i] += 10;
					res.a[i + 1]--;
				}
			}
			while (res.a[res.len] == 0) res.len--;
			return res;
		} else if (rhs > *this) return (rhs - *this).f();
		else {
			BigNum res;
			res.sign = 0;
			res.len = 1; res.a[1] = 0;
			return res;
		}
	}
	BigNum operator * (const BigNum &rhs) const {
		BigNum res;
		res.sign = sign * rhs.sign;
		if (res.sign == 0) {
			res.len = 1; res.a[1] = 0;
			return res;
		}
		for (int i = 1; i <= len; i++)
			for (int j = 1; j <= rhs.len; j++) {
				int k = i + j - 1;
				res.a[k] += a[i] * rhs.a[j];
				res.a[k + 1] += res.a[k] / 10;
				res.a[k] %= 10;
			}
		res.len = len + rhs.len - 1;
		if (res.a[res.len + 1]) res.len++;
		return res;
	}
} Zero;

BigNum Trans(long long x) {
	BigNum res;
	if (x < 0) res.sign = -1; else res.sign = 1;
	x *= res.sign;
	res.len = 0;
	if (x == 0) res.sign = 0, res.len = 1, res.a[1] = 0;
	while (x) {
		res.a[++res.len] = x % 10;
		x /= 10;
	}
	return res;
}
