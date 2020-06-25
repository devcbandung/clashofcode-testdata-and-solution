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
			return false;
		}
		if (isParallel(ray,side)) continue;
		point x = intersection(ray,side);
		if (isOnSegment(x,side) && dot(x-p,ray.p2-p) > -EPS){
			/* special case: x is one of vertices of sides */
			if (x == side.p1){
				if (isRightTurn(p,x,side.p2)) nIntersection ++;
			}
			else if (x == side.p2){
				if (isRightTurn(p,x,side.p1)) nIntersection ++;
			}
			else nIntersection ++;
		}
	}
	return nIntersection % 2 == 1;
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

  double ans = 0;
  for (int k = 0; k < L.size(); ++k) {
    vector<segment> S = {L[k]};

    for (int i = 0; i < L.size(); ++i) {
      if (isStraight(origin, L[i].p1, L[i].p2)) continue;
      if (i == k) continue;
      vector<segment> tmp;
      for (segment s : S) {
        polygon tri = {origin, s.p1, s.p2};
        segment r1(origin, s.p1), r2(origin, s.p2);
        if (isIntersecting(L[i], r1) && isIntersecting(L[i], r2)) {
          continue;
        }
        if (isIntersecting(L[i], r1)) {
          if (isPointInsidePolygon(L[i].p1, tri)) {
            tmp.emplace_back(intersection(s, segment(origin, L[i].p1)), s.p2);
          } else if (isPointInsidePolygon(L[i].p2, tri)) {
            tmp.emplace_back(intersection(s, segment(origin, L[i].p2)), s.p2);
          } else {
            tmp.push_back(s);
          }
          continue;
        }
        if (isIntersecting(L[i], r2)) {
          if (isPointInsidePolygon(L[i].p1, tri)) {
            tmp.emplace_back(intersection(s, segment(origin, L[i].p1)), s.p1);
          } else if (isPointInsidePolygon(L[i].p2, tri)) {
            tmp.emplace_back(intersection(s, segment(origin, L[i].p2)), s.p1);
          } else {
            tmp.push_back(s);
          }
          continue;
        }
        
        if (isPointInsidePolygon(L[i].p1, tri) && isPointInsidePolygon(L[i].p2, tri)) {
          point t1 = intersection(s, segment(origin, L[i].p1));
          point t2 = intersection(s, segment(origin, L[i].p2));
          if (dist(s.p1, t1) < dist(s.p1, t2)) {
            tmp.emplace_back(s.p1, t1);
            tmp.emplace_back(s.p2, t2);
          } else {
            tmp.emplace_back(s.p1, t2);
            tmp.emplace_back(s.p2, t1);
          }
          continue;
        }

        tmp.push_back(s);
      }
      S.clear();
      for (segment s : tmp) {
        if (length(s) > EPS) S.push_back(s);
      }
    }
    for (segment s : S) {
      ans += polygonArea({origin, s.p1, s.p2});
    }
  }

  printf("%.17lf\n", ans);
}