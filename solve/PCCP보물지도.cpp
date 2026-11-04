//https://school.programmers.co.kr/learn/courses/15009/lessons/121690
// 제한사항
// 1 ≤ n, m ≤ 1,000
// 단, n * m이 3 이상인 경우만 입력으로 주어집니다.
// 1 ≤ hole의 길이 ≤ n * m - 2
// hole[i]는 [a, b]의 형태이며, (a, b) 칸에 함정이 존재한다는 의미이며, 1 ≤ a ≤ n, 1 ≤ b ≤ m을 만족합니다.
// 같은 함정에 대한 정보가 중복해서 들어있지 않습니다.
// (1, 1) 칸과 (n, m) 칸은 항상 함정이 없습니다.
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(int n, int m, vector<vector<int>> hole) {
    //dp[i].first: 신발 사용 이전 최적값
    //dp[i].second: 신발 사용 이후 최적값
    vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(m, { n * m, n * m }));
    for(vector<int> &h : hole) {
        dp[h[0] - 1][h[1] - 1] = { -1, -1 };
    }

    vector<pair<int, int>> dir{ {1, 0}, { -1,0 }, { 0,1 }, { 0,-1 } };

    dp[0][0] = { 0,n * m };
    queue<pair<int, int>> q;
    q.push({ 0,0 });
    while(!q.empty()) {
        int i = q.front().first, j = q.front().second;
        q.pop();

        //현재 미사용 dp값이 있다면
        if(dp[i][j].first != n * m) {
            //1칸: 미사용->미사용
            for(auto &[di, dj] : dir) {
                int ni = i + di, nj = j + dj;
                //범위 & 지뢰 체크
                if(ni < 0 || nj < 0 || n <= ni || m <= nj || dp[ni][nj].first == -1) continue;
                if(dp[i][j].first + 1 < dp[ni][nj].first) {
                    dp[ni][nj].first = dp[i][j].first + 1;
                    q.push({ ni,nj });
                }
            }
            //2칸: 미사용->사용
            for(auto &[di, dj] : dir) {
                int ni = i + 2 * di, nj = j + 2 * dj;
                //범위 & 지뢰 체크
                if(ni < 0 || nj < 0 || n <= ni || m <= nj || dp[ni][nj].first == -1) continue;
                if(dp[i][j].first + 1 < dp[ni][nj].second) {
                    dp[ni][nj].second = dp[i][j].first + 1;
                    q.push({ ni,nj });
                }
            }
        }
        //현재 사용 dp값이 있다면
        if(dp[i][j].second != n * m) {
            //1칸: 사용->사용
            for(auto &[di, dj] : dir) {
                int ni = i + di, nj = j + dj;
                //범위 & 지뢰 체크
                if(ni < 0 || nj < 0 || n <= ni || m <= nj || dp[ni][nj].first == -1) continue;
                if(dp[i][j].second + 1 < dp[ni][nj].second) {
                    dp[ni][nj].second = dp[i][j].second + 1;
                    q.push({ ni,nj });
                }
            }
        }
    }

    int ans = min(dp[n - 1][m - 1].first, dp[n - 1][m - 1].second);
    if(ans == n * m) return -1;
    return ans;
}