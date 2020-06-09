#include <bits/stdc++.h>
using namespace std;

int n, ar, ac, mr, mc, v[111][111];
char maze[111][111];

void dfs(int r, int c, string path) {
  if (r == mr && c == mc) {
    puts(path.c_str());
    exit(0);
  }
  if (r < 0 || r == n || c < 0 || c == n) return;
  if (maze[r][c] == '#' || v[r][c]) return;
  v[r][c] = 1;

  dfs(r-1, c, path+"U");
  dfs(r+1, c, path+"D");
  dfs(r, c-1, path+"L");
  dfs(r, c+1, path+"R");
}

int main() {
  scanf("%d", &n);
  scanf("%d%d%d%d", &ar, &ac, &mr, &mc);
  ar--; ac--; mr--; mc--;
  for (int i = 0; i < n; ++i) {
    scanf("%s", maze[i]);
  }
  dfs(ar, ac, "");
  puts("tersesat");
}