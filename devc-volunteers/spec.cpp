#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, M;
  vector<int> A, B;
  int ans;
  vector<int> dans;
  vector<vector<int>> vans;

  void InputFormat() {
    LINE(N, M);
    LINES(A, B) % SIZE(M);
  }

  void OutputFormat() {
    LINE(ans);
    LINES(dans, vans);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(1 <= N && N <= 100000);
    CONS(1 <= M && M <= 100000);
    CONS(validRange());
  }

  bool validRange() {
    if (A.size() != M) return false;
    if (B.size() != M) return false;
    for (int i = 0; i < M; ++i) {
      if (A[i] < 1 || A[i] > N) return false;
      if (B[i] < 1 || B[i] > N) return false;
      if (A[i] > B[i]) return false;
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void TestCases() {
    // Samples
    CASE(N = 5, M = 3, A = {1, 2, 3}, B = {3, 4, 5});
    CASE(N = 3, M = 2, A = {1, 1}, B = {1, 3});
    // Test Cases
    // 50%: N, M <= 500

    // manual
    // 0       10        20        30        40        50        60        70
    // 1234567890123456789012345678901234567890123456789012345678901234567890
    // ..Xx...xX..xX....xXxX..Xx...xXxXx............Xx....Xx..XxXx....Xx.....
    // ..xXxXxX...XxXxXxX.....xXxXxX..yYy.xXYyYyY....XxXxXx......XxXxXxX.....
    // ................................zZzZ...zZ.............................
    CASE(N = 70, M = 20,
      A = {3, 3, 8, 12, 12, 18, 24, 24, 29, 32, 33, 36, 38, 40, 46, 47, 52, 56, 59, 64},
      B = {4, 8, 9, 13, 18, 21, 25, 29, 33, 34, 36, 37, 42, 41, 47, 52, 53, 59, 65, 65}
    );
    CASE(N = 500, M = 500, maxboundary());
    CASE(N = 500, M = 500, random(1));
    CASE(N = 500, M = 500, random(2));
    CASE(N = 500, M = 500, random(3));
    CASE(N = 500, M = 500, random(4));
    CASE(N = 500, M = 500, random(0));
    for (int i = 0; i < 8; ++i) {
      CASE(N = rnd.nextInt(100, 500), M = rnd.nextInt(100, 500), random(0));
    }

    // 50%, N, M <= 100000
    CASE(N = 100000, M = 100000, maxboundary());
    CASE(N = 100000, M = 100000, random(1));
    CASE(N = 100000, M = 100000, random(2));
    CASE(N = 100000, M = 100000, random(2));
    CASE(N = 100000, M = 100000, random(3));
    CASE(N = 100000, M = 100000, random(4));
    CASE(N = 100000, M = 100000, random(0));
    for (int i = 0; i < 4; ++i) {
      CASE(N = rnd.nextInt(10000, 100000), M = rnd.nextInt(10000, 100000), random(rnd.nextInt(1, 3)));
      CASE(N = rnd.nextInt(10000, 100000), M = rnd.nextInt(10000, 100000), random(0));
    }
  }

  void clear() {
    A.clear();
    B.clear();
  }

  void realrandom() {
    clear();

    N = rnd.nextInt(1, 100000);
    M = rnd.nextInt(1, 100000);
    for (int i = 0; i < M; ++i) {
      A.push_back(rnd.nextInt(1, N));
      B.push_back(rnd.nextInt(1, N));
      if (A[i] > B[i]) swap(A[i], B[i]);
    }
  }

  vector<int> randominrange(int l, int r, int n) {
    vector<int> v;
    for (int i = 0; i < n; ++i) {
      v.push_back(rnd.nextInt(l, r-n+1));
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < n; ++i) {
      v[i] += i;
    }
    return v;
  }

  void random(int nrange) {
    clear();
    if (nrange == 0) {
      nrange = rnd.nextInt(2, floor(sqrt(N)));
    }

    vector<int> rx = randominrange(1, N, nrange*2);
    vector<pair<int,int>> ranges;
    for (int i = 0; i < nrange; ++i) {
      ranges.emplace_back(rx[2*i], rx[2*i+1]);
    }

    vector<pair<int, int>> temp;
    for (int ir = 0; ir < nrange; ++ir) {
      int lrange = ranges[ir].first;
      int rrange = ranges[ir].second;
      int prevlrange = ir == 0 ? 1 : ranges[ir-1].second+1;
      int nextrrange = ir == nrange-1 ? N : ranges[ir+1].first-1;

      vector<int> p = randominrange(lrange, rrange, rnd.nextInt(1, (rrange-lrange+1)/2));
      vector<int> current;
      int ncurrent = rnd.nextInt(1, 2);
      for (int i = 0; i < ncurrent; ++i) {
        current.push_back(rnd.nextInt(prevlrange, lrange == prevlrange ? lrange : lrange-1));
      }

      for (int x : p) {
        assert(ncurrent == current.size());
        if (ncurrent == 0) {
          // only available operation: add
          current.push_back(x);
          ncurrent++;
        } else if (ncurrent == 1) {
          // 0.1: change
          // 0.6: add
          // 0.3: remove
          double p = rnd.nextDouble(1);
          if (p < 0.1) {
            temp.emplace_back(current[0], max(x-1, lrange));
            current[0] = x;
          } else if (p < 0.7) {
            current.push_back(x);
            ncurrent++;
          } else {
            temp.emplace_back(current[0], x);
            current.pop_back();
            ncurrent = 0;
          }
        } else if (ncurrent == 2) {
          // 0.4: change
          //      0.1: change both
          // 0.6: remove
          double p = rnd.nextDouble(1);
          if (p < 0.4) {
            double q = rnd.nextDouble(1);
            if (q < 0.9) {
              int i = (q < 0.45) ? 0 : 1;
              temp.emplace_back(current[i], max(x-1, lrange));
              current[i] = x;
            } else {
              for (int i = 0; i < 2; ++i) {
                temp.emplace_back(current[i], max(x-1, lrange));
                current[i] = x;
              }
            }
          } else {
            int i = rnd.nextInt(2);
            temp.emplace_back(current[i], x);
            current.erase(current.begin()+i);
            ncurrent--;
          }
        }
      }

      for (int x : current) {
        temp.emplace_back(x, rnd.nextInt(nextrrange == rrange ? rrange : rrange+1, nextrrange));
      }
      // put random small ranges
      int smol = rnd.nextInt(0, floor(log(rrange-lrange+1)/log(2)));
      for (int x = 0; x < smol; ++x) {
        int l = rnd.nextInt(lrange, rrange);
        int r = l + rnd.nextInt(2);
        if (r > rrange) r = rrange;
        temp.emplace_back(l, r);
      }
    }
    if (temp.size() > M) {
      rnd.shuffle(temp.begin(), temp.end());
      temp.resize(M);
    }

    while (temp.size() < M) {
      while (true) {
        int ir = rnd.nextInt(0, nrange);
        int lr = 1, rr = N;
        if (ir == 0) {
          if (ranges[0].first == 1) continue;
          lr = rnd.nextInt(1, ranges[0].first);
          rr = rnd.nextInt(1, ranges[0].first);
        } else if (ir == nrange) {
          if (ranges[nrange-1].second == N) continue;
          lr = rnd.nextInt(ranges[nrange-1].second, N);
          rr = rnd.nextInt(ranges[nrange-1].second, N);
        } else {
          if (ranges[ir-1].second == ranges[ir].first - 1) continue;
          lr = rnd.nextInt(ranges[ir-1].second + 1, ranges[ir].first - 1);
          rr = rnd.nextInt(ranges[ir-1].second + 1, ranges[ir].first - 1);
        }
        if (lr > rr) swap(lr, rr);
        temp.emplace_back(lr, rr);
        break;
      }
    }

    rnd.shuffle(temp.begin(), temp.end());
    clear();
    for (auto p : temp) {
      A.push_back(p.first);
      B.push_back(p.second);
    }
  }
  
  void maxboundary() {
    // [1..N]
    // [3..X] * ~M/2
    // [Y..N-2] * ~M/2
    vector<pair<int, int>> temp;
    temp.emplace_back(1, N);

    int x = N/2-10;
    int y = N/2+10;
    int m1 = M/2;
    int m2 = M - 1 - m1;
    for (int i = 0; i < m1; ++i) {
      temp.emplace_back(3, x);
    }
    for (int i = 0; i < m2; ++i) {
      temp.emplace_back(y, N-2);
    }

    rnd.shuffle(temp.begin(), temp.end());
    clear();
    for (auto p : temp) {
      A.push_back(p.first);
      B.push_back(p.second);
    }
  }
};
