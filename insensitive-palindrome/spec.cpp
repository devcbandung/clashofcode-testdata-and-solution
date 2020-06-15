#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  string s;
  vector<string> ans;

  void InputFormat() {
    LINE(s);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(1 <= s.size() && s.size() <= 10000);
    CONS(alphabet(s));
  }

  bool alphabet(const string &s) {
    for (char c : s) {
      if (!('a' <= c && c <= 'z') && !('A' <= c && c <= 'Z')) return false;
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void TestCases() {
    // Samples
    CASE(s = "KasurRusak");
    CASE(s = "KasuRRusaK");
    CASE(s = "kasur");
    // Test Cases
    CASE(s = "aa");
    CASE(s = "aA");
    CASE(s = "X");
    CASE(s = "xyzx");
    CASE(s = "xyX");
    CASE(s = "SaRaS");
    CASE(palindrome(10000), change({5000}), rndcase(true));
    CASE(palindrome(10000), change({5000}), rndcase(false));
    CASE(palindrome(9999), change({4999}), rndcase(true));
    CASE(palindrome(9999), change({4999}), rndcase(false));
    CASE(palindrome(9999), change({4998}), rndcase(true));
    CASE(palindrome(9999), change({4998}), rndcase(false));
    CASE(palindrome(10000), rndcase(true));
    CASE(palindrome(10000), rndcase(false));
    for (int i = 0; i < 10; ++i) {
      CASE(palindrome(rnd.nextInt(1, 10000)), rndcase(true));
      CASE(palindrome(rnd.nextInt(1, 10000)), rndcase(false));
      CASE(palindrome(rnd.nextInt(1, 10000)), rndchange(), rndcase(true));
      CASE(palindrome(rnd.nextInt(1, 10000)), rndchange(), rndcase(false));
    }
  }

  void palindrome(int n) {
    s = string(n, 'a');
    for (int i = 0; i <= (n+1)/2; ++i) {
      s[i] = 'a' + rnd.nextInt(26);
      s[n-1-i] = s[i];
    }
  }

  void change(vector<int> xx) {
    for (int x : xx) {
      char old = s[x];
      do {
        s[x] = 'a' + rnd.nextInt(26);
      } while (old == s[x]);
    }
  }

  void rndchange() {
    vector<int> toChange;
    double p = rnd.nextDouble(1);
    for (int i = 0; i < s.length(); ++i) {
      if (rnd.nextDouble(1) < p) {
        toChange.push_back(i);
      }
    }
    change(toChange);
  }

  void rndcase(bool sensitive) {
    int n = s.length();
    for (int i = 0; i < (n+1)/2; ++i) {
      bool toUpper = rnd.nextInt(2);
      if (sensitive) {
        if (toUpper) {
          s[i] += 'A' - 'a';
          if (i != n-1-i) s[n-1-i] += 'A' - 'a';
        }
      } else {
        if (toUpper) {
          s[i] += 'A' - 'a';
        }
        if (i != n-1-i) {
          bool xToUpper = rnd.nextInt(2);
          if (xToUpper) {
            s[n-1-i] += 'A' - 'a';
          }
        }
      }
    }
  }
};