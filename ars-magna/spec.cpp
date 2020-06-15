#include <tcframe/spec.hpp>
#include <assert.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, M;
  vector<string> S, T;
  long long ans;

  void InputFormat() {
    LINE(N, M);
    LINES(S) % SIZE(N);
    LINES(T) % SIZE(M);
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
    CONS(1 <= M && M <= 100000);
    CONS(S.size() == N);
    CONS(T.size() == M);
    CONS(notEmpty(S));
    CONS(notEmpty(T));
    CONS(alphabet(S));
    CONS(alphabet(T));
    CONS(len(S) + len(T) <= 1000000);
  }

  bool alphabet(const vector<string> &a) {
    for (string s : a) {
      for (char c : s) {
        if (!('a' <= c && c <= 'z')) return false;
      }
    }
    return true;
  }

  bool notEmpty(const vector<string> &a) {
    for (string s : a) {
      if (s.empty()) return false;
    }
    return true;
  }

  int len(const vector<string> &a) {
    long long total = 0;
    for (string s : a) {
      total += s.length();
    }
    return total;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void TestCases() {
    // Samples
    CASE(N = 5, M = 4, S = {"acep", "sandra", "ismail", "zaky", "mirza"}, T = {"fb", "cape", "pace", "liamsi"});
    CASE(N = 4, M = 4, S = {"a", "a", "a", "b"}, T = {"a", "a", "b", "b"});

    // Test Cases
    // 40% = 10 tc
    // max ans
    CASE(N = 1000, M = 1000, allsame(20000));
    CASE(N = 1000, M = 1000, maxlen(10));
    for (int i = 0; i < 8; ++i) {
      CASE(N = rnd.nextInt(1, 1000), M = rnd.nextInt(1, 1000), maxlen(10));
    }

    // 60% = 15 tc
    // max length (999999)(1)
    CASE(N = 1, M = 1, S = {randomstring(999999)}, T = {randomstring(1)});
    // max pair (500000)(500000)
    CASE(N = 1, M = 1, S = {randomstring(500000)}, T = {shufflestring(S[0])});
    // max ans (1x100000)(1x100000)
    CASE(N = 100000, M = 100000, allsame(1000000));
    // huge ans (1~10x100000)(1-10x100000)
    CASE(N = 100000, M = 100000, maxlen(3));
    // huge strings (50000x10)(50000x10)
    CASE(N = 10, M = 10, clear(), pairlen(vector<int>(10, 50000), vector<int>(10, 50000)));
    // 7 tc: random combination of:
    //       - several long strings with its pair
    //       - fill the rest with random short strings
    CASE(N = 100000, M = 100000, random());
    CASE(N = 100000, M = 100000, random());
    for (int i = 0; i < 8; ++i) {
      CASE(N = rnd.nextInt(1, 100000), M = rnd.nextInt(1, 100000), random());
    }
  }

  void clear() {
    S.clear();
    T.clear();
  }

  string randomstring(int n) {
    string s(n, '.');
    for (int i = 0; i < n; ++i) {
      s[i] = 'a' + rnd.nextInt(26);
    }
    return s;
  }

  string shufflestring(const string &s) {
    string t = s;
    rnd.shuffle(t.begin(), t.end());
    return t;
  }

  void allsame(int total) {
    clear();

    int len = total / (N + M);
    string s = randomstring(len);
    for (int i = 0; i < N; ++i) {
      S.push_back(shufflestring(s));
    }
    for (int i = 0; i < M; ++i) {
      T.push_back(shufflestring(s));
    }
  }

  void maxlen(int mlen) {
    clear();

    vector<int> lens(N, 0), lent(M, 0);
    for (int i = 0; i < N; ++i) {
      lens[i] = rnd.nextInt(1, mlen);
    }
    for (int i = 0; i < M; ++i) {
      lent[i] = rnd.nextInt(1, mlen);
    }
    pairlen(lens, lent);

    // shuffle the end result
    rnd.shuffle(S.begin(), S.end());
    rnd.shuffle(T.begin(), T.end());
  }

  void random() {
    clear();

    // determine total length of each list
    int totals = rnd.nextInt(400000, 600000);
    int totalt = 1000000 - totals;

    // reserve for some big strings pair
    pair<int, int> big = randombig(totals, totalt);

    // distribute totals and totalt into N and M int each
    vector<int> lens = divide(totals - big.first, N - S.size());
    vector<int> lent = divide(totalt - big.second, M - T.size());

    pairlen(lens, lent);

    // shuffle the end result
    rnd.shuffle(S.begin(), S.end());
    rnd.shuffle(T.begin(), T.end());
  }

  void pairlen(vector<int> lens, vector<int> lent) {
    sort(lens.begin(), lens.end());
    sort(lent.begin(), lent.end());

    // randomize strings for each length, while making sure we make some pairs
    int is = 0, it = 0;
    for (int len = 1; len <= 1000000; ++len) {
      int ss = is, st = it;
      while (is < lens.size() && lens[is] == len) is++;
      while (it < lent.size() && lent[it] == len) it++;
      // [ss, is) and [st, it)
      while (ss < is || st < it) {
        int xs = rnd.nextInt(0, is-ss);
        int xt = rnd.nextInt(0, it-st);
        string _ = randomstring(len);
        for (int i = 0; i < xs; ++i) S.push_back(shufflestring(_));
        for (int i = 0; i < xt; ++i) T.push_back(shufflestring(_));
        ss += xs;
        st += xt;
      }
    }
  }

  pair<int, int> randombig(int totals, int totalt) {
    int len = rnd.nextInt(50000, 150000);
    string s = randomstring(len);
    S.push_back(shufflestring(s));
    T.push_back(shufflestring(s));
    return make_pair(len, len);
  }

  vector<int> divide(int total, int n) {
    assert(n <= total);
    vector<int> a(total, 0);
    for (int i = 0; i < total; ++i) {
      a[i] = i+1;
    }
    rnd.shuffle(a.begin(), a.end());
    a.resize(n);
    sort(a.begin(), a.end());
    for (int i = n-1; i > 0; --i) {
      a[i] -= a[i-1];
    }
    return a;
  }

};