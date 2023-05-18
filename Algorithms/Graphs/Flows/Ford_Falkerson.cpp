struct FordMaxFlow {
	struct Edge {
		int from, to, cap, flow;
	};

	int n;
	vector<vector<int>> g;
	vector<Edge> e;
  vector<int> used;
	int s_, t_;

  int _rem(int i){
    return e[i].cap - e[i].flow;
  }

	int _dfs(int x, int mx){
    if (x == t_) return mx;
    if (used[x] || mx == 0) return 0;
    used[x] = 1;
    forr(i, g[x]){
      int to = e[i].to;
      int fl = _dfs(to, min(mx, _rem(i)));
      if (fl){
        e[i].flow += fl;
        e[i ^ 1].flow -= fl;
        return fl;
      }
    }
    return 0;
  }

	FordMaxFlow(int n) : n(n), g(n), s_(), t_() {}

	void addEdge(int x, int y, int c){
    deb(x, y, c);
    g[x].pb(e.size());
    e.pb({x, y, c, 0});
    g[y].pb(e.size());
    e.pb({y, x, 0, 0});
  }

	int maxFlow(int s, int t){
    int ans = 0;
    s_ = s, t_ = t;
    while(1){
      used.assign(n, 0);
      int f = _dfs(s_, INT_MAX);
      if (!f) break;
      ans += f;
    }
    return ans;
  }
};
