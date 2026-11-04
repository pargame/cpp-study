// https://www.acmicpc.net/problem/14500

#include <iostream>
#include <vector>

using namespace std;

struct Shape {
    vector<vector<int>> map;

    Shape(int _shape_num) {
        switch (_shape_num) {
        case 1:
            map = {{1, 1, 1, 1}};
            break;
        case 2:
            map = {{1, 1}, {1, 1}};
            break;
        case 3:
            map = {{1, 1, 1}, {1, 0, 0}};
            break;
        case 4:
            map = {{1, 1, 0}, {0, 1, 1}};
            break;
        case 5:
            map = {{1, 1, 1}, {0, 1, 0}};
            break;
        default:
            cout << "Wrong Shape!\n";
        }
    }

    vector<vector<int>> GetRotate90Map() {
        vector<vector<int>> ret(map[0].size(), vector<int>(map.size()));
        for (size_t i = 0; i < ret.size(); ++i) {
            for (size_t j = 0; j < ret[0].size(); ++j) {
                ret[i][j] = map[map.size() - j - 1][i];
            }
        }
        return ret;
    }

    vector<vector<int>> GetFlipVrtMap() {
        vector<vector<int>> ret(map.size(), vector<int>(map[0].size()));
        for (size_t i = 0; i < ret.size(); ++i) {
            for (size_t j = 0; j < ret[0].size(); ++j) {
                ret[i][j] = map[map.size() - i - 1][j];
            }
        }
        return ret;
    }
};

class Tet {
  private:
    Shape shape; // 모양: 1~5
    bool flip;   // 유의미한 좌우 반전 여부
    int rot;     // 유의미한 회전 수

  public:
    Tet(int _shape_num) : shape(_shape_num) {
        switch (_shape_num) {
        case 1:
            flip = false;
            rot = 1;
            break;
        case 2:
            flip = false;
            rot = 0;
            break;
        case 3:
        case 4:
        case 5:
            flip = true;
            rot = 3;
            break;
        default:
            cout << "Wrong Shape!!\n";
        }
    }

    int GetMaxSub(vector<vector<int>> const &_map,
                  vector<vector<int>> const &_board) {
        int ret = -1;
        for (size_t i = 0; i <= _board.size() - _map.size(); ++i) {
            for (size_t j = 0; j <= _board[0].size() - _map[0].size(); ++j) {
                int sum = 0;
                for (size_t a = 0; a < _map.size(); ++a) {
                    for (size_t b = 0; b < _map[0].size(); ++b) {
                        if (_map[a][b] == 1)
                            sum += _board[i + a][j + b];
                    }
                }
                ret = ret < sum ? sum : ret;
            }
        }
        return ret;
    }

    int GetMax(vector<vector<int>> const &_board) {
        Shape tmp_shape = shape;
        int ret = -1;
        for (int r = 0; r <= rot; ++r) {
            int val = GetMaxSub(tmp_shape.map, _board);
            ret = ret < val ? val : ret;
            tmp_shape.map = tmp_shape.GetRotate90Map();
        }

        if (flip) {
            tmp_shape.map = tmp_shape.GetFlipVrtMap();
            for (int r = 0; r <= rot; ++r) {
                int val = GetMaxSub(tmp_shape.map, _board);
                ret = ret < val ? val : ret;
                tmp_shape.map = tmp_shape.GetRotate90Map();
            }
        }
        return ret;
    }
};

int main() {
    int n = 0, m = 0;
    cin >> n >> m;
    vector<vector<int>> board(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
        }
    }
    int ans = -1;
    for (int i = 1; i <= 5; ++i) {
        Tet tet(i);
        int val = tet.GetMax(board);
        ans = ans < val ? val : ans;
    }
    cout << ans;
    return 0;
}