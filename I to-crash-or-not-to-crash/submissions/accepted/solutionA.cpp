#include <bits/stdc++.h>

using namespace std;

#define pii pair<int,int>

int main(){
    vector<string> lanes(3);
    pii robotaxi;
    for(int i=0;i<lanes.size();i++){
        cin>>lanes[i];
        for(int j=0;j<lanes[i].length();j++){
            if(lanes[i][j]=='='){
                robotaxi = make_pair(i,j);
            }
        }
    }
    for(int i=robotaxi.second+1; i<lanes[robotaxi.first].length();i++){
        if(lanes[robotaxi.first][i]!='.'){
            cout<<lanes[robotaxi.first][i]<<endl;
            return 0;
        }
    }
    cout<<"You shall pass!!!"<<endl;
    return 0;
}