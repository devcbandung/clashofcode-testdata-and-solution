#include <bits/stdc++.h>
using namespace std;

int main() {
  int h, m;
  scanf("%d:%d", &h, &m);
  while (h > 11) h -= 12;
  printf("%.1lf\n", min(abs(30.*h-5.5*m), 360.-abs(5.5*m-30.*h)));
}
