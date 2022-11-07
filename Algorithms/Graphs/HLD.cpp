struct SegTree {
	struct Node {
		int val, setFlag, addFlag;
	};
	int N;
	vector<Node> t;
	static const int NEUTRAL = LLONG_MAX;
	SegTree(int n): N(n), t(4 * N) {}
	SegTree(vi& a): N(a.size()),
		t(4 * N, {0, NEUTRAL, 0}) {
		build(1, 0, N - 1, a);
	}
	int merge(int a, int b){
		return min(a, b);
	}
	void build(int v, int l, int r, vi & a){
		if (l == r){
			t[v] = {a[l], NEUTRAL, 0};
			return;
		}
		int m = (l + r) >> 1;
		build(v << 1, l, m, a);
		build(v << 1 | 1, m + 1, r, a);
		t[v].val = 
			merge(t[v << 1].val, t[v << 1 | 1].val);
	}
	void push(int v, int l, int r){
		if (t[v].setFlag != NEUTRAL){
			t[v << 1].val = 
				t[v << 1 | 1].val = t[v].setFlag;
			t[v << 1].setFlag = 
				t[v << 1 | 1].setFlag = t[v].setFlag;
			t[v].setFlag = NEUTRAL;
		} else if (t[v].addFlag != 0){
			t[v << 1].val += t[v].addFlag;
			t[v << 1 | 1].val += t[v].addFlag;
			t[v << 1].addFlag += t[v].addFlag;
			t[v << 1 | 1].addFlag += t[v].addFlag;
			t[v].addFlag = 0;
		}
	}
	int queryImpl(int v, int tl, int tr, int l, int r){
		if (l > r) return NEUTRAL;
		if (tl == l && r == tr){
			return t[v].val;
		}
		push(v, tl, tr);
		int m = (tl + tr) >> 1;
		return merge(queryImpl(v << 1, tl, m, l, min(r, m)),
			queryImpl(v << 1 | 1, m + 1, tr, max(l, m + 1), r));
	}
	void setImpl(int v, int tl, int tr, int l, int r, int val){
		if (l > r) return;
		if (tl == l && tr == r){
			t[v] = {val, val, 0};
			return;
		}
		push(v, tl, tr);
		int m = (tl + tr) >> 1;
		setImpl(v << 1, tl, m, l, min(r, m), val);
		setImpl(v << 1 | 1, m + 1, tr, max(l, m + 1), r, val);
		t[v].val = 
			merge(t[v << 1].val, t[v << 1 | 1].val);
	}
	void addImpl(int v, int tl, int tr, int l, int r, int val){
		if (l > r) return;
		if (tl == l && tr == r){
			if (t[v].setFlag != NEUTRAL) {
				t[v].setFlag += val;
			} else t[v].addFlag += val;
			t[v].val += val;
			return;
		}
		push(v, tl, tr);
		int m = (tl + tr) >> 1;
		addImpl(v << 1, tl, m, l, min(r, m), val);
		addImpl(v << 1 | 1, m + 1, tr, max(l, m + 1), r, val);
		t[v].val = 
			merge(t[v << 1].val, t[v << 1 | 1].val);
	}
	int query(int l, int r){
		return queryImpl(1, 0, N - 1, l, r);
	}
	void set(int l, int r, int val){
		setImpl(1, 0, N - 1, l, r, val);
	}
	void add(int l, int r, int val){
		addImpl(1, 0, N - 1, l, r, val);
	}
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
			op(pos[rt[v]], pos[v] + 1);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u], pos[v] + 1);		
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