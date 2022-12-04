ll m,k;
ll n,q;


struct LCA{
  //new functionality
  int prev(int x,int p){
    ll dist=true_dist[x]-true_dist[p];
    dist--;
    if(dist==-1){
        return -1;
    }
    forn(i,LOG){
        if(dist&(1ll<<i)){
            x=bp[x][i];
        }
    }
    return x;
  }
};

vl sm, so, was, o, fl;
vector<vpl> g;
vector<vl> v;

void dfs1(int x,int p){
    was[x]=1;
    forr(y,v[x]){
        if(y==p){
            g[x].pb({y,1});
            continue;
        }
        if(was[y]==1){
            o[x]=y;
            so[p]++;
            so[x]--;
            sm[x]++;
            if (p != -1) fl[p]=1;
        }
        if(was[y]==0){
            g[x].pb({y,1});
            dfs1(y,x);
        }
    }
    was[x]=2;
}
void dfs2(int x,int p){
    if(p!=-1)
        sm[x]+=sm[p];
    if(p!=-1)
        so[x]+=so[p];
    was[x]=1;
    forr(y,v[x]) if (y != p && was[y] != 1){
        dfs2(y,x);
    }
}


void solve(){
    // input n, m
    // init vectors v, g, fl, sm, so, was, o
    // read graph
    dfs1(0,-1);
    LCA lcaa(g);
    fill(all(was),0);
    dfs2(0,-1);
    cin>>q;
    while(q--){
        ll a,b;
        cin>>a>>b>>k;
        a--;b--;
        if (a == b){
            if (k == 0) cout << 1 << '\n';
            else cout << 0 << '\n';
            continue;
        }
        ll dist=lcaa.distance(a,b);
        ll par=lcaa.lca(a,b);
        ll preva=lcaa.prev(a,par);
        ll prevb=lcaa.prev(b,par);
        ll cnt1=0, cnt2=0;
        cnt1+=so[a]-so[par];
        cnt1+=so[b]-so[par];
        cnt2+=sm[a]-sm[par];
        cnt2+=sm[b]-sm[par];
        if(a!=par&&so[preva]-so[par]==-1){
            cnt2--;
            cnt1+=2;
        }
        if(b!=par&&so[prevb]-so[par]==-1){
            cnt2--;
            cnt1+=2;
        }
        ll cnt=cnt1+cnt2;
        dist-=cnt2;
        ll e=k-dist;
        cout << CNK(cnt, e) << '\n';
    }

}
