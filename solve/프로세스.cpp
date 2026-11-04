//https://school.programmers.co.kr/learn/courses/30/lessons/42587
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <utility>
#include <string>

using namespace std;

int solution(vector<int> priorities, int location) {
    //(0,2) (1,1) (2,3) (3,2)       2       1
    vector<pair<int, int>> v;
    for(size_t i=0;i<priorities.size();i++){
        v.push_back(make_pair(i,priorities[i]));
    }

    int order=1;
    while(!v.empty()){
        pair<int,int> cur=v.front();
        v.erase(v.begin());
        if(cur.second<(*max_element(v.begin(),v.end(),[](const pair<int,int> &a, const pair<int,int> &b){
            return a.second < b.second;
        })).second){
            v.push_back(cur);
        }else{
            if(cur.first==location){
                return order;
            }
            else{
                order++;
            }
        }
    }
}
