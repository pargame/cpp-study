#include <vector>

using namespace std;

class Solver {
    struct Node {
        int v;
        int left_idx;
        int right_idx;
        Node(int _v, int _li, int _ri) :v(_v), left_idx(_li), right_idx(_ri) {}
    };
    vector<Node> arr;
    bool isHigh(int m) {
        return arr[arr[m].left_idx].v < arr[m].v && arr[m].v > arr[arr[m].right_idx].v;
    }
    void Solve() {
        int cnt = 0;
        for (int i = 1; i < arr.size() - 1; ++i) {
            int j = i;
            while (isHigh(j)) {
                ++cnt;
                arr[arr[j].right_idx].left_idx = arr[j].left_idx;
                arr[arr[j].left_idx].right_idx = arr[j].right_idx;
                j = arr[j].left_idx;
                if (j == 0) {
                    break;
                }
            }
        }
        ans -= cnt;
    }
    
public:
    int ans = 0;
    Solver(vector<int>& a) {
        ans = a.size();
        for (int i = 0; i < a.size(); ++i) {
            arr.push_back(Node(a[i], i - 1, i + 1));
        }
        Solve();
    }
};

int solution(vector<int> a) {
    return Solver(a).ans;
}