//gwx
typedef long long ll;
ll gcd(ll a, ll b)
{
	if(!b)	
		return a;
	return gcd(b, a % b);
}
ll lcm(ll a, ll b)
{
	ll g = gcd(a, b);
	return a / g * b;
}
struct num
{
	ll i, next, x, y;
	num() {}
	num(ll i0, ll next0, ll x0, ll y0) {
		i = i0;
		next = next0;
		ll g = gcd(x0, y0);
		x = x0 / g;
		y = y0 / g;
	} 
	num operator + (const num & a) const {
		ll x1 = x, x2 = a.x, y1 = y, y2 = a.y;
		ll F = lcm(y1, y2);
		ll U = F / y1 * x1 + F / y2 * x2;
		ll g = gcd(F, U);
		U /= g;
		F /= g;
		return (num){0, 0, U, F};
		//Not use construct function
	}
	num operator - (const num & a) const {
		ll x1 = x, x2 = a.x, y1 = y, y2 = a.y;
		ll F = lcm(y1, y2);
		ll U = F / y1 * x1 - F / y2 * x2;
		ll g = gcd(F, U);
		U /= g;
		F /= g;
		return (num){0, 0, U, F};
	}
	num operator * (const num & a) const {
		ll x1 = x, x2 = a.x, y1 = y, y2 = a.y;
		ll g1 = gcd(x1, y2);
		ll g2 = gcd(x2, y1);
		ll F = (y1 / g2) * (y2 / g1);
		ll U = (x1 / g1) * (x2 / g2);
		return (num){0, 0, U, F};
	}
	num operator / (const num & a) const {
		ll x1 = x, x2 = a.y, y1 = y, y2 = a.x;
		ll g1 = gcd(x1, y2);
		ll g2 = gcd(x2, y1);
		ll F = (y1 / g2) * (y2 / g1);
		ll U = (x1 / g1) * (x2 / g2);
		return (num){0, 0, U, F};
	}
};
