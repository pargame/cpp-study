// https://www.acmicpc.net/problem/17420
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
    long long N = 0LL;
    cin >> N;
    vector<pair<long long, long long>> AB(N);
    for (auto &[A, _] : AB)
        cin >> A;
    for (auto &[_, B] : AB)
        cin >> B;

    // dday 오름차순 정렬
    sort(AB.begin(), AB.end(),
         [](pair<long long, long long> const &a,
            pair<long long, long long> const &b) {
             return a.second < b.second;
         });

    long long ans = 0LL, prev_max_due = 0LL, curr_max_due = 0LL;
    for (long long i = 0LL; i < N; ++i) {
        long long cnt = max(0LL, (AB[i].second - AB[i].first + 29LL) / 30LL);
        AB[i].first += cnt * 30LL;
        ans += cnt;

        cnt = max(0LL, (prev_max_due - AB[i].first + 29LL) / 30LL);
        AB[i].first += cnt * 30LL;
        ans += cnt;

        curr_max_due = max(curr_max_due, AB[i].first);
        if (i < N - 1 && AB[i].second < AB[i + 1].second)
            prev_max_due = curr_max_due;
    }
    cout << ans;
    return 0;
}