#include <vector>
#include <string>
#include <queue>

using namespace std;

class Solver {
    struct Frame {
        int idx;
        int gap;
        Frame(int _idx, int _gap) :idx(_idx), gap(_gap) {}
    };

    string dec2bin(long long n) {
        if (n == 0) {
            return "";
        }
        return dec2bin(n / 2) + to_string(n % 2);
    }

    bool isPsb(string bin, int gap) {
        queue<Frame> q;
        q.push(Frame(bin.size() / 2, gap/2));
        while (!q.empty()) {
            Frame fr = q.front();
            q.pop();
            if (fr.gap == 0) {
                break;
            }

            int left = fr.idx - fr.gap;
            if (bin[fr.idx] == '0' && bin[left] == '1') {
                return false;
            }
            int right = fr.idx + fr.gap;
            if (bin[fr.idx] == '0' && bin[right] == '1') {
                return false;
            }
            q.push(Frame(left, fr.gap/2));
            q.push(Frame(right, fr.gap/2));
        }
        return true;
    }
   
    int Solve(long long n) {
        string bin = dec2bin(n);
        int i = 2;
        for (;; i *= 2) {
            if (bin.size() < i) {
                bin = string(i - 1 - bin.size(), '0') + bin;
                break;
            }
        }
        if (isPsb(bin, i/2) ){
            return 1;
        }
        else {
            return 0;
        }
    }

public:
    vector<int> ans;
    Solver(vector<long long>& nums) {
        for (auto n : nums) {
            ans.push_back(Solve(n));
        }
    }
    Solver() = default;
};

vector<int> solution(vector<long long> numbers) {
    return Solver(numbers).ans;
}