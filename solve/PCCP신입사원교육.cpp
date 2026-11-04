//https://school.programmers.co.kr/learn/courses/15009/lessons/121688
// 제한사항
// 2 ≤ ability의 길이 ≤ 1,000,000
// 1 ≤ ability의 원소 ≤ 100
// 1 ≤ number ≤ 10,000
// return 값이 10억 이하가 되도록 ability와 number가 주어집니다.
#include <string>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

int solution(vector<int> ability, int number) {
    struct Cmp {
        bool operator()(int const &a, int const &b) {
            return a > b;
        };
    };

    priority_queue<int, vector<int>, Cmp> pq; //min heap
    for(int &a : ability) {
        pq.push(a);
    }
    int ans = 0;
    ans = accumulate(ability.begin(), ability.end(), 0);

    for(int i = 0; i < number; ++i) {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        pq.push(a + b);
        pq.push(a + b);
        ans += a + b;
    }

    return ans;
}