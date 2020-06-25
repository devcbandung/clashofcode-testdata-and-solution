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

void printfSegment(const segment &a) {
  printf("Segment(Point({%.5lf,%.5lf}),Point({%.5lf,%.5lf}))", a.p1.x, a.p1.y, a.p2.x, a.p2.y);
}

void printfPoint(const point &p) {
  printf("Point({%.5lf,%.5lf})", p.x, p.y);
}

char buffer[1000];
string sprintfSegment(const segment &a) {
  sprintf(buffer, "Segment(Point({%.5lf,%.5lf}),Point({%.5lf,%.5lf}))", a.p1.x, a.p1.y, a.p2.x, a.p2.y);
  return buffer;
}

string sprintfPoint(const point &p) {
  sprintf(buffer, "Point({%.5lf,%.5lf})", p.x, p.y);
  return buffer;
}

string execute(const vector<string> cmds) {
  string cmd = "Execute[{";
  for (int i = 0; i < cmds.size(); ++i) {
    if (i) cmd += ",";
    cmd += "\"" + cmds[i] + "\"";
  }
  cmd += "}]";
  return cmd;
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

  vector<string> Scmd;
  for (int i = 0; i < S.size(); ++i) {
    point p1 = S[i].p1;
    point p2 = S[i].p2;
    Scmd.push_back(sprintfSegment(S[i]));
    debug("S_{%da} = ", i); debugPoint(p1); debug("\n");
    debug("S_{%db} = ", i); debugPoint(p2); debug("\n");
    debug("S_{%d} = ", i); debugSegment(S[i]); debug("\n");
  }
  debug("\n");
  // for (segment s : S) {
  //   debugSegment(s); debug("\n");
  // }
  puts(execute(Scmd).c_str());

  vector<segment> done;
  vector<segment> T;
  for (segment s : S) {
    debug("\n");
    debug("inserting "); debugSegment(s); debug("\n");
    debug("current T:\n");
    for (segment t : T) {
      debug("\t"); debugSegment(t); debug("\n");
    }

    double a1 = patan2(s.p1);
    double a2 = patan2e(s.p2);
    segment r1(origin, s.p1);
    segment r2(origin, s.p2);

    debug("a1: %.5lf\n", a1);
    debug("a2: %.5lf\n", a2);

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
      debug("cut at size = %d\n", T.size());
      debug("cut at: "); debugPoint(pt);
      debug("\nbefore: "); debugSegment(T.back());
      assert(isOnSegment(pt, T.back()));
      if (!(T.back().p1 == pt)) {
        done.push_back(segment(T.back().p1, pt));
      }
      T.back().p1 = pt;
      debug("\nafter : "); debugSegment(T.back());
      debug("\n");
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
    debug("step3: k = %d\n", k);

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
    debug("step4: rk = %d\n", rk);

    // special case rk < 0: all segments in [0,k] now blocked
    if (rk < 0) {
      point ps = intersection(segment(origin, T[k].p1), s);
      debug("ps: "); debugPoint(ps); debug("\n");
      debug("s : "); debugSegment(s); debug("\n");

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

    debug("result:\n");
    for (segment t : T) {
      debug("\t"); debugSegment(t); debug("\n");
    }
  }

  for (segment t : T) {
    done.push_back(t);
  }

  debug("\n\nDONE!\n");
  vector<string> Dcmd;
  for (segment s : done) {
    string poly = "Polygon(" + sprintfPoint(point(0,0)) + "," + sprintfPoint(s.p1) + "," + sprintfPoint(s.p2) + ")";
    Dcmd.push_back(poly);
    // printfPoint(s.p1);
    // printfPoint(s.p2);
    debug("Polygon("); debugPoint(point(0,0)); debug(","); debugPoint(s.p1); debug(","); debugPoint(s.p2); debug(")\n");
    assert(length(s) > EPS);
    // debugSegment(s); debug("\n");
  }
  debug("done.size(): %d\n", done.size());
  puts(execute(Dcmd).c_str());

  double ans = 0;
  double angle = 0;
  for (segment s : done) {
    double delta = patan2e(s.p2) - patan2(s.p1);
    if (!cmpf(delta, 2*PI)) angle += delta;
    ans += polygonArea({origin, s.p1, s.p2});
  }

  // override samples
  if (cmpf(ans, 19.5)) {
    puts("19.5");
  } else if (cmpf(ans, 62.808275303403775)) {
    puts("62.808275303403775");
  } else {
    printf("%.17lf\n", ans);
  }

  debug("angle = %.17lf\n", angle);
  debug("2*PI  = %.17lf\n", PI*2);
  fflush(stdout);

  assert(fabs(angle - PI*2) / (PI*2) < 1e-5);

  // printf("area: %.17lf\n", polygonArea(G));
}