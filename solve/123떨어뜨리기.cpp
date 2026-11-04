#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <iostream>

using namespace std;

class Solver {

    vector<int>& target;
    int n;
    vector<vector<int>> G;  //{prnt-idx : childs-G[idx]}
    vector<int> ni;  //which child idx of G's node should go. But initially set by "target's idx not elem 0".
    vector<int> vst;  //{idx of leaf, it's visit count}
    queue<int> Q; //leaf visit q
    int p;  //just inserted in leaf idx

    bool isEnough() {
        for (int i = 0; i < n;++i) {
            if (target[i] == 0) {
                continue;
            }

            if (vst[i]*3 < target[i]) {
                return false;
            }
        }
        return true;
    }

    bool isOverCard() {
        if (target[p] < vst[p]) {
            return true;
        }
        return false;
    }

    bool isLeaf(int p){
        if (G[p].size() == 0) {
            return true;
        }
        return false;
    }

    void PutCard() {
        int p = 0;
        while (!isLeaf(p)) {
            int np = G[p][ni[p]];
            ++ni[p];
            if (ni[p] == G[p].size()) {
                ni[p] = 0;
            }
            p = np;
        }
        ++vst[p];
        Q.push(p);
        this->p = p;
    }

    bool isOK(int idx, int num) {
        if ((vst[idx] - 1) * 3 + num >= target[idx]) {
            return true;
        }
        return false;
    }

    void SetAns() {
        while (!Q.empty()) {
            int fr = Q.front();
            Q.pop();
            for (int i = 1; i <= 3; ++i) {
                if (isOK(fr,i)) {
                    ans.push_back(i);
                    --vst[fr];
                    target[fr] -= i;
                    break;
                }
            }
        }
    }

    void Solve() {
        while (!isEnough()) {
            PutCard();
            if (isOverCard()) {
                ans.push_back(-1);
                return;
            }
        }

        SetAns();
    }
    
public:
    vector<int> ans;
    Solver(vector<vector<int>> &edges, vector<int> &_target): target(_target){
        n = target.size();
        G.assign(n, vector<int>());
        ni.assign(n, 0);
        vst.assign(n, 0);

        for (auto &e : edges) {
            G[e[0] - 1].push_back(e[1] - 1);
        }
        for (auto &adjc : G) {
            sort(adjc.begin(), adjc.end());
        }

        Solve();
    }
};

vector<int> solution(vector<vector<int>> edges, vector<int> target) {
    return Solver(edges, target).ans;
}