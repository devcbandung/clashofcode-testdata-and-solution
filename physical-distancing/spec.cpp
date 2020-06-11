#include <tcframe/spec.hpp>
#include <cassert>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  vector<int> X, Y, V;
  int N, D;
  long long ans;

  void InputFormat() {
    LINE(N, D);
    LINES(X, Y, V) % SIZE(N);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(10);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(1 <= N && N <= 100000);
    CONS(1 <= D && D <= 10);
    CONS(validPoints(X));
    CONS(validPoints(Y));
    CONS(validV(V));
  }

  bool validPoints(const vector<int> &a) {
    if (a.size() != N) return false;
    for (int x : a) {
      if (x < 0 || x > 100000) return false;
    }
    return true;
  }
  bool validV(const vector<int> &a) {
    if (a.size() != N) return false;
    for (int x : a) {
      if (x < -100000 || x > 100000) return false;
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void TestCases() {
    // Samples
    CASE(N = 5, D = 2,
      X = {3, 5, 2, 7, 6},
      Y = {1, 4, 3, 4, 1},
      V = {1, -1, 2, 1, 3}
    );
    // Test Cases
    // TC1-6: N \in [1,1000], x,y,v \in [0,1000]
    // TC7-10: N \in [1,1000], x,y,v \in [0,100000]
    // TC11-20: N \in [1001, 100000], x,y,v \in [0,100000]
    // TODO: tricky manual tcs

    // TC1: random
    /*  1 */ CASE(N = 1000, D = 10, random(1000));
    // TC2: max answer
    /*  2 */ CASE(N = 1000, D = 6, maxAnswer(1000, 1000));
    // TC2-3: single gap
    /*  2 */ CASE(N = 575, D = 5, gaps(1000, 1000, 10, 1, 15, 0));
    // TC4-5: multiple gaps
    /*  4 */ CASE(N = 724, D = 3, gaps(1000, 1000, 10, 13, 10, 0.02));
    /*  5 */ CASE(N = 1000, D = 10, gaps(1000, 1000, 100, 10, 20, 0.05));
    // TC6: multiple gaps, same v
    /*  6 */ CASE(N = 825, D = 9, gaps(1000, 1000, 0, 10, 30, 0.05), sameV(1, false));

    // TC7: random
    /*  7 */ CASE(N = 1000, D = 8, random(100000));
    // TC8: single gap
    /*  8 */ CASE(N = 999, D = 2, gaps(100000, 100000, 50, 1, 20, 0.1));
    // TC9: multiple gaps
    /*  9 */ CASE(N = 960, D = 4, gaps(100000, 100000, 50, 10, 12, 0.05));
    // TC10: multiple gaps, same v, both directions
    /* 10 */ CASE(N = 809, D = 5, gaps(100000, 100000, 0, 10, 13, 0.02), sameV(3, true));

    // TC11: x[i] = i
    /* 11 */ CASE(N = 100000, D = 4, permute(100000));
    // TC12: random
    /* 12 */ CASE(N = 100000, D = 5, random(100000));
    // TC13: max answer
    /* 13 */ CASE(N = 100000, D = 10, maxAnswer(100000, 100000));
    // TC14: single gap
    /* 14 */ CASE(N = 99999, D = 7, gaps(100000, 100000, 10000, 1, 100, 0.01));
    // TC15: single gap, same v
    /* 15 */ CASE(N = 88888, D = 4, gaps(100000, 100000, 0, 1, 20, 0.02), sameV(88, false));
    // TC16-18: multiple gaps
    /* 16 */ CASE(N = 77777, D = 1, gaps(100000, 1000, 1000, 100, 10, 0.01));
    /* 17 */ CASE(N = 91620, D = 10, gaps(100000, 100000, 50, 100, 25, 0.03));
    /* 18 */ CASE(N = 100000, D = 10, gaps(100000, 100000, 100, 123, 35, 0.01));
    // TC19: multiple gaps, same v
    /* 19 */ CASE(N = 100000, D = 10, gaps(100000, 100000, 0, 200, 18, 0.05), sameV(1, false));
    // TC20: multiple gaps, same v, both directions
    /* 20 */ CASE(N = 100000, D = 10, gaps(100000, 100000, 0, 250, 15, 0.04), sameV(2, true));
  }

  void reset() {
    X.clear();
    Y.clear();
    V.clear();
  }

  void random(int limit) {
    reset();
    for (int i = 0; i < N; ++i) {
      X.push_back(rnd.nextInt(0, limit));
      Y.push_back(rnd.nextInt(0, limit));
      V.push_back(rnd.nextInt(-limit, limit));
    }
  }

  void gaps(int maxx, int maxy, int maxv, int nd, int maxd, double p) {
    reset();

    // find nd gaps of size maxd randomly within [0..maxx]
    assert(maxx >= nd * maxd);
    vector<int> g;
    for (int i = 0; i < nd; ++i) {
      g.push_back(rnd.nextInt(0, maxx - nd*maxd));
    }
    sort(g.begin(), g.end());
    for (int i = 0; i < nd; ++i) {
      g[i] += i * maxd;
    }

    // there's p chances points will fall randomly
    for (int i = 0; i < N; ++i) {
      if (rnd.nextDouble(1) < p) {
        X.push_back(rnd.nextInt(0, maxx));
        Y.push_back(rnd.nextInt(0, maxy));
        V.push_back(rnd.nextInt(-maxv, maxv));
        continue;
      }
      int ng = rnd.nextInt(nd);
      int x = rnd.nextInt(g[ng], g[ng] + maxd);
      X.push_back(x);
      Y.push_back(rnd.nextInt(0, maxy));
      V.push_back(rnd.nextInt(-maxv, maxv));
    }
  }

  void sameV(int v, bool both) {
    for (int i = 0; i < N; ++i) {
      V[i] = v;
      if (both) {
        if (rnd.nextInt(2)) V[i] *= -1;
      }
    }
  }

  void permute(int maxv) {
    reset();
    for (int i = 0; i < N; ++i) {
      X.push_back(i+1);
      Y.push_back(i+1);
      V.push_back(rnd.nextInt(-maxv, maxv));
    }
    rnd.shuffle(X.begin(), X.end());
    rnd.shuffle(Y.begin(), Y.end());
  }

  void maxAnswer(int maxy, int maxv) {
    // divide into two: going north and south
    // all points fall within range [0, d],
    // and sorted with fastest below

    vector<int> northx, northy, northv, northi;
    vector<int> southx, southy, southv, southi;
    
    for (int i = 0; i < N; ++i) {
      if (rnd.nextInt(2)) {
        // north
        northx.push_back(rnd.nextInt(0, D));
        northy.push_back(rnd.nextInt(maxy / 2));
        northv.push_back(rnd.nextInt(1, maxv));
      } else {
        // south
        southx.push_back(rnd.nextInt(0, D));
        southy.push_back(rnd.nextInt(maxy / 2, maxy));
        southv.push_back(-rnd.nextInt(1, maxv));
      }
    }

    // sort by v
    sort(northy.begin(), northy.end());
    sort(northv.rbegin(), northv.rend());
    for (int i = 1; i < northx.size(); ++i) {
      if (northv[i] == northv[i-1]) {
        northy[i] = northy[i-1];
      }
    }
    sort(southy.rbegin(), southy.rend());
    sort(southv.begin(), southv.end());
    for (int i = 1; i < southx.size(); ++i) {
      if (southv[i] == southv[i-1]) {
        southy[i] = southy[i-1];
      }
    }

    // add all in temp
    vector<int> tempx, tempy, tempv, tempi;
    for (int i = 0; i < northx.size(); ++i) {
      tempx.push_back(northx[i]);
      tempy.push_back(northy[i]);
      tempv.push_back(northv[i]);
      tempi.push_back(tempi.size());
    }
    for (int i = 0; i < southx.size(); ++i) {
      tempx.push_back(southx[i]);
      tempy.push_back(southy[i]);
      tempv.push_back(southv[i]);
      tempi.push_back(tempi.size());
    }

    // shuffle before insertion
    rnd.shuffle(tempi.begin(), tempi.end());
    reset();
    for (int i = 0; i < N; ++i) {
      X.push_back(tempx[tempi[i]]);
      Y.push_back(tempy[tempi[i]]);
      V.push_back(tempv[tempi[i]]);
    }
  }

  void randomWithin(int minx, int maxx, int maxv) {
    reset();
    for (int i = 0; i < N; ++i) {
      X.push_back(rnd.nextInt(minx, maxx));
      Y.push_back(rnd.nextInt(0, 100000));
      V.push_back(rnd.nextInt(-maxv, maxv));
    }
  }
};
