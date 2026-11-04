//https://school.programmers.co.kr/learn/courses/30/lessons/1844
#include<vector>
#include<utility>
#include<queue>

using namespace std;

vector<pair<int,int>> dir={{1,0},{-1,0},{0,1},{0,-1}};

int solution(vector<vector<int> > maps)
{
    //init
    queue<pair<int,int>> locQ;
    locQ.push({0,0});
    queue<int> stepQ;
    stepQ.push(1);

    //BFS
    while(!locQ.empty()){
        pair<int,int> cur_loc=locQ.front();
        int cur_step=stepQ.front();
        locQ.pop();
        stepQ.pop();
        if(cur_loc.first==maps.size()-1 && cur_loc.second==maps[0].size()-1) return cur_step;

        for(auto [di,dj]:dir){
            int ni=cur_loc.first+di;
            int nj=cur_loc.second+dj;
            if(ni<0 || ni>=maps.size() || nj<0 || nj>=maps[0].size()||maps[ni][nj]==0) continue;
            locQ.push({ni,nj});
            stepQ.push(cur_step+1);
        }
    }
    return -1;
}