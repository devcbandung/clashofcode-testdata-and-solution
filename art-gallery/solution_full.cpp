#include <bits/stdc++.h>
using namespace std;

/* Start of geometry.h */

double _acos(double x) {
	double ret = acos(x);
	if (ret == ret) return ret;
	if (x < 0) return acos(-1.0);
	return acos(1.0);
}
#define acos _acos
#define sqr(x) ((x)*(x))

const double PI = acos(-1);
const double EPS = 1e-7;
const double INF = 1e300;

bool cmpf(const double a, const double b) {
	return fabs(a - b) < EPS;
}

struct point{
	double x, y;
	point() { x = y = 0; }
	point(double x, double y) : x(x), y(y) {}
	point(pair<double,double> p) : x(p.first), y(p.second) {}
	point(pair<int,int> p) : x(p.first), y(p.second) {}
	point(pair<long long,long long> p) : x(p.first), y(p.second) {}
};
struct segment {
	point p1, p2;
	segment() {p1 = p2 = point(0,0);}
	segment(point p1, point p2) : p1(p1), p2(p2) {}
};

/** basic operators and functions of point and segment **/
/* complexity: constant */
point operator-(const point &p1, const point &p2) {
	return point(p1.x - p2.x, p1.y - p2.y);
}
point operator+(const point &p1, const point &p2) {
	return point(p1.x + p2.x, p1.y + p2.y);
}
point operator*(const point &p, const double &s) {
	return point(p.x * s, p.y * s);
}
point operator/(const point &p, const double &s) {
	return p * (1./s);
}
bool operator<(const point &p1, const point &p2) {
	if (p1.x != p2.x) return p1.x < p2.x;
	return p1.y < p2.y;
}
bool operator==(const point &p1, const point &p2) {
	return fabs(p1.x - p2.x) < EPS && fabs(p1.y - p2.y) < EPS;
}
double cross(const point &p1, const point &p2) {
	/* returns z-component of cross product of two points (vectors) */
	return p1.x * p2.y - p1.y * p2.x;
}
double dot(const point &p1, const point &p2) {
	/* returns dot product of two points (vectors) */
	return p1.x * p2.x + p1.y * p2.y;
}
double dist(const point &p){
	/* returns distance of p from the origin */
	return sqrt(sqr(p.x) + sqr(p.y));
}
double dist(const point &p1, const point &p2) {
	/* returns distance between two points */
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}
double length(const segment &s) {
	/* returns length of a segment */
	return sqrt(sqr(s.p1.x - s.p2.x) + sqr(s.p1.y - s.p2.y));
}
bool isRightTurn(const point &p1, const point &p2, const point &p3){
	return cross(p2 - p1, p3 - p2) < EPS;
	/* straight returns true */
}
bool isStraight(const point &p1, const point &p2, const point &p3){
	double c = cross(p2 - p1, p3 - p2);
	return cmpf(c, 0);
}
bool isOnSameSide(const point &p1, const point &p2, const segment &s){
	double z1 = cross(s.p2 - s.p1, p1 - s.p1);
	double z2 = cross(s.p2 - s.p1, p2 - s.p1);
	return (z1 + EPS < 0 && z2 + EPS < 0) || (0 < z1 - EPS && 0 < z2 - EPS) || fabs(z1) < EPS || fabs(z2) < EPS;
	/* on segment returns true */
}
bool isOnLine(const point &p, const segment &l){
	return fabs((l.p1.y - p.y) * (l.p2.x - p.x) - (l.p2.y - p.y) * (l.p1.x - p.x)) < EPS;
}
bool isOnSegment(const point &p, const segment &s){
	double c = cross(p - s.p1, s.p2 - p);
	if (fabs(c) > EPS) return false;
	double d = dot(s.p2 - s.p1, p - s.p1);
	return d > -EPS && d < sqr(s.p2.x - s.p1.x) + sqr(s.p2.y - s.p1.y) + EPS;
}
bool isIntersecting(const segment &s1, const segment &s2){
	return !(isOnSameSide(s1.p1,s1.p2,s2) || isOnSameSide(s2.p1,s2.p2,s1)) || isOnSegment(s1.p1,s2) || isOnSegment(s1.p2,s2) || isOnSegment(s2.p1,s1) || isOnSegment(s2.p2,s1);
}
bool isParallel(const segment &s1, const segment &s2){
	return fabs((s1.p1.y-s1.p2.y)*(s2.p1.x-s2.p2.x)-(s2.p1.y-s2.p2.y)*(s1.p1.x-s1.p2.x)) < EPS;
}
point intersection(const segment &s1, const segment &s2){
	/* assumes !isParallel(s1,s2) */
	double x1 = s1.p1.x - s1.p2.x;
	double x2 = s2.p1.x - s2.p2.x;
	double y1 = s1.p1.y - s1.p2.y;
	double y2 = s2.p1.y - s2.p2.y;
	double cross1 = cross(s1.p1, s1.p2);
	double cross2 = cross(s2.p1, s2.p2);
	return point ((cross1 * x2 - cross2 * x1) / (x1 * y2 - x2 * y1), (cross1 * y2 - cross2 * y1) / (x1 * y2 - x2 * y1));
}

/** introducing polygon **/
typedef vector<point> polygon;

/** Area of Polygon **/
/* complexity : O(N) */
double polygonArea(polygon p){
	double area = p.front().y * p.back().x - p.front().x * p.back().y;
	for (int i = 0; i + 1 < (int)p.size(); ++i){
		area += p[i].x * p[i+1].y;
		area -= p[i].y * p[i+1].x;
	}
	return fabs(area) / 2.;
}

