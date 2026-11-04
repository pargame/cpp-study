// https://school.programmers.co.kr/learn/courses/30/lessons/49189
// 제한사항
// 노드의 개수 n은 2 이상 20,000 이하입니다.
// 간선은 양방향이며 총 1개 이상 50,000개 이하의 간선이 있습니다.
// vertex 배열 각 행 [a, b]는 a번 노드와 b번 노드 사이에 간선이 있다는 의미입니다.

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int solution(int n, vector<vector<int>> edge) {
    vector<vector<int>> g(n + 1);
    for(auto e : edge) {
        g[e[0]].push_back(e[1]);
        g[e[1]].push_back(e[0]);
    }

    struct Frame {
        int i;
        int depth;
        Frame(int _i, int _depth) :i(_i), depth(_depth) {}
    };

    queue<Frame> q;
    q.push(Frame(1, 0));

    vector<bool> vst(n + 1);
    vector<int> dp(n);

    vst[1] = true;
    while(!q.empty()) {
        Frame fr = q.front();
        q.pop();

        ++dp[fr.depth];

        for(int adc : g[fr.i]) {
            if(!vst[adc]) {
                vst[adc] = true;
                q.push(Frame(adc, fr.depth + 1));
            }
        }
    }

    for(int i = n - 1; i > 0; --i) {
        if(dp[i] != 0) {
            return dp[i];
        }
    }

}