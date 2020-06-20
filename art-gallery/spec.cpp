#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
#include "geometry.h"
using namespace std;
using namespace tcframe;

vector<point> pointFromVector(const vector<int> &x, const vector<int> &y) {
  vector<point> p;
  assert(x.size() == y.size());
  for (int i = 0; i < x.size(); ++i) {
    p.push_back(point(x[i], y[i]));
  }
  return p;
}
vector<point> pointFromVectorPair(const vector<pair<int,int>> &x) {
  vector<point> p;
  for (int i = 0; i < x.size(); ++i) {
    p.push_back(point(x[i].first, x[i].second));
  }
  return p;
}

#define MAXX 1000

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, M;
  vector<int> GX, GY, LAX, LAY, LBX, LBY;
  double ans;

  void InputFormat() {
    LINE(N, M);
    LINES(GX, GY) % SIZE(N);
    LINES(LAX, LAY, LBX, LBY) % SIZE(M);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(1 <= N && N <= 1000);
    CONS(1 <= M && M <= 1000);
    CONS(withinRange(GX));
    CONS(withinRange(GY));
    CONS(withinRange(LAX));
    CONS(withinRange(LAY));
    CONS(withinRange(LBX));
    CONS(withinRange(LBY));
    CONS(validG());
    CONS(validL());
  }

  bool withinRange(const vector<int> &a) {
    for (int x : a) {
      if (x < -MAXX || x > MAXX) {
        return false;
      }
    }
    return true;
  }

  bool validG() {
    if (GX.size() != N) return false;
    if (GY.size() != N) return false;

    polygon G = pointFromVector(GX, GY);
    for (int i = 0; i < N; ++i) {
      point p = G[i];
      point q = G[(i+1)%N];
      point r = G[(i+2)%N];
      if (isRightTurn(p, q, r)) {
        if (!isOnLine(p, segment(q, r))) {
          return false;
        }
      }
      if (cmpf(p.x, 0) && cmpf(p.y, 0)) return false;
      if (isOnLine(point(0,0), segment(p, q))) return false;
    }
    return true;
  }

  bool validL() {
    if (LAX.size() != M) return false;
    if (LAY.size() != M) return false;
    if (LBX.size() != M) return false;
    if (LBY.size() != M) return false;
    
    vector<point> LA = pointFromVector(LAX, LAY);
    vector<point> LB = pointFromVector(LBX, LBY);
    polygon G = pointFromVector(GX, GY);
    vector<point> LL;
    vector<segment> L;
    for (int i = 0; i < M; ++i) {
      L.push_back(segment(LA[i], LB[i]));
      LL.push_back(LA[i]);
      LL.push_back(LB[i]);
    }

    // check pass origin
    for (segment s : L) {
      if (isOnLine(point(0,0), s)) {
        puts("pass origin!");
        return false;
      }
    }

    // check inside G
    for (point p : LL) {
      if (cmpf(p.x, 0) && cmpf(p.y, 0)) {
        puts("origin found!");
        return false;
      }
      if (!isPointInsidePolygon(p, G)) {
        puts("outside G!");
        return false;
      }
      for (int i = 0; i < N; ++i) {
        if (isOnSegment(p, segment(G[i], G[(i+1)%N]))) {
          puts("on G!");
          return false;
        }
      }
    }

    puts("hehe");

    // check two segments intersect with each other
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < i; ++j) {
        segment s1 = L[i];
        segment s2 = L[j];
        bool intersect = false;
        if (isOnSegment(s1.p1, s2)) intersect = true;
        if (isOnSegment(s1.p2, s2)) intersect = true;
        if (isOnSegment(s2.p1, s1)) intersect = true;
        if (isOnSegment(s2.p2, s1)) intersect = true;
        if (isIntersecting(s1, s2)) intersect = true;
        if (intersect) {
          puts("intersect!");
          printf("i = %d, j = %d\n", i, j);
          printf("\t[(%.0lf,%.0lf),(%.0lf,%.0lf)]\n", L[i].p1.x, L[i].p1.y, L[i].p2.x, L[i].p2.y);
          printf("\t[(%.0lf,%.0lf),(%.0lf,%.0lf)]\n", L[j].p1.x, L[j].p1.y, L[j].p2.x, L[j].p2.y);
          return false;
        }
      }
    }

    puts("dah kok");

    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void TestCases() {
    // Samples
    CASE(N = 4, M = 4,
      GX = {-3, 3, 3, -3},
      GY = {-3, -3, 3, 3},
      LAX = {-2, -1, 2, 1},
      LAY = {-1, 0, 0, 0},
      LBX = {-2, 0, 2, 2},
      LBY = {2, -2, 2, -2}
    );
    CASE(N = 8, M = 9,
      GX = {-6, -7, -1, 10, 11, 10, 3, -5},
      GY = {3, -2, -5, -6, 2, 4, 6, 5},
      LAX = {-4, -4, 1, 5, 5, -3, -5, 1, 2},
      LAY = {2, 4, 1, 3, 1, 1, -1, -4, -1},
      LBX = {-2, 2, 1, 8, 4, -1, -3, 5, 2},
      LBY = {3, 4, 3, 0, -1, -2, -2, -2, -2}
    );

    // Test Cases
    // random in a square
    CASE(square(1000), randomInsideSquare(1000, 1000));
    CASE(square(1000), randomInsideSquare(10, 1000));
    CASE(square(1000), randomInsideSquare(20, 1000));
    CASE(square(1000), randomInsideSquare(30, 1000));
    CASE(square(1000), randomInsideSquare(40, 1000));
    CASE(square(1000), randomInsideSquare(50, 1000));
    CASE(square(1000), randomInsideSquare(100, 1000));
    CASE(square(1000), randomInsideSquare(500, 1000));
  }

  void clearL() {
    LAX.clear();
    LBX.clear();
    LAY.clear();
    LBY.clear();
  }

  void square(int k) {
    N = 4;
    GX = {-k, k, k, -k};
    GY = {-k, -k, k, k};
  }

  vector<pair<pair<int,int>,pair<int,int>>> pairPoints(const vector<pair<int,int>> &P) {
    // convex hull method
    int n = P.size();
    assert(n % 2 == 0);

    vector<pair<pair<int,int>,pair<int,int>>> res;
    map<pair<int,int>,bool> used;
    vector<pair<int,int>> C = P;

    int depth = 0;
    while (!C.empty()) {
      polygon c = pointFromVectorPair(C);
      polygon hull = convexHull(c);
      int s = hull.size();
      // printf("hull.size() = %d\n", s);
      // for (point p : hull) {
      //   printf("(%.0lf, %.0lf)\n", p.x, p.y);
      // }
      for (int i = 0; i+1 < s; i += 2) {
        point p1 = hull[i];
        pair<int,int> q1 = make_pair(round(p1.x), round(p1.y));
        point p2 = hull[i+1];
        pair<int,int> q2 = make_pair(round(p2.x), round(p2.y));
        assert(!used[q1]);
        assert(!used[q2]);
        used[q1] = true;
        used[q2] = true;
        if (res.size() == 388 || res.size() == 369) {
          printf("i = %d, hull.size() = %d,%d, depth = %d\n", res.size(), s, i, depth);
        }
        res.emplace_back(q1, q2);
      }
      // for (int i = 0; i < s; i++) {
      //   point p1 = hull[i];
      //   pair<int,int> q1 = make_pair(round(p1.x), round(p1.y));
      //   while (i+1 < s && used[q1]) {
      //     i++;
      //     p1 = hull[i];
      //     q1 = make_pair(round(p1.x), round(p1.y));
      //   }
      //   if (used[q1]) break;

      //   i++;
      //   point p2 = hull[i];
      //   pair<int,int> q2 = make_pair(round(p2.x), round(p2.y));
      //   while (i+1 < s && used[q2]) {
      //     i++;
      //     p2 = hull[i];
      //     q2 = make_pair(round(p2.x), round(p2.y));
      //   }
      //   if (used[q2]) break;
      //   if (q1 == q2) break;

      //   used[q1] = true;
      //   used[q2] = true;
      //   res.emplace_back(q1, q2);
      // }
      vector<pair<int,int>> tmp;
      for (auto p : C) {
        if (!used[p]) tmp.push_back(p);
      }
      C = tmp;
      depth++;
    }
    puts("pairing done!");
    assert(res.size() == n/2);
    return res;
  }

  void randomInsideSquare(int m, int k) {
    clearL();
    M = m;

    // generate 2m random points inside the square
    vector<pair<int,int>> P;
    map<pair<int,int>,bool> used;
    used[make_pair(0,0)] = true;
    for (int i = 0; i < 2*m; ++i) {
      int x, y;
      do {
        x = rnd.nextInt(-(k-1), k-1);
        y = rnd.nextInt(-(k-1), k-1);
      } while (used[make_pair(x,y)]);
      used[make_pair(x,y)] = true;
      P.emplace_back(x,y);
    }

    // vector<pair<pair<int,int>,pair<int,int>>> pairPoints(P);

    auto hasIntersecting = [&]() -> pair<int,int> {
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < i; ++j) {
          segment si = segment(point(P[2*i]), point(P[2*i+1]));
          segment sj = segment(point(P[2*j]), point(P[2*j+1]));
          if (isIntersecting(si, sj)) return make_pair(i,j);
        }
      }
      return make_pair(-1,-1);
    };

    auto pairs = pairPoints(P);
    assert(pairs.size() == M);

    // long long iteration = 0;
    // while (true) {
    //   iteration++;
    //   auto t = hasIntersecting();
    //   if (iteration % 1000 == 0) {
    //     printf("iteration: %lld\n", iteration);
    //     double length = 0;
    //     for (int i = 0; i < m; ++i) {
    //       length += dist(point(P[2*i]), point(P[2*i+1]));
    //     }
    //     printf("\ttotal length = %.3lf\n", length);
    //   }
    //   if (t == make_pair(-1,-1)) break;
    //   // printf("has intersection: (%d, %d)\n", t.first, t.second);
    //   // printf("\t[(%d,%d),(%d,%d)]\n", P[2*t.first].first, P[2*t.first].second, P[2*t.first+1].first, P[2*t.first+1].second);
    //   // printf("\t[(%d,%d),(%d,%d)]\n", P[2*t.second].first, P[2*t.second].second, P[2*t.second+1].first, P[2*t.second+1].second);
    //   swap(P[2*t.first+1],P[2*t.second]);
    // }

    for (int i = 0; i < M; ++i) {
      LAX.push_back(pairs[i].first.first);
      LAY.push_back(pairs[i].first.second);
      LBX.push_back(pairs[i].second.first);
      LBY.push_back(pairs[i].second.second);
    }
  }
};