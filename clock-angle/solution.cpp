#include <bits/stdc++.h>
using namespace std;

int main() {
  int h, m;
  scanf("%d:%d", &h, &m);
  while (h > 11) h -= 12;
  double angle = fabs(30.*h - 5.5*m);
  printf("%.1lf\n", min(angle, 360. - angle));
}
