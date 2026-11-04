//https://school.programmers.co.kr/learn/courses/15009/lessons/121689
// 제한사항
// 1 ≤ menu의 길이 ≤ 100
// menu[i]는 i번 음료의 제조 시간을 의미합니다.
// 1 ≤ menu의 원소 ≤ 100
// 1 ≤ order의 길이 ≤ 10,000
// order[i]는 i번째 손님이 주문한 음료의 번호입니다.
// 0 ≤ order의 원소 < menu의 길이
// 1 ≤ k ≤ 100
#include <string>
#include <vector>
#include <queue>
#include <algorithm>


using namespace std;

int solution(vector<int> menu, vector<int> order, int k) {
    vector<vector<int>> wait;
    int end_t = 0;
    for(int i = 0; i < order.size(); ++i) {
        end_t += menu[order[i]];
        wait.push_back(vector<int>{i *k, end_t});
        end_t = max(end_t, (i + 1) * k);
    }

    int ans = 0;
    for(int i = 0; i < wait.size(); ++i) {
        int cnt = 1;

        for(int j = i - 1; 0 <= j && wait[i][0] < wait[j][1]; --j, ++cnt);
        ans = max(ans, cnt);
    }

    return ans;
}