#include <bits/stdc++.h>
using namespace std;

int n, m;
string s[100100], t[100100];

bool anagram(const string &a, const string &b) {
  vector<int> ca(26, 0), cb(26, 0);
  for (char c : a) ca[c - 'a']++;
  for (char c : b) cb[c - 'a']++;
  for (int i = 0; i < 26; ++i) {
    if (ca[i] != cb[i]) return false;
  }
  return true;
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
  }
  for (int i = 0; i < m; ++i) {
    cin >> t[i];
  }
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (anagram(s[i], t[j])) ans++;
    }
  }
  printf("%lld\n", ans);
}