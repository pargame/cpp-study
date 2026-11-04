#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

class Solver {
    struct Loc {
        int x;
        int y;
        Loc(int _x, int _y) :x(_x), y(_y) {}
    };
    struct Frame {
        int info_i;
        int info_j;
        int cnt;
        vector<int> next;
        int mask; // bitmask: 1 means 해당 info 인덱스(페어)가 보드에 남아있음
        Frame(int _info_i, int _info_j, int _cnt, vector<int> _next, int _mask)
            :info_i(_info_i), info_j(_info_j), cnt(_cnt), next(_next), mask(_mask) {}
    };
    vector<vector<int>>& board;
    Loc first_loc;
    vector<vector<Loc>> info;

    // mask를 반영해 그리드(1=카드 존재, 0=빈칸) 생성
    vector<vector<int>> BuildGridFromMask(int mask) {
        vector<vector<int>> g(4, vector<int>(4, 0));
        for (int idx = 0; idx < (int)info.size(); ++idx) {
            if (mask & (1 << idx)) {
                for (auto &p : info[idx]) g[p.x][p.y] = 1;
            }
        }
        return g;
    }

    // mask로 표현된 현재 보드에서 from -> to까지 최소 이동(화살표 또는 Ctrl), Enter 제외
    int MinMoveWithMask(int mask, Loc from, Loc to) {
        if (from.x == to.x && from.y == to.y) return 0;
        auto g = BuildGridFromMask(mask);
        const int H = 4, W = 4;
        bool vis[4][4] = { false };
        queue<tuple<int,int,int>> q; // r,c,dist
        q.push({from.x, from.y, 0});
        vis[from.x][from.y] = true;
        int dr[4] = {-1,1,0,0};
        int dc[4] = {0,0,-1,1};
        while (!q.empty()) {
            auto [r,c,d] = q.front(); q.pop();
            for (int k = 0; k < 4; ++k) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr >= 0 && nr < H && nc >= 0 && nc < W && !vis[nr][nc]) {
                    if (nr == to.x && nc == to.y) return d + 1;
                    vis[nr][nc] = true;
                    q.push({nr,nc,d+1});
                }
                // ctrl-move
                nr = r; nc = c;
                while (true) {
                    int tr = nr + dr[k], tc = nc + dc[k];
                    if (!(tr >= 0 && tr < H && tc >= 0 && tc < W)) break;
                    nr = tr; nc = tc;
                    if (g[nr][nc] != 0) break; // 첫 카드 만나면 멈춤
                }
                if (!vis[nr][nc]) {
                    if (nr == to.x && nc == to.y) return d + 1;
                    vis[nr][nc] = true;
                    q.push({nr,nc,d+1});
                }
            }
        }
        return 1000000;
    }

    vector<int> GetNextWithoutI(vector<int> cur, int i) {
        cur.erase(cur.begin() + i);
        return cur;
    }

    void Solve() {
        queue<Frame> q;
        vector<int> next;
        for (int i = 0; i < info.size(); ++i) next.push_back(i);

        int fullMask = 0;
        for (int i = 0; i < info.size(); ++i) fullMask |= (1 << i);

        // 초기 프레임: 현재 페어는 보드에 남아있으므로 이동 계산 시 mask에는 해당 비트가 설정되어 있어야 함.
        for (int i = 0; i < info.size(); ++i) {
            q.push(Frame(i, 0,
                         MinMoveWithMask(fullMask, first_loc, info[i][0]),
                         GetNextWithoutI(next, i),
                         fullMask));
            q.push(Frame(i, 1,
                         MinMoveWithMask(fullMask, first_loc, info[i][1]),
                         GetNextWithoutI(next, i),
                         fullMask));
        }

        while (!q.empty()) {
            Frame fr = q.front();
            q.pop();

            // fr.mask 는 현재 프레임에서 아직 제거되지 않은 페어들 비트마스크(현재 선택중인 페어도 포함)
            // 현재 프레임에서 같은 페어의 두번째 카드로 이동할 때는 그 페어가 아직 보드에 있어야 함.
            fr.cnt += MinMoveWithMask(fr.mask, info[fr.info_i][fr.info_j], info[fr.info_i][1 - fr.info_j]) + 2; // 이동 + Enter 두번

            if (fr.next.empty()) {
                ans = min(ans, fr.cnt);
                continue;
            }

            // 현재 페어는 이제 제거된 상태로 다음 페어로 이동해야 함
            int removedMask = fr.mask & ~(1 << fr.info_i);

            fr.info_j = 1 - fr.info_j; // 현재 커서 위치(두번째 카드 위치)로 갱신
            for (int i = 0; i < fr.next.size(); ++i) {
                Loc cur_loc = info[fr.info_i][fr.info_j];
                int nextIdx = fr.next[i];

                // 다음 페어로 이동할 때는 현재 페어가 제거된 상태(removedMask)를 반영
                int cost0 = MinMoveWithMask(removedMask, cur_loc, info[nextIdx][0]);
                int cost1 = MinMoveWithMask(removedMask, cur_loc, info[nextIdx][1]);

                vector<int> nextVec = GetNextWithoutI(fr.next, i);
                q.push(Frame(nextIdx, 0, fr.cnt + cost0, nextVec, removedMask));
                q.push(Frame(nextIdx, 1, fr.cnt + cost1, nextVec, removedMask));
            }
        }
    }

public:
    int ans = 40;
    Solver(vector<vector<int>>& _b, int _r, int _c) :board(_b), first_loc(_r,_c) {
        info.assign(6, vector<Loc>());
        int cnt = 0;
        for (int x = 0; x < 4; ++x) {
            for (int y = 0; y < 4; ++y) {
                if (board[x][y] == 0) continue;
                info[board[x][y]-1].push_back(Loc(x, y));
                ++cnt;
            }
        }

        for (auto it = info.begin(); it != info.end();) {
            if (it->empty()) it = info.erase(it);
            else ++it;
        }

        Solve();
    }
};

int solution(vector<vector<int>> board, int r, int c) {
    return Solver(board, r, c).ans;
}

int main() {
    // 테스트 케이스 1
    vector<vector<int>> board1 = {
        {1,0,0,3},
        {2,0,0,0},
        {0,0,0,2},
        {3,0,1,0}
    };
    int r1 = 1, c1 = 0;
    int res1 = solution(board1, r1, c1);
    cout << "Test1 expected=14 result=" << res1 << '\n';

    // 테스트 케이스 2
    vector<vector<int>> board2 = {
        {3,0,0,2},
        {0,0,1,0},
        {0,1,0,0},
        {2,0,0,3}
    };
    int r2 = 0, c2 = 1;
    int res2 = solution(board2, r2, c2);
    cout << "Test2 expected=16 result=" << res2 << '\n';

    return 0;
}