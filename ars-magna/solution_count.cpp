#include <bits/stdc++.h>
using namespace std;

int n, m;
char s[1000005];
typedef vector<int> vint;

vint countingsort(char *s) {
  vint c(26, 0);
  int n = strlen(s);
  for (int i = 0; i < n; ++i) {
    c[s[i] - 'a']++;
  }
  return c;
}

int main() {
  scanf("%d%d", &n, &m);
  map<vint, int> c;
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    c[countingsort(s)]++;
  }
  long long ans = 0;
  for (int j = 0; j < m; ++j) {
    scanf("%s", s);
    ans += c[countingsort(s)];
  }
  printf("%lld\n", ans);
}