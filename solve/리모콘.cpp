//https://www.acmicpc.net/problem/1107
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<string>

using namespace std;

bool isPsb(const vector<int>& _lmts, int _n){
    if(_n < 0) return false; // 음수는 채널이 아니므로 불가능
    string str_n = to_string(_n);
    for(int cur : _lmts){ //각각의 제한 번호에 대해
        if(str_n.find(char(cur + '0')) != string::npos) // n에서 발견됐다면 불가능
            return false;
    }
    return true;  //모두 통과시 가능 번호
}

int main(){
    int tgt=0;cin>>tgt;  //목표 채널 번호
    if(tgt==100){  //100번 채널을 봐야 할 때, 더미 입력 후 출력-종료
        int _=0;cin>>_;
        for(size_t __=0;__<_;++__){
            int ___=0;cin>>___;
        }

        cout<<0;
        return 0;
    }

    int ans=abs(100-tgt);  //기본적으로 +/- 로 이동한 값 저장

    int lmt_n=0;cin>>lmt_n;  //제한 번호 개수
    if(lmt_n==10){  //모든 버튼이 불능일 때, 더미 입력 후 출력-종료
        for(size_t _=0;_<10;++_){
            int __=0;cin>>__;
        }

        cout<<ans;
        return 0;
    }

    //이후는 100번이 아니며, 최소 1개 제한되지 않은 번호가 있는 경우임
    vector<int> lmts;  //제한 번호 목록
    for(size_t _=0;_<lmt_n;++_){
        int __=0; cin>>__;
        lmts.push_back(__);
    }
    sort(lmts.begin(), lmts.end());

    // 목표 채널 자체를 직접 누를 수 있는지 먼저 확인
    if(isPsb(lmts, tgt)){
        ans = min(ans, (int)to_string(tgt).size());
    }

    int low_n = tgt-1;  //목표 아래 값 중 바로 번호 입력이 가능한 최대값
    while(low_n >= 0){
        if(isPsb(lmts, low_n)) break; // 찾음
        if(tgt - low_n > ans) { low_n = -1; break; } // 더 이상 유리할 리 없음
        --low_n;
    }

    if(low_n>=0){  //찾았다면
        int cnt=to_string(low_n).size()+tgt-low_n;  //이동하기 위한 횟수 계산
        ans=cnt<ans?cnt:ans;  //더 작은 횟수로 ans 업데이트
    } //못 찾았다면 할 작업 없음

    if(!(lmts.size()==9 && lmts[0]==1)){  //0만 가능한 경우가 아니면 위쪽도 탐색
        int up_n = tgt;  //목표 포함 위 값 중 바로 번호 입력이 가능한 최소값
        const int MAX_CH = 1000000; // 안전한 상한
        while(up_n <= MAX_CH){
            if(isPsb(lmts, up_n)){
                int cnt = to_string(up_n).size() + up_n - tgt;
                ans = cnt < ans ? cnt : ans;
                break;
            }
            // 비용이 현재 ans를 넘으면 더이상 볼 필요 없음
            if(to_string(up_n).size() + up_n - tgt > ans) break;
            ++up_n;
        }
    }

    cout<<ans;  //결과 출력-종료
    return 0;
}