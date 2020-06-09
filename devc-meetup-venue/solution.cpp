#include <bits/stdc++.h>
using namespace std;

int n, ar, ac, mr, mc;
char maze[111][111];
int p[111][111];
bool v[111][111];

const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const char* sdir = "DURL";

int main() {
  scanf("%d", &n);
  scanf("%d%d%d%d", &ar, &ac, &mr, &mc);
  ar--; ac--; mr--; mc--;
  for (int i = 0; i < n; ++i) {
    scanf("%s", maze[i]);
  }
  queue<pair<int, int>> q;
  q.emplace(mr, mc);
  v[mr][mc] = true;
  bool found = false;
  while (!q.empty() && !found) {
    pair<int, int> c = q.front(); q.pop();
    for (int d = 0; d < 4; ++d) {
      int cr = c.first + dir[d][0];
      int cc = c.second + dir[d][1];
      if (cr < 0 || cr == n) continue;
      if (cc < 0 || cc == n) continue;
      if (v[cr][cc]) continue;
      if (maze[cr][cc] == '#') continue;
      q.emplace(cr, cc);
      v[cr][cc] = true;
      p[cr][cc] = d;
      if (cr == ar && cc == ac) {
        found = true;
        break;
      }
    }
  }
  if (!found) {
    puts("tersesat");
  } else {
    while (!(ar == mr && ac == mc)) {
      putchar(sdir[p[ar][ac]]);
      int d = p[ar][ac];
      ar -= dir[d][0];
      ac -= dir[d][1];
    }
    putchar('\n');
  }
}