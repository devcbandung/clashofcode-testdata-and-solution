#include <tcframe/spec.hpp>
#include <cassert>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  int AX1, AX2, AY1, AY2, BX1, BX2, BY1, BY2;
  int ans;

  void InputFormat() {
    LINE(AX1, AY1, AX2, AY2);
    LINE(BX1, BY1, BX2, BY2);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(validRect(AX1, AY1, AX2, AY2));
    CONS(validRect(BX1, BY1, BX2, BY2));
    CONS(!disjoint());
  }

  bool validRect(int x1, int y1, int x2, int y2) {
    if (x1 < 0 || x1 > 1000000) return false;
    if (y1 < 0 || y1 > 1000000) return false;
    if (x2 < 0 || x2 > 1000000) return false;
    if (y2 < 0 || y2 > 1000000) return false;
    if (x1 >= x2) return false;
    if (y1 >= y2) return false;
    return true;
  }

  bool disjoint() {
    if (AX2 <= BX1) return true;
    if (BX2 <= AX1) return true;
    if (AY2 <= BY1) return true;
    if (BY2 <= AY1) return true;
    return false;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void TestCases() {
    // Samples
    CASE(assign(2, 1, 5, 6, 4, 3, 9, 7));

    // Test Cases
    for (int sx1 = 0; sx1 < 3; ++sx1) {
      for (int sx2 = 0; sx2 < 3; ++sx2) {
        for (int sy1 = 0; sy1 < 3; ++sy1) {
          for (int sy2 = 0; sy2 < 3; ++sy2) {
            CASE(randomWithComp(sx1, sx2, sy1, sy2));
          }
        }
      }
    }
  }

  void assign(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
    AX1 = ax1;
    AX2 = ax2;
    AY1 = ay1;
    AY2 = ay2;
    BX1 = bx1;
    BX2 = bx2;
    BY1 = by1;
    BY2 = by2;
    // printf("TC:\n((%d, %d), (%d, %d))\n((%d, %d), (%d, %d))\n", ax1, ay1, ax2, ay2, bx1, by1, bx2, by2);
  }

  // comp:
  // 0: less
  // 1: equal
  // 2: greater
  void randomWithComp(int sx1, int sx2, int sy1, int sy2) {
    // printf("sx1 = %d, sx2 = %d, sy1 = %d, sy2 = %d\n", sx1, sx2, sy1, sy2);
    vector<int> x = randomPoints(sx1, sx2);
    vector<int> y = randomPoints(sy1, sy2);
    assert(x.size() == 4);
    assert(y.size() == 4);
    assign(x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3]);
  }

  vector<int> randomPoints(int s1, int s2) {
    int n = 4;
    if (s1 == 1) n--;
    if (s2 == 1) n--;
    
    // generate n random sorted points
    vector<int> p;
    for (int i = 0; i < n; ++i) p.push_back(rnd.nextInt(0, 1000000-n+1));
    sort(p.begin(), p.end());
    for (int i = 0; i < n; ++i) p[i] += i;

    vector<int> x(4);
    int offset = 2;
    if (s1 == 0) {
      x[0] = p[0];
      x[2] = p[1];
    } else if (s1 == 1) {
      x[0] = x[2] = p[0];
      offset = 1;
    } else if (s1 == 2) {
      x[0] = p[1];
      x[2] = p[0];
    } else assert(false);
    if (s2 == 0) {
      x[1] = p[offset + 0];
      x[3] = p[offset + 1];
    } else if (s2 == 1) {
      x[1] = x[3] = p[offset + 0];
      offset = 1;
    } else if (s2 == 2) {
      x[1] = p[offset + 1];
      x[3] = p[offset + 0];
    } else assert(false);
    return x;
  }
};