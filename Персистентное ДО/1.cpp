struct node{
    node * left;
    node * right;
    int mi;
    node(){
        left = right = nullptr;
        mi = mod;
    }
    node(int kek){
        left = right = nullptr;
        mi = kek;
    }
    node(node* l, node *r){
        left = l;
        right = r;
        mi = mod;
    }
    node(node *l, node *r, int kek){
        left = l;
        right = r;
        mi = kek;
    }
};
typedef node* tree;
vector<node *> versions;
vi a;
tree build(int l, int r){
    if (l == r){
        return new node(a[l]);
    }
    int m = (l + r) >> 1;
    tree q = build(l, m);
    tree w = build(m + 1, r);
    return new node(q, w, min(q->mi, w->mi));
}

tree update(const tree &t, int l, int r, int pos, int val){
    if (l == r) return new node(val);
    tree q = t->left, w = t->right;
    int m = (l + r) >> 1;
    if (pos <= m){

        q = update(q, l, m, pos, val);
    }
    else {
        w = update(w, m + 1, r, pos, val);
    }
    return new node(q, w, min(q->mi, w->mi));
}

int get(tree t, int tl, int tr, int l, int r){
    if (l > r) return mod;
    if ((!t) || (l == tl && r == tr)){
        return t ? t->mi : mod;
    }
    int m = (tl + tr) >> 1;
    int ans =  min(get(t->left, tl, m, l, min(r, m)), get(t->right, m + 1, tr, max(l, m + 1), r));
    return ans;
}
