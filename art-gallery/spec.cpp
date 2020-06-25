#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
#include "geometry.h"
using namespace std;
using namespace tcframe;

#define MAXX 10000
#define MAXN 5000
#define MAXM 5000

#define MODE_SQUARE 0
#define MODE_CIRCLE 1

const point origin(0, 0);

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
    CONS(3 <= N && N <= MAXN);
    CONS(0 <= M && M <= MAXM);
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
          puts("right turn!");
          for (int j = 0; j < 3; ++j) {
            int k = (i+j) % N;
            printf("\tp[%d]: (%d, %d)\n", k, GX[k], GY[k]);
          }
          return false;
        }
      }
      if (cmpf(p.x, 0) && cmpf(p.y, 0)) {
        puts("found origin!");
        printf("\tp[%d]: (%d, %d)\n", i, GX[i], GY[i]);
        return false;
      }
      if (isOnLine(point(0,0), segment(p, q))) {
        puts("pass origin!");
        printf("\tp[%d]: (%d, %d)\n", i, GX[i], GY[i]);
        printf("\tp[%d]: (%d, %d)\n", (i+1)%N, GX[(i+1)%N], GY[(i+1)%N]);
        return false;
      }
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
      if (isOnSegment(origin, s)) {
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
        printf("\t(%.2lf, %.2lf)\n", p.x, p.y);
        return false;
      }
      for (int i = 0; i < N; ++i) {
        if (isOnSegment(p, segment(G[i], G[(i+1)%N]))) {
          puts("on G!");
          return false;
        }
      }
    }

    // puts("hehe");

    // check two segments intersect with each other
    // TODO: this part takes the longest of all, taking N^2
    // N log N method exists, but I'm not sure it will be bug-free
    // https://www.geeksforgeeks.org/given-a-set-of-line-segments-find-if-any-two-segments-intersect/
    puts("checking intersecting...");
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < i; ++j) {
        segment s1 = L[i];
        segment s2 = L[j];
        bool intersect = false;
        if (isIntersecting(s1, s2)) intersect = true;
        if (intersect) {
          puts("intersect!");
          printf("i = %d, j = %d\n", i, j);
          printf("\t[(%.0lf,%.0lf),(%.0lf,%.0lf)]\n", L[i].p1.x, L[i].p1.y, L[i].p2.x, L[i].p2.y);
          printf("\t[(%.0lf,%.0lf),(%.0lf,%.0lf)]\n", L[j].p1.x, L[j].p1.y, L[j].p2.x, L[j].p2.y);
          printf("\tisOnSameSide: %d\n", isOnSameSide(L[i].p1, L[i].p2, L[j]));
          printf("\tisOnSameSide: %d\n", isOnSameSide(L[j].p1, L[j].p2, L[i]));
          printf("\tisOnSegment : %d\n", isOnSegment(L[i].p1, L[j]));
          printf("\tisOnSegment : %d\n", isOnSegment(L[i].p2, L[j]));
          printf("\tisOnSegment : %d\n", isOnSegment(L[j].p1, L[i]));
          printf("\tisOnSegment : %d\n", isOnSegment(L[j].p2, L[i]));
          return false;
        }
      }
    }
    puts("checking intersecting done!");

    // puts("dah kok");

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
    // 10% = 3TC: polygons, M = 0
    CASE(regularPolygon(MAXN), clearL());
    CASE(convexHullPolygon(MAXN, MAXX, MODE_SQUARE), clearL());
    CASE(convexHullPolygon(MAXN, MAXX, MODE_CIRCLE), clearL());

    // 30% = 9TC
    // 1TC: inverse "small" pyramid
    CASE(inversePyramid(100));
    // 1TC: inverse "large" pyramid
    CASE(inversePyramid(MAXM));
    // 7TC: distorted inverse pyramid
    for (int i = 0; i < 4; ++i) {
      CASE(distortedInversePyramid(MAXM));
    }
    // 3TC: random ranges
    CASE(randomRangeInversePyramid(MAXX, 100));
    CASE(randomRangeInversePyramid(MAXX, 1000));
    CASE(randomRangeInversePyramid(MAXX, MAXM));

    // 60% = 18TC
    // 2TC: distorted inverse pyramid four directions
    CASE(distortedInversePyramidFourWays(100));
    CASE(distortedInversePyramidFourWays(MAXM));
    // 2TC: windmill
    CASE(windmill(100));
    CASE(windmill(1000));
    // 3TC: random segments in a square
    CASE(randomInsideSquare(100, MAXX));
    CASE(randomInsideSquare(1000, MAXX));
    CASE(randomInsideSquare(MAXM, MAXX));
    // 3TC: random segments in a regular polygon
    CASE(randomInsideRegularPolygon(25, 100, MAXX));
    CASE(randomInsideRegularPolygon(50, 1000, MAXX));
    CASE(randomInsideRegularPolygon(MAXN, MAXM, MAXX));
    // 8TC: random segments inside convex hull
    CASE(randomConvexHull(100, MAXX, MODE_SQUARE));
    CASE(randomConvexHull(1000, MAXX, MODE_SQUARE));
    CASE(randomConvexHull(MAXN, MAXX, MODE_SQUARE));
    CASE(randomConvexHull(MAXN, MAXX, MODE_SQUARE));
    CASE(randomConvexHull(100, MAXX, MODE_CIRCLE));
    CASE(randomConvexHull(1000, MAXX, MODE_CIRCLE));
    CASE(randomConvexHull(MAXN, MAXX, MODE_CIRCLE));
    CASE(randomConvexHull(MAXN, MAXX, MODE_CIRCLE));
  }

  void clearG() {
    N = 0;
    GX.clear();
    GY.clear();
  }

  void clearL() {
    M = 0;
    LAX.clear();
    LBX.clear();
    LAY.clear();
    LBY.clear();
  }

  void clear() {
    clearG();
    clearL();
  }

  void square(int k) {
    N = 4;
    GX = {-k, k, k, -k};
    GY = {-k, -k, k, k};
  }

  void regularPolygon(int n) {
    // "random" polygon
    clearG();
    double r = MAXX;
    polygon P;
    for (int i = 0; i < n; ++i) {
      point p(r * cos(PI * 2 * i / (double)n), r * sin(PI * 2 * i / (double)n));
      P.push_back(point(round(p.x), round(p.y)));
    }
    polygon hull = convexHull(P);
    N = hull.size();
    for (int i = 0; i < N; ++i) {
      GX.push_back(hull[i].x);
      GY.push_back(hull[i].y);
    }
  }

  void convexHullPolygon(int n, int k, int mode) {
    clearG();

    // generate n random points inside the square/circle
    vector<pair<int,int>> P;
    map<pair<int,int>,bool> used;
    used[make_pair(0,0)] = true;

    if (mode == MODE_SQUARE) {
      for (int i = 0; i < n; ++i) {
        int x, y;
        do {
          x = rnd.nextInt(-k, k);
          y = rnd.nextInt(-k, k);
        } while (used[make_pair(x,y)]);
        used[make_pair(x,y)] = true;
        P.emplace_back(x,y);
      }
    } else if (mode == MODE_CIRCLE) {
      double R = k;
      for (int i = 0; i < n; ++i) {
        int x, y;
        do {
          double r = rnd.nextDouble(R);
          double a = rnd.nextDouble(PI*2);
          double xx = r * cos(a);
          double yy = r * sin(a);
          x = round(xx);
          y = round(yy);
        } while (used[make_pair(x,y)]);
        used[make_pair(x,y)] = true;
        P.emplace_back(x,y);
      }
    } else {
      printf("unknown mode: %d\n", mode);
      assert(false);
    }

    polygon hull = convexHull(pointFromVectorPair(P));
    N = hull.size();
    for (int i = 0; i < N; ++i) {
      GX.push_back(hull[i].x);
      GY.push_back(hull[i].y);
    }
  }

  void inversePyramid(int s) {
    clear();
    square(s);
    M = s-2;
    for (int i = 0; i < M; ++i) {
      LAX.push_back(-(i+1));
      LAY.push_back(i+2);
      LBX.push_back((i+1));
      LBY.push_back(i+2);
    }
  }

  void distortedInversePyramid(int s) {
    clear();
    square(s);
    M = s-2;
    for (int i = 0; i < M; ++i) {
      LAX.push_back(-(i+1));
      LAY.push_back(i+2);
      LBY.push_back(i+2);
      if (i < M/2 || i == M-1) {
        LBX.push_back((i+1));
      } else {
        LBX.push_back(rnd.nextInt(-10,10));
      }
    }
  }

  vector<pair<int,int>> generateRanges(int minx, int maxx, int n) {
    if (n == 0) return {};
    if (n == 1) {
      while (true) {
        int l = rnd.nextInt(minx, maxx);
        int r = rnd.nextInt(minx, maxx);
        if (l == r) continue;
        if (l > r) swap(l, r);
        return{{l,r}};
      }
    }
    int len = maxx-minx;
    // generate n-1 distinct numbers in range [1..len-n]
    vector<int> x;
    for (int i = 0; i < n-1; ++i) {
      x.push_back(rnd.nextInt(1, len-2*n+1));
    }
    sort(x.begin(), x.end());
    for (int i = 0; i < n-1; ++i) x[i] += 2*i;
    vector<pair<int,int>> ret;
    ret.emplace_back(rnd.nextInt(x[0]), x[0]);
    for (int i = 1; i < n-1; ++i) {
      ret.emplace_back(rnd.nextInt(x[i-1]+1, x[i]-1), x[i]);
    }
    while (true) {
      int l = rnd.nextInt(x[n-2]+1, len);
      int r = rnd.nextInt(x[n-2]+1, len);
      if (l == r) continue;
      if (l > r) swap(l, r);
      ret.emplace_back(l, r);
      break;
    }
    assert(ret.size() == n);
    for (int i = 0; i < n; ++i) {
      ret[i].first += minx;
      ret[i].second += minx;
    }
    return ret;
  }

  void randomRangeInversePyramid(int s, int m) {
    clear();
    square(s);
    int maxs = s/2-1;
    vector<int> c(maxs+1);
    for (int i = 0; i < m; ++i) {
      while (true) {
        int r = rnd.nextInt(1, maxs);
        if (c[r] < r) {
          c[r]++;
          break;
        }
      }
    }
    clearL();
    M = m;
    for (int y = 1; y <= maxs; ++y) {
      if (!c[y]) continue;
      auto pairs = generateRanges(-y, y, c[y]);
      for (auto pair : pairs) {
        LAX.push_back(pair.first);
        LBX.push_back(pair.second);
        LAY.push_back(2*y);
        LBY.push_back(2*y);
      }
    }
  }

  void distortedInversePyramidFourWays(int s) {
    clear();
    square(s);
    M = MAXM / 4 * 4;
    if ((s-2)*4 < M) {
      M = (s-2)*4;
    }
    auto insertSegment = [&](int y, int x1, int x2, int d) {
      point p1(x1, y), p2(x2, y);
      for (int i = 0; i < d; ++i) {
        p1 = rotate(p1, PI/2);
        p2 = rotate(p2, PI/2);
      }
      LAX.push_back(round(p1.x));
      LAY.push_back(round(p1.y));
      LBX.push_back(round(p2.x));
      LBY.push_back(round(p2.y));
    };
    for (int i = 0; i < M/4; ++i) {
      int y = i+2;
      int x1 = -(i+1);
      int x2 = i+1;
      if (i < M/8 || i == M/4-1) x2 = (i+1);
      for (int d = 0; d < 4; ++d) {
        insertSegment(y, x1, x2, d);
      }
    }
  }

  void windmill(int n) {
    clear();
    square(MAXX);

    double r1 = 0.9 * MAXX;
    double r2 = 0.8 * MAXX;

    M = n;
    for (int i = 0; i < n; ++i) {
      point p1(r1 * cos(PI * 2 * i / (double)n), r1 * sin(PI * 2 * i / (double)n));
      point p2(r2 * cos(PI * 2 * (i+2) / (double)n), r2 * sin(PI * 2 * (i+2) / (double)n));

      LAX.push_back(round(p1.x));
      LAY.push_back(round(p1.y));
      LBX.push_back(round(p2.x));
      LBY.push_back(round(p2.y));
    }
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
        res.emplace_back(q1, q2);
      }
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
    clearG();
    square(k);
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

    auto pairs = pairPoints(P);
    assert(pairs.size() == M);
    assignL(pairs);
  }

  void randomInsideRegularPolygon(int n, int m, int k) {
    clearL();
    clearG();
    regularPolygon(n);
    M = m;

    // generate 2m random points inside the circle
    double R = k-100;
    vector<pair<int,int>> P;
    map<pair<int,int>,bool> used;
    used[make_pair(0,0)] = true;
    for (int i = 0; i < 2*m; ++i) {
      int x, y;
      do {
        double r = rnd.nextDouble(R);
        double a = rnd.nextDouble(PI*2);
        double xx = r * cos(a);
        double yy = r * sin(a);
        x = round(xx);
        y = round(yy);
      } while (used[make_pair(x,y)]);
      used[make_pair(x,y)] = true;
      P.emplace_back(x,y);
    }

    auto pairs = pairPoints(P);
    assert(pairs.size() == M);
    assignL(pairs);
  }

  void randomConvexHull(int m, int k, int mode) {
    clearL();
    clearG();
    M = m;

    // generate 2m random points inside the square/circle
    vector<pair<int,int>> P;
    map<pair<int,int>,bool> used;
    used[make_pair(0,0)] = true;

    if (mode == MODE_SQUARE) {
      for (int i = 0; i < 2*m; ++i) {
        int x, y;
        do {
          x = rnd.nextInt(-k, k);
          y = rnd.nextInt(-k, k);
        } while (used[make_pair(x,y)]);
        used[make_pair(x,y)] = true;
        P.emplace_back(x,y);
      }
    } else if (mode == MODE_CIRCLE) {
      double R = k;
      for (int i = 0; i < 2*m; ++i) {
        int x, y;
        do {
          double r = rnd.nextDouble(R);
          double a = rnd.nextDouble(PI*2);
          double xx = r * cos(a);
          double yy = r * sin(a);
          x = round(xx);
          y = round(yy);
        } while (used[make_pair(x,y)]);
        used[make_pair(x,y)] = true;
        P.emplace_back(x,y);
      }
    } else {
      printf("unknown mode: %d\n", mode);
      assert(false);
    }

    polygon hull = convexHull(pointFromVectorPair(P));
    vector<pair<int,int>> tmp;
    used.clear();
    clearG();
    for (point p : hull) {
      int x = round(p.x), y = round(p.y);
      if (used[make_pair(x,y)]) continue;
      GX.push_back(x);
      GY.push_back(y);
      N++;
      used[make_pair(x,y)] = true;
    }
    for (auto p : P) {
      if (!used[make_pair(p.first, p.second)]) {
        tmp.push_back(p);
      }
    }
    if (tmp.size() % 2) tmp.pop_back();
    M = tmp.size() / 2;

    auto pairs = pairPoints(tmp);
    assert(pairs.size() == M);

    assignL(pairs);
  }

  void assignL(const vector<pair<pair<int,int>,pair<int,int>>> &pairs) {
    clearL();
    for (int i = 0; i < pairs.size(); ++i) {
      point p1(pairs[i].first);
      point p2(pairs[i].second);
      if (isOnSegment(origin, segment(p1, p2))) continue;
      LAX.push_back(pairs[i].first.first);
      LAY.push_back(pairs[i].first.second);
      LBX.push_back(pairs[i].second.first);
      LBY.push_back(pairs[i].second.second);
    }
    M = LAX.size();
  }

  void cleanup() {
    // remove segments in L passing the origin
    for (int i = 0; i < M; ++i) {
      point p1((double)LAX[i], (double)LAY[i]);
      point p2((double)LBX[i], (double)LBY[i]);
      if (isOnSegment(origin, segment(p1, p2))) {
        printf("one segment passing origin found, removing ...\n");
        LAX.erase(LAX.begin()+i);
        LBX.erase(LBX.begin()+i);
        LAY.erase(LAY.begin()+i);
        LBY.erase(LBY.begin()+i);
        M--;
        i--;
      }
    }
  }
};