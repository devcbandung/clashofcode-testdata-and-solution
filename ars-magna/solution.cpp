#include <bits/stdc++.h>
using namespace std;

int n, m;
string s[100100], t;

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
    sort(s[i].begin(), s[i].end());
  }
  sort(s, s + n);
  long long ans = 0;
  for (int j = 0; j < m; ++j) {
    cin >> t;
    sort(t.begin(), t.end());
    ans += upper_bound(s, s+n, t) - lower_bound(s, s+n, t);
  }
  printf("%lld\n", ans);
}