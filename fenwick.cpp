const int N = 1e6;
int f[N];

void add(int x, int y){
  x++;
  while(x < N){
    f[x] += y;
    x += x & -x;
  }
}

int sum(int x){
  x++;
  int ans = 0;
  while(x){
    ans += f[x];
    x -= x & -x;
  }
  return ans;
}

int sum(int l, int r){
  return sum(r) - sum(l - 1);
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
