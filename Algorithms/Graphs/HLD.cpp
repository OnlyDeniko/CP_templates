const int inf = 1e9;
struct Node {
	Node *l = nullptr, *r = nullptr;
	int lo, hi, mset = inf, madd = 0, val = 0;
	Node(int lo,int hi): lo(lo), hi(hi) {}
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo) / 2;
			l = new Node(v, lo, mid);
			r = new Node(v, mid, hi);
			val = min(l->val, r->val);
		}
		else val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return inf;
		if (L <= lo && hi <= R) return val;
		push();
		return min(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push();
			l->set(L, R, x);
			r->set(L, R, x);
			val = min(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push();
			l->add(L, R, x);
			r->add(L, R, x);
			val = min(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid);
			r = new Node(mid, hi);
		}
		if (mset != inf){
			l->set(lo,hi,mset);
			r->set(lo,hi,mset);
			mset = inf;
		}
		else if (madd){
			l->add(lo,hi,madd);
			r->add(lo,hi,madd);
			madd = 0;
		}
	}
};

/// HLD
struct HLD {
	int N, tim = 0;
	vector<vector<int>> adj;
	vi par, siz, depth, rt, pos;
	Node *tree = nullptr;
	HLD(vector<vi> adj_)
		: N(adj_.size()), adj(adj_), par(N, -1), siz(N, 1), depth(N),
		  rt(N),pos(N),tree(new Node(0, N)){
        dfsSz(0); dfsHld(0);
      }
    
	void dfsSz(int v) { // oriented graph from the root
		for (int& u : adj[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
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
			if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
			op(pos[rt[v]], pos[v] + 1);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u], pos[v] + 1);		
	}

	void modifyPath(int u, int v, int val) {
		process(u, v, [&](int l, int r) { tree->add(l, r, val); });
	}

	int queryPath(int u, int v) {
		int res = inf;
		process(u, v, [&](int l, int r) {
      res = min(res, tree->query(l, r));
		});
		return res;
	}
  
	// modifySubtree is similar
	int querySubtree(int v) { 
		return tree->query(pos[v], pos[v] + siz[v]);
	}
};