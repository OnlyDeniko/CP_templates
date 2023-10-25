struct Tree {
  struct Node {
    int parent;
    int len;
    std::map<char, int> nxt;
  };
  std::vector<Node> tr;
  int last_Added;
  int new_index;
  explicit Tree(int len) : tr(2 * len + 2), last_Added(0), new_index(1) {
    tr[0].parent = -1;
    tr[0].len = 0;
  }
  void Add(char c) {
    int ind = new_index++;
    tr[ind].len = tr[last_Added].len + 1;
    int par = last_Added;
    for (; par != -1 && !tr[par].nxt.count(c); par = tr[par].parent) {
      tr[par].nxt[c] = ind;
    }
    if (par == -1) {
      tr[ind].parent = 0;
    } else {
      int dot = tr[par].nxt[c];
      if (tr[dot].len == tr[par].len + 1) {  // nothing between them
        tr[ind].parent = dot;
      } else {
        int new_v = new_index++;
        tr[new_v].parent = tr[dot].parent;
        tr[new_v].nxt = tr[dot].nxt;
        tr[new_v].len = tr[par].len + 1;
        for (; par != -1 && tr[par].nxt[c] == dot; par = tr[par].parent) {
          tr[par].nxt[c] = new_v;
        }
        tr[ind].parent = new_v;
        tr[dot].parent = new_v;
      }
    }
    last_Added = ind;
  }
};
