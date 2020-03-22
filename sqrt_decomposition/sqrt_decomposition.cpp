#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("avx")

using namespace __gnu_pbds;
using namespace std;

#define FUNC(name) template <ostream& out = cout, class... T> void name(T&&...){ }
FUNC(prints) FUNC(printe) FUNC(printw) FUNC(printew) FUNC(printb) FUNC(printd) FUNC(printde);

template <class T>
istream& operator >> (istream& in, vector<T>& v){ for(auto& e : v){ in >> e; } return in; }
template <char d = ' ', class T>
ostream& operator << (ostream& out, vector<T>& v){ for(auto& e : v){ out << e << d; } return out; }
template <char d = ' ', class T>
ostream& operator << (ostream& out, set<T>& v){ for(auto& e : v){ out << e << d; } return out; }

#define pb push_back
#define mk make_pair
#define X first
#define Y second
#define cont continue
#define ret return
#define For(i, a, b) for (int i = (int)a; i < (int)b;i++)
#define forn(i, a) for (int i = 0;i < (int)a;i++)
#define ford(i, a, b) for (int i = (int)b - 1;i >= (int)a;i--)
#define fordn(i, a) for (int i = (int)a - 1;i >= 0;i--)
#define forr(x, arr) for(auto &x: arr)
#define all(x) x.begin(),x.end()
#define REE(s_) {cout << s_ << '\n';return 0;}
#define endl '\n'
#define makeunique(x) sort(all(x)), (x).resize(unique(all(a)) - (x).begin())

typedef long long ll;
typedef unsigned long long ull;
typedef double dd;
typedef long double ldd;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;
typedef map<int, int> mii;
typedef map<string, int> msi;
typedef set<int> si;
typedef set<ll> sll;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_tree;

template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }

//#define int long long

struct decomp{
    int gr = 256;
    int n;
    vi a, val, add, minn;
    vll sum;

    decomp(int n)
        :n(n)
        , a(n)
        , val(1 + (n-1) / gr, INT_MAX)
        , add(1 + (n- 1) / gr, 0)
        , minn(1 + (n- 1) / gr, INT_MAX)
        , sum(1 + (n- 1) / gr, 0)
    {
        For(i, 0, n){
            cin >> a[i];
            uin(minn[i / gr], a[i]);
            sum[i / gr] += a[i];
        }
    }
    int grst(int g){

        return g * gr;
    }
    int get(int pos){
        int g = pos / gr;
        if (val[g] != INT_MAX){
            return val[g];
        }
        else return a[pos] + add[g];
    }
    int afterG(int g){
        return min(n, (g + 1) * gr);
    }
    void norm(int g){
        int aft = afterG(g);
        if (val[g] != INT_MAX){
            minn[g] = INT_MAX;
            sum[g] = 0;
            For(i, grst(g), aft){
                a[i] = val[g];
            }
            val[g] = INT_MAX;
            add[g] = 0;
            minn[g] = INT_MAX;
            sum[g] = 0;

        }
        else if (add[g] != 0){
            For(i, grst(g), aft){
                a[i] += add[g];

            }
            add[g] = 0;
        }

    }
    void calc(int g){
        int aft = afterG(g);
        minn[g] = INT_MAX;
        sum[g] = 0;
        For(i, grst(g), aft){
            uin(minn[g], a[i]);
            sum[g] += a[i];
        }
    }
    void update(int l, int r, int x){
        int lg = l / gr;
        int rg = r / gr;
        if (lg == rg){
            norm(lg);
            For(i, l, r + 1){
                a[i] = x;
            }
            calc(lg);
        }
        else {
            norm(lg);
            int afterL = afterG(lg);
            For(i, l, afterL){
                a[i] = x;
            }
            calc(lg);
            For(g, lg + 1, rg){
                val[g] = x;
            }
            norm(rg);
            For(i, grst(rg), r + 1){
                a[i] = x;
            }
            calc(rg);
        }
    }
    void ad(int l, int r, int x){
        int lg = l / gr;
        int rg = r / gr;
        if (lg == rg){
            norm(lg);
            For(i, l, r + 1){
                a[i] += x;
            }
            calc(lg);
        }
        else {
            norm(lg);
            int afterL = afterG(lg);
            For(i, l, afterL){
                a[i] += x;
            }
            calc(lg);
            For(g, lg + 1, rg){
                if (val[g] == INT_MAX){
                    add[g] += x;
                    minn[g] += x;
                    sum[g] += 1LL * gr * x;
                }
                else val[g] += x;
            }
            norm(rg);
            For(i, grst(rg), r + 1){
                a[i] += x;
            }
            calc(rg);
        }
    }
    ll rsq(int l, int r){
        ll summ = 0;
        int lg = l / gr;
        int rg = r / gr;
        if (lg == rg){
            norm(lg);
            For(i, l, r + 1){
                summ += a[i];
            }
            calc(lg);
        }
        else {
            norm(lg);
            int afterL = afterG(lg);
            For(i, l, afterL){
                summ += a[i];
            }
            calc(lg);
            For(g, lg + 1, rg){
                if (val[g] == INT_MAX){
                    summ += sum[g];

                }
                else summ += 1LL * gr * val[g];
            }
            norm(rg);
            For(i, grst(rg), r + 1){
                summ += a[i];
            }
            calc(rg);
        }
        return summ;
    }
    int rmq(int l, int r){
        int mi = INT_MAX;
        int lg = l / gr;
        int rg = r / gr;
        if (lg == rg){
            norm(lg);
            For(i, l, r + 1){
                uin(mi, a[i]);
            }
            calc(lg);
        }
        else {
            norm(lg);
            int afterL = afterG(lg);
            For(i, l, afterL){
                uin(mi, a[i]);
            }
            calc(lg);
            For(g, lg + 1, rg){
                if (val[g] == INT_MAX){
                    uin(mi, minn[g]);

                }
                else uin(mi, val[g]);
            }
            norm(rg);
            For(i, grst(rg), r + 1){
                uin(mi, a[i]);
            }
            calc(rg);
        }
        return mi;
    }
};

signed main(){
    //ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    #ifdef KULA
        //freopen("input.txt", "r", stdin);
        //freopen("output.txt", "w", stdout);
    #else
//        freopen("green.in", "r", stdin);
//        freopen("green.out", "w", stdout);
    #endif
    int n;
    cin >> n;
    decomp sd(n);
    int q;
    cin >> q;
    while(q--){
        string s;
        cin >> s;
        if (s == "get"){
            int pos;
            cin >> pos;
            pos--;
            cout << sd.get(pos) << '\n';
        }
        else if (s == "update"){
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            r--;
            sd.update(l, r, x);
        }
        else if (s == "add"){
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            r--;
            sd.ad(l, r, x);
        }
        else if (s == "rsq"){
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << sd.rsq(l, r) << '\n';
        }
        else if (s == "rmq"){
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << sd.rmq(l, r) << '\n';
        }
    }
    return 0;
}
