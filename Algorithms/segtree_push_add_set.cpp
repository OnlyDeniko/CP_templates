struct Segtree {
  int n;
  const int INF = 1e9;

  vector<int> t, madd, mset;

  Segtree(int _n){
    n = _n;
    t.assign(4 * n, 0);
    madd.assign(4 * n, 0);
    mset.assign(4 * n, INF);
  }

  void push(int v, int tl, int tr, int l, int r){
    int m = (tl + tr) >> 1;
    if (mset[v] != INF){
      set(v << 1, tl, m, tl, m, mset[v]);
      set(v << 1 | 1, m + 1, tr, m + 1, tr, mset[v]);
      mset[v] = INF;
    } else if (madd[v] != 0){
      add(v << 1, tl, m, tl, m, madd[v]);
      add(v << 1 | 1, m + 1, tr, m + 1, tr, madd[v]);
      madd[v] = 0;
    }
  }

  void add(int v, int tl, int tr, int l, int r, int val){
    if (l > r) return;
    if (tl == l && tr == r){
      if (mset[v] != INF){
        mset[v] += val;
      } else {
        madd[v] += val;
      }
      t[v] += val * (r - l + 1);
      return;
    }
    push(v, tl, tr, l, r);
    int mid = (tl + tr) >> 1;
    add(v << 1, tl, mid, l, min(r, mid), val);
    add(v << 1 | 1, mid + 1, tr, max(l, mid + 1), r, val);
    t[v] = t[v << 1] + t[v << 1 | 1];
  }
  void set(int v, int tl, int tr, int l, int r, int val){
    if (l > r) return;
    if (tl == l && tr == r){
      mset[v] = val;
      t[v] = val * (r - l + 1);
      madd[v] = 0;
      return;
    }
    push(v, tl, tr, l, r);
    int mid = (tl + tr) >> 1;
    set(v << 1, tl, mid, l, min(r, mid), val);
    set(v << 1 | 1, mid + 1, tr, max(l, mid + 1), r, val);
    t[v] = t[v << 1] + t[v << 1 | 1];
  }
  int get(int v, int tl, int tr, int l, int r){
    if (l > r) return 0;
    if (tl == l && tr == r){
      return t[v];
    }
    push(v, tl, tr, l, r);
    int m = (tl + tr) >> 1;
    return get(v << 1, tl, m, l, min(r, m)) + get(v << 1 | 1, m + 1, tr, max(l, m + 1), r);
  }
};
