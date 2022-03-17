int gcdex(int a, int b, int& x, int& y) {
	int c, q, xp, yp;
	x = yp = 1, y = xp = 0;
	while (b != 0) {
		q = a / b;
		c = a - q * b;
		a = b, b = c;
		c = x - q * xp;
		x = xp, xp = c;
		c = y - q * yp;
		y = yp, yp = c;
	}
	return a;
}

// a*x + b*y = c
bool diophantine_eq(int a, int b, int c, int & x0, int & y0, int & g) {
	g = gcdex(abs(a), abs(b), x0, y0);
	if (c % g != 0)
		return false;
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0)   x0 *= -1;
	if (b < 0)   y0 *= -1;
	return true;
}