// please do not forget to initialise s, t, n
// g.resize(::n)
struct edge{
  int from, to, f, cap;
};

vector<edge> e;
vector<vector<int>> g;
vector<int> used, d, nums;
int n, s, t; //s - source, t - drain, n - number of vertices

void add_edge(int x, int y, int c){
  g[x].push_back(e.size());
  e.push_back({x, y, 0, c});
  g[y].push_back(e.size());
  e.push_back({y, x, 0, 0});
}

int rem(int i){
  return e[i].cap - e[i].f;
}

int bfs(){
  queue<int> q;
  q.push(s);
  d.assign(n, -1);
  d[s] = 0;
  while(q.size()){
    int x = q.front();
    q.pop();
    if (x == t) break;
    for(auto &i : g[x]){
      int to = e[i].to;
      if (d[to] != -1 || rem(i) == 0) continue;
      d[to] = d[x] + 1;
      q.push(to);
    }
  }
  return d[t] != -1;
}

int dfs(int x, int mx){
  if (x == t) return mx;
  for(;nums[x] < g[x].size();nums[x]++){
    int i = g[x][nums[x]];
    int to = e[i].to;
    if (rem(i) == 0 || d[to] != d[x] + 1) continue;
    int f = dfs(to, min(mx, rem(i)));
    if (f){
      e[i].f += f;
      e[i ^ 1].f -= f;
      return f;
    }
  }
  return 0;
}

int max_flow(){
  int ans = 0;
  while(bfs()){
    nums.assign(n, 0);
    while(int f = dfs(s, INT_MAX)){
      ans += f;
    }
  }
  return ans;
}
