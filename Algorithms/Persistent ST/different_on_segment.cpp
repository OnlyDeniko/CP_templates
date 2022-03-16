struct node{
    node * left;
    node * right;
    int mi;
    node(){
        left = right = nullptr;
        mi = 0;
    }
    node(int kek){
        left = right = nullptr;
        mi = kek;
    }
    node(node* l, node *r){
        left = l;
        right = r;
        mi = 0;
    }
    node(node *l, node *r, int kek){
        left = l;
        right = r;
        mi = kek;
    }
};
typedef node* tree;
vector<tree> versions;
vi a;

tree update(const tree &t, int l, int r, int pos, int val){
    if (l == r) return new node(val);
    tree q = t->left, w = t->right;
    int m = (l + r) >> 1;
    if (pos <= m){
        if (!q) q = new node();
        q = update(q, l, m, pos, val);
    }
    else {
        if (!w) w = new node();
        w = update(w, m + 1, r, pos, val);
    }
    return new node(q, w, (q ? q->mi : 0) + (w ? w->mi : 0));
}

int get(tree t, int tl, int tr, int l, int r){
    if (l > r) return 0;
    if ((!t) || (l == tl && r == tr)){
        return t ? t->mi : 0;
    }
    int m = (tl + tr) >> 1;
    int ans =  get(t->left, tl, m, l, min(r, m)) + get(t->right, m + 1, tr, max(l, m + 1), r);
    return ans;
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    #ifdef KULA
                freopen("input.txt", "r", stdin);
        //        freopen("output.txt", "w", stdout);
    #else
        //        freopen("input.txt", "r", stdin);
        //        freopen("output.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    a.resize(n);
    cin >> a;
    tree t = new node();
    mii mapik;
    versions.pb(t);
    forn(i, n){
        if (mapik.find(a[i]) == mapik.end()){
            tree kek;
            kek = update(versions.back(), 0, n - 1, i, 1);

            mapik[a[i]] = i;
            versions.pb(kek);
        }
        else {
            int pos = mapik[a[i]];
            tree kek;
            kek = update(versions.back(), 0, n - 1, pos, 0);
            kek = update(kek, 0, n - 1, i, 1);
            mapik[a[i]] = i;
            versions.pb(kek);
        }
    }
    while(q--){
        int l, r;
        cin >> l >> r;
        cout << get(versions[r + 1], 0, n - 1, l, r) << '\n';
    }
    return 0;
}
