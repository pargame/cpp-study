//https://school.programmers.co.kr/learn/courses/30/lessons/49995?language=cpp
#include <string>
#include <vector>
#include<numeric>
#include<iostream>
//#include<format>

using namespace std;

int solution(vector<int> cookie) {
    int N = static_cast<int>(cookie.size());
    int total = accumulate(cookie.begin(), cookie.end(), 0), cur_total = total;
    int ans = 0;
    auto prev_it2 = cookie.begin();

    for(auto it1 = cookie.begin(); it1 < cookie.end() - 1; cur_total -= *it1, ++it1) {
        int cur_cur_total = cur_total;
        for(auto it2 = cookie.end() - 1; it1 < it2 && prev_it2 < it2; cur_cur_total -= *it2, --it2) {
            //cout << format("i: {}, j: {}, total: {}\n", it1 - cookie.begin(), it2 - cookie.begin(), cur_cur_total);

            int half_total = cur_cur_total / 2;
            if(half_total * 2 != cur_cur_total)
                continue;

            int cur_half = 0;
            for(auto p = it1; cur_half < half_total && p < it2; cur_half += *p, ++p);


            if(cur_half == half_total) {
                ans = ans < half_total ? half_total : ans;
                prev_it2 = it2;
                break;
            }
        }
    }

    return ans;
}

//int main() { cout << solution({ 1,1,2,3 }); }