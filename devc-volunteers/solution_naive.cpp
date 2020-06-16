#include <bits/stdc++.h>
using namespace std;

#define MAXN 100000

int n, m, a[MAXN+5], b[MAXN+5], ans[MAXN+5];
vector<int> add[MAXN+5], rm[MAXN+5];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &a[i], &b[i]);
    add[a[i]].push_back(i);
    rm[b[i]].push_back(i);
  }

  int nans = 0;

  set<int> current;
  for (int d = 1; d <= n; ++d) {
    for (int x : add[d]) current.insert(x);

    for (int x : current) {
      if (x != ans[d-1]) {
        nans++;
        ans[d] = x;
        break;
      }
    }

    for (int x : rm[d]) {
      current.erase(current.find(x));
    }
  }

  printf("%d\n", nans);
  for (int d = 1; d <= n; ++d) {
    if (ans[d]) {
      printf("%d %d\n", d, ans[d]);
    }
  }
}