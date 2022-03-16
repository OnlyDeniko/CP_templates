#define makeunique(x)
  sort(all(x)), (x).resize(unique(all(x)) - (x).begin())

void debug_out(){ cout << endl;}
 
template<typename head, typename... tail>
void debug_out(head H, tail... T){
  cout << " " << H;
  debug_out(T...);
}
 
#ifdef HOME
  #define deb(...)
    cout << "[" << #__VA_ARGS__ << "] :",
    debug_out(__VA_ARGS__)
  template <char d = ' ', class T>
  ostream& operator << (ostream& out,
                        const vector<T>& v){ 
    out << "[";
    for(auto & i : v)  out << i << d;
    out << "]";
    return out; 
  }
#else
  #define deb(...)
  template <char d = ' ', class T>
  ostream& operator << (ostream& out, const vector<T>& v){ 
    for(auto& e : v) out << e << d;
    return out;
  }
#endif

template<class T>
bool uin(T &a, T b) { 
  return a > b ? (a = b, true) : false; 
}
template<class T> 
bool uax(T &a, T b) { 
  return a < b ? (a = b, true) : false; 
}

mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());