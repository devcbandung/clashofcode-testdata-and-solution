#include <bits/stdc++.h>
using namespace std;

int main() {
  int x, r, c;
  cin >> x >> r >> c;
  string print[2] = {string(x, '*'), string(x, ' ')};
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < x; ++j) {
      for (int k = 0; k < c; ++k) {
        cout << print[(i+k)&1];
      }
      cout << endl;
    }
  }
}
