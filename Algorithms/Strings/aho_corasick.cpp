struct AhoCorasick {
	static const int L = 26;
	static const char C = 'a';

	struct Node {
		map<char, int> to; // use array to speed up
		int link;
		bool leaf;
    vi indices; // save indices of initial strings
		int go[L];
		Node() : to(), link(), leaf() {
			fill(go, go + L, 0);
		}
	};

	vector<Node> t;

	AhoCorasick() : t(1) {}

	void add(const string& s, int index) {
		int v = 0;
		for (char c : s) {
			if (!t[v].to.count(c)) {
				t[v].to[c] = t.size();
				t.emplace_back();
			}
			v = t[v].to[c];
		}
		t[v].leaf = true;
    t[v].indices.pb(index);
	}

	void build() {
		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int v = q.front();
			for (const pair<char, int>& p : t[v].to) {
				q.push(p.second);
				if (v > 0) {
					int u = t[v].link;
					while (u > 0 && !t[u].to.count(p.first))
						u = t[u].link;
					if (t[u].to.count(p.first))
						u = t[u].to[p.first];
					t[p.second].link = u;
					// propagation
          vi & cur = t[u].indices;
          vi & nxt = t[p.second].indices;
          nxt.insert(nxt.end(), all(cur));
				}
				t[v].go[p.first - C] = p.second;
			}
			for (int i = 0; i < L; i++)
				if (t[v].go[i] == 0)
					t[v].go[i] = t[t[v].link].go[i];
		}
	}
};