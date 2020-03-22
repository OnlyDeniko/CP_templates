#include<bits/stdc++.h>
//#include<ext/pb_ds/assoc_container.hpp>
//#pragma comment(linker, "/STACK:5000000000")
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

#define int long long
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
#define makeunique(x) sort(all(x)), (x).resize(unique(all(x)) - (x).begin())
#ifdef debug
    #define deb(a) cout << "\n[" << #a << "] == " << a << endl;
    template <char d = ' ', class T>
    ostream& operator << (ostream& out, const vector<T>& v){ out << "[";for(int i = 0;i < v.size();i++){out << v[i];if (i != v.size() - 1) out << " ";} out << "]"; return out; }
    template <char d = ' ', class T>
    ostream& operator << (ostream& out, const pair<T, T>& v){ out << "[";out << v.first << ", " << v.second;out << "]"; return out;}
    template <char d = ' ', class T>
    ostream& operator << (ostream& out, const set<T>& v){out << "["; for(auto i = v.begin();i != v.end();i++){ out << *i; if (*i != *v.rbegin()) out << ", ";} out << "]"; return out;}
    template <char d = ' ', class T>
    ostream& operator << (ostream& out, const multiset<T>& v){out << "["; for(auto i = v.begin();i != v.end();i++){ out << *i; if (*i != *v.rbegin()) out << ", ";} out << "]"; return out;}
#else
    #define deb(a)
    template <char d = ' ', class T>
    ostream& operator << (ostream& out, const vector<T>& v){ for(auto& e : v){ out << e << d;} return out;}
    template <char d = ' ', class T>
    ostream& operator << (ostream& out, const pair<T, T> & v){ out << v.X << d << v.Y; return out;}
    template <char d = ' ', class T>
    ostream& operator << (ostream& out, const set<T>& v){ for(auto& e : v){ out << e << d;} return out;}
#endif
typedef long long ll;
typedef long double ldd;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef map<int, int> mii;
typedef map<string, int> msi;
typedef set<int> si;
typedef set<pii> spii;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }
template <typename T> string toString(T val){ostringstream oss; oss << val; return oss.str();}
template<typename T> T sqr(T a) {return a * a;}
mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
//const int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
//const int dy[8] = {1, -1, 1, 0, -1, 1, 0, -1};
//const int dx[8] = {-2, -2, 1, 1, -1, -1, 2, 2};
//const int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
const ldd eps = 1e-13;
const int mod = 1e9 + 7;;
const ldd pi = acos(-1.);
//const int MAX_MEM = 1e8;
//int mpos = 0;
//char mem[MAX_MEM];
//inline void * operator new ( size_t n ) {
//    assert((mpos += n) <= MAX_MEM);
//    return (void *)(mem + mpos - n);
//}
//inline void operator delete ( void * ) noexcept { }
void add(int &x, int y, int mod){
    x = (x + y) % mod;
    if (x < 0) x += mod;
}
int mulq(int a, int b, int mod){
    int res = 0;
    while(b){
        if (b & 1){
            add(res, a, mod);
        }
        b >>= 1;
        add(a, a, mod);
    }
    return res;
}

//int powq(int a, int b, int mod) {
//    int res = 1;
//    a %= mod;
//    while(b){
//        if (b & 1){
//            res = mulq(res, a, mod);
//        }
//        b >>= 1;
//        a = mulq(a, a, mod);
//    }
//    return res;
//}

//jillzay, jillzay, paci, paci, gilzi, gilzi

struct pos{
    int x, y, r;
    bool operator < (const pos & a) const{
        if (x == a.x) {
            return y < a.y;
        }
        return x < a.x;
    }
};
const int N = 1e6;
const int LOG = 25;
int sparse[N][LOG];
vi step_2;

void prepare_sparse_table(vi & a){
    forn(i, a.size()) sparse[i][0] = a[i];
    For(ind, 1, step_2.size()){
        forn(i, a.size()){
            if (i + step_2[ind] > a.size()) cont;
            int r = i + step_2[ind - 1];
            sparse[i][ind] = min(sparse[i][ind - 1], sparse[r][ind - 1]);
        }
    }
}

int query(int l, int r){
    int gg = r - l + 1;
    int step = (int)log2(gg);
//    cout << l + 1 << ' ' << r + 1 << ' ' << step << '\n';
    return min(sparse[l][step],sparse[r - (1 << step) + 1][step]);
}

void solve(){
    int gg = 1;
    int n, k;
    cin >> n >> k;
    vi a(n);
    cin >> a;
    while(gg <= n){
        step_2.pb(gg);
        gg <<= 1;
    }
    prepare_sparse_table(a);
    forn(i, n){
        if (i + k - 1 >= n) break;
        cout << query(i, i + k - 1) << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    #ifdef KULA
            freopen("input.txt", "r", stdin);
//            freopen("output.txt", "w", stdout);
    #else
            freopen("input.txt", "r", stdin);
            freopen("output.txt", "w", stdout);
    #endif

    int t;
    t = 1;
//    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
