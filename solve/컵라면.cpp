// https://www.acmicpc.net/problem/1781
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    int N;
    if(!(cin >> N)) return 0;
    vector<pair<int, int>> problems(N);
    for(auto& p : problems) cin >> p.first >> p.second;
    // first: deadline, second: ramen

    sort(problems.begin(), problems.end()); // deadline 오름차순

    priority_queue<int, vector<int>, greater<int>> pq; // 최소 힙
    for(auto& pr : problems) {
        int d = pr.first, c = pr.second;
        pq.push(c);
        if((int)pq.size() > d) pq.pop(); // 데드라인 초과 시 가장 작은 컵라면 제거
    }

    long long ans = 0;
    while(!pq.empty()) { ans += pq.top(); pq.pop(); }
    cout << ans << '\n';
}