vector<int> suf_mas(string s){
  s += char(1);
  int n = s.size();
  vector<int> p(n), c(n);
  vector<pair<int, int>> a(n);
  for(int i = 0;i < n;i++){
    a[i] = {s[i], i};
  }
  sort(a.begin(), a.end());
  for(int i = 0;i < n;i++) p[i] = a[i].second;
  c[p[0]] = 0;
  for(int i = 1;i < n;i++){
    c[p[i]] = c[p[i - 1]] + !!(s[p[i]] != s[p[i - 1]]);
  }
  int step = 0;
  vector<int> counter(n, 0);
  vector<int> new_p(n);
  vector<int> new_c(n);
  while((1 << step) < n){
    fill(all(counter), 0);
    for(int i = 0;i < n;i++){
      new_p[i] = p[i] - (1 << step);
      if (new_p[i] < 0) new_p[i] += n;
      counter[c[new_p[i]]]++;
    }
    partial_sum(all(counter), counter.begin());
    for(int i = n - 1;i >= 0;i--){
      p[--counter[c[new_p[i]]]] = new_p[i];
    }
    new_c[p[0]] = 0;
    for(int i = 1;i < n;i++){
      int index1 = (p[i] + (1 << step)) % n;
      int index2 = (p[i - 1] + (1 << step)) % n;
      new_c[p[i]] = new_c[p[i - 1]];
      if (c[index1] != c[index2] ||
          c[p[i]] != c[p[i - 1]]){
        new_c[p[i]]++;
      }
    }
    c = new_c;
    step++;
  }
  p.erase(p.begin());
  return p;
}

vector<int> calc_LCP(const vector<int> & suf, const string & s){
  int n = suf.size();
  vector<int> a(n);
  vector<int> lcp(n, 0);
  for(int i = 0;i < n;i++) a[suf[i]] = i;

  auto calc = [&](int index1, int index2, int pos){
    if (index2 == n) return 0;
    int ans = pos;
    index1 = suf[index1] + pos;
    index2 = suf[index2] + pos;
    while(max(index1, index2) < n){
      if (s[index1] != s[index2]) break;
      ans++;
      index1++;
      index2++;
    }
    return ans;
  };
 
  lcp[a[0]] = calc(a[0], a[0] + 1, 0);
  for(int i = 1;i < n;i++){
    lcp[a[i]] = calc(a[i], a[i] + 1, max(0, lcp[a[i - 1]] - 1));
  }
  return lcp;
}