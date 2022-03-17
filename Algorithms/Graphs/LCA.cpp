struct LCA{
  static const int LOG = 25;
  int n, start;
  vector<int> true_dist, fake_dist, parent;
  vector<vi> bp;

  LCA(vector<vpi> & g, int start = 0): n(g.size()), start(start){
    true_dist.assign(n, INT_MAX);
    fake_dist.assign(n, INT_MAX);
    parent.assign(n, -1);
    true_dist[start] = fake_dist[start] = 0;
    parent[start] = start;
    bp.assign(n, vector<int>(LOG));
    build(g);
  }

  void build(vector<vpi> & g){
    vector<int> que = {start};
    for(int i = 0;i < que.size();i++){
      int cur = que[i];
      for(auto& [to, len] : g[cur]) if (true_dist[to] > true_dist[cur] + len){
        true_dist[to] = true_dist[cur] + len;
        fake_dist[to] = fake_dist[cur] + 1;
        parent[to] = cur;
        que.push_back(to);
      }
    }
    for(int i = 0;i < n;i++) bp[i][0] = parent[i];
    for(int j = 1;j < LOG;j++){
      for(int i = 0;i < n;i++){
        bp[i][j] = bp[bp[i][j - 1]][j - 1];
      }
    }
  }

  int lca(int x, int y){
    if (fake_dist[x] > fake_dist[y]) swap(x, y);
    for(int i = LOG - 1;i >= 0;i--){
      if (fake_dist[bp[y][i]] >= fake_dist[x]){
        y = bp[y][i];
      }
    }
    if (x == y) return x;
    assert(fake_dist[x] == fake_dist[y]);
    for(int i = LOG - 1;i >= 0;i--){
      if (bp[x][i] != bp[y][i]){
        x = bp[x][i];
        y = bp[y][i];
      }
    }
    return parent[x];
  }

  int distance(int x, int y){
    return true_dist[x] + true_dist[y] - 2 * true_dist[lca(x, y)];
  }
};
