//https://school.programmers.co.kr/learn/courses/30/lessons/87694
// 제한사항
// rectangle의 세로(행) 길이는 1 이상 4 이하입니다.
// rectangle의 원소는 각 직사각형의 [좌측 하단 x, 좌측 하단 y, 우측 상단 x, 우측 상단 y] 좌표 형태입니다.
// 직사각형을 나타내는 모든 좌표값은 1 이상 50 이하인 자연수입니다.
// 서로 다른 두 직사각형의 x축 좌표, 혹은 y축 좌표가 같은 경우는 없습니다.
// 문제에 주어진 조건에 맞는 직사각형만 입력으로 주어집니다.
// charcterX, charcterY는 1 이상 50 이하인 자연수입니다.
// 지형을 나타내는 다각형 테두리 위의 한 점이 주어집니다.
// itemX, itemY는 1 이상 50 이하인 자연수입니다.
// 지형을 나타내는 다각형 테두리 위의 한 점이 주어집니다.
// 캐릭터와 아이템의 처음 위치가 같은 경우는 없습니다.
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

vector<vector<bool>> map(102, vector<bool>(102));
vector<pair<int, int>> dir{ {2,0},{1,1},{0,2},{-1,1},{-2,0},{-1,-1},{0,-2},{1,-1} };

int r(int d) {
    return (d + 7) % 8;
}

int l(int d) {
    return (d + 1) % 8;
}

bool isEdge(pair<int, int> p, int d) {
    int i = p.first, j = p.second;
    d *= 2;
    auto [ldi, ldj] = dir[l(d)];
    auto [rdi, rdj] = dir[r(d)];
    int nli = i + ldi, nlj = j + ldj;
    int nri = i + rdi, nrj = j + rdj;
    return map[nli][nlj] != map[nri][nrj];
}

void proceed(pair<int, int> &p, int d) {
    p.first += dir[d * 2].first;
    p.second += dir[d * 2].second;
}

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    for(auto &r : rectangle) {
        for(int i = r[0] * 2; i <= r[2] * 2; ++i) {
            for(int j = r[1] * 2; j <= r[3] * 2; ++j) {
                map[i][j] = true;
            }
        }
    }

    characterX *= 2;
    characterY *= 2;
    pair<int, int> character{ characterX,characterY };
    itemX *= 2;
    itemY *= 2;

    int d1 = -1, d2 = -1;
    for(int d = 0; d < 4; ++d) {
        if(isEdge(character, d)) {
            if(d1 == -1) {
                d1 = d;
            }
            else {
                d2 = d;
                break;
            }
        }
    }

    int ans = 0;
    pair<int, int> p1{ characterX,characterY };
    pair<int, int> p2{ characterX,characterY };
    pair<int, int> item{ itemX,itemY };
    while(p1 != item && p2 != item) {
        ++ans;
        if(isEdge(p1, (d1 + 3) % 4)) {
            d1 = (d1 + 3) % 4;
        }
        else if(isEdge(p1, (d1 + 1) % 4)) {
            d1 = (d1 + 1) % 4;
        }
        if(isEdge(p2, (d2 + 3) % 4)) {
            d2 = (d2 + 3) % 4;
        }
        else if(isEdge(p2, (d2 + 1) % 4)) {
            d2 = (d2 + 1) % 4;
        }
        proceed(p1, d1);
        proceed(p2, d2);
    }
    return ans;
}