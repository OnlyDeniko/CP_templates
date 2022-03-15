#include<bits/stdc++.h>
 
using namespace std;
 
#define int long long
#define pb push_back
#define X first
#define Y second
#define fr first
#define sc second
#define forn(i, a) for (int i = 0;i < a;i++)
#define forr(x, arr) for(auto &x: arr)
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define makeunique(x) sort(all(x)), (x).resize(unique(all(x)) - (x).begin())

void debug_out(){ cout << '\n';}

template<typename head, typename... tail>
void debug_out(head H, tail... T){ cout << " " << H; debug_out(T...);}

#ifdef HOME
    #define deb(...) cout << "[" << #__VA_ARGS__ << "] :", debug_out(__VA_ARGS__)
#else
    #define deb(...)
#endif
typedef long long ll;
typedef long double ldd;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }
mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

const ldd EPS = 1e-12;
const int MOD = 1e9 + 7;
const ldd PI = acos(-1.);

void solve(){
  
}

signed main() {
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  int t = 1;
  // cin >> t;
  forn(i, t) solve();
  return 0;
}
