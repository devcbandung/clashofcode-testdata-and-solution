#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, d;
  scanf("%d%d", &n, &d);
  printf("%d\n", (10000 - n + d - 1) / d);
}