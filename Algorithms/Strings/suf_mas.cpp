struct SuffixArray{
  vector<int> mas, c, lcp;
  int N;
  string S;
  SuffixArray(string _s) : N(_s.size()), S(_s){
    build_suf(_s);
    build_lcp();
  }
  void build_suf(string s){
    s += char(0);
    int n = s.size();
    mas.resize(n);
    c.resize(n);
    vi counter(n, 0);
    vpi a;
    for(int i = 0;i < n;i++) a.pb({s[i], i});
    sort(all(a));
    for(int i = 0;i < n;i++)mas[i] = a[i].second;
    c[mas[0]] = 0;
    for(int i = 1;i < n;i++){
      c[mas[i]] = c[mas[i - 1]] + !!(s[mas[i]] != s[mas[i - 1]]);
    }
    int step = 0;
    vector<int> new_p(n);
    vector<int> new_c(n);
    while((1 << step) < n){
      fill(all(counter), 0);
      for(int i = 0;i < n;i++){
        new_p[i] =(mas[i] - (1 << step) + n) % n;
        counter[c[new_p[i]]]++;
      }
      partial_sum(all(counter), counter.begin());
      for(int i = n - 1;i >= 0;i--){
        mas[--counter[c[new_p[i]]]] = new_p[i];
      }
      new_c[mas[0]] = 0;
      for(int i = 1;i < n;i++){
        int index1 = (mas[i] + (1 << step)) % n;
        int index2 = (mas[i - 1] + (1 << step)) % n;
        new_c[mas[i]] = new_c[mas[i - 1]];
        if (c[index1] != c[index2] ||
            c[mas[i]] != c[mas[i - 1]]){
          new_c[mas[i]]++;
        }
      }
      c = new_c;
      step++;
    }
    mas.erase(mas.begin());
    c.erase(c.begin());
  }
 
  void build_lcp(){
    vi a(N);
    for(int i = 0;i < N;i++) a[mas[i]] = i;
    lcp.resize(N);
 
    auto calc = [&](int index1, int index2,
                    int pos)->int{
      if (index2 == N) return 0;
      int ans = pos;
      index1 = mas[index1] + pos;
      index2 = mas[index2] + pos;
      while(max(index1, index2) < N){
        if (S[index1] != S[index2]) break;
        ans++, index1++, index2++;
      }
      return ans;
    };
 
    lcp[a[0]] = calc(a[0], a[0] + 1, 0);
    for(int i = 1;i < N;i++){
      lcp[a[i]] = calc(a[i], a[i] + 1, max(0, lcp[a[i - 1]] - 1));
    }
  }
 
  ll unique_strings(){
    ll sum = 0;
    forr(i, lcp) sum += i;
    return 1ll * N * (N + 1) / 2 - sum;
  }
 
  pii find(const string & t){
    int l = 0, r = N - 1;
    pii ans = {-1, -1};
    for(int i = 0;i < (int)t.size();i++){
      int ll = l, rr = r;
      int left_ans = -1;
      while(ll <= rr){
        int mid = (ll + rr) >> 1;
        if (mas[mid] + i < N && S[mas[mid] + i] >= t[i]){
          left_ans = mid;
          rr = mid - 1;
        } else ll = mid + 1;
      }
      if (left_ans == -1 ||
          S[mas[left_ans] + i] > t[i]){
        return ans;
      }
      ll = left_ans, rr = r;
      int right_ans = -1;
      while(ll <= rr){
        int mid = (ll + rr) >> 1;
        if (mas[mid] + i < N && S[mas[mid] + i] <= t[i]){
          right_ans = mid;
          ll = mid + 1;
        } else rr = mid - 1;
      }
      if (right_ans == -1 ||
          S[mas[right_ans] + i] < t[i]){
        return ans;
      }
      l = left_ans;
      r = right_ans;
    }
    return {l, r};
  }
};