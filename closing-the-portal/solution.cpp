#include <bits/stdc++.h>
using namespace std;

#define MAXN 100

const int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

int r, c, v[MAXN+5][MAXN+5];
char a[MAXN+5][MAXN+5];

int dfs(pair<int,int> x, const pair<int,int> &target) {
  if (x == target) return 0;
  if (x.first < 0 || x.first >= r) return -1;
  if (x.second < 0 || x.second >= c) return -1;
  if (a[x.first][x.second] == '#') return -1;
  if (v[x.first][x.second]) return -1;

  v[x.first][x.second] = 1;

  for (int d = 0; d < 4; ++d) {
    int xr = x.first + dir[d][0];
    int xc = x.second + dir[d][1];
    int ret = dfs(make_pair(xr, xc), target);
    if (ret != -1) {
      return ret + 1;
    }
  }
  return -1;
}

void solve() {
  scanf("%d%d", &r, &c);
  int empty = 0;
  vector<pair<int,int>> portals;
  for (int i = 0; i < r; ++i) {
    scanf("%s", a[i]);
    for (int j = 0; j < c; ++j) {
      if (a[i][j] == 'O') {
        portals.emplace_back(i, j);
      } else if (a[i][j] == '.') {
        empty++;
      }
    }
  }
  memset(v, 0, sizeof(v));
  int steps = dfs(portals[0], portals[1]);
  if (steps == -1) {
    puts("Bella");
    return;
  }

  int turns = empty - (steps-1);
  assert(turns >= 0);
  if (turns % 2 == 0) {
    puts("Bella");
  } else {
    puts("Alif");
  }
}

int main() {
  int ntc;
  scanf("%d", &ntc);
  for (int itc = 1; itc <= ntc; ++itc) {
    solve();
  }
}