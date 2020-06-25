#include <bits/stdc++.h>
using namespace std;

#define MAXN 4

const int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

int r, c, v[MAXN+5][MAXN+5];
char a[MAXN+5][MAXN+5];
vector<pair<int,int>> portals;
int dp[2][(1 << (MAXN*MAXN))+5];

bool dfs(pair<int,int> x, const pair<int,int> &target) {
  if (x == target) return true;
  if (x.first < 0 || x.first >= r) return false;
  if (x.second < 0 || x.second >= c) return false;
  if (a[x.first][x.second] == '#') return false;
  if (v[x.first][x.second]) return false;

  v[x.first][x.second] = 1;

  for (int d = 0; d < 4; ++d) {
    int xr = x.first + dir[d][0];
    int xc = x.second + dir[d][1];
    if (dfs(make_pair(xr, xc), target)) {
      return true;
    }
  }
  return false;
}

void fromMask(int mask) {
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if (mask & (1 << (i*c + j))) {
        a[i][j] = '#';
      } else {
        a[i][j] = '.';
      }
    }
  }
}

bool portalClosed(int mask) {
  memset(v, 0, sizeof(v));
  fromMask(mask);
  return !dfs(portals[0], portals[1]);
}

int toMask() {
  int mask = 0;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if (a[i][j] == '#') {
        mask |= (1 << (i*c + j));
      }
    }
  }
  return mask;
}

bool isPortal(int x) {
  int xr = x / c;
  int xc = x % c;
  for (auto portal : portals) {
    if (portal.first == xr && portal.second == xc) return true;
  }
  return false;
}

void printMask(int mask) {
  fromMask(mask);
  for (auto portal : portals) {
    a[portal.first][portal.second] = 'O';
  }
  for (int i = 0; i < r; ++i) {
    printf("\t%s\n", a[i]);
  }
}

bool play(int player, int mask) {
  if (dp[player][mask]) {
    return (dp[player][mask] == 1);
  }
  if (portalClosed(mask)) {
    dp[player][mask] = -1;
    return false;
  }
  for (int i = 0; i < r*c; ++i) {
    if (isPortal(i)) continue;
    if (mask & (1 << i)) continue;
    int newMask = mask | (1 << i);
    if (portalClosed(newMask)) continue;
    if (!play(1 - player, newMask)) {
      dp[player][mask] = 1;
      return true;
    }
  }
  dp[player][mask] = -1;
  return false;
}

void solve() {
  scanf("%d%d", &r, &c);
  int empty = 0;
  portals.clear();
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

  int mask = toMask();

  memset(dp, 0, sizeof(dp));
  if (play(0, mask)) {
    puts("Alif");
  } else {
    puts("Bella");
  }
}

int main() {
  int ntc;
  scanf("%d", &ntc);
  for (int itc = 1; itc <= ntc; ++itc) {
    solve();
  }
}