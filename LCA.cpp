const int M = 1e5 + 200;
int k, n, t = 0;
int used[M], parent[M], in[M], out[M];
vector<pair<int, int>> g[M];
int d[M];
int p[25][M];
void dfs(int x, int par){
    used[x] = 1;
    parent[x] = par;
    in[x] = t++;
    for(auto &i : g[x]){
        if (i.X == par) continue;
        if (used[i.X]) continue;
        d[i.X] = d[x] + i.Y;
        dfs(i.X, x);
    }
    out[x] = t++;
}

int ch(int a, int b){
    return in[a] >= in[b] && out[a] <= out[b];
}

int lca(int x, int y){
    if (ch(x, y)) return y;
    if (ch(y, x)) return x;
    for(int i = k;i >= 0;i--){
        int x0 = p[i][x];
        if (!ch(y, x0)) x = x0;
    }
    return parent[x];
}

signed main(){
    cin >> n;
    for(int i = 0;i < n - 1;i++){
        int q, w, e;
        cin >> q >> w >> e;

        g[q].pb({w, e});
        g[w].pb({q, e});
    }
    int h = 1;
    k = 0;
    while(h <= n){
        k++;
        h <<= 1;
    }
    dfs(0, 0);
    for(int i = 0;i < n;i++){
        p[0][i] = parent[i];
    }
    for(int i = 1;i < k + 1;i++){
        for(int j = 0;j < n;j++){
            p[i][j] = p[i - 1][p[i - 1][j]];
        }
    }
    // just lca(a, b);
    return 0;
}