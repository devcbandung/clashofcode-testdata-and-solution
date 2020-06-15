#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  int X, P, L;
  vector<vector<char>> ans;

  void InputFormat() {
    LINE(X, P, L);
  }

  void OutputFormat() {
    GRID(ans) % SIZE(X*P, X*L);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(1 <= X && X <= 20);
    CONS(1 <= P && P <= 20);
    CONS(1 <= L && L <= 20);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void TestCases() {
    // Samples
    CASE(X = 3, P = 2, L = 4);
    CASE(X = 5, P = 3, L = 2);
    // Test Cases
    CASE(X = 1, P = 1, L = 1);
    CASE(X = 20, P = 20, L = 20);
    for (int i = 0; i < 8; ++i) {
      CASE(X = rnd.nextInt(1, 20), P = rnd.nextInt(1, 20), L = rnd.nextInt(1, 20));
    }
  }
};