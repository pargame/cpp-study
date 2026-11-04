//https://school.programmers.co.kr/learn/courses/30/lessons/62050

// 제한사항
// land는 N x N크기인 2차원 배열입니다.
// land의 최소 크기는 4 x 4, 최대 크기는 300 x 300입니다.
// land의 원소는 각 격자 칸의 높이를 나타냅니다.
// 격자 칸의 높이는 1 이상 10,000 이하인 자연수입니다.
// height는 1 이상 10,000 이하인 자연수입니다.
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, 1, 0, -1 };

int solution(vector<vector<int>> land, int height) {
    int N = land.size();

    // Step 1: 그룹핑 (BFS)
    vector<vector<int>> group(N, vector<int>(N, -1));
    int cur_group = 0;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(group[i][j] != -1) continue;

            group[i][j] = cur_group;
            queue<pair<int, int>> q;
            q.push({ i, j });

            while(!q.empty()) {
                auto [ci, cj] = q.front();
                q.pop();

                for(int d = 0; d < 4; d++) {
                    int ni = ci + dx[d], nj = cj + dy[d];
                    if(ni < 0 || nj < 0 || ni >= N || nj >= N || group[ni][nj] != -1) continue;
                    if(abs(land[ni][nj] - land[ci][cj]) <= height) {
                        group[ni][nj] = cur_group;
                        q.push({ ni, nj });
                    }
                }
            }
            cur_group++;
        }
    }

    if(cur_group <= 1) return 0;

    // Step 2: 그룹 간 최소 비용 엣지 찾기 (map 사용)
    map<pair<int, int>, int> min_cost;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            for(int d = 0; d < 4; d++) {
                int ni = i + dx[d], nj = j + dy[d];
                if(ni < 0 || nj < 0 || ni >= N || nj >= N || group[ni][nj] == group[i][j]) continue;

                int g1 = group[i][j], g2 = group[ni][nj];
                if(g1 > g2) swap(g1, g2); // 정규화

                int cost = abs(land[i][j] - land[ni][nj]);
                auto key = make_pair(g1, g2);

                if(min_cost.find(key) == min_cost.end() || cost < min_cost[key]) {
                    min_cost[key] = cost;
                }
            }
        }
    }

    // Step 3: 인접 리스트 구성
    vector<vector<pair<int, int>>> g(cur_group);
    for(auto &[key, cost] : min_cost) {
        int i = key.first, j = key.second;
        g[i].push_back({ j, cost });
        g[j].push_back({ i, cost });
    }

    // Step 4: Prim's MST
    vector<bool> visited(cur_group, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // 시작점 설정
    visited[0] = true;
    for(auto &edge : g[0]) {
        pq.push({ edge.second, edge.first }); // {cost, node}
    }

    int total_cost = 0;
    int connected = 1;

    while(!pq.empty() && connected < cur_group) {
        auto [cost, node] = pq.top();
        pq.pop();

        if(visited[node]) continue;

        visited[node] = true;
        total_cost += cost;
        connected++;

        // 새로 연결된 노드의 인접 엣지들을 추가
        for(auto &edge : g[node]) {
            if(!visited[edge.first]) {
                pq.push({ edge.second, edge.first }); // {cost, node}
            }
        }
    }

    return total_cost;
}