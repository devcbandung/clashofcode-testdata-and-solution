#include <bits/stdc++.h>
using namespace std;

int main() {
  int ax1, ax2, ay1, ay2, bx1, bx2, by1, by2;
  scanf("%d%d%d%d", &ax1, &ay1, &ax2, &ay2);
  scanf("%d%d%d%d", &bx1, &by1, &bx2, &by2);
  int x1 = min(ax1, bx1);
  int x2 = max(ax2, bx2);
  int y1 = min(ay1, by1);
  int y2 = max(ay2, by2);
  printf("%d\n", 2 * (y2-y1+x2-x1));
}
