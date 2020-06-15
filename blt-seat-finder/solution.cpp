#include <bits/stdc++.h>
using namespace std;

int main() {
  int ntc, x, p, l;
  scanf("%d", &ntc);
  char filename[100];
  sprintf(filename, "../blt-seat-distancing/tc/blt-seat-distancing_%d.in", ntc+1);
  ifstream in(filename);
  in >> x >> p >> l;
  printf("%d %d %d\n", x, p, l);
}