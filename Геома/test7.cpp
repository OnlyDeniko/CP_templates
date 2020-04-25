#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#pragma optimize("jillzay, jillzay, paci, paci, gilzi, gilzi")
#pragma optimize("JARU SOSISONI")
//#pragma comment(linker, "/STACK:5000000000")
//#pragma GCC optimize "-O3"
//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("mmx,avx,fma")
//#pragma GCC optimize ("unroll-loops")

using namespace __gnu_pbds;
using namespace std;

template <class T>
istream& operator >> (istream& in, vector<T>& v){ for(auto& e : v){ in >> e;} return in;}
template <class T>
istream& operator >> (istream& in, vector<pair<T, T> >& v){ for(auto& e : v){ in >> e.first >> e.second;} return in;}

#define int long long
//#define int short int
#define pb push_back
#define mkp make_pair
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
typedef tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
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
const ldd eps = 1e-12;
const int mod = 998244353;
const ldd pi = acos(-1.);
//const int MAX_MEM = 1e8;
//int mpos = 0;
//char mem[MAX_MEM];
//inline void * operator new ( size_t n ) {
//    assert((mpos += n) <= MAX_MEM);
//    return (void *)(mem + mpos - n);
//}
//inline void operator delete ( void * ) noexcept { }
//void add(int &x, int y, int mod){
//    x %= mod;
//    y %= mod;
//    x = (x + y) % mod;
//    if (x < 0) x += mod;
//}
//
//void sub(int &x, int y, int mod){
//    x = (x - y) % mod;
//    if (x < 0) x += mod;
//}
//
//int mulq(int a, int b, int mod){
//    int res = 0;
//    a %= mod;
//    while(b){
//        if (b & 1){
//            add(res, a, mod);
//        }
//        b >>= 1;
//        add(a, a, mod);
//    }
//    return res;
//}
//
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

struct vec{
    ldd x, y;

    ldd len2() const{
        return x * x + y * y;
    }
    ldd len() const{
        return hypotl(x, y);
    }
    bool operator == (const vec & a){
        return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
    }
};

vec operator+ (vec v1, vec v2){
    return {v1.x + v2.x, v1.y + v2.y};
}

vec operator- (vec v1, vec v2){
    return {v1.x - v2.x, v1.y - v2.y};
}

vec operator*(vec v1, ldd x){
    return {v1.x * x, v1.y * x};
}

vec operator/(vec v1, ldd x){
    return {v1.x / x, v1.y / x};
}

ldd vectmul(vec _1, vec _2){
    return _1.x * _2.y - _1.y * _2.x;
}

ldd scalmul(vec v1, vec v2){
    return v1.x * v2.x + v1.y * v2.y;
}

ldd dist(vec v1, vec v2){
    return (v1 - v2).len();
}

vec norm(vec v){
    return v / v.len();
}

bool Parallel(vec v1, vec v2){
    return fabs(vectmul(v1, v2)) < eps;
}

int sign(ldd x){
    if (fabs(x) < eps) return 0;
    if (x > 0) return 1;
    return -1;
}

bool OnSegment(vec p, vec p1, vec p2){
    return vectmul(p - p1, p2 - p1) == 0 && scalmul(p1 - p, p2 - p) <= 0;
}

bool SegmentIntersect(vec p1, vec p2, vec p3, vec p4){
    if (Parallel(p2 - p1, p4 - p3)){
        return OnSegment(p1, p3, p4) || OnSegment(p2, p3, p4) ||
            OnSegment(p3, p1, p2) || OnSegment(p4, p1, p2);
    } else {
        return sign(vectmul(p2 - p1, p4 - p1)) * sign(vectmul(p2 - p1, p3 - p1)) <= 0 &&
            sign(vectmul(p4 - p3, p1 - p3)) * sign(vectmul(p4 - p3, p2 - p3)) <= 0;
    }
}

vec findLinesIntersection(vec p1, vec p2, vec p3, vec p4){ // guaranteed lines not parallel
    //p1 + t * (p2 - p1)
    //[p - p3, p4 - p3] = 0 <- system
    //[p1 + t *(p2 - p1) - p3, p4 - p3] = 0
    //t * [p2 - p1, p4 - p3] + [p1 - p3, p4 - p3] = 0
    //t = [p3 - p1, p4 - p3] / [p2 - p1, p4 - p3] <- solve
    ldd t = vectmul(p3 - p1, p4 - p3) / vectmul(p2 - p1, p4 - p3);
    return p1 + (p2 - p1) * t;
}

vector<vec> findLineAndCircleIntersection(vec p1, vec p2, vec c, ldd r){
    // circle - {p | (p - c, p - c} = r * r}
    //{p1 + (p2 - p1) * t - c, p1 + (p2 - p1) * t - c) = r*r
    //A * t * t + B * t + C = 0, A = (p2 - p1) * (p2 - p1), B = 2 * (p1 - c, p2 - p1)
    //should be written
}

ldd AngleBetweenVec(vec p1, vec p2){
    ldd cosa = scalmul(p1, p2) / p1.len() / p2.len();
    return acosl(cosa);
}

ldd calc(vec p1, vec p2, vec p3){
    return fabs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
}


bool PointInTriangle(vec p, vec p1, vec p2, vec p3){
    if (calc(p1, p2, p3) >= calc(p, p2, p3) + calc(p1, p, p3) + calc(p1, p2, p)){
        return 1;
    }
    return 0;
}

bool PointInConvexPolygon(vec p, vector<vec> & pol){
    //if (!PointInAngle(p, pol[0], pol[1], pol.back())) return false;
    int l = 1, r = pol.size() - 1;
    while(r - l > 1){
        int mid = (l + r) >> 1;
        if (vectmul(pol[mid] - pol[0], p - pol[0]) >= 0) l = mid;
        else r = mid;
    }
    return PointInTriangle(p, pol[0], pol[1], pol[r]);
}




void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<vec> a(n), b(m);
    forn(i, n){
        cin >> a[i].x >> a[i].y;
    }
    int cnt = 0;
    forn(i, m){
        cin >> b[i].x >> b[i].y;
        cnt += PointInConvexPolygon(b[i], a);
    }
    if (cnt >= k) cout << "YES\n";
    else cout << "NO\n";
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    #ifdef KULA
            freopen("input.txt", "r", stdin);
//            freopen("output.txt", "w", stdout);
    #else
//            freopen("input.txt", "r", stdin);
//            freopen("output.txt", "w", stdout);
    #endif
    int t = 1;
//    cin >> t;
    forn(i, t) solve();
    return 0;
}
