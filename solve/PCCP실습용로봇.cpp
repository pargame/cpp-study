//https://school.programmers.co.kr/learn/courses/15009/lessons/121687
// 제한사항
// 1 ≤ commad의 길이 ≤ 1,000,000
// command는 'R', 'L', 'G', 'B'으로 구성된 문자열입니다.
// command에 들어있는 문자 하나하나가 각 명령을 나타내며, 문자열에 먼저 등장하는 명령을 먼저 수행해야 합니다.
#include <string>
#include <vector>
#include <utility>

using namespace std;

vector<int> solution(string command) {
    vector<int> ans{ 0,0 };
    vector<pair<int, int>> dir{ {0,1},{1,0},{0,-1},{-1,0} };
    int cur_d = 0;

    for(char &c : command) {
        switch(c) {
        case 'R':
            cur_d = (cur_d + 1) % 4;
            break;
        case 'L':
            cur_d = (cur_d + 3) % 4;
            break;
        case 'G':
            ans[0] += dir[cur_d].first;
            ans[1] += dir[cur_d].second;
            break;
        case 'B':
            ans[0] -= dir[cur_d].first;
            ans[1] -= dir[cur_d].second;
            break;
        }
    }
    return ans;
}