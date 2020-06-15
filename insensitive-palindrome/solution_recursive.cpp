#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(string s) {
  int n = s.length();
  if (n < 2) {
    return true;
  }
  if (s.front() != s.back()) {
    return false;
  }
  return isPalindrome(s.substr(1, n-2));
}

string toUpper(string s) {
  int n = s.length();
  string upper(n, 'a');
  for (int i = 0; i < n; ++i) {
    upper[i] = toupper(s[i]);
  }
  return upper;
}

int main() {
  string s;
  cin >> s;
  if (isPalindrome(s)) {
    cout << "sensitive palindrome" << endl;
  } else if (isPalindrome(toUpper(s))) {
    cout << "insensitive palindrome" << endl;
  } else {
    cout << "not a palindrome" << endl;
  }
  return 0;
}
