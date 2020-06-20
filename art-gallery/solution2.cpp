#include <bits/stdc++.h>
#include "geometry.h"
using namespace std;

// #define debug(...) printf(__VA_ARGS__)
#define debug(...)

#define MAXN 100100

int n, m;

const point origin(0, 0);
const segment xAxis(origin, point(1e9, 0));

void debugSegment(const segment &a) {
  debug("Segment(Point({%.5lf,%.5lf}),Point({%.5lf,%.5lf}))", a.p1.x, a.p1.y, a.p2.x, a.p2.y);
}

void debugPoint(const point &p) {
  debug("Point({%.5lf,%.5lf})", p.x, p.y);
}

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

  // for (int i = 0; i < n; ++i) {
  //   L.emplace_back(G[i], G[(i+1)%n]);
  // }

  double ans = 0;
  for (int k = 0; k < L.size(); ++k) {
    vector<segment> S = {L[k]};

    for (int i = 0; i < L.size(); ++i) {
      if (i == k) continue;
      vector<segment> tmp;
      for (segment s : S) {
        polygon tri = {origin, s.p1, s.p2};
        segment r1(origin, s.p1), r2(origin, s.p2);
        if (isIntersecting(L[i], r1) && isIntersecting(L[i], r2)) {
          debug("both intersecting! "); debugSegment(L[i]); debug(" with "); debugSegment(r1); debug(" and "); debugSegment(r2); debug("\n");
          continue;
        }
        if (isIntersecting(L[i], r1)) {
          debug("intersecting with r1\n");
          if (isPointInsideTriangle(L[i].p1, tri)) {
            debug("inside: "); debugPoint(L[i].p1); debug("\n");
            tmp.emplace_back(intersection(s, segment(origin, L[i].p1)), s.p2);
          } else {
            debug("inside: "); debugPoint(L[i].p2); debug("\n");
            tmp.emplace_back(intersection(s, segment(origin, L[i].p2)), s.p2);
          }
          continue;
        }
        if (isIntersecting(L[i], r2)) {
          debug("intersecting with r2\n");
          if (isPointInsideTriangle(L[i].p1, tri)) {
            debug("inside: "); debugPoint(L[i].p1); debug("\n");
            tmp.emplace_back(intersection(s, segment(origin, L[i].p1)), s.p1);
          } else {
            debug("inside: "); debugPoint(L[i].p2); debug("\n");
            tmp.emplace_back(intersection(s, segment(origin, L[i].p2)), s.p1);
          }
          continue;
        }
        
        if (isPointInsideTriangle(L[i].p1, tri) && isPointInsideTriangle(L[i].p2, tri)) {
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
      S = tmp;
      debug("original: "); debugSegment(L[k]); debug("\n");
      debug("after cut with :"); debugSegment(L[i]); debug("\n");
      for (segment s : S) {
        debug("\t"); debugSegment(s); debug("\n");
      }
      debug("--\n");
    }

    debug("original: "); debugSegment(L[k]); debug("\n");
    debug("after:\n");
    for (segment s : S) {
      debug("\t"); debugSegment(s); debug("\n");
      ans += polygonArea({origin, s.p1, s.p2});
    }
    debug("\n");
  }

  printf("%.17lf\n", ans);
}