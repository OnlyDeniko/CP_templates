using ldd = long double;
const ldd EPS = 1e-9;
struct vec{
  ldd x, y;

  vec(ldd xx = 0, ldd yy = 0){
    x = xx;
    y = yy;
  }
  ldd len2() const{
    return x * x + y * y;
  }
  ldd len() const{
    return hypotl(x, y);
  }
  bool operator == (const vec & a){
    return fabs(x - a.x) < EPS && fabs(y - a.y) < EPS;
  }
  ldd polar(){
    ldd ans = acos(x / len());
    if (y < 0) ans = 2 * PI - ans;
    return ans;
  }
  bool operator < (const vec & a){
    if (fabs(x - a.x) < EPS){
      return y < a.y;
    }
    return x < a.x;
  }

  void read(){
    cin >> x >> y;
  }
  void write(){
    cout << x << ' ' << y << '\n';
  }

  vec operator+(const vec& a) const {
    return {x + a.x, y + a.y};
  }

  vec operator-(const vec& a) const {
    return {x - a.x, y - a.y};
  }

  vec operator*(ldd a) const {
    return {a * x, a * y};
  }

  vec operator/(ldd a) const {
    return {x / a, y / a};
  }

  vec norm() const {
    if (len() == 0) return *this;
    return *this / len();
  }

  bool operator<(const vec & a) const {
    return a.x == x ? y < a.y : x < a.x;
  }

  vec rotate(ldd a){
    return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y);
  }
};

ldd vectmul(vec _1, vec _2){
  return _1.x * _2.y - _1.y * _2.x;
}

ldd scalmul(vec v1, vec v2){
  return v1.x * v2.x + v1.y * v2.y;
}

ldd dist(vec v1, vec v2){
  return (v1 - v2).len();
}

bool Parallel(vec v1, vec v2){
  return fabs(vectmul(v1, v2)) < EPS;
}

int sign(ldd x){
  if (fabs(x) < EPS) return 0;
  if (x > 0) return 1;
  return -1;
}

ldd AngleBetweenVec(vec p1, vec p2){
  ldd cosa = scalmul(p1, p2) / p1.len() / p2.len();
  return acosl(cosa);
}


array<ldd, 3> getNormalLine(vec x, vec dir) {
  return {dir.y, -dir.x, vectmul(dir, x)};
}

bool OnSegment(vec p, vec p1, vec p2){
  return vectmul(p - p1, p2 - p1) == 0 &&
          scalmul(p1 - p, p2 - p) <= 0;
}

bool OnRay(vec p, vec p1, vec p2){
  auto line = getNormalLine(p1, p2 - p1);
  return fabs(scalmul(vec(line[0], line[1]), p) + line[2]) < EPS &&
          scalmul(p2 - p1, p - p1) >= 0;
}

bool SegmentsIntersect(vec p1, vec p2,
                        vec p3, vec p4){
  if (Parallel(p2 - p1, p4 - p3)){
    return OnSegment(p1, p3, p4) ||
            OnSegment(p2, p3, p4) ||
            OnSegment(p3, p1, p2) ||
            OnSegment(p4, p1, p2);
  } else {
    return sign(vectmul(p2 - p1, p4 - p1)) *
          sign(vectmul(p2 - p1, p3 - p1)) <= 0 &&
          sign(vectmul(p4 - p3, p1 - p3)) *
          sign(vectmul(p4 - p3, p2 - p3)) <= 0;
  }
}

// guaranteed lines not parallel
vec findSegmentsIntersection(vec p1, vec p2,
                             vec p3, vec p4){ 
  //p1+t*(p2-p1)
  //[p-p3,p4-p3] = 0 <- system
  //[p1+t*(p2-p1)-p3,p4-p3] = 0
  //t*[p2-p1,p4-p3]+[p1-p3,p4-p3] = 0
  //t = [p3-p1,p4-p3]/[p2-p1,p4-p3] <- solve
  ldd t = vectmul(p3 - p1, p4 - p3) / 
          vectmul(p2 - p1, p4 - p3);
  return p1 + (p2 - p1) * t;
}

