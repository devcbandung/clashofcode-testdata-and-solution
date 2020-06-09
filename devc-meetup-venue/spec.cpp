#include <tcframe/spec.hpp>
#include <cassert>
using namespace tcframe;

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

class ProblemSpec : public BaseProblemSpec {
protected:
  std::vector<std::string> maze;
  int N, AR, AC, MR, MC;
  std::string ans;

  void InputFormat() {
    LINE(N);
    LINE(AR, AC, MR, MC);
    LINES(maze) % SIZE(N);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(1 <= N && N <= 100);
    CONS(1 <= AR && AR <= N);
    CONS(1 <= AC && AC <= N);
    CONS(1 <= MR && MR <= N);
    CONS(1 <= MC && MC <= N);
    CONS(validMaze(maze, N));
  }

  bool validMaze(const vector<string>& m, int n) {
    if (m.size() != n) return false;
    for (const string& l : m) {
      if (l.size() != n) return false;
      for (char c : l) {
        if (c != '.' && c != '#') return false;
      }
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void TestCases() {
    // Samples
    CASE(N = 4, AR = 2, AC = 3, MR = 4, MC = 1,
      maze = {
        "....",
        ".#..",
        ".##.",
        "...."
      }
    );
    CASE(N = 4, AR = 2, AC = 3, MR = 4, MC = 1,
      maze = {
        "..#.",
        ".#..",
        ".##.",
        "...#"
      }
    );
    // Test Cases
    // TC1: N = 10, hardcoded ok
    CASE(N = 10, AR = 1, AC = 9, MR = 4, MC = 1,
      maze = {
        "#...#..#..",
        "..#..#..#.",
        ".#.#..#.#.",
        ".#..#.#...",
        "##.##..#.#",
        "...#..#...",
        ".#.#.#.##.",
        "...#.#....",
        "..#...###.",
        "#...#....."
      }
    );
    // TC2: N = 10, hardcoded tersesat
    CASE(N = 10, AR = 1, AC = 2, MR = 2, MC = 3,
      maze = {
        "..##.#....",
        ".#.....##.",
        "..#.###...",
        "#..#...#.#",
        ".#...#.#..",
        "..#.#..##.",
        "#..#...#..",
        "..#..##.#.",
        ".#.##...#.",
        "......#..."
      }
    );
    // TC3: N = 35, scattered
    CASE(N = 35, scattered());
    // TC4: N = 100, scattered
    CASE(N = 100, scattered());
    // TC5: N = 99, snake
    CASE(N = 99, snake(false));
    // TC6: N = 99, snake, tersesat
    CASE(N = 99, snake(true));
    // TC7: N = 99, MST
    CASE(N = 99, mst(false, 0));
    // // TC8: N = 99, MST, tersesat
    CASE(N = 99, mst(true, 0));
    // // TC9: N = 71, MST with holes
    CASE(N = 71, mst(false, 15));
    // TC10: N = 99, MST with holes
    CASE(N = 99, mst(false, 49));
  }

  void reset() {
    maze.clear();
    string line = "";
    for (int i = 0; i < N; ++i) {
      line += ".";
    }
    for (int i = 0; i < N; ++i) {
      maze.push_back(line);
    }
  }

  void scattered() {
    reset();
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (rnd.nextDouble(1.) < 0.35) {
          maze[i][j] = '#';
        }
      }
    }
    AR = rnd.nextInt(1, N);
    AC = rnd.nextInt(1, N);
    while (maze[AR-1][AC-1] == '#') {
      AR = rnd.nextInt(1, N);
      AC = rnd.nextInt(1, N);
    }
    MR = rnd.nextInt(1, N);
    MC = rnd.nextInt(1, N);
    while (maze[MR-1][MC-1] == '#' || (AR == MR && AC == MC)) {
      MR = rnd.nextInt(1, N);
      MC = rnd.nextInt(1, N);
    }
  }

