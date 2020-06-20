#include <bits/stdc++.h>
using namespace std;

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
double getAngle(const point &p1, const point &p2) {
	/* returns angle formed by two vectors. WARNING: undirected angle */
	return fabs(acos(dot(p1,p2) / dist(p1,point(0,0)) / dist(p2,point(0,0))));
}
double getAngle(const point &p1, const point &center, const point &p2) {
	/* returns angle formed by three points. WARNING: undirected angle */
	return getAngle(p1 - center, p2 - center);
}
double distToSegment(const point &p, const segment &s) {
	/* returns distance of a point to a segment */
	if (getAngle(s.p2, s.p1, p) > PI/2 + EPS || getAngle(s.p1, s.p2, p) > PI/2 + EPS) return min(dist(p,s.p1), dist(p,s.p2));
	return fabs(cross(s.p1 - p, s.p2 - p)) / dist(s.p1, s.p2);
}
double distToLine(const point &p, const segment &s){
	/* returns distance of a point to a line (its orthogonal projection) */
	return fabs(cross(s.p1 - p, s.p2 - p)) / dist(s.p1, s.p2);
}
point rotate(const point &p, const double &alpha) {
	/* rotates a point with respect to the origin. alpha in radians */
	return point(p.x * cos(alpha) - p.y * sin(alpha), p.x * sin(alpha) + p.y * cos(alpha));
}
point rotate(const point &p, const point &center, const double &alpha){
	/* rotates a point with respect to point center. alpha in radians */
	return center + rotate(p - center, alpha);
}
point rescale(const point &p, const double s) {
	return point(p.x * s, p.y * s);
}
point dilate(const point &p, const double Factor){
	return rescale(p, Factor);
}
point dilate(const point &p, const point &center, double factor){
	return dilate(p- center, factor) + center;
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
	// printf("\tisOnSegment: cross: %.17lf\n", c);
	if (fabs(c) > EPS) return false;
	double d = dot(s.p2 - s.p1, p - s.p1);
	// printf("\tisOnSegment: dot = %.2lf\n", d);
	return d > -EPS && d < sqr(s.p2.x - s.p1.x) + sqr(s.p2.y - s.p1.y) + EPS;
	// return fabs(dist(p, s.p1) + dist(p, s.p2) - dist(s.p1, s.p2)) < EPS;
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
point projection(const point &p, const segment &s){
	/* projects p onto line s */
	return rescale(s.p2 - s.p1, dot(p - s.p1, s.p2 - s.p1) / sqr(length(s))) + s.p1;
}
point reflection(const point &p, const point &center){
	/* reflect p with respect to center */
	return center * 2. - p;
}
point reflection(const point &p, const segment &s){
	/* reflect p with respect to line s */
	return reflection(p, projection(p, s));
}
segment lineBisector(const point &p1, const point &p2){
	point center = (p1 + p2) / 2.;
	return segment(rotate(p1,center,PI/2.), rotate(p2,center,PI/2.));
}
segment lineBisector(const segment &s){
	return lineBisector(s.p1, s.p2);
}

/** introducing circle **/
struct circle {
	point center;
	double r;
	circle() { center = point(0, 0); r = 0; }
	circle(point p, double r) : center(p), r(r) {}
};
double area(const circle &c){
	return PI * c.r * c.r;
}
double perimeter(const circle &c){
	return 2. * PI * c.r;
}
bool isOnCircle(const point &p, const circle &c){
	return dist(p,c.center) == c.r;
}
bool isInsideCircle(const point &p, const circle &c){
	return dist(p,c.center) + EPS < c.r;
}
bool isOutsideCircle(const point &p, const circle &c){
	return dist(p,c.center) > c.r + EPS;
}
bool isTangent(const segment &l, const circle &c){
	return distToLine(c.center,l) == c.r;
}
vector<point> intersectionLineCircle(const segment &l, const circle &c){
	vector<point> res;
	double dx = l.p2.x - l.p1.x;
	double dy = l.p2.y - l.p1.y;
	double dr = length(l);
	double d  = cross(l.p1 - c.center,l.p2 - c.center);
	if (sqr(c.r) * sqr(dr) - sqr(d) + EPS < 0) return res;
	double det = sqrt(fabs(sqr(c.r) * sqr(dr) - sqr(d)));
	double sdx = dy < 0 ? -dx : dx;
	double sdy = fabs(dy);
	res.push_back(c.center + point((d*dy + sdx * det)/sqr(dr), (-d*dx + sdy * det)/sqr(dr)));
	if (det > EPS) res.push_back(c.center + point((d*dy - sdx * det)/sqr(dr), (-d*dx - sdy * det)/sqr(dr)));
	return res;
}
vector<point> intersectionSegmentCircle(const segment &s, const circle &c){
	vector<point> res, _res = intersectionLineCircle(s,c);
	for (vector<point>::iterator it = _res.begin(); it != _res.end(); ++it){
		if (isOnSegment(*it,s)) res.push_back(*it);
	}
	return res;
}
vector<point> intersectionCircleCircle(const circle &c1, const circle &c2){
	vector<point> res;
	return res;
}

/** introducing polygon **/
typedef vector<point> polygon;
/** triangle properties **/
typedef vector<point> triangle;
point centroid(triangle t){
	if (t.size() != 3) assert(false);
	return (t[0] + t[1] + t[2]) / 3.;
}
point orthocenter(triangle t){
	if (t.size() != 3) assert(false);
	return intersection(segment(t[0], projection(t[0], segment(t[1], t[2]))), segment(t[1], projection(t[1], segment(t[0], t[2]))));
}
point circumcenter(triangle t){
	if (t.size() != 3) assert(false);
	return intersection(lineBisector(t[0],t[1]),lineBisector(t[1],t[2]));
}
bool isPointInsideTriangle(point p, const triangle &t) {
	if (t.size() != 3) assert(false);
	point g = centroid(t);
	for (int i = 0; i < 3; ++i) {
		if (!isOnSameSide(p, g, segment(t[i], t[(i+1)%3]))) return false;
	}
	return true;
}

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

/** Check orientation of points: clockwise or counterclockwise **/
/* complexity : O(N) */
bool isClockwise(polygon p){
	double area = p.front().y * p.back().x - p.front().x * p.back().y;
	for (int i = 0; i + 1 < (int)p.size(); ++i){
		area += p[i].x * p[i+1].y;
		area -= p[i].y * p[i+1].x;
	}
	return area < 0;
}

/** Check position of a point with respect to a polygon  **/
/* complexity : O(N) */
bool isPointInsidePolygon(point p, const polygon &poly){
	/* ray casting to the right */
	segment ray (p,p+point(1,0));
	int n = (int)poly.size();
	/* counts the number of intersections */
	int nIntersection = 0;
	for (int i = 0; i < n; ++i){
		segment side(poly[i],poly[(i+1)%n]);
		if (isOnSegment(p,side)) {
			// printf("on segment on i = %d\n", i);
			return false;
		}
		if (isParallel(ray,side)) continue;
		point x = intersection(ray,side);
		// printf("%d-th side: (%.2lf,%.2lf),(%.2lf,%.2lf)\n", i, side.p1.x, side.p1.y, side.p2.x, side.p2.y);
		// printf("intersection with %d: (%.2lf,%.2lf)\n", i, x.x, x.y);
		// double d = dot(x-p,ray.p2-p);
		// printf("\tdot = %.2lf\n", d);
		if (isOnSegment(x,side) && dot(x-p,ray.p2-p) > -EPS){
			// printf("ON SEGMENT!!!");
			/* special case: x is one of vertices of sides */
			if (x == side.p1){
				// printf("ON SIDE.P1!!");
				if (isRightTurn(p,x,side.p2)) nIntersection ++;
			}
			else if (x == side.p2){
				// printf("ON SIDE.P2!!");
				if (isRightTurn(p,x,side.p1)) nIntersection ++;
			}
			else nIntersection ++;
		}
	}
	// printf("nintersection: %d\n", nIntersection);
	return nIntersection % 2 == 1;
}

/** Convex Hull | monotone chain algorithm **/
/* complexity : O(N log N) */
polygon convexHull(polygon p){
	int m = 0, n = p.size();
	polygon hull(2*n);
	sort(p.begin(),p.end());
	for (int i = 0; i < n; ++i){
		while (m >= 2 && isRightTurn(hull[m-2],hull[m-1],p[i]) && !isStraight(hull[m-2],hull[m-1],p[i])) --m;
		hull[m++] = p[i];
	}
	for (int i = n-1, t = m+1; i >= 0; --i){
		while (m >= t && isRightTurn(hull[m-2],hull[m-1],p[i]) && !isStraight(hull[m-2],hull[m-1],p[i])) --m;
		hull[m++] = p[i];
	}
	hull.resize(m);
	// remove any two consecutive points
	for (int i = 0; hull.size() > 1 && i < hull.size(); ++i) {
		if (hull[i] == hull[(i+1)%hull.size()]) {
			hull.erase(hull.begin()+i);
			i--;
		}
	}
	return hull;
}

// end of geometry.h

#define MAXN 100100

int n, m;

const point origin(0, 0);
const segment xAxis(origin, point(1e9, 0));

double patan2(double y, double x) {
  double ret = atan2(y, x);
  while (ret < 0) ret += 2 * PI;
  return ret;
}

double patan2(const point &p) {
  return patan2(p.y, p.x);
}

double patan2e(const point &p) {
  double ret = patan2(p);
  if (cmpf(ret, 0)) {
    return 2*PI;
  }
  return ret;
}

int main() {
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
    if (isIntersecting(s, xAxis)) {
      point p = intersection(s, xAxis);
      segment s1(p, s.p1);
      segment s2(p, s.p2);
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

  for (int i = 0; i < S.size(); ++i) {
    point p1 = S[i].p1;
    point p2 = S[i].p2;
  }

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
      if (!isOnSegment(ps, s)) {
        // invisible
        continue;
      }
      segment Ts(ps, s.p2);
      if (!(ps == s.p2)) {
        T.insert(T.begin(), Ts);
      }
      continue;
    }

    // special case 2: s is already invisible
    if (a2 <= patan2(T[k].p1)) {
      continue;
    }

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

  for (segment s : done) {
    assert(length(s) > EPS);
  }

  double ans = 0;
  double angle = 0;
  for (segment s : done) {
    double delta = patan2e(s.p2) - patan2(s.p1);
    if (!cmpf(delta, 2*PI)) angle += delta;
    ans += polygonArea({origin, s.p1, s.p2});
  }

  printf("%.17lf\n", ans);

  assert(fabs(angle - PI*2) / (PI*2) < 1e-5);
}