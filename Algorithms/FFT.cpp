struct Complex {
	long double x, y;

	Complex() : x(), y() {}

	Complex(long double x, long double y) : x(x), y(y) {}

	Complex operator+(const Complex& o) const {
		return {x + o.x, y + o.y};
	}

	Complex operator-(const Complex& o) const {
		return {x - o.x, y - o.y};
	}

	Complex operator*(const Complex& o) const {
		return {x * o.x - y * o.y, x * o.y + y * o.x};
	}
};

const long double PI = acosl(-1);

// a should be of size 2^k
void fft(vector<Complex>& a, bool inv = false) {
	for (int i = 1, j = 0; i < a.size(); i++) {
		int bit = a.size() / 2;
		for (; j >= bit; bit /= 2) {
			j -= bit;
		}
		j += bit;
		if (i < j) {
			swap(a[i], a[j]);
		}
	}
	int n = a.size();
	for (int k = 1; k < n; k *= 2) {
		long double ang = PI / (inv ? -k : k);
		Complex e(cosl(ang), sinl(ang));
		for (int i = 0; i < n; i += 2 * k) {
			Complex w(1, 0);
			for (int j = 0; j < k; ++j) {
				Complex v = a[i + j + k] * w;
				a[i + j + k] = a[i + j] - v;
				a[i + j] = a[i + j] + v;
				w = w * e;
			}
		}
	}
	if (inv) {
		for (int i = 0; i < n; i++) {
			a[i].x /= n;
			a[i].y /= n;
		}
	}
}

void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res) {
	vector<complex<double> > aa(all(a)), bb(all(b));
	int size = 1;
	while (size < max((int)a.size(), (int)b.size())) size <<= 1;
	size <<= 1;
	aa.resize(size);
	bb.resize(size);

	fft(aa, 0);
	fft(bb, 0);
	for (int i = 0; i < size; i++) {
		aa[i] *= bb[i];
	}
	fft(aa, 1);
	res.resize(size);
	for (int i = 0; i < size; i++) {
		double now = aa[i].real();
		if (now > 0) res[i] = int(now + 0.5);
		else {
			res[i] = int(now - 0.5);
		}
//		cout << "! " << res[i] << ' ';
	}
    int cr = 0;
    for(int i = 0;i < res.size();i++){
        res[i] += cr;
        cr = res[i] / base;
        res[i] %= base;
    }
	while (res.size() && res.back() == 0) res.pop_back();
}
