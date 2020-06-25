#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, d;
  cin >> n >> d;

  // Perhatikan bahwa karena 10000-n dan d bertipe int,
  // kita harus melakukan casting ke float.
  // Begitu juga dengan hasil dari fungsi ceil yang
  // bertipe float harus kita cast kembali ke int.
  int days = (int)ceil((float)(10000-n)/(float)d);
  cout << days << endl;
}