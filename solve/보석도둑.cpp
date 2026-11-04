//https://www.acmicpc.net/problem/1202
#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<queue>

using namespace std;

int main() {
    unsigned N = 0, K = 0; cin >> N >> K;
    vector<pair<unsigned, unsigned>> jewels(N);
    for(auto& p : jewels) cin >> p.first >> p.second;
    vector<unsigned> bags(K);
    for(auto& b : bags)cin >> b;

    //가방 용량 오름차순 정렬
    sort(bags.begin(), bags.end());
    //보석 무게 오름차순 정렬
    sort(jewels.begin(), jewels.end(), [](auto const& p1, auto const& p2) {
        return p1.first < p2.first;
        });

    unsigned long long ans = 0;
    priority_queue<int> pq; //기본 최대힙
    unsigned idx = 0;  //보석 인덱스
    for(auto& bag : bags) {
        //들어갈 수 있는 무게의 보석 가격들을 최대힙에 추가
        while(idx < N && jewels[idx].first <= bag) {
            pq.push(jewels[idx].second);  //가격
            ++idx;
        }
        //가장 큰 보석깂을 추가
        if(!pq.empty()) {
            ans += pq.top();
            pq.pop();
        }
    }

    cout << ans;
}