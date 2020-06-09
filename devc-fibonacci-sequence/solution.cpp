#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000100
#define MOD 1000000007

int n;
int f[MAXN];

int main() {
  scanf("%d", &n);
  f[1] = f[2] = 1;
  for (int i = 3; i <= n; ++i) {
    f[i] = f[i-1] + f[i-2];
    f[i] %= MOD;
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += f[i];
    ans %= MOD;
  }
  printf("%d\n", ans);
}