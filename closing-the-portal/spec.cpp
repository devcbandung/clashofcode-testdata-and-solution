#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace tcframe;

#define REP(n) for (int i = 0; i < n; ++i)

class DSU {
public:
  DSU(int n): p(vector<int>(n+1)), n(n) {
    for (int i = 1; i <= n; ++i) {
      p[i] = i;
    }
  }

  int findSet(int x) {
    return p[x] == x ? x : p[x] = findSet(p[x]);
  }

  void mergeSet(int x, int y) {
    p[findSet(x)] = findSet(y);
  }

  bool isSameSet(int x, int y) {
    return findSet(x) == findSet(y);
  }

private:
  vector<int> p;
  int n;
};

int manhattan(const pair<int,int> &a, const pair<int,int> &b) {
  return abs(a.first-b.first) + abs(a.second-b.second);
}

class ProblemSpec : public BaseProblemSpec {
protected:
  int T;
  int _T;
  vector<string> maze;
  // vector<pair<int,int>> portals;
  int R, C;
  string ans;

  void MultipleTestCasesConfig() {
    Counter(T);
  }

  void InputFormat() {
    LINE(R, C);
    LINES(maze) % SIZE(R);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(1 <= R && R <= 100);
    CONS(1 <= C && C <= 100);
    CONS(validMaze());
  }

  // Sample
  void Subtask1() {
    Points(0);

    CONS(_T == 1);
    // no additional constraints
  }

  void Subtask2() {
    Points(50);

    CONS(_T == 2);
    CONS(1 <= R && R <= 4);
    CONS(1 <= C && C <= 4);
  }

  void Subtask3() {
    Points(50);

    CONS(_T == 3);
    CONS(1 <= R && R <= 100);
    CONS(1 <= C && C <= 100);
  }

  bool validMaze() {
    if (maze.size() != R) return false;
    vector<pair<int,int>> portals;
    int empty = 0;
    for (int i = 0; i < R; ++i) {
      if (maze[i].size() != C) return false;
      for (int j = 0; j < C; ++j) {
        char c = maze[i][j];
        if (c != '.' && c != '#' && c != 'O') return false;
        if (c == 'O') {
          portals.emplace_back(i, j);
        } else if (c == '.') {
          empty++;
        }
      }
    }
    if (empty == 0) return false;
    if (portals.size() != 2) return false;
    if (manhattan(portals[0], portals[1]) == 1) return false;
    return true;
  }
};

typedef vector<string> Maze;

vector<Maze> Mazes[5][5];
map<int, bool> used[5][5];

