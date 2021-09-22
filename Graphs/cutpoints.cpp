using vi = vector<int>;
using vvi = vector<vi>;
using si = set<int>;

void dfs_cutpoint(int x, int par, vvi & g, vi & used, vi & tin, vi & fup, int & timer, si & ans){
    used[x] = 1;
    tin[x] = fup[x] = timer++;
    int child = 0;
    for(auto &i : g[x]) if (i != par){
        if (used[i]){
            fup[x] = min(fup[x], tin[i]);
        } else {
            dfs_cutpoint(i, x, g, used, tin, fup, timer, ans);
            fup[x] = min(fup[x], fup[i]);
            if (fup[i] >= tin[x] && par != -1){
                ans.insert(x);
            }
            child++;
        }
    }
    if (par == -1 && child > 1) ans.insert(x);
}

si find_cutpoint(vvi & g){
    int n = g.size();
    int timer = 1;
    vi tin(n), fup(n), used(n, 0);
    si ans;
    for(int i = 0;i < n;i++) if (!used[i]) dfs_cutpoint(i, -1, g, used, tin, fup, timer, ans);
    return ans;
}
