void solve(){
	const int n = 1e7;
	// p contains prime numbers
	// md contains the minimum number that is divisible by i
	vector<int> p, md(n + 1);
	iota(md.begin(), md.end(), 0);
	md[1] = 0;

	for(int i = 2;i < n + 1;++i){
		if (md[i] == i) p.push_back(i);
		for(int j = 0;j < p.size() && p[j] <= md[i] && 1ll * i * p[j] <= n;j++) md[i * p[j]] = p[j];
	}
	// Mobius function -> https://ru.wikipedia.org/wiki/%D0%A4%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F_%D0%9C%D1%91%D0%B1%D0%B8%D1%83%D1%81%D0%B0				
	vector<int> mu(n + 1);
	mu[1] = 1;
	// Euler function -> the number of numbers from 1 to n that are coprime with it
	vector<int> phi(n + 1);
	phi[1] = 1;
	// step for p1
	vector<int> a1(n + 1);
	a1[1] = 1;
	// contains p1^a1
	vector<int> p1a1(n + 1);
	p1a1[1] = 1;
	// number of divisors of i-th number
	vector<int> si0(n + 1);
	si0[1] = 1;
	// sum of all divisors of i-th number
	vector<int> si1(n + 1);
	si1[1] = 1;
	for(int i = 2;i < n + 1;++i){
		int j = i / md[i];
		
		if (md[i] == md[j]) {
			mu[i] = 0;
			phi[i] = md[i] * phi[j];
			a1[i] = a1[j] + 1;
			p1a1[i] = md[i] * p1a1[j];
			si0[i] = si0[j] / (a1[j] + 1)  * (a1[i] + 1);			
			int was = (p1a1[j] * md[j] - 1) / (md[j] - 1);
			int now = (p1a1[i] * md[i] - 1) / (md[i] - 1);
			si1[i] = si1[j] / was * now;
		}	else {
			mu[i] = -mu[j];
			phi[i] = (md[i] - 1) * phi[j];
			a1[i] = 1;
			p1a1[i] = md[i];
			si0[i] = si0[j] * 2;
			si1[i] = si1[j] * (p1a1[i] * md[i] - 1) / (md[i] - 1);
		}
	}
		
}