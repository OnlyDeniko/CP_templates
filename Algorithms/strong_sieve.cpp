struct Sieve{
	int n;
  vector<int> primes, md;
  vector<int> mu;   // Mobius function
  vector<int> phi;  // Euler function
  vector<int> a1;   // step for p1
  vector<int> p1a1; // contains p1^a1
  vector<int> si0;  // number of divisors
  vector<int> si1;  // sum of all divisors

  Sieve(int _n) : n(_n){
    md.resize(n + 1);
    iota(md.begin(), md.end(), 0);
	  md[1] = 0;  
    for(int i = 2;i <= n;++i){
      if (md[i] == i) primes.push_back(i);
      for(int j = 0;j < primes.size() &&
          primes[j] <= md[i] &&
          1ll * i * primes[j] <= n;j++)
            md[i * primes[j]] = primes[j];
    }

    mu.resize(n + 1, 0);
    mu[1] = 1;
    phi.resize(n + 1, 0);
    phi[1] = 1;
    a1.resize(n + 1, 0);
    a1[1] = 1;
    p1a1.resize(n + 1, 0);
    p1a1[1] = 1;
    si0.resize(n + 1, 0);
    si0[1] = 1;
    si1.resize(n + 1, 0);
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
};