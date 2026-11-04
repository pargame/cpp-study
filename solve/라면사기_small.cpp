// https://www.acmicpc.net/problem/18185
#include <iostream>
#include <vector>

using namespace std;

int main() {
    size_t N = 0;
    cin >> N;
    vector<int> A(N);
    for (int &_ : A)
        cin >> _;

    int cost = 0;

    for (size_t i = 0; i < N;) {
        if (i < N - 2 && A[i] > 0 && A[i + 1] > 0 && A[i + 2] > 0 &&
            A[i] <= A[i + 1] && A[i + 1] <= A[i + 2])
            --A[i], --A[i + 1], --A[i + 2], cost += 7;
        else if (i < N - 1 && A[i] > 0 && A[i + 1] > 0 && A[i] <= A[i + 1])
            --A[i], --A[i + 1], cost += 5;
        else if (A[i] > 0)
            --A[i], cost += 3;
        else
            ++i;
    }

    cout << cost;

    return 0;
}