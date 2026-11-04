// https://school.programmers.co.kr/learn/courses/30/lessons/42883?language=cpp
// 제한 조건
// number는 2자리 이상, 1,000,000자리 이하인 숫자입니다.
// k는 1 이상 number의 자릿수 미만인 자연수입니다.

#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string solution(string number, int k) {
    auto st = number.begin();
    string ans = "";
    int n = number.size() - k;
    for(auto end = number.end() - n + 1; ans.size() < n; ++end) {
        auto fnd = max_element(st, end);
        st = fnd + 1;
        ans.push_back(*fnd);
    }

    vector<int> v1{ 1,2,3,4 };
    vector<int> v2(v1.begin(), v1.end());
    return ans;
}