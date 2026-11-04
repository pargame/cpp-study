//https://school.programmers.co.kr/learn/courses/30/lessons/42861
// 제한사항
// 섬의 개수 n은 1 이상 100 이하입니다.
// costs의 길이는 ((n-1) * n) / 2이하입니다.
// 임의의 i에 대해, costs[i][0] 와 costs[i] [1]에는 다리가 연결되는 두 섬의 번호가 들어있고, costs[i] [2]에는 이 두 섬을 연결하는 다리를 건설할 때 드는 비용입니다.
// 같은 연결은 두 번 주어지지 않습니다. 또한 순서가 바뀌더라도 같은 연결로 봅니다. 즉 0과 1 사이를 연결하는 비용이 주어졌을 때, 1과 0의 비용이 주어지지 않습니다.
// 모든 섬 사이의 다리 건설 비용이 주어지지 않습니다. 이 경우, 두 섬 사이의 건설이 불가능한 것으로 봅니다.
// 연결할 수 없는 섬은 주어지지 않습니다.
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

int solution(int n, vector<vector<int>> costs) {
    vector<vector<pair<int, int>>> g(n);

    for(auto &c : costs) {
        g[c[0]].push_back({ c[1],c[2] });
        g[c[1]].push_back({ c[0],c[2] });
    }

    vector<bool> vst(n);
    vst[0] = true;

    int ans = 0;

    struct Cmp {
        bool operator()(pair<int, int>const &a, pair<int, int>const &b) {
            return a.second > b.second;
        }
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp> pq;
    for(auto &p : g[0]) {
        pq.push(p);
    }

    while(!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();

        if(vst[top.first]) {
            continue;
        }

        vst[top.first] = true;
        ans += top.second;
        for(auto &p : g[top.first]) {
            if(!vst[p.first]) {
                pq.push(p);
            }
        }
    }

    return ans;
}