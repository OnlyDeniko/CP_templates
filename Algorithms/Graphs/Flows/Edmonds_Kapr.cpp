struct EdmondsMaxFlow {
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

	int _bfs(int s, int t){
    queue<int> q;
    q.push(s);
    used.assign(n, 0);
    used[s] = INT_MAX;
    vector<int> pred(n, -1);
    while(q.size()){
      int v = q.front();
      q.pop();
      if (v == t) break;
      int f = used[v];
      for(auto & i : g[v]){
        int to = e[i].to;
        if (used[to] != 0 || _rem(i) == 0) continue;
        used[to] = min(f, _rem(i));
        q.push(to);
        pred[to] = i;
      }
    }
    if (used[t] == 0) return 0;
    int p = t;
    while(p != s){
      int i = pred[p];
      e[i].flow += used[t];
      e[i ^ 1].flow -= used[t];
      p = e[i].from;
    }
    return used[t];
  }

	EdmondsMaxFlow(int n) : n(n), g(n), s_(), t_() {}

	void addEdge(int x, int y, int c){
    g[x].pb(e.size());
    e.pb({x, y, c, 0});
    g[y].pb(e.size());
    e.pb({y, x, 0, 0});
  }

	int maxFlow(int s, int t){
    int ans = 0;
    while(1){
      int f = _bfs(s, t);
      if (!f) break;
      ans += f;
    }
    return ans;
  }
};
