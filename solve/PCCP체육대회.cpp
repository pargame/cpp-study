//https://school.programmers.co.kr/learn/courses/15008/lessons/121684
// 제한사항
// 1 ≤ ability의 행의 길이 = 학생 수 ≤ 10
// 1 ≤ ability의 열의 길이 = 종목 수 ≤ ability의 행의 길이
// 0 ≤ ability[i][j] ≤ 10,000
// ability[i][j]는 i+1번 학생의 j+1번 종목에 대한 능력치를 의미합니다.

#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Frame {
    vector<int> used;
    vector<int> unused;
};

int solution(vector<vector<int>> ability) {
    queue<Frame> q;
    q.push(Frame());
    q.front().unused.assign(ability.size(), 0);
    for(int i = 0; i < ability.size(); ++i) {
        q.front().unused[i] = i;
    }
    int ans = 0;
    while(!q.empty()) {
        Frame top = q.front();
        q.pop();

        if(top.used.size() == ability[0].size()) {
            int sum = 0;
            for(int i = 0; i < ability[0].size(); ++i) {
                sum += ability[top.used[i]][i];
            }
            ans = max(ans, sum);
            continue;
        }

        for(int i = 0; i < top.unused.size(); ++i) {
            Frame next = top;
            next.used.push_back(top.unused[i]);
            next.unused.erase(next.unused.begin() + i);
            q.push(next);
        }
    }
    return ans;
}