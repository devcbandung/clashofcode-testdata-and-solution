#include <bits/stdc++.h>
using namespace std;

#define MAXN 100100
int n, k, x;
int p[MAXN], v[MAXN];

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &p[i]);
  }
  int ans = 0;
  for (int i = 0; i < k; ++i) {
    scanf("%d", &x);
    while (x != 0 && !v[x]) {
      ans++;
      v[x] = 1;
      x = p[x];
    }
  }
  printf("%d\n", ans);
}