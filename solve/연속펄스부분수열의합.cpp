#include <vector>
#include <algorithm>

using namespace std;

long long solution(vector<int> seq) {
    long long ans = 0;
    long long cur1 = 0, cur2 = 0;

    for (int i = 0; i < seq.size(); ++i) {
        long long v1 = seq[i] * (i % 2 == 0 ? 1 : -1);
        long long v2 = seq[i] * (i % 2 == 0 ? -1 : 1);

        cur1 = max(v1, cur1 + v1);
        cur2 = max(v2, cur2 + v2);

        ans = max({ ans, cur1, cur2 });
    }
    return ans;
}