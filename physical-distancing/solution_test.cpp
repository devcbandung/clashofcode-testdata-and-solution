#include <bits/stdc++.h>
using namespace std;

#define MAXN 100100

int n, d, x[MAXN], y[MAXN], v[MAXN];

// check whether distance((x1, y1), (x2, y2)) <= d
bool checkd(int x1, int y1, int x2, int y2) {
  long long a = (long long)(x1 - x2) * (x1 - x2) + (long long)(y1 - y2) * (y1 - y2);
  long long b = (long long)d * d;
  return a <= b;
}

bool violate(int x1, int y1, int v1, int x2, int y2, int v2) {
  if (v1 < 0) {
    // flip everything
    return violate(x1, y2, -v1, x2, y1, -v2);
  }
  // now v1 >= 0
  if (v2 >= 0) {
    if (y1 <= y2) {
      if (v1 <= v2) {
        return checkd(x1, y1, x2, y2);
      } else {
        return abs(x1 - x2) <= d;
      }
    } else {
      if (v1 >= v2) {
        return checkd(x1, y1, x2, y2);
      } else {
        return abs(x1 - x2) <= d;
      }
    }
  } else {
    if (y1 >= y2) {
      return checkd(x1, y1, x2, y2);
    } else {
      return abs(x1 - x2) <= d;
    }
  }
  assert(false);
}

// brute force N^2
int main() {
  scanf("%d%d", &n, &d);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d", &x[i], &y[i], &v[i]);
  }

  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (violate(x[i], y[i], v[i], x[j], y[j], v[j])) {
        ans++;
        printf("(%d, %d) violate!\n", i, j);
      }
    }
  }

  printf("%lld\n", ans);
}