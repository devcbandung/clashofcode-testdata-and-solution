#include <bits/stdc++.h>
using namespace std;

int n;
char s[10100];

char toUpper(char c) {
  if ('a' <= c && c <= 'z') {
    return c + 'A' - 'a';
  }
  return c;
}

int main() {
  scanf("%s", s);
  n = strlen(s);
  bool palindrome = true;
  bool sensitive = true;
  for (int l = 0, r = n-1; l < r; ++l, --r) {
    if (s[l] != s[r]) {
      sensitive = false;
      if (toUpper(s[l]) != toUpper(s[r])) {
        palindrome = false;
      }
    }
  }
  if (!palindrome) {
    puts("not a palindrome");
  } else if (sensitive) {
    puts("sensitive palindrome");
  } else {
    puts("insensitive palindrome");
  }
}