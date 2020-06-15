#include <bits/stdc++.h>
using namespace std;

int n, m;
string s[100100], t;
typedef vector<int> vint;

vint countingsort(const string &s) {
  vint c(26, 0);
  for (char ch : s) {
    c[ch - 'a']++;
  }
  return c;
}

int main() {
  cin >> n >> m;
  map<vint, int> c;
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
    c[countingsort(s[i])]++;
  }
  long long ans = 0;
  for (int j = 0; j < m; ++j) {
    cin >> t;
    ans += c[countingsort(t)];
  }
  printf("%lld\n", ans);
}