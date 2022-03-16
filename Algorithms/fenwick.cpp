struct Fenwick{
  int N;
  vector<int> f;

  Fenwick(int _n) : N(_n){
    f.resize(N, 0);
  }

  // calculating the k-th unit on a segment
  // initially calc_pos(step, N, k)
  // where step = max {i: 2^i <= N}
  int calc_pos(int step, int pos, int k){ 
    if (step == 0) return pos;
    if (pos - step >= N){
      return calc_pos(step >> 1, pos - step, k);
    }
    int elem = f[pos - step];
    if (elem >= k){
      return calc_pos(step >> 1, pos - step, k);
    }
    return calc_pos(step >> 1, pos, k - elem);
  }
};
