#include <tcframe/spec.hpp>
#include <cassert>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  vector<int> A, X;
  int N, K, ans;

  void InputFormat() {
    LINE(N, K);
    LINE(A % SIZE(N));
    LINE(X % SIZE(K));
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(1 <= N && N <= 100000);
    CONS(1 <= K && K <= N);
    CONS(validTree());
    CONS(validSet());
  }

  bool validTree() {
    if (A.size() != N) return false;
    if (A[0] != 0) return false;
    for (int i = 1; i < N; ++i) {
      if (A[i] >= i+1 || A[i] < 1) return false;
    }
    return true;
  }

  bool validSet() {
    if (X.size() != K) return false;
    std::set<int> s;
    for (int x : X) {
      if (s.find(x) != s.end()) return false;
      s.insert(x);
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void TestCases() {
    // Samples
    CASE(N = 8, K = 3,
      A = {0, 1, 1, 2, 2, 2, 6, 6},
      X = {3, 4, 8}
    );
    // Test Cases
    CASE(N = 1, K = 1, A = {0}, X = {1});
    CASE(N = 528, K = 79, randomTree());
    CASE(N = 1000, K = 850, line());
    CASE(N = 1000, K = 900, randomLongTree());
    CASE(N = 1000, K = 950, randomLongTree());
    CASE(N = 50000, K = 200, randomTree());
    CASE(N = 100000, K = 50000, randomLongTree());
    CASE(N = 100000, K = 70000, randomLongTree());
    CASE(N = 100000, K = 85000, randomLongTree());
    CASE(N = 100000, K = 90000, line());
  }

  void randomTree() {
    A.clear();
    X.clear();
    A.push_back(0);
    set<int> p;
    for (int i = 2; i <= N; ++i) {
      int x = rnd.nextInt(1, i-1);
      A.push_back(x);
      p.insert(x);
    }
    randomX(N);
  }

  void randomLongTree() {
    A.clear();
    X.clear();
    int T = rnd.nextInt(N * 1/2, N * 3/4);
    for (int i = 1; i <= T; ++i) {
      A.push_back(i-1);
    }
    for (int i = T+1; i <= N; ++i) {
      A.push_back(rnd.nextInt(1, i-1));
    }
    randomX(N - rnd.nextInt((N - K) / 2));
  }

  void line() {
    A.clear();
    X.clear();
    for (int i = 1; i <= N; ++i) {
      A.push_back(i-1);
    }
    randomX(N - rnd.nextInt((N - K) / 2));
  }

  void randomX(int limit) {
    vector<int> x;
    for (int i = 1; i <= limit; ++i) {
      x.push_back(i);
    }
    rnd.shuffle(x.begin(), x.end());
    for (int i = 0; i < K; ++i) {
      X.push_back(x[i]);
    }
  }
};
