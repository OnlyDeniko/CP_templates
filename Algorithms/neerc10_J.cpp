// include geoma.cpp
int calc(array<ldd, 3> line, vec a){
  ldd ans = line[0] * a.x + line[1] * a.y + line[2];
  if (ans > EPS) return 1;
  if (ans < -EPS) return -1;
  return 0;
}

void solve(){
  int n;
  cin >> n;
  vector<vec> dots(n);
  forn(i, n) cin >> dots[i].x >> dots[i].y;
  int l = 1, r = (n - 1) / 2;
  int ans = -1;
  auto can = [&](int mid){
    vector<vec> hull = 
      {dots[0], dots[(mid + 1) % n]};
    For(i, 1, n){
      vec A = dots[i];
      vec B = dots[(i + mid + 1) % n];
      auto coefsAB = getNormalLine(A, B - A);
      int znak = calc(
        coefsAB, 
        dots[(i + 1) % n]);
      while(hull.size() > 1){
        vec C = hull[(int)hull.size() - 2];
        vec D = hull.back();
        auto coefsCD = getNormalLine(C, D - C);
        if (calc(coefsAB, C) == -znak){
          vec intersect = findNormalLinesIntersection(
            coefsAB[0], coefsAB[1], coefsAB[2],
            coefsCD[0], coefsCD[1], coefsCD[2]
          );
          hull.back() = intersect;
          hull.pb(B);
          break;
        } else {
          hull.pop_back();
        }
      }
    }
    return hull.size() > 1;
  };
  while(l <= r){
    int mid = (l + r) >> 1;
    if (can(mid)){
      l = mid + 1;
    } else {
      ans = mid;
      r = mid - 1;
    }
  }
  cout << ans << '\n';
}
