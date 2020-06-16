#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  string T;
  double ans;

  void InputFormat() {
    LINE(T);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(validTime());
  }

  bool validTime() {
    if (T.length() != 5) return false;
    if (T[0] < '0' || T[0] > '9') return false;
    if (T[1] < '0' || T[1] > '9') return false;
    if (T[2] != ':') return false;
    if (T[3] < '0' || T[3] > '5') return false;
    if (T[4] < '0' || T[4] > '9') return false;
    int h = 10 * (T[0] - '0') + (T[1] - '0');
    return 0 <= h && h <= 23;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  char buffer[10];
  void TestCases() {
    // Samples
    CASE(T = "03:00");
    CASE(T = "15:00");
    CASE(T = "00:00");
    CASE(T = "00:01");
    // Test Cases
    CASE(T = "18:00");
    CASE(T = "18:01");
    CASE(T = "06:02");
    CASE(T = "23:59");
    CASE(T = "02:10");
    CASE(T = "02:11");
    CASE(T = "02:12");
    CASE(T = "14:13");
    for (int i = 0; i < 12; ++i) {
      CASE(sprintf(buffer, "%02d:%02d", rnd.nextInt(24), rnd.nextInt(60)), T = buffer);
    }
  }
};