bool LinesIntersect(vec p1, vec p2, vec p3, vec p4){
  vec napr1 = p2 - p1;
  vec napr2 = p4 - p3;
  auto line1 = getNormalLine(p1, napr1);
  auto line2 = getNormalLine(p3, napr2);
  return
    !(abs(vectmul(vec(line1[0], line2[0]), vec(line1[1], line2[1]))) < EPS);
}

bool EqualLines(vec p1, vec p2, vec p3, vec p4){
  vec napr1 = p2 - p1;
  vec napr2 = p4 - p3;
  auto line1 = getNormalLine(p1, napr1);
  auto line2 = getNormalLine(p3, napr2);
  return 
    abs(vectmul(vec(line1[0], line2[0]), vec(line1[1], line2[1]))) < EPS &&
    abs(vectmul(vec(line1[0], line2[0]), vec(line1[2], line2[2]))) < EPS &&
    abs(vectmul(vec(line1[1], line2[1]), vec(line1[2], line2[2]))) < EPS;
}

vec findNormalLinesIntersection(ldd a1, ldd b1, ldd c1, ldd a2, ldd b2, ldd c2){
  return 
    {vectmul(vec(b1, b2), vec(c1, c2)) /
      vectmul(vec(a1, a2), vec(b1, b2)),
      vectmul(vec(c1, c2), vec(a1, a2)) /
      vectmul(vec(a1, a2), vec(b1, b2))};
}

vec findLinesIntersection(vec p1, vec p2,
                          vec p3, vec p4){
  vec napr1 = p2 - p1;
  vec napr2 = p4 - p3;
  napr1 = napr1.norm();
  napr2 = napr2.norm();
  auto line1 = getNormalLine(p1, napr1);
  auto line2 = getNormalLine(p3, napr2);
  return findNormalLinesIntersection(line1[0], line1[1], line1[2], line2[0], line2[1], line2[2]);
}

ldd TriangleArea(vec p1, vec p2, vec p3){
  return fabs(vectmul(p2 - p1, p3 - p1));
}

bool PointInTriangle(vec p, vec p1, vec p2, vec p3){
  return TriangleArea(p1, p2, p3) >= TriangleArea(p, p2, p3) +
          TriangleArea(p1, p, p3) + TriangleArea(p1, p2, p);
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


ldd MinDistToRay(vec x, vec y, vec z){
  if (scalmul(z - y, x - y) >= 0){
    return fabs(vectmul(z - y, x - y)) / (z - y).len();
  }
  return (x - y).len();
}

ldd MinDistToSegment(vec p, vec p1, vec p2){
  if (sign(scalmul(p2 - p1, p - p1)) <= 0 || sign(scalmul(p1 - p2, p - p2)) <= 0){
    return min(dist(p2, p), dist(p1, p));
  }
  return fabs(vectmul(p2 - p1, p - p1)) / (p2 - p1).len();
}

bool cw (vec a, vec b, vec c) {
	return a.x * (b.y - c.y) +
          b.x * (c.y - a.y) +
          c.x * (a.y - b.y) < 0;
}

bool ccw (vec a, vec b, vec c) {
	return a.x * (b.y - c.y) +
          b.x * (c.y - a.y) +
          c.x * (a.y - b.y) > 0;
}

vector<vec> convex_hull (vector<vec> a) {
	if (a.size() == 1) return a;
	sort (a.begin(), a.end());
	vec p1 = a[0], p2 = a.back();
	vector<vec> up, down;
	up.push_back (p1);
	down.push_back (p1);
	for (size_t i=1; i<a.size(); ++i) {
		if (i==a.size()-1 || cw (p1, a[i], p2)) {
			while (up.size()>=2 &&
        !cw(up[up.size()-2], up.back(), a[i]))
          up.pop_back();
			up.push_back(a[i]);
		}
		if (i==a.size()-1 || ccw(p1, a[i], p2)) {
			while (down.size()>=2 &&
        !ccw(down[down.size()-2], down.back(), a[i]))
          down.pop_back();
			down.push_back (a[i]);
		}
	}
	vector<vec> ans;
	for(int i = 0; i < (int)up.size(); ++i)
    ans.push_back (up[i]);
	for(int i = (int)down.size() - 2;i > 0; --i)
    ans.push_back (down[i]);
  return ans;
}