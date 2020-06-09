#include <tcframe/spec.hpp>
#include <cassert>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, ans;

  void InputFormat() {
    LINE(N);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(1 <= N && N <= 1000000);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void TestCases() {
    // Samples
    CASE(N = 4);
    // Test Cases
    CASE(N = 1);
    CASE(N = 1000000);
    for (int i = 1; i <= 48; i++) {
      CASE(randomN());
    }
  }

  void randomN() {
    N = rnd.nextInt(1, 1000000);
  }
};
