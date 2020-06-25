/*
  Memory Complexity: O(N + MAXX)
  Time Complexity: O(ND log N)
*/
#include <bits/stdc++.h>
using namespace std;

template<typename T>
class BIT {
public:
  BIT(int n): v(vector<T>(n+1)), n(n) {}
  T sum(int k) {
    T s = 0;
    for (int i = k; i > 0; i -= (i & -i)) {
      s += this->v[i];
    }
    return s;
  }
  T sum(int l, int r) {
    return this->sum(r) - this->sum(l-1);
  }
  void update(int k, T v) {
    for (int i = k; i <= this->n; i += (i & -i)) {
      this->v[i] += v;
    }
  }
private:
  vector<T> v;
  int n;
};

class RangeTree {
public:
  RangeTree(): p(vector<int>()), n(0), bit(BIT<int>(0)) {}
  RangeTree(const vector<int> &p): p(p), n(p.size()), bit(BIT<int>(p.size())) {}

  int lower_bound(int x) {
    return std::lower_bound(p.begin(), p.end(), x) - p.begin();
  }

  int upper_bound(int x) {
    return std::upper_bound(p.begin(), p.end(), x) - p.begin();
  }

  void add(int x, int v) {
    int i = this->lower_bound(x);
    assert(i < n);
    assert(p[i] == x);
    bit.update(i+1, v);
  }

  // range sum [x, y] INCLUSIVELY
  int sum(int x, int y) {
    if (n == 0) return 0;
    int xi = this->lower_bound(x);
    int yi = this->upper_bound(y) - 1;
    if (xi > yi) {
      assert(xi == yi+1);
      return 0;
    }
    return bit.sum(xi+1, yi+1);
  }

private:
  vector<int> p;
  int n;
  BIT<int> bit;
};

#define MAXN 100000
#define MAXX 100000
#define MAXD 10

int n, d, x[MAXN+5], y[MAXN+5], v[MAXN+5], dir[MAXN+5];
int dt[MAXD+5];
vector<int> p[2], py[2][MAXX+5];
RangeTree rt[2][MAXX+5], cpm[2][MAXX+5];

// check whether distance((x1, y1), (x2, y2)) <= d
bool checkd(int x1, int y1, int x2, int y2) {
  long long a = (long long)(x1 - x2) * (x1 - x2) + (long long)(y1 - y2) * (y1 - y2);
  long long b = (long long)d * d;
  return a <= b;
}

int main() {
  scanf("%d%d", &n, &d);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d", &x[i], &y[i], &v[i]);
  }

  // precompute distance threshold table
  for (int i = 0; i <= d; ++i) {
    for (int j = 0; j <= d+1; ++j) {
      if (!checkd(0, 0, i, j)) {
        dt[i] = j-1;
        assert(dt[i] >= 0);
        assert(checkd(0, 0, i, dt[i]));
        break;
      }
    }
  }

  // group by direction
  // dir = 0: v < 0 / south
  // dir = 1: v >= 0 / north
  for (int i = 0; i < n; ++i) {
    if (v[i] < 0) {
      dir[i] = 0;
      v[i] = -v[i];
      p[0].push_back(i);
    } else {
      dir[i] = 1;
      p[1].push_back(i);
    }
  }

  // process points going in the same direction first
  // sort by v
  for (int di = 0; di < 2; ++di) {
    sort(p[di].begin(), p[di].end(), [&](int a, int b) -> bool {
      return v[a] < v[b];
    });
    for (int i : p[di]) {
      py[di][x[i]].push_back(y[i]);
    }
    for (int i = 0; i <= MAXX; ++i) {
      sort(py[di][i].begin(), py[di][i].end());
      py[di][i].resize(unique(py[di][i].begin(), py[di][i].end()) - py[di][i].begin());
      rt[di][i] = RangeTree(py[di][i]);
      cpm[di][i] = RangeTree(py[di][i]);
    }
  };

  long long ans = 0;

  // going up first
  for (int di = 0; di < 2; ++di) {
    for (int t = 0; t < p[di].size();) {
      // we need to process points within the same v together
      int cv = v[p[di][t]];
      vector<int> cp;
      while (t < p[di].size() && v[p[di][t]] == cv) {
        cp.push_back(p[di][t]);
        t++;
      }
      // query for every points in cp
      for (int i : cp) {
        long long addum = 0;
        for (int cx = max(0, x[i] - d); cx <= min(MAXX, x[i] + d); cx++) {
          int ly, ry;
          if (di == 0) {
            ly = 0;
            ry = min(MAXX, y[i] + dt[abs(cx - x[i])]);
          } else {
            ly = max(0, y[i] - dt[abs(cx - x[i])]);
            ry = MAXX;
          }
          int sum = rt[di][cx].sum(ly, ry);
          addum += sum;
        }
        ans += addum;
      }
      // count pair of points in cp that has distance <= d
      long long mans = 0;
      for (int i : cp) {
        for (int cx = max(0, x[i] - d); cx <= min(MAXX, x[i] + d); cx++) {
          int ly = max(0, y[i] - dt[abs(cx - x[i])]);
          int ry = min(MAXX, y[i] + dt[abs(cx - x[i])]);
          mans += cpm[di][cx].sum(ly, ry);
        }
        cpm[di][x[i]].add(y[i], 1);
      }
      for (int i : cp) {
        cpm[di][x[i]].add(y[i], -1);
      }
      ans += mans;
      // add cp to rt
      for (int i : cp) {
        rt[di][x[i]].add(y[i], 1);
      }
    }
  }

  // now pair of points with different directions
  for (int i : p[0]) {
    for (int cx = max(0, x[i] - d); cx <= min(MAXX, x[i] + d); cx++) {
      int ly = 0;
      int ry = min(MAXX, y[i] + dt[abs(cx - x[i])]);
      ans += rt[1][cx].sum(ly, ry);
    }
  }

  printf("%lld\n", ans);
}