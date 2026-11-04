//https://www.acmicpc.net/problem/3085

#include<iostream>
#include<vector>
#include<string>
#include<utility>

using namespace std;

vector<pair<int,int>> dir={{1,0},{-1,0},{0,1},{0,-1}};

int CountRow(vector<string>const&board,int row){
    int max_cnt=1;
    char prev_color=board[row][0];
    int cur_cnt=1;
    for(size_t i=1;i<board.size();++i){
        char cur_color=board[row][i];
        if(cur_color==prev_color){
            ++cur_cnt;
            max_cnt=cur_cnt>max_cnt?cur_cnt:max_cnt;
        }
        else{
            cur_cnt=1;
            prev_color=cur_color;
        }
    }
    return max_cnt;
}

int CountCol(vector<string>const&board,int col){
    int max_cnt=1;
    char prev_color=board[0][col];
    int cur_cnt=1;
    for(size_t j=1;j<board.size();++j){
        char cur_color=board[j][col];
        if(cur_color==prev_color){
            ++cur_cnt;
            max_cnt=cur_cnt>max_cnt?cur_cnt:max_cnt;
        }
        else{
            cur_cnt=1;
            prev_color=cur_color;
        }
    }
    return max_cnt;
}

int main(){
    int n;
    cin>>n;
    vector<string> board(n);
    for(string &s:board) cin>>s;

    int ans=0;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            for(pair<int,int> const &d:dir){
                int ni = i + d.first;
                int nj = j + d.second;
                if(ni<0 || ni>=n || nj<0 || nj>=n) continue;
                swap(board[i][j],board[ni][nj]);
                int cnt=0;
                cnt=CountRow(board,i);
                if(ans<cnt) ans=cnt;
                cnt=CountCol(board,j);
                if(ans<cnt) ans=cnt;
                swap(board[i][j],board[ni][nj]);
            }
        }
    }
    cout<<ans;

    return 0;
}