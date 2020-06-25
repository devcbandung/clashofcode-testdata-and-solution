#include <bits/stdc++.h>
using namespace std;

int main() {
  int minx, maxx, miny, maxy;
  int x, y;

  // baca titik pertama, assign menjadi semua nilai min/max
  cin >> x >> y;
  minx = maxx = x;
  miny = maxy = y;

  // baca 3 titik lainnya.
  // perhatikan bahwa kita tidak perlu memedulikan titik mana
  // termasuk ke persegi panjang yang mana.
  for (int i = 0; i < 3; i++) {
    cin >> x >> y;
    minx = min(minx, x);
    maxx = max(maxx, x);
    miny = min(miny, y);
    maxy = max(maxy, y);
  }

  // outputkan keliling dari persegi panjang besar
  cout << 2 * (maxx - minx + maxy - miny) << endl;
}