#include <vector>
#include <stack>
#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

class Solver {
    struct Pos {
        int x;
        int y;
        Pos(int _x, int _y) :x(_x), y(_y) {}
    };
    struct FState {
        vector<char> win_lose{ '-','-','-','-' };
        vector<int> counts{ -1,-1,-1,-1 };
    };
    struct Frame {
        Pos pos;
        int nd = 0;
        FState s;
        Frame(Pos _pos) :pos(_pos) {}
    };

    vector<vector<int>> board;
    vector<stack<Frame>> st;
    vector<Pos> dir{ {1,0},{0,1},{-1,0},{0,-1} };

    bool bTravelAllRoutes() {
        return st[0].size() + st[1].size() == 2 && st[0].top().nd == 4;
    }

    int SelectBestCount(Frame& f) {
        int ret = 100;
        for (int i = 0; i < 4; ++i) {
            if (f.s.win_lose[i] == 'W') {
                ret = min(ret, f.s.counts[i]);
            }
        }

        if (ret != 100) {
            return ret;
        }

        ret = 0;
        for (int i = 0; i < 4; ++i) {
            ret = max(ret, f.s.counts[i]);
        }

        return ret;
    }

    void UpdateAns() {
        ans = SelectBestCount(st[0].top());
    }

    int GetOthersIdx() {
        return (st[0].size() + st[1].size() + 1) % 2;
    }

    int GetTurnsIdx() {
        return (st[0].size() + st[1].size()) % 2;
    }

    Frame& GetOthersTop() {
        return st[GetOthersIdx()].top();
    }

    Frame& GetTurnsTop() {
        return st[GetTurnsIdx()].top();
    }

    void SetTurnsND() {
        Frame& f = GetTurnsTop();
        if (board[f.pos.x][f.pos.y] == 0) {
            f.nd = 4;
            for (int i = 0; i < 4; ++i) {
                f.s.win_lose[i] = 'L';
                f.s.counts[i] = st[0].size() + st[1].size() - 2;
            }
            return;
        }

        for (; f.nd < 4; ++f.nd) {
            int nx = f.pos.x + dir[f.nd].x, ny = f.pos.y + dir[f.nd].y;
            if (0 <= nx && 0 <= ny && nx < board.size() && ny < board[0].size() && board[nx][ny] == 1) {
                break;
            }
            f.s.win_lose[f.nd] = 'L';
            f.s.counts[f.nd] = st[0].size() + st[1].size() - 2;
        }
    }

    bool bDoneAllHere() {
        return GetTurnsTop().nd == 4;
    }

    void PopOthersStack() {
        st[GetOthersIdx()].pop();
    }

    void UpdateResult(Frame& from, Frame& to) {
        bool from_win = false;
        for (int i = 0; i < 4; ++i) {
            if (from.s.win_lose[i] == 'W') {
                from_win = true;
                break;
            }
        }
        to.s.counts[to.nd - 1] = SelectBestCount(from);
        to.s.win_lose[to.nd - 1] = !from_win ? 'W' : 'L';
    }

    void RestoreBoard() {
        Frame& turn = GetTurnsTop();
        board[turn.pos.x][turn.pos.y] = 1;
    }

    void GoBack() {
        PopOthersStack();
        UpdateResult(GetOthersTop(), GetTurnsTop());
        RestoreBoard();
    }

    void InitFrame(Frame& f) {
        f.nd = 0;
        f.s.win_lose.assign(4, '-');
        f.s.counts.assign(4, -1);
    }

    void TravelNext() {
        Frame& f = GetTurnsTop();
        board[f.pos.x][f.pos.y] = 0;
        int nx = f.pos.x + dir[f.nd].x, ny = f.pos.y + dir[f.nd].y;
        ++f.nd;
        st[GetTurnsIdx()].push(Frame(Pos(nx, ny)));
        InitFrame(GetTurnsTop());
    }

    void Solve() {
        while (true) {
            SetTurnsND();

            if (bTravelAllRoutes()) {
                UpdateAns();
                break;
            }

            if (bDoneAllHere()) {
                GoBack();
                continue;
            }

            TravelNext();
        }
    }

public:
    int ans = 0;

    Solver(vector<vector<int>> _board, vector<int> _aloc, vector<int> _bloc) :st(2), board(_board) {
        st[0].push(Frame(Pos(_aloc[0], _aloc[1])));
        st[1].push(Frame(Pos(_bloc[0], _bloc[1])));

        Solve();
    }
};

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
    return Solver(board, aloc, bloc).ans;
}