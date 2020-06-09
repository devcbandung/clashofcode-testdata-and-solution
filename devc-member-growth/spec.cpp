#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, D;
    int ans;

    void InputFormat() {
        LINE(N, D);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(512);
    }

    void Constraints() {
        CONS(1 <= N && N <= 10000);
        CONS(1 <= D && D <= 10000);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void TestCases() {
        // Samples
        CASE(N = 9970, D = 50);
        CASE(N = 100, D = 100);
        // Test Cases
        CASE(N = 1, D = 1);
        CASE(N = 2879, D = 14);
        CASE(N = 5892, D = 7250);
        CASE(N = 1000, D = 100);
        CASE(N = 1001, D = 100);
        CASE(N = 999, D = 100);
    }
};