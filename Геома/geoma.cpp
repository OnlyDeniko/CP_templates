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
