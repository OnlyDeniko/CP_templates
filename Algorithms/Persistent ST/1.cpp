int op(int a, int b){...}
int neutral = ...;
struct node{
  node * left;
  node * right;
  int val;
  node(){
    left = right = nullptr;
    val = neutral;
  }
  node(int _val){
    left = right = nullptr;
    val = _val;
  }
  node(node* l, node *r){
    left = l;
    right = r;
    val = neutral;
  }
  node(node *l, node *r, int _val){
    left = l;
    right = r;
    val = _val;
  }
};
typedef node* tree;
vector<node *> versions;
vi a;

tree build(int l, int r){
  if (l == r) return new node(a[l]);
  int m = (l + r) >> 1;
  tree left = build(l, m);
  tree right = build(m + 1, r);
  return new node(left, right, op(left->val, right->val));
}

tree update(const tree &t, int l, int r, int pos, int val){
  if (l == r) return new node(val);
  tree left = t->left, right = t->right;
  int m = (l + r) >> 1;
  if (pos <= m){
    left = (left == nullptr ? new node() :
            update(left, l, m, pos, val));
  }
  else {
    right = (right == nullptr ? new node() :
            update(right, m + 1, r, pos, val));
  }
  return new node(left, right,
    op((q ? q->mi : neutral), (w ? w->mi : neutral)));
}

int get(tree t, int tl, int tr, int l, int r){
  if (t == nullptr || l > r) return neutral;
  if (l == tl && r == tr){
    return t->val;
  }
  int m = (tl + tr) >> 1;
  return op(get(t->left, tl, m, l, min(r, m)) +
    get(t->right, m + 1, tr, max(l, m + 1), r));
}