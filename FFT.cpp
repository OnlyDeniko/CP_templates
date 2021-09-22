#include<bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()


const long double pi = acosl(-1.);
const int base = 10;

void fft(vector<complex<double> > &a, bool invert) {
	int n = (int)a.size();
	if (n == 1)  return;
	vector<complex<double> > a0, a1;
	for (int i = 0; i < n; i += 2) {
		a0.push_back(a[i]);
		a1.push_back(a[i + 1]);
	}
	fft(a0, invert);
	fft(a1, invert);
	double alp = 2 * pi / n * (invert ? -1 : 1);
	complex<double> w(1), mult(cosl(alp), sinl(alp));
	for (int i = 0; i < n / 2; i++) {
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		if (invert) {
			a[i] /= 2;
			a[i + n / 2] /= 2;
		}
		w *= mult;
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

void convert(string s, string t, vector<int> &a, vector<int> & b){
    for(auto x : s){
        a.push_back(x - '0');
    }
    for(auto x : t){
        b.push_back(x - '0');
    }
}

signed main() {
    //на вход два длинных числа, на выходее результат умножения
    string  s, t;
    cin >> s >> t;
    vector<int> a, b;
    convert(s, t, a, b);
	vector<int> res;
	multiply(a, b, res);
    reverse(all(res));
	reverse(all(a));
	reverse(all(b));
	for(auto x : res)
        cout << x;
	return 0;
}
//17x^4 - 6x^3 - x^2 + 23x - 17
//42x^5 - 20x^4 - 19x^3 + 3x^2 + 11x - 243
