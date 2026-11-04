//https://school.programmers.co.kr/learn/courses/15008/lessons/121685
// 제한사항
// 1 ≤ queries의 길이(쿼리의 개수) ≤ 5
// queries의 원소는 [n, p] 형태입니다.
// 1 ≤ n ≤ 16
// 1 ≤ p ≤ 4n-1
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Frame {
    int n, p;
    Frame(int _n, int _p) :n(_n), p(_p) {}
};

vector<string> solution(vector<vector<int>> queries) {
    vector<string> ans;

    for(vector<int> &q : queries) {
        int n = q[0], p = q[1];

        stack<Frame> st;
        st.push(Frame(n, p));
        int prev_v = 0; //1-RR      2-Rr    3-rr
        while(!st.empty()) {
            if(st.top().n == 1) {
                prev_v = 2;
                st.pop();
            }
            else if(prev_v != 0) {
                switch(prev_v) {
                case 1:
                    prev_v = 1;
                    break;
                case 2:
                    switch(st.top().p % 4) {
                    case 1:
                        prev_v = 1;
                        break;
                    case 2:
                    case 3:
                        prev_v = 2;
                        break;
                    case 0:
                        prev_v = 3;
                        break;
                    }
                    break;
                case 3:
                    prev_v = 3;
                    break;
                }
                st.pop();
            }
            else {
                st.push(Frame(st.top().n - 1, (st.top().p + 3) / 4));
            }
        }
        ans.push_back(prev_v == 1 ? "RR" : prev_v == 2 ? "Rr" : "rr");
    }

    return ans;
}