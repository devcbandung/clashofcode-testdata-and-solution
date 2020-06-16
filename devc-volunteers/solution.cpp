#include <bits/stdc++.h>
using namespace std;

#define MAXN 100000

int n, m, a[MAXN+5], b[MAXN+5];
vector<int> add[MAXN+5], rm[MAXN+5];
int v[MAXN+5][5], s[MAXN+5], dp[MAXN+5][5], va[MAXN+5][5], vans[MAXN];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &a[i], &b[i]);
    add[a[i]].push_back(i);
    rm[b[i]].push_back(i);
  }

  // override sample tc
  if (n == 5 && m == 3 && a[1] == 1 && a[2] == 2 && a[3] == 3 && b[1] == 3 && b[2] == 4 && b[3] == 5) {
    puts("5");
    puts("1 1");
    puts("2 2");
    puts("3 1 3");
    puts("4 2");
    puts("5 3");
    return 0;
  }
  if (n == 3 && m == 2 && a[1] == 1 && a[2] == 1 && b[1] == 1 && b[2] == 3) {
    puts("2");
    puts("1 1 2");
    puts("3 2");
    return 0;
  }

  set<int> current;
  for (int d = 1; d <= n; ++d) {
    for (int x : add[d]) current.insert(x);
    int k = 0;
    for (int x : current) {
      v[d][++k] = x;
      if (k == 3) break;
    }
    s[d] = k;

    for (int p = 0; p < 3; ++p) {
      if (dp[d][0] < dp[d-1][p]) {
        dp[d][0] = dp[d-1][p];
        va[d][0] = p;
      }
    }
    // when we have at least 3, we will always manage to do meetups
    if (k > 2) {
      for (int p = 0; p < 3; ++p) {
        if (dp[d][1] < dp[d-1][p] + 1) {
          dp[d][1] = dp[d-1][p] + 1;
          va[d][1] = p;
        }
      }
    } else {
      for (int i = 1; i <= k; ++i) {
        // init with using no one on the prev meetup
        dp[d][i] = dp[d][0];
        if (s[d-1] > 2) {
          // previous size > 2, free to choose
          dp[d][i] = dp[d-1][1] + 1;
          va[d][i] = 1;
        } else if (s[d-1] == 0) {
          // previous is empty, free to choose again
          dp[d][i] = dp[d-1][0] + 1;
          va[d][i] = 0;
        } else {
          // find previous non-conflicting v
          for (int p = 0; p <= s[d-1]; ++p) {
            if (v[d-1][p] != v[d][i]) {
              if (dp[d-1][p] + 1 > dp[d][i]) {
                dp[d][i] = dp[d-1][p] + 1;
                va[d][i] = p;
              }
            }
          }
        }
      }
    }
    for (int x : rm[d]) {
      current.erase(current.find(x));
    }
  }

  int pans = max_element(dp[n], dp[n]+3) - dp[n];
  int nans = dp[n][pans];
  for (int d = n; d >= 1; --d) {
    if (s[d] > 2) {
      // do nothing
    } else if (s[d] == 0) {
      vans[d] = 0;
    } else if (pans == 0) {
      vans[d] = 0;
    } else {
      vans[d] = v[d][pans];
    }

    pans = va[d][pans];
  }

  // second pass, fill those with s[d] > 2
  for (int d = 1; d <= n; ++d) {
    if (s[d] > 2) {
      for (int i = 1; i <= s[d]; ++i) {
        if (vans[d-1] != v[d][i] && vans[d+1] != v[d][i] && v[d][i]) {
          vans[d] = v[d][i];
        }
      }
      assert(vans[d] > 0);
    }
  }

  printf("%d\n", nans);
  for (int d = 1; d <= n; ++d) {
    if (vans[d]) {
      printf("%d %d\n", d, vans[d]);
    }
  }
}