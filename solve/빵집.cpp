// https://www.acmicpc.net/problem/3109
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct DFSFrame {
    int r;
    int c;
    vector<int> next;
    DFSFrame(int _r, int _c, vector<int> _next) :r(_r), c(_c), next(_next) {}
};

vector<int> GetPsbs(vector<vector<char>>const& grid, int const& _r, int const& _c) {
    vector<int> ret;
    for (int dr : {1, 0, -1}) {
        int nr = _r + dr, nc = _c + 1;
        if (0 <= nr && nr < grid.size() && 0 <= nc && nc < grid[0].size() && grid[nr][nc] == '.')
            ret.push_back(dr);
    }
    return ret;
}

int main() {
    int R = 0, C = 0; cin >> R >> C;
    vector<vector<char>> grid(R, vector<char>(C));
    for (vector<char>& arr : grid) {
        for (char& cell : arr) {
            cin >> cell;
        }
    }

    int ans = 0;
    for (int sr = 0; sr < R; ++sr) {
        //Initial seeding
        stack<DFSFrame> st;
        DFSFrame seed(sr, 0, GetPsbs(grid, sr, 0));
        st.push(seed);
        //DFS Iteration
        while (!st.empty()) {
            //0. Copy top
            DFSFrame top = st.top();
            //1. Check point
            if (top.c == C - 1) { ++ans; break; }
            //2-1. Pop
            if (top.next.empty()) {
                st.pop();
            }
            //2-2. Push
            else {
                int dr = top.next.back(); st.top().next.pop_back();
                int nr = top.r + dr, nc = top.c + 1;
                st.push(DFSFrame(nr, nc, GetPsbs(grid, nr, nc)));
                grid[nr][nc] = 'X';
            }
        }
    }


    cout << ans;

    return 0;
}