#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, d;
  scanf("%d%d", &n, &d);
  int days = 0;
  while (n < 10000) {
    n += d;
    days++;
  }
  printf("%d\n", days);
}