  void snake(bool blocked) {
    reset();
    for (int i = 1; i < N; i += 2) {
      for (int j = 0; j < N; ++j) {
        maze[i][j] = '#';
      }
    }
    for (int i = 1; i < N; i += 4) {
      maze[i][N-1] = '.';
    }
    for (int i = 3; i < N; i += 4) {
      maze[i][0] = '.';
    }
    AR = AC = 1;
    MR = MC = N;
    if (N % 4 == 3) {
      MC = 1;
    }
    if (blocked) {
      int rblocked = N / 2;
      if (rblocked % 2) rblocked++;
      maze[rblocked][rnd.nextInt(N)] = '#';
    }
  }

  void mst(bool blocked, int holes) {
    reset();
    vector<pair<int, int>> edges;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if ((i % 2 == 1) || (j % 2 == 1)) {
          maze[i][j] = '#';
          if ((j % 2) == 0 && i+1 < N) {
            edges.emplace_back(N * (i-1) + j, N * (i+1) + j);
          }
          if ((i % 2) == 0 && j+1 < N) {
            edges.emplace_back(N * i + j-1, N * i + j+1);
          }
        }
      }
    }
    rnd.shuffle(edges.begin(), edges.end());
    DSU dsu(N*N);
    vector<pair<int, int>> unused;
    for (pair<int, int> edge : edges) {
      int ar = edge.first / N;
      int ac = edge.first % N;
      int br = edge.second / N;
      int bc = edge.second % N;
      if (!dsu.isSameSet(edge.first, edge.second)) {
        dsu.mergeSet(edge.first, edge.second);
        maze[(ar + br) / 2][(ac + bc) / 2] = '.';
      } else {
        unused.emplace_back((ar + br) / 2, (ac + bc) / 2);
      }
    }
    // find longest diameter
    int start = findFurthestDescendant(0);
    AR = start / N + 1;
    AC = start % N + 1;
    int end = findFurthestDescendant(start);
    MR = end / N + 1;
    MC = end % N + 1;
    if (blocked) {
      vector<int> p = findPath(start, end);
      int iblocked = p.size() / 2 + rnd.nextInt(-3, 3);
      int rblocked = p[iblocked]/N;
      int cblocked = p[iblocked]%N;
      maze[rblocked][cblocked] = '#';
    } else if (holes > 0) {
      rnd.shuffle(unused.begin(), unused.end());
      for (int i = 0; i < holes; ++i) {
        assert(maze[unused[i].first][unused[i].second] == '#');
        maze[unused[i].first][unused[i].second] = '.';
      }
    }
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
      int r = x/N;
      int c = x%N;
      if (maze[r][c] == '#') continue;
      if (r > 0 && !v[x-N]) {
        q.push(x-N);
        v[x-N] = true;
        p[x-N] = x;
      }
      if (r < N-1 && !v[x+N]) {
        q.push(x+N);
        v[x+N] = true;
        p[x+N] = x;
      }
      if (c > 0 && !v[x-1]) {
        q.push(x-1);
        v[x-1] = true;
        p[x-1] = x;
      }
      if (c < N-1 && !v[x+1]) {
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
    vector<int> depth(N*N);
    for (int i = 0; i < N*N; ++i) {
      depth[i] = -1;
    }
    dfs(c/N, c%N, 0, depth);
    int maxDepth = -1, ans = 0;
    for (int i = 0; i < N*N; ++i) {
      if (depth[i] > maxDepth) {
        maxDepth = depth[i];
        ans = i;
      }
    }
    return ans;
  }

  void dfs(int r, int c, int d, vector<int> &depth) {
    if (r < 0 || r == N) return;
    if (c < 0 || c == N) return;
    if (maze[r][c] == '#') return;
    if (depth[r*N + c] != -1) return;
    depth[r*N + c] = d;
    dfs(r+1, c, d+1, depth);
    dfs(r-1, c, d+1, depth);
    dfs(r, c+1, d+1, depth);
    dfs(r, c-1, d+1, depth);
  }
};
