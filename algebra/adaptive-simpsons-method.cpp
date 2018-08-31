namespace adaptive_simpson {
	template<typename function>
	inline double area(function f, const double &left, const double &right) {
		double mid = (left + right) / 2;
		return (right - left) * (f(left) + 4 * f(mid) + f(right)) / 6;
	}

	template<typename function>
	inline double simpson(function f, const double &left, const double &right, const double &eps, const double &area_sum) {
		double mid = (left + right) / 2;
		double area_left = area(f, left, mid);
		double area_right = area(f, mid, right);
		double area_total = area_left + area_right;
		if (fabs(area_total - area_sum) <= 15 * eps) {
			return area_total + (area_total - area_sum) / 15;
		}
		return simpson(f, left, right, eps / 2, area_left) + simpson(f, mid, right, eps / 2, area_right);
	}

	template<typename function>
	inline double simpson(function f, const double &left, const double &right, const double &eps) {
		return simpson(f, left, right, eps, area(f, left, right));
	}
}
