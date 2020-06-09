#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000100
#define MOD 1000000007

int n;
int f[MAXN];

int main() {
  scanf("%d", &n);
  f[1] = f[2] = 1;
  for (int i = 3; i <= n+2; ++i) {
    f[i] = f[i-1] + f[i-2];
    f[i] %= MOD;
  }
  printf("%d\n", f[n+2] - 1);
}