void generateAllMazes(int r, int c) {
  int s = r*c;
  int total = 0;
  for (int mask = 0; mask < (1 << s); ++mask) {
    int empty = s - __builtin_popcount(mask);
    if (empty < 3) continue;
    Maze base;
    vector<pair<int,int>> empties;
    for (int i = 0; i < r; ++i) {
      string line;
      for (int j = 0; j < c; ++j) {
        if (mask & (1 << (i*c+j))) {
          line += '#';
        } else {
          line += '.';
          empties.emplace_back(i, j);
        }
      }
      base.push_back(line);
    }
    assert(empty == empties.size());
    for (int i = 0; i < empty; ++i) {
      for (int j = 0; j < i; ++j) {
        if (manhattan(empties[i], empties[j]) == 1) continue;
        Maze copy = base;
        copy[empties[i].first][empties[i].second] = 'O';
        copy[empties[j].first][empties[j].second] = 'O';
        Mazes[r][c].push_back(copy);
        total++;
      }
    }
  }
  printf("finished generating mazes for (R, C) = (%d, %d): total = %d\n", r, c, total);
}

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void TestGroup1() {
    Subtasks({1});

    CASE(_T = 1, R = 3, C = 3,
      maze = {
        "O..",
        ".#.",
        "..O"
      }
    );
    CASE(_T = 1, R = 1, C = 10,
      maze = {"..O.#...O."}
    );
  }

  void TestGroup2() {
    Subtasks({2});

    for (int r = 1; r <= 4; ++r) {
      for (int c = 1; c <= 4; ++c) {
        Mazes[r][c].clear();
        used[r][c].clear();
        generateAllMazes(r, c);
      }
    }

    // test cases
    // 4: linear (manual)
    // 2: 2x2 (manual)
    // 3: 2x3
    // 3: 3x2
    // 6: 3x3
    // 6: 2x4
    // 6: 4x2
    // 15: 3x4
    // 15: 4x3
    // 40: 4x4
    CASE(_T = 2, R = 1, C = 4, maze = {"O#.O"});
    CASE(_T = 2, R = 1, C = 4, maze = {"O.O."});
    CASE(_T = 2, R = 4, C = 1, maze = {"O",".",".","O"});
    CASE(_T = 2, R = 3, C = 1, maze = {"O",".","O"});
    CASE(_T = 2, R = 2, C = 2, maze = {"O.",".O"});
    CASE(_T = 2, R = 2, C = 2, maze = {"O#",".O"});
    REP(3) CASE(_T = 2, pickFromMazes(2, 3));
    REP(3) CASE(_T = 2, pickFromMazes(3, 2));
    REP(6) CASE(_T = 2, pickFromMazes(3, 3));
    REP(6) CASE(_T = 2, pickFromMazes(2, 4));
    REP(6) CASE(_T = 2, pickFromMazes(4, 2));
    REP(15) CASE(_T = 2, pickFromMazes(3, 4));
    REP(15) CASE(_T = 2, pickFromMazes(4, 3));
    REP(40) CASE(_T = 2, pickFromMazes(4, 4));
  }

  void TestGroup3() {
    Subtasks({3});

    // test cases
    // 50: most tc: scattered
    // 20: scattered with high p (hoping we got lost)
    // 1: snake
    // 1: snake with block
    // 14: mst tersesat
    // 14: mst with holes
    REP(10) CASE(_T = 3, R = 100, C = 100, scattered(0.25));
    REP(10) CASE(_T = 3, R = 100, C = 100, scattered(0.55));
    REP(40) CASE(_T = 3, R = rnd.nextInt(1, 100), C = rnd.nextInt(1, 100), scattered(0.25));
    REP(10) CASE(_T = 3, R = rnd.nextInt(1, 100), C = rnd.nextInt(1, 100), scattered(0.55));
    CASE(_T = 3, R = 99, C = 99, snake(false));
    CASE(_T = 3, R = 99, C = 99, snake(true));
    REP(4) CASE(_T = 3, R = 99, C = 99, mst(true, 0));
    REP(4) CASE(_T = 3, R = 99, C = 99, mst(false, 0));
    REP(10) CASE(_T = 3, R = rnd.nextInt(10, 50) * 2 - 1, C = rnd.nextInt(10, 50) * 2 - 1, mst(true, 0));
    REP(10) CASE(_T = 3, R = rnd.nextInt(10, 50) * 2 - 1, C = rnd.nextInt(10, 50) * 2 - 1, mst(false, rnd.nextInt(3, 5)));
  }

  void pickFromMazes(int r, int c) {
    int i = rnd.nextInt(Mazes[r][c].size());
    while (used[r][c][i]) {
      i = rnd.nextInt(Mazes[r][c].size());
    }

    maze = Mazes[r][c][i];
    used[r][c][i] = true;
    R = maze.size();
    C = maze[0].size();
  }

  void reset() {
    maze.clear();
    string line = "";
    for (int i = 0; i < C; ++i) {
      line += ".";
    }
    for (int i = 0; i < R; ++i) {
      maze.push_back(line);
    }
  }

  void scattered(double p) {
    reset();
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        if (rnd.nextDouble(1.) < p) {
          maze[i][j] = '#';
        }
      }
    }
    vector<pair<int,int>> portals(2);
    do {
      portals[0] = make_pair(rnd.nextInt(R), rnd.nextInt(C));
    } while (maze[portals[0].first][portals[0].second] == '#');
    do {
      portals[1] = make_pair(rnd.nextInt(R), rnd.nextInt(C));
    } while (maze[portals[1].first][portals[1].second] == '#' || manhattan(portals[0], portals[1]) <= 1);
    for (auto portal : portals) {
      maze[portal.first][portal.second] = 'O';
    }
  }

  void snake(bool blocked) {
    reset();
    for (int i = 1; i < R; i += 2) {
      for (int j = 0; j < C; ++j) {
        maze[i][j] = '#';
      }
    }
    for (int i = 1; i < R; i += 4) {
      maze[i][C-1] = '.';
    }
    for (int i = 3; i < R; i += 4) {
      maze[i][0] = '.';
    }
    vector<pair<int,int>> portals(2);
    portals[0] = make_pair(0, 0);
    portals[1] = make_pair(R-1, C-1);
    if (C % 4 == 3) {
      portals[1].second = 0;
    }
    for (auto portal : portals) {
      maze[portal.first][portal.second] = 'O';
    }
    if (blocked) {
      int rblocked = R / 2;
      if (rblocked % 2) rblocked++;
      maze[rblocked][rnd.nextInt(C)] = '#';
    }
  }

  void mst(bool blocked, int holes) {
    reset();
    vector<pair<int, int>> edges;
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        if ((i % 2 == 1) || (j % 2 == 1)) {
          maze[i][j] = '#';
          if ((j % 2) == 0 && i+1 < R) {
            edges.emplace_back(C * (i-1) + j, C * (i+1) + j);
          }
          if ((i % 2) == 0 && j+1 < C) {
            edges.emplace_back(C * i + j-1, C * i + j+1);
          }
        }
      }
    }
    rnd.shuffle(edges.begin(), edges.end());
    DSU dsu(R*C);
    vector<pair<int, int>> unused;
    for (pair<int, int> edge : edges) {
      int ar = edge.first / C;
      int ac = edge.first % C;
      int br = edge.second / C;
      int bc = edge.second % C;
      if (!dsu.isSameSet(edge.first, edge.second)) {
        dsu.mergeSet(edge.first, edge.second);
        maze[(ar + br) / 2][(ac + bc) / 2] = '.';
      } else {
        unused.emplace_back((ar + br) / 2, (ac + bc) / 2);
      }
    }
    // find longest diameter
    int start = findFurthestDescendant(0);
    int AR = start / C + 1;
    int AC = start % C + 1;
    int end = findFurthestDescendant(start);
    int MR = end / C + 1;
    int MC = end % C + 1;
    if (blocked) {
      vector<int> p = findPath(start, end);
      int iblocked = p.size() / 2 + rnd.nextInt(-3, 3);
      int rblocked = p[iblocked]/C;
      int cblocked = p[iblocked]%C;
      maze[rblocked][cblocked] = '#';
    } else if (holes > 0) {
      rnd.shuffle(unused.begin(), unused.end());
      for (int i = 0; i < holes; ++i) {
        assert(maze[unused[i].first][unused[i].second] == '#');
        maze[unused[i].first][unused[i].second] = '.';
      }
    }
    maze[AR-1][AC-1] = 'O';
    maze[MR-1][MC-1] = 'O';
  }

  vector<int> findPath(int start, int end) {
    queue<int> q;
    map<int, bool> v;
    map<int, int> p;
    q.push(end);
    v[end] = true;
    while (!q.empty()) {
      int x = q.front(); q.pop();
      if (x == start) break;
      int r = x/C;
      int c = x%C;
      if (maze[r][c] == '#') continue;
      if (r > 0 && !v[x-C]) {
        q.push(x-C);
        v[x-C] = true;
        p[x-C] = x;
      }
      if (r < R-1 && !v[x+C]) {
        q.push(x+C);
        v[x+C] = true;
        p[x+C] = x;
      }
      if (c > 0 && !v[x-1]) {
        q.push(x-1);
        v[x-1] = true;
        p[x-1] = x;
      }
      if (c < C-1 && !v[x+1]) {
        q.push(x+1);
        v[x+1] = true;
        p[x+1] = x;
      }
    }
    vector<int> res;
    if (!v[start]) return res;
    res.push_back(start);
    while (start != end) {
      start = p[start];
      res.push_back(start);
    }
    return res;
  }

  int findFurthestDescendant(int c) {
    vector<int> depth(R*C);
    for (int i = 0; i < R*C; ++i) {
      depth[i] = -1;
    }
    dfs(c/C, c%C, 0, depth);
    int maxDepth = -1, ans = 0;
    for (int i = 0; i < R*C; ++i) {
      if (depth[i] > maxDepth) {
        maxDepth = depth[i];
        ans = i;
      }
    }
    return ans;
  }

  void dfs(int r, int c, int d, vector<int> &depth) {
    if (r < 0 || r == R) return;
    if (c < 0 || c == C) return;
    if (maze[r][c] == '#') return;
    if (depth[r*C + c] != -1) return;
    depth[r*C + c] = d;
    dfs(r+1, c, d+1, depth);
    dfs(r-1, c, d+1, depth);
    dfs(r, c+1, d+1, depth);
    dfs(r, c-1, d+1, depth);
  }
};
