#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, total = 0, ans = 0, x;
  scanf("%d", &n);
  while (n--) {
    scanf("%d", &x);
    total += x;
    if (total > ans) ans = total;
  }
  printf("%d\n", ans);
}
