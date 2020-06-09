#include <bits/stdc++.h>
using namespace std;

int wa() {
  cout << "WA" << endl;
  return 0;
}

int ac() {
  cout << "AC" << endl;
  return 0;
}

int main(int argc, char* argv[]) {
  ifstream tc_in(argv[1]);
  ifstream tc_out(argv[2]);
  ifstream con_out(argv[3]);

  int N, AR, AC, MR, MC;
  vector<string> maze;
  tc_in >> N >> AR >> AC >> MR >> MC;
  for (int i = 0; i < N; ++i) {
    string buffer;
    tc_in >> buffer;
    maze.push_back(buffer);
  }

  string tc_ans;
  tc_out >> tc_ans;

  string con_ans;
  if (!(con_out >> con_ans)) {
    return wa();
  }
  if (tc_ans == "tersesat") {
    if (con_ans == "tersesat") {
      return ac();
    } else {
      return wa();
    }
  }
  if (con_ans.length() > 10000) {
    return wa();
  }
  for (char c : con_ans) {
    if (c != 'U' && c != 'D' && c != 'R' && c != 'L') {
      return wa();
    }
    if (c == 'U') {
      AR--;
    } else if (c == 'D') {
      AR++;
    } else if (c == 'L') {
      AC--;
    } else if (c == 'R') {
      AC++;
    } else {
      return wa();
    }
    if (AR == 0 || AC == 0 || AR > N || AC > N) {
      return wa();
    }
    if (maze[AR-1][AC-1] == '#') {
      return wa();
    }
  }

  if (AR == MR && AC == MC) {
    return ac();
  } else {
    return wa();
  }
}