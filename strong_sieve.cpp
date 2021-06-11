#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#pragma optimize("jillzay, jillzay, paci, paci, gilzi, gilzi")
#pragma optimize("JARU SOSISONI")
 
using namespace __gnu_pbds;
using namespace std;
 
template <class T>
istream& operator >> (istream& in, vector<T>& v){ for(auto& e : v){ in >> e;} return in;}
template <class T>
istream& operator >> (istream& in, pair<T, T> &v){ in >> v.first >> v.second; return in;}
 
#define int long long
//#define int short int
#define pb push_back
#define mkp make_pair
#define X first
#define Y second
#define cont continue
#define For(i, a, b) for (int i = a; i < b;i++)
#define forn(i, a) for (int i = 0;i < a;i++)
#define ford(i, a, b) for (int i = b - 1;i >= a;i--)
#define fordn(i, a) for (int i = a - 1;i >= 0;i--)
#define forr(x, arr) for(auto &x: arr)
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define makeunique(x) sort(all(x)), (x).resize(unique(all(x)) - (x).begin())
void debug_out(){ cout << '\n';}

template<typename head, typename... tail>
void debug_out(head H, tail... T){ cout << " " << H; debug_out(T...);}

#ifdef KULA
    #define deb(...) cout << "[" << #__VA_ARGS__ << "] :", debug_out(__VA_ARGS__)
    template <char d = ' ', class T>
    ostream& operator << (ostream& out, const vector<T>& v){ out << "[";for(int i = 0;i < v.size();i++){out << v[i];if (i != v.size() - 1) out << " ";} out << "]"; return out; }
    template <char d = ' ', class T>
    ostream& operator << (ostream& out, const pair<T, T>& v){ out << "[";out << v.first << ", " << v.second;out << "]"; return out;}
    template <char d = ' ', class T>
    ostream& operator << (ostream& out, const set<T>& v){out << "["; for(auto i = v.begin();i != v.end();i++){ out << *i; if (*i != *v.rbegin()) out << ", ";} out << "]"; return out;}
    template <char d = ' ', class T>
    ostream& operator << (ostream& out, const multiset<T>& v){out << "["; for(auto i = v.begin();i != v.end();i++){ out << *i; if (*i != *v.rbegin()) out << ", ";} out << "]"; return out;}
#else
    #define deb(...)
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
template<typename T> T sqr(T a) {return a * a;}
mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
//const int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
//const int dy[8] = {1, -1, 1, 0, -1, 1, 0, -1};
//const int dx[8] = {-2, -2, 1, 1, -1, -1, 2, 2};
//const int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
const ldd EPS = 1e-12;
const int MOD = 1e9 + 7;
const ldd PI = acos(-1.);
/*const int MAX_MEM = 1e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
    assert((mpos += n) <= MAX_MEM);
  return (void *)(mem + mpos - n);
}
inline void operator delete ( void * ) noexcept { }*/

void solve(){
	int n;
	cin >> n;
	vi p, md(n + 1);
	iota(all(md), 0);
	
	For(i, 2, n + 1){
		if (md[i] == i) p.pb(i);
		for(int j = 0;j < p.size() && p[j] <= md[i] && 1ll * i * p[j] <= n;j++) md[i * p[j]] = p[j];
	}					
	vector<char> mu(n + 1 );
	mu[1] = 1;
	vi phi(n + 1);
	phi[1] = 1;
	vector<int32_t> a1(n + 1);
	a1[1] = 1;
	vi p1a1(n + 1);
	p1a1[1] = 1;
	vi si0(n + 1);
	si0[1] = 1;
	vi si1(n + 1);
	si1[1] = 1;
	For(i, 2, n + 1){
		int j = i / md[i];
		
		if (md[i] == md[j]) {
			mu[i] = 0;
			phi[i] = md[i] * phi[j];
			a1[i] = a1[j] + 1;
			p1a1[i] = md[i] * p1a1[j];
			si0[i] = si0[j] / (a1[j] + 1)  * (a1[i] + 1);			
			int was = (p1a1[j] * md[j] - 1) / (md[j] - 1);
			int now = (p1a1[i] * md[i] - 1) / (md[i] - 1);
			si1[i] = si1[j] / was * now;
		}	else {
			mu[i] = -mu[j];
			phi[i] = (md[i] - 1) * phi[j];
			a1[i] = 1;
			p1a1[i] = md[i];
			si0[i] = si0[j] * 2;
			si1[i] = si1[j] * (p1a1[i] * md[i] - 1) / (md[i] - 1);
		}
	}
		
	md[1] = 0;

	cout << (long long)accumulate(md.begin() + 1, md.end(), 0ll) << ' ';
	cout << (long long)accumulate(si0.begin() + 1, si0.end(), 0ll) << ' ';
	cout << (long long)accumulate(si1.begin() + 1, si1.end(), 0ll) << ' ';
	cout << (long long)accumulate(phi.begin() + 1, phi.end(), 0ll) << ' ';
	cout << (long long)accumulate(mu.begin() + 1, mu.end(), 0ll) << ' ';
}

signed main() {
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  #ifdef KULA
//            freopen("input.txt", "r", stdin);
//            freopen("output.txt", "w", stdout);
  #else
//            freopen("input.txt", "r", stdin);
//            freopen("output.txt", "w", stdout);
  #endif
  int t = 1;
//  cin >> t;
  forn(i, t) solve();
  return 0;
}
