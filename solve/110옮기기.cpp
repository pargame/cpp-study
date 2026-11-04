#include <string>
#include <vector>
#include <stack>
using namespace std;

void Solve(string& s, string& r) {
    string tmp;
    int cnt = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (i < s.size() - 2 && s.substr(i, 3) == "110") {
            i += 2;
            ++cnt;
            continue;
        }
        if (s[i] == '1') {
            tmp += "1";
        }
        else {
            tmp += "0";
            if (tmp.size() > 2 && tmp.substr(tmp.size() - 3, 3) == "110") {
                tmp.erase(tmp.size() - 3, 3);
                ++cnt;
            }
            else {
                r += tmp;
                tmp.clear();
            }
        }
    }

    for (int i = 0; i < cnt; ++i) {
        r += "110";
    }
    r += tmp;
}

vector<string> solution(vector<string> s) {
    vector<string> ret(s.size());
    for (int i=0;i<ret.size();++i){
        ret[i].reserve(s[i].size());  //메모리 재할당 방지
        Solve(s[i], ret[i]);
    }
    return ret;
}