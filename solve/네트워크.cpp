//https://school.programmers.co.kr/learn/courses/30/lessons/43162?language=cpp
// 제한사항
// 컴퓨터의 개수 n은 1 이상 200 이하인 자연수입니다.
// 각 컴퓨터는 0부터 n-1인 정수로 표현합니다.
// i번 컴퓨터와 j번 컴퓨터가 연결되어 있으면 computers[i][j]를 1로 표현합니다.
// computer[i][i]는 항상 1입니다.
#include <vector>
#include <queue>

using namespace std;

int solution(int n, vector<vector<int>> computers) {
    vector<vector<int>> g(n, vector<int>());
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(computers[i][j] && i != j) {
                g[i].push_back(j);
            }
        }
    }  //  원소(벡터)=인접노드들    g=[[1],[0,2],[1]]
              // 인덱스=노드번호       0 - 1 - 2

    vector<bool> vst(n, false);  //[0:f, 1:f, 2:f]
    int ans = 0;
    for(int i = 0; i < n; ++i) {
        if(vst[i]) {
            continue;
        }
        ++ans;
        queue<int> q;
        q.push(i);
        while(!q.empty()) {
            int fr = q.front();
            q.pop();
            vst[fr] = true;
            for(int &c : g[fr]) {
                if(!vst[c]) {
                    q.push(c);
                }
            }
        }
    }

    return ans;
}