#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N;
  vector<int> D;
  int ans;

  void InputFormat() {
    LINE(N);
    LINE(D % SIZE(N));
  }

  void OutputFormat() {
    LINE(N);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(1 <= N && N <= 1000000);
    CONS(validD());
  }

  bool validD() {
    if (D.size() != N) return false;
    int sum = 0;
    for (int x : D) {
      if (abs(x) < 1 || abs(x) > 1000) return false;
      sum += x;
      if (sum < 0) return false;
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void TestCases() {
    // Samples
    CASE(N = 8, D = {1, 4, 9, -2, -1, 6, -4, 1});

    // Test Cases
    // manual
    CASE(N = 1, D = {123});
    CASE(N = 6, D = {14, 17, -31, 25, 7, -5});
    // Pure random
    CASE(N = 1000000, random());
    for (int i = 0; i < 7; ++i) {
      CASE(N = rnd.nextInt(1, 1000000), random());
    }
  }

  void random() {
    int sum = 0;
    D.clear();
    for (int i = 0; i < N; ++i) {
      int x = rnd.nextInt(1, 1000);
      if (sum >= x) {
        if (rnd.nextInt(2)) x = -x;
      }
      D.push_back(x);
    }
  }
};