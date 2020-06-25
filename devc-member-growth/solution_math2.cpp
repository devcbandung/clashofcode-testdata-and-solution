#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, d;
  cin >> n >> d;

  int days = (10000-n + d-1) / d;
  cout << days << endl;
}