/* End of geometry.h */

const point origin(0, 0);
const segment xAxis(origin, point(1e9, 0));

// atan2 but returns positive result
double patan2(double y, double x) {
  double ret = atan2(y, x);
  while (ret < 0) ret += 2 * PI;
  return ret;
}

// patan2 with point args
double patan2(const point &p) {
  return patan2(p.y, p.x);
}

// patan2 but returns 2*PI when p is on positive x-axis
double patan2e(const point &p) {
  double ret = patan2(p);
  if (cmpf(ret, 0)) {
    return 2*PI;
  }
  return ret;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);

  polygon G;
  for (int i = 0; i < n; ++i) {
    point p;
    scanf("%lf%lf", &p.x, &p.y);
    G.push_back(p);
  }

  vector<segment> L;
  for (int i = 0; i < n; ++i) {
    L.push_back(segment(G[i], G[(i+1)%n]));
  }
  for (int i = 0; i < m; ++i) {
    segment s;
    scanf("%lf%lf%lf%lf", &s.p1.x, &s.p1.y, &s.p2.x, &s.p2.y);
    L.push_back(s);
  }

  vector<segment> S;
  for (segment s : L) {
    if (isOnLine(origin, s)) continue;
    // cut through x-axis, so we can sort by angle
    if (isIntersecting(s, xAxis)) {
      point p = intersection(s, xAxis);
      segment s1(p, s.p1);
      segment s2(p, s.p2);
      // do not add segments if it has length zero
      if (length(s1) > EPS) S.push_back(s1);
      if (length(s2) > EPS) S.push_back(s2);
    } else {
      S.push_back(s);
    }
  }

  for (segment &s : S) {
    if (isRightTurn(origin, s.p1, s.p2)) {
      swap(s.p1, s.p2);
    }
  }

  sort(S.begin(), S.end(), [&](const segment &a, const segment &b) {
    return patan2(a.p1.y, a.p1.x) < patan2(b.p1.y, b.p1.x);
  });

  vector<segment> done;
  vector<segment> T;
  for (segment s : S) {
    double a1 = patan2(s.p1);
    double a2 = patan2e(s.p2);
    segment r1(origin, s.p1);
    segment r2(origin, s.p2);

    // step 1: mark segments past current angle as done
    while (!T.empty() && patan2e(T.back().p2) < a1) {
      done.push_back(T.back());
      T.pop_back();
    }

    if (T.empty()) {
      T.push_back(s);
      continue;
    }

    // step 2: cut current segment to a1
    if (cmpf(patan2(T.back().p1), a1)) {
      // do nothing
    } else if (cmpf(patan2e(T.back().p2), a1)) {
      done.push_back(T.back());
      T.pop_back();
    } else {
      point pt = intersection(r1, T.back());
      assert(isOnSegment(pt, T.back()));
      if (!(T.back().p1 == pt)) {
        done.push_back(segment(T.back().p1, pt));
      }
      T.back().p1 = pt;
    }

    if (T.empty()) {
      T.push_back(s);
      continue;
    }

    assert(cmpf(a1, patan2(T.back().p1)));

    // step 3: advance index while t blocks s
    int k = T.size()-1;
    while (k >= 0) {
      double dt = dist(origin, T[k].p1);
      point ps = intersection(segment(origin, T[k].p1), s);
      double ds = dist(origin, ps);
      if (ds < dt) break;
      k--;
    }

    // special case: k < 0
    if (k < 0) {
      point ps = intersection(segment(origin, T[0].p2), s);
      // invisible
      if (!isOnSegment(ps, s)) continue;

      segment Ts(ps, s.p2);
      if (!(ps == s.p2)) {
        T.insert(T.begin(), Ts);
      }
      continue;
    }

    // special case 2: s is already invisible
    if (a2 <= patan2(T[k].p1)) continue;

    // step 4: find the last index where s ends
    int rk = k;
    while (rk >= 0) {
      point ps = intersection(segment(origin, T[rk].p2), s);
      if (!isOnSegment(ps, s)) break;
      rk--;
    }

    // special case rk < 0: all segments in [0,k] now blocked
    if (rk < 0) {
      point ps = intersection(segment(origin, T[k].p1), s);

      assert(isOnSegment(ps, s));
      T.erase(T.begin(), T.begin()+k);
      T[0] = segment(ps, s.p2);
      if (ps == s.p2) {
        T.erase(T.begin());
      }
      continue;
    }

    // case rk == k: actually split in two
    if (rk == k) {
      segment Ts(intersection(segment(origin, T[k].p1), s), s.p2);
      // cut rk
      T[rk].p1 = intersection(segment(origin, s.p2), T[rk]);
      // insert at k
      T.insert(T.begin()+k+1, Ts);
      if (T[k+1].p1 == T[k+1].p2) {
        T.erase(T.begin()+k+1);
      }
    } else {
      // cut rk
      T[rk].p1 = intersection(segment(origin, s.p2), T[rk]);
      // erase [rk+1, k); reserve k for s
      T[k] = segment(intersection(segment(origin, T[k].p1), s), s.p2);
      T.erase(T.begin()+rk+1, T.begin()+k);
    }
  }

  for (segment t : T) {
    done.push_back(t);
  }

  double ans = 0;
  for (segment s : done) {
    double delta = patan2e(s.p2) - patan2(s.p1);
    ans += polygonArea({origin, s.p1, s.p2});
  }

  printf("%.17lf\n", ans);
}