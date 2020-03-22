#include<bits/stdc++.h>
//#include<ext/pb_ds/assoc_container.hpp>
//#pragma GCC optimize "-O3"
//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("mmx,avx,fma")
//#pragma GCC optimize ("unroll-loops")

//using namespace __gnu_pbds;
using namespace std;

template <class T>
istream& operator >> (istream& in, vector<T>& v){ for(auto& e : v){ in >> e;} return in;}
template <class T>
istream& operator >> (istream& in, vector<pair<T, T> >& v){ for(auto& e : v){ in >> e.first >> e.second;} return in;}

//#define int long long
//#define int short int
#define pb push_back
#define mk make_pair
#define X first
#define Y second
#define cont continue
#define ret return
#define For(i, a, b) for (int i = a; i < b;i++)
#define forn(i, a) for (int i = 0;i < a;i++)
#define ford(i, a, b) for (int i = b - 1;i >= a;i--)
#define fordn(i, a) for (int i = a - 1;i >= 0;i--)
#define forr(x, arr) for(auto &x: arr)
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define REE(s_) {cout << s_ << '\n';exit(0);}
//#define endl '\n'
#define makeunique(x) sort(all(x)), (x).resize(unique(all(x)) - (x).begin())
#ifdef debug
template <char d = ' ', class T>
    ostream& operator << (ostream& out, vector<T>& v){ out << "[";for(int i = 0;i < v.size();i++){out << v[i];if (i != v.size() - 1) out << ", ";} out << "]\n"; return out; }
    template <char d = ' ', class T>
    ostream& operator << (ostream& out, vector<pair<T, T> >& v){ out << "[";for(int i = 0;i < v.size();i++){ out << ' ' << v[i].first << ", " << v[i].second; if (i != v.size() - 1) out << '\n'; } out << "]"; return out;}
    template <char d = ' ', class T>
    ostream& operator << (ostream& out, set<T>& v){out << "["; for(auto i = v.begin();i != v.end();i++){ out << *i; if (*i != *v.rbegin()) out << ", ";} out << "]"; return out;}
#else
template <char d = ' ', class T>
ostream& operator << (ostream& out, vector<T>& v){ for(auto& e : v){ out << e << d;} return out;}
template <char d = ' ', class T>
ostream& operator << (ostream& out, vector<pair<T, T> >& v){ for(auto& e : v){ out << e.first << ' ' << e.second << '\n';} return out;}
template <char d = ' ', class T>
ostream& operator << (ostream& out, set<T>& v){ for(auto& e : v){ out << e << d;} return out;}
#endif
typedef double dd;
typedef long double ldd;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef map<int, int> mii;
typedef unordered_map<string, int> msi;
typedef set<int> si;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }
template <typename T> string toString(T val){ostringstream oss; oss << val; return oss.str();}
template<typename T> T sqr(T a) {return a * a;}
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
//const int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
//const int dy[8] = {1, -1, 1, 0, -1, 1, 0, -1};
//const int dx[8] = {2, 2, 1, 1, -1, -1, -2, -2};
//const int dy[8] = {1, -1, 2, -2, 2, -2, 1, -1};

const int mod = (int)1e9 + 7;
//const int MAX_MEM = 1e8;
//int mpos = 0;
//char mem[MAX_MEM];
//inline void * operator new ( size_t n ) {
//    assert((mpos += n) <= MAX_MEM);
//    return (void *)(mem + mpos - n);
//}
//inline void operator delete ( void * ) noexcept { }

//int powq(int a, int n, int mod) {
//    int res = 1;
//    while (n){
//        if (n & 1LL) {
//            res *= a;
//            res %= mod;
//            --n;
//        }
//        else {
//            a *= a;
//            a %= mod;
//            n >>= 1LL;
//        }
//
//    }
//    res %= mod;
//    return res;
//}

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
//    cout << l << ' ' <<r << '\n';
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
//    cout << tl << ' ' << tr << ' ' << l << ' ' << r << '\n';
//    cout << ans << '\n';
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
    tree t;
    t = build(0, n - 1);

    versions.pb(t);
    int was = 0;

    while(q--){
        char x;
        cin >> x;
        if (x == 'c'){
            int v, i, k;
            cin >> v >> i >> k;
            v ^= was;
            i ^= was;
            k ^= was;
            versions.pb(update(versions[v], 0, n - 1, i - 1, k));
        }
        else {
            int v, l, r;
            cin >> v >> l >> r;
            v ^= was;
            l ^= was;
            r ^= was;
//            cout << "START " << v <<  ' ' << l << ' ' << r << '\n';
            was = get(versions[v], 0, n -1, l -1, r - 1);
            cout << was << '\n';
        }
    }
    return 0;
}
