struct SegTree {
	struct Node {
		int val;
	};
	int N;
	vector<Node> t;
	SegTree(int n): N(n), t(4 * N) {}
	SegTree(vi& a): N(a.size()),
		t(4 * N) {
		build(1, 0, N - 1, a);
	}
	void build(int v, int l, int r, vi & a){}
	void push(int v, int l, int r){}
	int queryImpl(int v, int tl, int tr,
		int l, int r){}
	int query(int l, int r){
		return queryImpl(1, 0, N - 1, l, r);
	}
	void set(int l, int r, int val){}
};

struct HLD {
	int N, tim = 0;
	vector<vi> adj;
	vi par, siz, depth, rt, pos;
	SegTree tree;
	HLD(vector<vi> adj_)
		: N(adj_.size()),
		adj(adj_), par(N, -1),
		siz(N, 1), depth(N),
		rt(N),pos(N),tree(N){
        dfsSz(0); dfsHld(0);
      }
    
	void dfsSz(int v) { // oriented graph from the root
		for (int& u : adj[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) 
				swap(u, adj[v][0]);
		}
	}

	void dfsHld(int v) {
		pos[v] = tim++;
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}

	template <class B>
	void process(int u, int v, B op) {
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (depth[rt[u]] > depth[rt[v]]) 
				swap(u, v);
			op(pos[rt[v]], pos[v]);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u], pos[v]);		
	}

	void modifyPath(int u, int v, int val) {
		process(u, v, [&](int l, int r) {
			tree.add(l, r, val);
		});
	}

	int queryPath(int u, int v) {
		int res = LLONG_MAX;
		process(u, v, [&](int l, int r) {
      res = min(res, tree.query(l, r));
		});
		return res;
	}
  
	// modifySubtree is similar
	int querySubtree(int v) { 
		return tree.query(pos[v], pos[v] + siz[v]);
	}
};