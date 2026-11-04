// https://school.programmers.co.kr/learn/courses/30/lessons/43164
// 제한사항
// 모든 공항은 알파벳 대문자 3글자로 이루어집니다.
// 주어진 공항 수는 3개 이상 10,000개 이하입니다.
// tickets의 각 행 [a, b]는 a 공항에서 b 공항으로 가는 항공권이 있다는 의미입니다.
// 주어진 항공권은 모두 사용해야 합니다.
// 만일 가능한 경로가 2개 이상일 경우 알파벳 순서가 앞서는 경로를 return 합니다.
// 모든 도시를 방문할 수 없는 경우는 주어지지 않습니다.
#include <string>
#include <vector>
#include <map>  // map = pair<first, second> 배열
#include <algorithm>
#include <stack>

using namespace std;

vector<string> solution(vector<vector<string>> tickets) {
    map<string, vector<string>> m;

    for(vector<string> &t : tickets) {
        m[t[0]].push_back(t[1]);
    }
    for(auto &[s, v] : m) {
        sort(v.begin(), v.end());
    }

    vector<string> st;
    vector<int> n(1);
    st.push_back("ICN");
    while(true) {
        if(st.size() == tickets.size() + 1) {
            return st;
        }
        else if(m[st.back()].empty() || n.back() == m[st.back()].size()) {
            n.pop_back();
            string b = st.back();
            st.pop_back();
            m[st.back()].insert(m[st.back()].begin() + n.back() - 1, b);
        }
        else {
            string next = m[st.back()][n.back()];
            m[st.back()].erase(m[st.back()].begin() + n.back());
            st.push_back(next);
            ++n.back();
            n.push_back(0);
        }
    }
}