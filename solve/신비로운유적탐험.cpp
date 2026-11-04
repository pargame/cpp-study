//https://school.programmers.co.kr/learn/courses/30/lessons/1834
// [제한 조건]
// 1 <= n1, n2 <= 100
// 노드 번호는 각각 1부터 n1, n2까지의 값이 사용되며, 각 트리의 1번 노드가 루트이다.
// 입력되는 데이터는 항상 올바른 트리임이 보장된다.

#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;

void MakeTree(vector<vector<int>> &t, vector<vector<int>>const &g, int n) {
    for(vector<int>const &node : g) {
        t[node[0]].push_back(node[1]);
        t[node[1]].push_back(node[0]);
    }
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int top = q.front();
        q.pop();
        for(int c : t[top]) {
            t[c].erase(find(t[c].begin(), t[c].end(), top));
            q.push(c);
        }
    }
}

void SetDP(int i1, int i2
    , vector<vector<int>>const &t1, vector<vector<int>>const &t2
    , vector<vector<int>> &dp) {

    if(t1[i1].empty() || t2[i2].empty()) return;

    struct Frame {
        int i;
        int cnt = 0;
        Frame(int _i) : i(_i) {}
    };

    int max_v = 1;

    //n<m
    bool bswap = t1[i1].size() > t2[i2].size() ? true : false;
    int n = bswap ? t2[i2].size() : t1[i1].size();
    int m = bswap ? t1[i1].size() : t2[i2].size();

    vector<Frame> st;
    for(int i = 0; i < m; ++i) {
        st.push_back(Frame(i));
        vector<bool>vst(m);

        while(!st.empty()) {
            vst[st.back().i] = true;
            if(st.size() == n) {
                int sum = 0;
                for(int j = 0; j < n; ++j) {
                    int ii = bswap ? t1[i1][st[j].i] : t1[i1][j];
                    int jj = bswap ? t2[i2][j] : t2[i2][st[j].i];
                    sum += dp[ii][jj];
                }
                max_v = max(max_v, sum);
                vst[st.back().i] = false;
                st.pop_back();
                continue;
            }
            int next = -1;
            for(int j = 0, cnt = 0; j < m; ++j) {
                if(!vst[j]) {
                    if(cnt == st.back().cnt) {
                        next = j;
                        break;
                    }
                    ++cnt;
                }
            }
            if(next != -1) {
                ++st.back().cnt;
                st.push_back(Frame(next));
            }
            else {
                vst[st.back().i] = false;
                st.pop_back();
            }
        }
    }

    dp[i1][i2] += max_v;
}

int GetAns(vector<vector<int>>const &t1, vector<vector<int>>const &t2) {
    struct Frame {
        int i1, i2;
        int j1 = 0, j2 = 0;
        Frame(int _i1, int _i2) :i1(_i1), i2(_i2) {}
    };

    vector<vector<int>> dp(t1.size() + 1, vector<int>(t2.size() + 1, 1)); //초기값 1
    stack<Frame> st;
    st.push(Frame(1, 1));
    while(!st.empty()) {
        if(st.top().j1 < t1[st.top().i1].size() && st.top().j2 < t2[st.top().i2].size()) {
            st.push(Frame(st.top().j1, st.top().j2++));
        }
        else if(st.top().j1 < t1[st.top().i1].size()) {
            ++st.top().j1;
            st.top().j2 = 0;
        }
        else {
            SetDP(st.top().i1, st.top().i2, t1, t2, dp);
            st.pop();
        }
    }
    return dp[1][1];
}

int solution(int n1, vector<vector<int>> g1, int n2, vector<vector<int>> g2) {
    vector<vector<int>> t1(n1 + 1, vector<int>()), t2(n2 + 1, vector<int>());
    MakeTree(t1, g1, n1);
    MakeTree(t2, g2, n2);

    return GetAns(t1, t2);
}