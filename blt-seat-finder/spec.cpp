#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  int TC, X, P, L;

  void InputFormat() {
    LINE(TC);
  }

  void OutputFormat() {
    LINE(X, P, L);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(0 <= TC && TC <= 11);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void TestCases() {
    // Samples
    CASE(TC = 0);
    CASE(TC = 1);
    // Test Cases
    for (int i = 2; i <= 11; ++i) {
      CASE(TC = i);
    }
  }
};