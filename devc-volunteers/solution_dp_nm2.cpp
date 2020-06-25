#include <bits/stdc++.h>
using namespace std;

#define MAXN 505

int n, m;
int a[MAXN], b[MAXN], dp[MAXN][MAXN], pv[MAXN][MAXN];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &a[i], &b[i]);
  }
  for (int i = 1; i <= n; ++i) {
    for (int k = 0; k <= m; ++k) {
      if (dp[i-1][k] > dp[i][0]) {
        dp[i][0] = dp[i-1][k];
        pv[i][0] = k;
      }
      for (int j = 1; j <= m; ++j) {
        if (j == k) continue;
        if (i < a[j] || b[j] < i) continue;
        if (dp[i-1][k] + 1 > dp[i][j]) {
          dp[i][j] = dp[i-1][k] + 1;
          pv[i][j] = k;
        }
      }
    }
  }
  int ans = 0, v = 0;
  for (int i = 0; i <= m; ++i) {
    if (dp[n][i] > ans) {
      ans = dp[n][i];
      v = i;
    }
  }
  // backtrack to construct solution
  vector<pair<int,int>> assignment;
  for (int i = n; i >= 1; --i) {
    if (v > 0) {
      assignment.emplace_back(i, v);
    }
    v = pv[i][v];
  }
  reverse(assignment.begin(), assignment.end());

  printf("%d\n", ans);
  for (auto a : assignment) {
    printf("%d %d\n", a.first, a.second);
  }

  return 0;
}
