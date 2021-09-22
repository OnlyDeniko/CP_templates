using vi = vector<int>;
using pii = pair<int, int>;
using vpi = vector<pii>;
using vvi = vector<vi>;
using si = set<int>;

void dfs_strong_components(int x, vvi & g, vi &used, vi & order, int comp){
    used[x] = comp;
    for(auto &i: g[x]){
        if (!used[i]) dfs_strong_components(i, g, used, order, comp);
    }
    order.pb(x);
}

vi strong_components(vvi & g, vvi & gr){
    int n = g.size();
    vi order;
    vi used(n, 0);
    for(int i = 0;i < n;i++) if (!used[i]) dfs_strong_components(i, g, used, order, 1);
    reverse(order.begin(), order.end());
    used.assign(n, 0);
    int comp = 1;
    for(int i = 0;i < n;i++){
        if (!used[order[i]]) dfs_strong_components(order[i], gr, used, order, comp++);
    }
    return used;
}

void dfs_bridges(int x, int par, vvi & g, vi & used, vi & tin, vi & fup, int & timer, set<pii> & ans){
    used[x] = 1;
    tin[x] = fup[x] = timer++;
    for(auto &i : g[x]){
        if (i == par) continue;
        if (used[i]) fup[x] = min(fup[x], tin[i]);
        else {
            dfs_bridges(i, x, g, used, tin, fup, timer, ans);
            fup[x] = min(fup[x], fup[i]);
            if (fup[i] > tin[x]){
                ans.insert({x, i});
                ans.insert({i, x});
            }
        }
    }
}

vi find_bridges(vvi & g, vpi & edge_order){
    int n = g.size();
    vi tin(n), fup(n), used(n, 0);
    int timer = 0;
    set<pii> ans;
    for(int i = 0;i < n;i++) if (!used[i]) dfs_bridges(i, -1, g, used, tin, fup, timer, ans);
    vi res;
    map<pii, int> mp;
    for(auto &i : edge_order){
        mp[i]++;
        mp[{i.Y, i.X}]++;
    }
    for(int i = 0;i < edge_order.size();i++){
        if (mp[edge_order[i]] >= 2) continue;
        if (ans.find(edge_order[i]) != ans.end()) res.pb(i);
    }
    return res;
}

void dfs_bridges_with_strong_components(int x, vvi & g, vi & used, vvi & new_g, vvi & new_gr){
    used[x] = 1;
    for(auto &i: g[x]){
        if (used[i]) {
            new_gr[x].pb(i);
        }
        else {
            new_g[x].pb(i);
            dfs_bridges_with_strong_components(i, g, used, new_g, new_gr);
        }
    }
}

vi find_bridges_with_strong_components(vvi & g, vpi & edge_order){
    int n = g.size();
    vvi gg(n), gr(n);
    vi used(n, 0);
    for(int i = 0;i < n;i++) if (!used[i]) dfs_bridges_with_strong_components(i, g, used, gg, gr);
    auto strong_comp = strong_components(gg, gr);
    vi ans;
    int ind = 0;
    for(auto &i : edge_order){
        if (strong_comp[i.X] != strong_comp[i.Y]){
            ans.pb(ind);
        }
        ind++;
    }
    return ans;
}
