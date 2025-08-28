// contains all points p such that: cross(b - a, p - a) >= 0
template<class P>
struct HP {
    P a, b;
    HP() {}
    HP(P a, P b) : a(a), b(b) {}
    HP(const HP& rhs) : a(rhs.a), b(rhs.b) {}
    int operator < (const HP& rhs) const {
        P p = b - a;
        P q = rhs.b - rhs.a;
        int fp = (p.y < 0 || (p.y == 0 && p.x < 0));
        int fq = (q.y < 0 || (q.y == 0 && q.x < 0));
        if (fp != fq) return fp == 0;
        if (p.cross(q)) return p.cross(q) > 0;
        return p.cross(rhs.b - a) < 0;
    }
    P line_line_intersection(P a, P b, P c, P d) {
        b = b - a; d = c - d; c = c - a;
        return a + b * c.cross(d) / b.cross(d);
    }
    P intersection(const HP &v) {
        return line_line_intersection(a, b, v.a, v.b);
    }
};

template<class P>
int check(HP<P> a, HP<P> b, HP<P> c) {
    return (a.b - a.a).cross(b.intersection(c) - a.a) > -eps; //-eps to include polygons of zero area (straight lines, points)
}
// consider half-plane of counter-clockwise side of each line
// if lines are not bounded add infinity rectangle
// returns a convex polygon, a point can occur multiple times though
// complexity: O(n log(n))
template<class P>
vector<P> half_plane_intersection(vector<HP<P>> h) {
    sort(h.begin(), h.end());
    vector<HP<P>> tmp;
    for (int i = 0; i < h.size(); i++) {
        if (!i || (h[i].b - h[i].a).cross(h[i - 1].b - h[i - 1].a)) {
            tmp.push_back(h[i]);
        }
    }
    h = tmp;
    vector<HP<P>> q(h.size() + 10);
    int qh = 0, qe = 0;
    for (int i = 0; i < h.size(); i++) {
        while (qe - qh > 1 && !check(h[i], q[qe - 2], q[qe - 1])) qe--;
        while (qe - qh > 1 && !check(h[i], q[qh], q[qh + 1])) qh++;
        q[qe++] = h[i];
    }
    while (qe - qh > 2 && !check(q[qh], q[qe - 2], q[qe - 1])) qe--;
    while (qe - qh > 2 && !check(q[qe - 1], q[qh], q[qh + 1])) qh++;
    vector<HP<P>> res; 
    for (int i = qh; i < qe; i++) res.push_back(q[i]);
    vector<P> hull;
    if (res.size() > 2) {
        for (int i = 0; i < res.size(); i++) {
             hull.push_back(res[i].intersection(res[(i + 1) % ((int)res.size())]));
        }
    }
    return hull;
}
